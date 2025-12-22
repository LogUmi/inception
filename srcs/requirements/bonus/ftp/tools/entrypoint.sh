#!/bin/sh
set -e

if [ -z "$FTP_USER" ]; then
    echo "ERROR: FTP_USER is not set"
    exit 1
fi

FTP_PASSWORD="$(cat /run/secrets/ftp_password)"

if ! id "$FTP_USER" >/dev/null 2>&1; then
    adduser \
        --disabled-password \
        --home /var/www/html \
        --gecos "" \
        "$FTP_USER"
fi

adduser "$FTP_USER" www-data

echo "${FTP_USER}:${FTP_PASSWORD}" | chpasswd

echo "Starting vsftpd..."
exec vsftpd /etc/vsftpd.conf
