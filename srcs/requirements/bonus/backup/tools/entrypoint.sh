#!/bin/sh
set -eu

echo "[entrypoint] Backup container starting..."

# Vérification des prérequis
if [ ! -f /run/secrets/mysql_user_password ]; then
  echo "[entrypoint] ERROR: mysql_user_password secret missing"
  exit 1
fi

mkdir -p /backups

cat > /etc/backup.env <<EOF
MYSQL_DATABASE=${MYSQL_DATABASE:-}
MYSQL_USER=${MYSQL_USER:-}
EOF
chmod 600 /etc/backup.env

echo "[entrypoint] Starting cron in foreground..."
exec cron -f
