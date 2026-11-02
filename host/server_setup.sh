#!/bin/sh

SCRIPT_DIR=$(dirname "$0")
REPO_DIR=$(pwd "$SCRIPT_DIR/..")
GARDEN_HOST_DIR=$(pwd "$SCRIPT_DIR")

USER_SERVICE_DIR="$HOME/.config/systemd/user"
# the absolute path to uv executable as well as to the daemon
UV_PATH="$(which uv)"

if [ -z "$UV_PATH" ]; then
    echo "Please install uv"
    exit 1
fi

mkdir -p "$USER_SERVICE_DIR"

echo "Writing unit file to $USER_SERVICE_DIR"

IP_ADDR=$(hostname -I | cut -d " " -f 1)

cat > "$USER_SERVICE_DIR/dormgarden_server.service" << EOF
[Unit]
Description=Service to run dormgarden server

[Service]
Type=simple
WorkingDirectory=$GARDEN_HOST_DIR
ExecStart=$UV_PATH run gunicorn --workers 1 --bind "$IP_ADDR":9147 garden_server:app

[Install]
WantedBy=multi-user.target
EOF

echo "Reloading systemd user daemon"
systemctl --user daemon-reload
