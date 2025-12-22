#!/bin/sh
set -e

MYSQL_ROOT_PASSWORD="$(cat /run/secrets/mysql_root_password)"
MYSQL_USER_PASSWORD="$(cat /run/secrets/mysql_user_password)"

mkdir -p /run/mysqld
chown -R mysql:mysql /run/mysqld /var/lib/mysql

#if [ ! -d "/var/lib/mysql/mysql" ]; then
if [ ! -f /var/lib/mysql/.init_done ]; then
   echo "Initializing MariaDB data directory..."
   rm -rf /var/lib/mysql/*
   mariadb-install-db --user=mysql --datadir=/var/lib/mysql --skip-test-db > /dev/null

    echo "Running MariaDB bootstrap..."
   mysqld --user=mysql --datadir=/var/lib/mysql --bootstrap <<EOF
FLUSH PRIVILEGES;
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\`;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_USER_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
FLUSH PRIVILEGES;
EOF

    touch /var/lib/mysql/.init_done
fi

echo "Starting MariaDB..."
exec mysqld --user=mysql --console
