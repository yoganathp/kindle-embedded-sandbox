#!/bin/bash
# ------------------------------------------------------------------------------
# 📄 Kindle Embedded Sandbox Script
# File: store-env.sh
# Description: Backs up APT packages, Python packages, Git aliases, and configs.
# Author: yoganathp
# Repository: https://github.com/yoganathp/kindle-embedded-sandbox
# License: MIT (with GPL components as noted)
# ------------------------------------------------------------------------------

set -e

# Go to repo root
cd "$(git rev-parse --show-toplevel)"

BACKUP_DIR="scripts/env-backup"
mkdir -p "$BACKUP_DIR"

echo "📦 Backing up APT packages..."
dpkg --get-selections > "$BACKUP_DIR/apt-packages-list.txt"

echo "🐍 Backing up Python packages..."
pip freeze > "$BACKUP_DIR/python-packages.txt"

echo "🔧 Backing up git aliases..."
git config --get-regexp ^alias\. > "$BACKUP_DIR/git-aliases.txt" || echo "# No git aliases found" > "$BACKUP_DIR/git-aliases.txt"

echo "📝 Backing up any other custom configs..."
# Add other config backups here

echo "✅ Environment backup complete."