#!/bin/bash
# ------------------------------------------------------------------------------
# 📄 Kindle Embedded Sandbox Script
# File: backup-and-stop.sh
# Description: Saves environment, commits changes, and stops GitHub Codespace.
# Author: yoganathp
# Repository: https://github.com/yoganathp/kindle-embedded-sandbox
# License: MIT (with GPL components as noted)
# ------------------------------------------------------------------------------
#

set -e

REPO="yoganathp/kindle-embedded-sandbox"
BACKUP_BRANCH="codespace-backup"
MODE="$1"

# Go to repo root
cd "$(git rev-parse --show-toplevel)"

# Check if GitHub CLI is installed
if ! command -v gh &> /dev/null; then
  echo "❌ Error: GitHub CLI 'gh' is not installed."
  exit 1
fi

if [[ "$MODE" == "1" ]]; then

  echo "🔄 Checking if branch '$BACKUP_BRANCH' exists..."
  if git show-ref --verify --quiet refs/heads/"$BACKUP_BRANCH"; then
    git checkout "$BACKUP_BRANCH"
  else
    echo "❌ Error: Branch '$BACKUP_BRANCH' does not exist. Please create it first."
    exit 1
  fi

  echo "🗄️  Running environment backup script (store-env.sh)..."
  bash scripts/store-env.sh

  echo "🧐 Checking for uncommitted changes..."
  if [[ -n $(git status --porcelain) ]]; then
    echo "✍️  Changes found. Committing and pushing..."
    git add -A
    git commit -m "Auto commit before stopping Codespace on $(date +"%Y-%m-%d %H:%M:%S")"
    git push --set-upstream origin "$BACKUP_BRANCH"
    echo "✅ Changes committed and pushed."
  else
    echo "ℹ️  No changes to commit. Skipping save."
  fi

  # Return to previous branch
  if ! git checkout -; then
    echo "⚠️ Could not switch back to previous branch, please checkout manually."
  fi

elif [[ "$MODE" == "0" ]]; then
  echo "⏭️  Skipping save. Proceeding to stop."
else
  echo "❗ Usage: $0 [1 to save & stop | 0 to stop only]"
  exit 1
fi

echo "⏳ Stopping Codespace for repo $REPO..."
CODESPACE_NAME=$(gh codespace list --repo "$REPO" --json name -q '.[0].name')

if [ -z "$CODESPACE_NAME" ]; then
  echo "❌ No Codespace found for repo $REPO"
  exit 1
fi

gh codespace stop -c "$CODESPACE_NAME"
echo "✅ Codespace '$CODESPACE_NAME' stopped successfully."