#!/bin/sh
set -e

: "${DOMAIN_NAME:?DOMAIN_NAME is not set}"

CERT_DIR="/etc/nginx/ssl"
KEY_FILE="${CERT_DIR}/${DOMAIN_NAME}.key"
CRT_FILE="${CERT_DIR}/${DOMAIN_NAME}.crt"

mkdir -p "${CERT_DIR}"

sed -i "s/__DOMAIN_NAME__/${DOMAIN_NAME}/g" /etc/nginx/nginx.conf

if [ ! -f "$KEY_FILE" ] || [ ! -f "$CRT_FILE" ]; then
    echo "Generating self-signed certificate for ${DOMAIN_NAME}..."
    openssl req -x509 -nodes -newkey rsa:2048 \
	-keyout "$KEY_FILE" \
	-out "$CRT_FILE" \
	-days 365 \
	-subj "/C=FR/ST=Occitanie/L=Perpignan/O=42/OU=lgerard/CN=${DOMAIN_NAME}"
fi

echo "Starting Nginx..."
exec nginx -g "daemon off;"
