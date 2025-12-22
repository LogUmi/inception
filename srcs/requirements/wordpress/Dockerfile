
# wordpress
FROM debian:12.5

RUN apt update && apt install -y \
    php php-fpm php-mysql php-mbstring php-xml php-gd php-curl php-zip mariadb-client \
    wget curl tar less && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/www/html && chown -R www-data:www-data /var/www

WORKDIR /var/www/html

RUN curl -o /usr/local/bin/wp https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x /usr/local/bin/wp

RUN PHP_VER=$(php -r 'echo PHP_MAJOR_VERSION.".".PHP_MINOR_VERSION;') \
    && sed -i 's|^listen = .*|listen = 0.0.0.0:9000|' /etc/php/$PHP_VER/fpm/pool.d/www.conf \
    && sed -i 's|^;clear_env = no|clear_env = no|' /etc/php/$PHP_VER/fpm/pool.d/www.conf

COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
RUN chmod +x /usr/local/bin/entrypoint.sh

EXPOSE 9010
ENTRYPOINT ["entrypoint.sh"]

