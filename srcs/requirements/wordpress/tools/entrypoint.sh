#!/bin/sh
set -e

WP_ADMIN_PASSWORD="$(cat /run/secrets/wp_admin_password)"
WP_USER_PASSWORD="$(cat /run/secrets/wp_user_password)"
MYSQL_USER_PASSWORD="$(cat /run/secrets/wp_user_password)"
WP_PORT="${WP_PORT:-443}"
if [ "$WP_PORT" = "443" ]; then
  WP_URL="https://${DOMAIN_NAME}"
else
  WP_URL="https://${DOMAIN_NAME}:${WP_PORT}"
fi

cd  /var/www/html

if [ ! -f wp-config.php ]; then
      echo "Downloading Wordpress..."
      rm -rf ./*
      wp core download --allow-root

     echo "Creating wp-config.php..."
     wp config create \
        --dbname="${MYSQL_DATABASE}" \
        --dbuser="${MYSQL_USER}" \
        --dbpass="${MYSQL_USER_PASSWORD}" \
        --dbhost="mariadb:3306" \
        --allow-root
fi

if ! wp core is-installed --allow-root; then
     echo "Running WordPress Installation..."
     wp core install \
        --url="${WP_URL}" \
        --title="Inception" \
        --admin_user="${WP_ADMIN}" \
        --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}" \
        --skip-email \
        --allow-root

     echo "Creating additionnal user..."
     wp user create "${WP_USER}" "${WP_USER_EMAIL}" \
        --user_pass="${WP_USER_PASSWORD}" \
        --role=author \
        --allow-root
else
     echo "Wordpress already installed, installation skipped"
fi


if ! wp plugin is-installed --allow-root; then
     echo "Installing Redis Object Cache plugin..."
     wp plugin install redis-cache --activate --allow-root
else
     echo "Redis plugin already installed. Activating..."
     wp plugin redis-cache activate --allow-root || true
fi
if ! wp config has WP_REDIS_HOST --allow-root; then
     wp config set WP_REDIS_HOST "'redis'" --raw --type=constant --allow-root
else
     wp config set WP_REDIS_HOST "'redis'" --raw --type=constant --allow-root --quiet
fi
if ! wp config has WP_REDIS_PORT --allow-root; then
     wp config set WP_REDIS_PORT 6379 --raw --type=constant --allow-root
else
     wp config set WP_REDIS_PORT 6379 --raw --type=constant --allow-root --quiet
fi

wp redis enable --allow-root

chown -R www-data:www-data /var/www/html

echo "Fixing WordPress directory permissions..."
find /var/www/html -type d -exec chmod 775 {} \;
find /var/www/html -type f -exec chmod 664 {} \;

wp config set WP_HOME "$WP_URL" --type=constant --allow-root --quiet
wp config set WP_SITEURL "$WP_URL" --type=constant --allow-root --quiet
wp option update home "$WP_URL" --allow-root --quiet
wp option update siteurl "$WP_URL" --allow-root --quiet

echo "Starting PHP-FPM"
PHP_VER=$(php -r 'echo PHP_MAJOR_VERSION.".".PHP_MINOR_VERSION;')
exec php-fpm$PHP_VER -F
