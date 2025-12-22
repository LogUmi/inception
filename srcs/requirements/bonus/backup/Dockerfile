
# backup
FROM debian:12.5

RUN apt update && apt install -y \
    mariadb-client \
    cron \
    tar \
    gzip \
    procps \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -d /var/www/html -s /bin/bash -g www-data ftpuser 

COPY tools/backup.sh /usr/local/bin/backup.sh
COPY tools/restore.sh /usr/local/bin/restore.sh
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh

RUN chmod +x /usr/local/bin/*.sh

COPY tools/backup-cron /etc/cron.d/backup-cron

RUN chmod 0600 /etc/cron.d/backup-cron

ENTRYPOINT ["entrypoint.sh"]
