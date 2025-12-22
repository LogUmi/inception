#!/bin/sh
set -eu

if [ $# -ne 1 ]; then
  echo "Usage: restore.sh YYYYMMDD_HHMMSS"
  exit 1
fi

TS="$1"
BACKUP_DIR="/backups"

DB_FILE="${BACKUP_DIR}/db_${TS}.sql"
WP_FILE="${BACKUP_DIR}/wp_${TS}.tar.gz"

DB_HOST="mariadb"
DB_NAME="${MYSQL_DATABASE}"
DB_USER="${MYSQL_USER}"
DB_PASS="$(cat /run/secrets/mysql_user_password)"

[ -f "$DB_FILE" ] || { echo "Missing $DB_FILE"; exit 1; }
[ -f "$WP_FILE" ] || { echo "Missing $WP_FILE"; exit 1; }

echo "[restore] Restoring DB from $DB_FILE ..."
mysql -h "$DB_HOST" -u"$DB_USER" -p"$DB_PASS" "$DB_NAME" < "$DB_FILE"

echo "[restore] Restoring WordPress files from $WP_FILE ..."
# ⚠️ idéalement faire ça quand nginx/wordpress sont arrêtés pour éviter incohérences
rm -rf /var/www/html/*
tar -xzf "$WP_FILE" -C /var/www/html

echo "[restore] Done."

