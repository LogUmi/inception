
*Ce projet a été créé dans le cadre du cursus 42 par lgerard.*

# Inception — README

## 📝 Description
Inception est un projet du cursus 42 visant à découvrir, comprendre et manipuler l’écosystème Docker.  
L’objectif est de mettre en place une stack WordPress complète fonctionnant dans des conteneurs isolés — sans utiliser d’images préconstruites — tout en apprenant les bonnes pratiques de virtualisation, de sécurité et d’organisation d’infrastructure.

La stack finale doit comporter au minimum :
- Un conteneur **Nginx** configuré en HTTPS (certificat autosigné).
- Un conteneur **WordPress + PHP-FPM**.
- Un conteneur **MariaDB**, avec persistance des données.
- Un système de gestion des volumes, secrets, variables d’environnement, et réseau Docker.
- Un Makefile capable de builder, lancer et nettoyer l’ensemble.

---

## 🚀 Instructions

### 🔧 Compilation / Installation
```bash
make        # construit et lance la stack en mode détaché
make up     # construit et lance la stack en mode détaché
make down   # stoppe et supprime les conteneurs
make clean  # supprime volumes + dossiers data
make fclean # supprime images + volumes + data
make re     # relance tout depuis zéro
make ps     # affiche les dockers en service
make logs   # active le mode log
```

### 🌍 Accès au site
- URL principale : **https://lgerard.42.fr**  
- Le fichier `/etc/hosts` doit rediriger ce domaine vers `127.0.0.1`.

### 📌 Structure technique
```
inception/
 ├─ Makefile
 ├─ README.md
 ├─ USER_DOC.md
 ├─ DEV_DOC.md
 ├─ secrets/
 └─ srcs/
      ├─ docker-compose.yml
      └─ requirements/
           ├─ bonus/
           │    ├─ adminer
           │    ├─ backup
           │    ├─ cv
           │    ├─ ftp
           │    └─ redis
           ├─ mariadb/
           ├─ nginx/
           └─ wordpress/
```

---

## ⭐ Bonus (services additionnels)

Ce dépôt inclut des **services bonus** (optionnels) pour enrichir la stack :

- **Redis** : cache d’objets pour WordPress (accélération et réduction des requêtes DB).
- **Adminer** : interface web d’administration de la base MariaDB.
- **FTP** : serveur FTP pour déposer/récupérer des fichiers (ex. médias WordPress) de façon contrôlée.
- **Backup** : service dédié pour **sauvegarder** automatiquement MariaDB et les fichiers WordPress (tar + dump SQL).
- **Site statique (CV)** : un petit site statique (HTML/CSS) servi par Nginx (ex. `/cv`).

> Le périmètre exact (ports, URL, chemins) dépend de `docker-compose.yml` et de `nginx.conf`.

## 🧠 Project Description — Concepts et Choix Techniques

### 💻 Debian vs alpine
| VM debian | VM alpine |
|-----------|-----------|
| C’est la plus stable et la plus documentée | Ultra légère (~130 Mo) |
| Base solide pour apprendre le comportement d’un vrai serveur | Démarre très vite |
| Compatible directement avec Docker | Beaucoup plus minimaliste, tout est configurer à la main |

Le choix s'est donc orienté vers Debian 12 “Bookworm” — arm64 netinst pour une virtualization UTM pour Mac ARM avec pour principaux paramètres:
| Option | Valeur utilisée |
|--------|-----------------|
| RAM | 4 Go |
| Disque virtuel | 20 Go |
| CPU |	4 cœurs |
| Réseau | partagé |

### 🐳 Docker
Le coeur du projet repose sur trois images construites *from scratch* principalement à partir de `debian:bookworm`.  
Chaque service possède :
- un Dockerfile dédié,
- un entrypoint.sh personnalisant les actions au runtime,
- une configuration propre (MariaDB, PHP-FPM, Nginx).

Tous les autres services sont également intégrés à des docker construits *from scratch*.

### 🔐 Secrets vs Variables d’environnement
| Aspect | Secrets Docker | Variables d’environnement |
|--------|----------------|---------------------------|
| Sécurité | ✔ sécurisé, non visible dans l’historique | ❌ visible dans `docker inspect` |
| Usage idéal | mots de passe, clés, tokens | paramètres généraux |
| Support dans le sujet | recommandé mais optionnel | couramment utilisé |

Pour une sécurité optimale le dossier secrets et l'utilisation de Secrets Docker sont implémentés dans ce projet.

### 🖥️ Virtual Machines vs Docker
| Virtual Machine | Docker |
|----------------|--------|
| OS complet | Conteneur léger |
| Lourd, lent | Rapide, très peu de surcharge |
| Isolation forte | Isolation plus légère |
| Nettoyage complexe | Reproductibilité parfaite |

L'utilisation de dockers est mandatory dans ce projet.

### 🔗 Docker Network vs Host Network
- **Docker Network (bridge)** : recommandé ; isolation, contrôle précis, sécurité.
- **Host Network** : interdit dans le sujet ; conteneurs exposés directement au système hôte.

### 💾 Docker Volumes vs Bind Mounts
| Volumes | Bind Mounts |
|---------|-------------|
| filesystem interne Docker | dossier réel sur la machine |
| sécurisé, performant | utile pour inspection |
| idéal pour prod | idéal pour dev/sujets 42 |

L'utilsation de binds volumes est mandatory dans ce projet.

---

## 📚 Resources

### Documentation officielle
- Docker : https://docs.docker.com  
- WordPress : https://developer.wordpress.org  
- Nginx : https://nginx.org  
- MariaDB : https://mariadb.org  
- Redis : https://redis.io/docs/latest/
- Adminer : https://www.adminer.org/
- WP-CLI : https://wp-cli.org/  (commandes) https://developer.wordpress.org/cli/commands/
- Plugin Redis Object Cache (WP) : https://wordpress.org/plugins/redis-cache/
- vsftpd (FTP) : https://security.appspot.com/vsftpd.html  (référence) + `man vsftpd`
- Cron : https://man7.org/linux/man-pages/man8/cron.8.html
- rsync : https://download.samba.org/pub/rsync/rsync.html
- Backups MariaDB (dump) : https://mariadb.com/kb/en/mariadb-dump/  (alias `mysqldump`)
- Nginx FastCGI (PHP-FPM) : https://nginx.org/en/docs/http/ngx_http_fastcgi_module.html
- Site statique (HTML, CSS) : https://developer.mozilla.org

### Utilisation de l’IA
L’IA a été utilisée pour :
- recherches documentaires
- clarifier certains comportements spécifiques de Docker,
- obtenir des explications techniques sur les docker et la construction du docker-compose et Dockerfile,
- obtenir des explications techniques sur la configuration TLS,
- aider à affiner, améliorer et debugger les differents scripts, configurations et code.

Tout le code, la configuration et la compréhension ont été intégralement vérifiés, testés et validés par l’auteur.

---

## ✔️ Statut
La partie **mandatory** et **bonus** sont entièrement fonctionnelles et validées.

