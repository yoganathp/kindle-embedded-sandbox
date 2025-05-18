#!/bin/bash
# ------------------------------------------------------------------------------
# 📄 Kindle Embedded Sandbox Script
# File: restore-env.sh
# Description: Restores environment by applying backed-up packages and config.
# Author: yoganathp
# Repository: https://github.com/yoganathp/kindle-embedded-sandbox
# License: MIT (with GPL components as noted)
# ------------------------------------------------------------------------------

set -e

# Go to repo root
cd "$(git rev-parse --show-toplevel)"

BACKUP_BRANCH="codespace-backup"
BACKUP_DIR="scripts/env-backup"

echo "🛠️ Setting execute permission for all .sh scripts in scripts/ folder..."
find scripts/ -type f -name "*.sh" -exec chmod +x {} \;

echo "🌐 Fetching and checking out backup branch..."
git fetch origin "$BACKUP_BRANCH"
git checkout "$BACKUP_BRANCH"
git pull origin "$BACKUP_BRANCH"

echo "📦 Restoring APT packages..."
if [ -f "$BACKUP_DIR/apt-packages-list.txt" ]; then
  sudo apt-get update
  sudo dpkg --set-selections < "$BACKUP_DIR/apt-packages-list.txt"
  sudo apt-get dselect-upgrade -y
else
  echo "⚠️  No APT package backup found."
fi

echo "🐍 Restoring Python packages..."
if [ -f "$BACKUP_DIR/python-packages.txt" ]; then
  pip install -r "$BACKUP_DIR/python-packages.txt"
else
  echo "⚠️  No Python package backup found."
fi

echo "🔧 Restoring git aliases..."
if [ -f "$BACKUP_DIR/git-aliases.txt" ]; then
  while read -r line; do
    git config $line
  done < "$BACKUP_DIR/git-aliases.txt"
else
  echo "⚠️  No git aliases backup found."
fi

echo "📝 Restoring any other custom configs..."
# Add restore logic for additional config files here

echo "✅ Environment restore complete."