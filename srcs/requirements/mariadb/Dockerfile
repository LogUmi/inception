
# mariadb
FROM debian:12.5

RUN apt update && apt install -y mariadb-server && rm -rf /var/lib/apt/lists/*

COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh

RUN chmod +x /usr/local/bin/entrypoint.sh \
    && chown -R mysql:mysql /var/lib/mysql

EXPOSE 3306
ENTRYPOINT ["entrypoint.sh"]
