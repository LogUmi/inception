
# adminer
FROM debian:12.5

RUN apt-get update && apt-get install -y --no-install-recommends \
    php8.2-fpm php8.2-mysql ca-certificates curl \
    && rm -rf /var/lib/apt/lists/*

RUN mkdir -p /var/www/adminer

RUN curl -fsSL -o /var/www/adminer/index.php \
    https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php


RUN sed -i 's|^listen = .*|listen = 9001|g' /etc/php/8.2/fpm/pool.d/www.conf

EXPOSE 9001

CMD ["php-fpm8.2", "-F"]


