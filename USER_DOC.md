
# USER_DOC — Documentation Utilisateur

Ce document explique comment un utilisateur ou administrateur peut utiliser la stack Inception, accéder aux services, gérer les identifiants, et vérifier que tout fonctionne.

---

## 1️⃣ Services fournis

La stack Inception fournit :
- **Un serveur Nginx** configuré en HTTPS.
- **Un site WordPress entièrement fonctionnel**.
- **Une base de données MariaDB persistante**.
- **Une isolation complète via Docker** (réseau, filesystem, process).

### ⭐ Services bonus

Selon la configuration, tu peux aussi avoir :

- **Redis** : cache WordPress (transparent pour l’utilisateur ; utile pour les performances).
- **Adminer** : panneau web pour gérer MariaDB (tables, requêtes SQL, export).
- **FTP** : accès FTP pour déposer/récupérer des fichiers.
- **Backup** : sauvegardes automatiques de la base et des fichiers WordPress.
- **Site statique (CV)** : page statique servie par Nginx (ex. `/cv`).

> Si un service bonus n’est pas présent dans `docker ps`, il n’est simplement pas activé dans le `docker-compose.yml`.

---

## 2️⃣ Démarrer / arrêter le projet

### ▶️ Démarrer
```bash
make
```
ou
```bash
make up
```

### ⏹️ Arrêter
```bash
make down
```

### ⏹️ Arrêter, effacer les volumes et les dossier locaux
```bash
make clean
```

### ⏹️ Arrêter, effacer les volumes, les dossier locaux et les images
```bash
make fclean
```

### 🔄 Réinitialiser
```bash
make re
```

---

## 3️⃣ Accès au site & à l’interface admin
### 🗄️ Adminer (base de données)

Si le service **Adminer** est activé, il est accessible via l’URL prévue par ta conf Nginx, par exemple :

- `https://<DOMAIN_NAME>/adminer` (recommandé : derrière Nginx)

Connexion typique :
- **Système** : MariaDB / MySQL  
- **Serveur** : `mariadb` (nom du service Docker)  
- **Utilisateur** : `MYSQL_USER` (ou un autre utilisateur DB)
- **Mot de passe** : `mysql_user_password.txt` (ou mot de passe correspondant)
- **Base** : `MYSQL_DATABASE`

> Si Redis est activé pour WordPress, Adminer n’est pas censé “passer par Redis”.  
> Par contre, les modifications DB via Adminer peuvent ne pas sembler visibles côté site **si un cache WordPress est actif** : vide le cache Redis / plugin WordPress si nécessaire.

### 📁 FTP (optionnel)

Si le serveur **FTP** est activé, tu peux t’y connecter avec un client type FileZilla :

- **Hôte** : `<DOMAIN_NAME>` (ou l’IP de la VM)
- **Port** : (ex. `21` + plage passive, selon le `docker-compose.yml`)
- **Utilisateur / mot de passe** : fournis via secrets/variables (ex. `FTP_USER`, `ftp_password`)
- **Répertoire** : monté sur `/var/www/html` (WordPress) ou un sous-dossier

### 🌍 Site principal :
https://login.42.fr

> ⚠️ Assurez-vous d'avoir dans `/etc/hosts` :
```
127.0.0.1  login.42.fr
127.0.0.1  cv.42.fr
```

### 🔐 Interface Administrateur WordPress :
https://login.42.fr/wp-admin

---

## 4️⃣ Gestion des identifiants

- Identifiants stockés dans `.env`,
- Mots de passe stockés individuellement dans des fichiers `.txt` du dossier `secrets`,
- Création automatique du compte mariadb au démarrage du conteneur mariadb,
- Création automatique du compte admin + utilisateur secondaire au démarrage du conteneur WordPress.

contenu du `.env`:
```
DOMAIN_NAME=login.42.fr

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

contenu du dossier `secrets`;
```
inception/
├─ secrets/
│    ├─ credential.txt
│    ├─ ftp_password.txt
│    ├─ mysql_root_password.txt
│    ├─ mysql_user_password.txt
│    ├─ wp_admin_password.txt
│    └─ wp_user_password.txt
```
---

## 5️⃣ Vérifier que tout fonctionne

### Vérifier les conteneurs
```bash
make ps
```
ou
```bash
docker ps
```

### Vérifier l’état du service MariaDB
```bash
docker logs mariadb
```

### Vérifier le service WordPress/PHP-FPM
```bash
docker logs wordpress
```

### Vérifier Nginx
```bash
docker logs nginx
```

---

## 6️⃣ Où se trouvent les données ?

Les données persistent ici :
```
~/data/mariadb
~/data/wordpress
~/data/backups
```

### 🧰 Sauvegardes (si le service `backup` est activé)

En général, le service **backup** écrit des archives/dumps dans un dossier persistant (ex. `~/data/backups/`) :

- dump SQL MariaDB : `db_YYYYmmdd_HHMMSS.sql` (ou `.sql.gz`)
- archive WordPress : `wp_YYYYmmdd_HHMMSS.tar.gz`

Commandes utiles :
- Lister les backups : `ls -la ~/data/backups`
- Restaurer MariaDB : `mariadb -u root -p < dump.sql` (dans le conteneur `mariadb`)
- Restaurer WordPress : extraire l’archive dans le volume WordPress (avec les bons droits)

### 🧾 Site statique (CV)

Avec un service “site statique” (ou une route Nginx dédiée), le CV peut être accessible par :
- `https://<DOMAIN_NAME>/cv`
- `https://cv.42.fr`

---

## ✔️ FIN  
Votre environnement est prêt à être utilisé !
