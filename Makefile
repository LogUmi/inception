DC          := docker-compose -f srcs/docker-compose.yml

DATA_DIR    := /home/lgerard/data
MDB_DIR     := $(DATA_DIR)/mariadb
WP_DIR      := $(DATA_DIR)/wordpress
BCK_DIR     := $(DATA_DIR)/backups

MDB_VOLUME  := srcs_mariadb_data
WP_VOLUME   := srcs_wordpress_data
BCK_VOLUME  := srcs_backups_data

MDB_IMAGE   := srcs_mariadb
WP_IMAGE    := srcs_wordpress
NGX_IMAGE   := srcs_nginx
RDS_IMAGE   := srcs_redis
FTP_IMAGE   := srcs_ftp
ADM_IMAGE   := srcs_adminer
BCK_IMAGE   := srcs_backup
CV_IMAGE    := srcs_cv

all: up

up: create_dirs
	$(DC) up -d --build

down:
	$(DC) down

logs:
	$(DC) logs -f

ps:
	$(DC) ps

create_dirs:
	mkdir -p $(MDB_DIR) $(WP_DIR) $(BCK_DIR)

clean: down
	- docker volume rm $(MDB_VOLUME) $(WP_VOLUME) $(BCK_VOLUME) 2>/dev/null || true
	- docker run --rm -v $(MDB_DIR):/data debian:12.5 \
		bash -c "rm -rf /data/* /data/.init_done" 2>/dev/null || true
	- docker run --rm -v $(WP_DIR):/data debian:12.5 \
		bash -c "rm -rf /data/*" 2>/dev/null || true
	- docker run --rm -v $(BCK_DIR):/data debian:12.5 \
                bash -c "rm -rf /data/*" 2>/dev/null || true

fclean: clean
	- docker rmi -f $(MDB_IMAGE) $(WP_IMAGE) $(NGX_IMAGE) $(RDS_IMAGE) $(FTP_IMAGE) $(ADM_IMAGE) $(BCK_IMAGE) $(CV_IMAGE) 2>/dev/null || true

re: fclean up

.PHONY: all up down logs ps clean fclean re create_dirs
