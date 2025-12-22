
# redis
FROM debian:12.5

RUN apt update && apt install -y redis-server && rm -rf /var/lib/apt/lists/*

RUN sed -i 's/^protected-mode .*/protected-mode no/' /etc/redis/redis.conf \
    && sed -i 's/^bind .*/bind 0.0.0.0/' /etc/redis/redis.conf \
    && sed -i 's/^daemonize .*/daemonize no/' /etc/redis/redis.conf

EXPOSE 6379

CMD ["redis-server", "/etc/redis/redis.conf"]
