
# DEV_DOC — Documentation Développeur

Ce document explique comment un développeur peut configurer, builder, lancer et administrer la stack depuis zéro.

---

## 1️⃣ Prérequis

- Debian / Linux / macOS
- Docker >= 20.10
- Docker Compose >= v1.29.2
- Make
- ftp
- Le fichier `.env` correctement rempli :
```
DOMAIN_NAME=login.42.fr
#WP_PORT=XXXX en cas de redirection du port https sinon ne pas definir

# MYSQL
MYSQL_DATABASE= ...
MYSQL_USER= ...

# WORDPRESS ADMIN
WP_ADMIN= ...
WP_ADMIN_EMAIL= ...

# WORDPRESS USER
WP_USER= ...
WP_USER_EMAIL= ...

# FTP USER
FTP_USER= ...
```
- Un mot de passe sans /n par fichier du dossier `secrets`:
```
inception/
├─ secrets/
│    ├─ ftp_password.txt
│    ├─ mysql_root_password.txt
│    ├─ mysql_user_password.txt
│    ├─ wp_admin_password.txt
│    └─ wp_user_password.txt
```

---

## 2️⃣ Mise en place de l’environnement depuis zéro

### Clone du dépôt :
```bash
git clone <repo>
cd inception
```

### Création des dossiers de données :
```bash
mkdir -p ~/data/mariadb ~/data/wordpress ~/data/backups
chmod -R 777 ~/data
```

---

## 3️⃣ Construction et lancement via Makefile

### 🔨 Build & run
```bash
make
```

### 🚫 Stop
```bash
make down
```

### 🧹 Clean (volumes + data)
```bash
make clean
```

### 🔥 Full clean (images + volumes + data)
```bash
make fclean
```

---

## 4️⃣ Commandes utiles Docker

### Liste des conteneurs :
```bash
docker ps -a
```

### Entrer dans un conteneur :
```bash
docker exec -it wordpress bash
```

### Supprimer tous les conteneurs :
```bash
docker rm -f $(docker ps -aq)
```

### Construire manuellement :
```bash
docker-compose build
```

---

## 5️⃣ Localisation des données persistantes

| Service | Chemin |
|---------|--------|
| MariaDB | `~/data/mariadb` |
| WordPress | `~/data/wordpress` |
| backup | `~/data/backups` |

Ces dossiers ne sont jamais détruits sauf lors d’un :
```bash
make clean
```
ou
```bash
make fclean
```
Ils sont persistants car en dehors des conteneurs docker dans la VM. Ils sont liés (bind) aux volumes des conteneurs.

---

## 6️⃣ Structure des fichiers Docker

```
srcs/
├─ .env
├─ docker-compose.yml
└─ requirements/
    ├─ bonus/
    │   ├─ adminer
    │	│    └─ Dockerfile
    │   ├─ backup
    │   │   ├─ Dockerfile
    │   │   └─ tools/
    │   │       ├─ backup.sh
    │   │       ├─ backup-cron
    │   │       ├─ entrypoint.sh
    │   │       └─ restore.sh
    │   ├─ cv
    │   │   ├─ Dockerfile
    │   │   │   ├─ conf/
    │   │   │    └─ default.conf
    │   │   └─ site/
    │   │       ├─ index.html
    │   │       └─ assets/
    │   │           ├─ app.js
    │   │           └─ style.css
    │   ├─ ftp
    │   │   ├─ Dockerfile
    │   │   ├─ conf/
    │   │   |   └─ vsftpd.cnf
    │   │   └─ tools/
    │   │       └─ entrypoint.sh
    │   └─ redis
    │       └─ Dockerfile
    ├─ mariadb/
    │   ├─ Dockerfile
    │   ├─ conf/
    │   │   └─ 50-server.cnf
    │   └─ tools/
    │       └─ entrypoint.sh
    ├─ nginx/
    │   ├─ Dockerfile
    │   ├─ conf/
    │   │   └─ nginx.conf
    │   └─ tools/
    │       └─ entrypoint.sh
    └─ wordpress/
        ├─ Dockerfile
        └─ tools/
            └─ entrypoint.sh
```

---

## ⭐ Bonus — Implémentation des services supplémentaires

Les bonus sont généralement ajoutés comme **services Docker Compose** supplémentaires, avec :
- un `Dockerfile` minimal (si nécessaire),
- un `entrypoint.sh` (si configuration/initialisation),
- des **volumes** pour la persistance (si données),
- des **secrets** pour éviter les mots de passe en clair.

### 1) Redis (cache WordPress)

**Objectif :** fournir un cache d’objets à WordPress.

- Service `redis` basé sur `redis:alpine` ou Debian + `redis-server`.
- Exposer **uniquement** en interne (pas de port publié).
- Dans WordPress :
  - installer/activer un plugin “Redis Object Cache” (ou équivalent),
  - pointer vers `redis` (nom du service Docker) sur le port `6379`.

Il est accessible dans la page administration de wordpress pour notamment:
- activation/desactivation,
- effacer la cache (cache flush utile si modification de la base via adminer)

### 2) Adminer (DB GUI)

**Objectif :** administrer MariaDB via navigateur.

- Service `adminer` basé sur `adminer:latest` (ou PHP + Adminer).
- Recommandation : **ne pas exposer** directement `9001` et le mettre derrière Nginx :
  - route `/adminer` vers `adminer:9001`.

⚠️ Avec Redis actif, les modifications DB via Adminer peuvent ne pas être visibles immédiatement sur le site : prévoir un mécanisme de **flush cache** (plugin WP / `redis-cli FLUSHALL` en dev).

### 3) FTP Server

**Objectif :** transfert de fichiers (optionnel).

- Service `ftp` (ex. vsftpd ou pure-ftpd).
- Points sensibles :
  - mode **passif** (plage de ports) + publication des ports,
  - répertoire “chroot” (ex. `/var/www/html`) monté sur le volume WordPress,
  - identifiants en **secrets** (`FTP_USER`, `ftp_password`).

Se connecter depuis le dossier ou des fichiers a échanger sont présent avec:
- `ftp <FTP_USER>@127.0.0.1` (recommandé),
- `ftp localhost`.

Une fois connecté un certain nombre de commandes bash sont disponibles, ainsi que:
- `get <NOM_FICHIER>` pour récupérer un fichier dans le dossier courant bash,
- `put <NOM_FICHIER>` pour importer un fichier depuis le dossier courant bash,
- `passive` pour basculer de mode actif ou mode passif et vice versa.

⚠️ Après echange de fichiers il faut vérifier que les droits sont corrects.

### 4) Backup (MariaDB + WordPress)

**Objectif :** sauvegardes automatisées.

- Service `backup` (Debian minimal + `cron`, `tar`, `mariadb-client`).
- Sortie des backups dans un dossier persistant (`~/data/backups` bind-mount).
- Stratégie typique :
  - `mariadb-dump` / `mysqldump` pour la base, 
  - `tar.gz` du volume WordPress,
  - rotation (garder 7 derniers jours).

La version de base est règlée sur backup toutes les 5 minutes pour les besoins de correction. 
Le règlage peut se faire par modification du fichier ~/inception/srcs/requirements/bonus/backup/tools/backup-cron avant construction des conteneurs.

Dans le conteneur, un script `restore.sh' peut être utilisé avec le timestamp de la version visée
Il convient de stopper les conteneurs wordpress et nginx avant de restaurer puis les rétablir:
- **stopper:** `docker-compose -f srcs/docker-compose.yml stop wordpress nginx` ou `docker stop wordpress nginx`,
- **restaurer:** `docker exec backup /usr/local/bin/./restore.sh YYYYmmdd_HHMMSS`
- **redémarrer:**`docker-compose -f srcs/docker-compose.yml start wordpress nginx` ou `docker start wordpress nginx`

Test d'exécution de cron et accès aux logs:
```bash
docker exec -it backup sh -lc 'ps aux | grep -E "[c]ron"'
docker exec -it backup sh -lc 'ls -l /var/log/backup.log 2>/dev/null || true; tail -n 50 /var/log/backup.log 2>/dev/null || true'
```

### 5) Site statique (CV)

**Objectif :** servir un dossier statique (HTML/CSS/JS) via Nginx.

Deux approches :
- **Dans Nginx existant** : copier le dossier `cv/` dans l’image Nginx et ajouter une location `/cv`.
- **Service séparé** : un conteneur “static” (nginx:alpine) qui sert le CV, reverse-proxy par Nginx principal.

---

## 🔐 Secrets vs variables d’environnement (rappel pratique)

- **Secrets** : mots de passe, clés privées, tokens (ex. DB password, root password, FTP password).
  - montés dans le conteneur sous `/run/secrets/<nom_du_secret>`
  - lus par les entrypoints (`cat /run/secrets/...`).
- **Variables d’environnement (.env)** : valeurs non sensibles et paramètres (ex. noms de base, hostnames, ports, domaines).
  - attention : `.env` est facilement “leaké” si commité.

### Exemple d’utilisation (entrypoint)

```sh
DB_PASS="$(cat /run/secrets/mysql_user_password)"
DB_ROOT_PASS="$(cat /run/secrets/mysql_root_password)"
```

Puis utiliser `$DB_PASS` dans les commandes (SQL, clients, etc.).

## ✔️ FIN  
Votre environnement de développement est prêt !
