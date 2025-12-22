#!/bin/sh
set -e

if [ -f /etc/backup.env ]; then
  . /etc/backup.env
fi

BACKUP_DIR="/backups"

DB_HOST="mariadb"
DB_NAME="${MYSQL_DATABASE}"
DB_USER="${MYSQL_USER}"
DB_PASS="$(cat /run/secrets/mysql_user_password)"

TIMESTAMP="$(date +'%Y%m%d_%H%M%S')"

DB_FILE="${BACKUP_DIR}/db_${TIMESTAMP}.sql"
WP_FILE="${BACKUP_DIR}/wp_${TIMESTAMP}.tar.gz"

echo "[backup] $(date) Starting backup..."

if [ -z "${DB_NAME}" ] || [ -z "${DB_USER}" ] || [ -z "${DB_PASS}" ]; then
    echo "[backup] ERROR: DB env vars are not set (MYSQL_DATABASE / MYSQL_USER / MYSQL_PASSWORD)."
    exit 1
fi

echo "[backup] Dumping database ${DB_NAME}..."
mysqldump -h "${DB_HOST}" -u"${DB_USER}" -p"${DB_PASS}" "${DB_NAME}" > "${DB_FILE}"

echo "[backup] Archiving WordPress files..."
tar -czf "${WP_FILE}" -C /var/www/html .

echo "[backup] Done."

echo "[backup] Cleaning old backups (older than 7 days)..."
find "${BACKUP_DIR}" -type f -mtime +7 -printf "[backup] Removing %p\n" -delete || true

echo "[backup] Done."
