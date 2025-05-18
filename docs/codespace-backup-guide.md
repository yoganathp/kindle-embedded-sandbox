<!--
  📄 Kindle Embedded Sandbox Documentation
  File: codespace-backup-guide.md
  Description: Guide for setting up environment backup and restore in GitHub Codespaces, including tooling, usage, and scripts to manage packages, configs, and branches.
  Author: yoganathp
  Repository: https://github.com/yoganathp/kindle-embedded-sandbox
  License: MIT (with GPL components as noted)
-->

# 🗃️ GitHub Codespace Backup & Restore Guide

This guide provides tools and usage instructions to automatically **backup**, **restore**, and **stop** a GitHub Codespace for the [Kindle Embedded Sandbox](https://github.com/yoganathp/kindle-embedded-sandbox).

---

## 📦 What It Does

- 📋 Backs up:
  - APT packages
  - Python packages
  - Git aliases
  - Other system configs (optionally)
- 💾 Saves the backup to a `codespace-backup` Git branch
- ⛔ Stops the Codespace via GitHub CLI
- 🔁 Supports restoration from saved backup

---

## 📁 Script Overview

### `scripts/backup-and-stop.sh`

- Saves environment and commits to `codespace-backup` branch
- Stops the active Codespace
- Can be run with:
  ```bash
  ./scripts/backup-and-stop.sh 1  # Save and stop
  ./scripts/backup-and-stop.sh 0  # Stop only
  ```

### `scripts/store-env.sh`

- Stores:
  - APT packages → `scripts/env-backup/apt-packages-list.txt`
  - Python packages → `scripts/env-backup/python-packages.txt`
  - Git aliases → `scripts/env-backup/git-aliases.txt`

### `scripts/restore-env.sh`
- ⚙️ Before use: Ensure this script is executable
    ```bash
    chmod +x scripts/restore-env.sh
    ```
- Grants execution to all `.sh` files in `scripts/`
- Restores from latest `codespace-backup` branch
- Applies:
  - APT + Python packages
  - Git aliases

---

## 🧰 Git Alias Setup (Optional but Recommended)

Run this once in your repository:

```bash
git config alias.cs-save-stop "!f() { cd \"$(git rev-parse --show-toplevel)\" && ./scripts/backup-and-stop.sh 1; }; f"
git config alias.cs-stop "!f() { cd \"$(git rev-parse --show-toplevel)\" && ./scripts/backup-and-stop.sh 0; }; f"
```

Then you can use:

```bash
git cs-save-stop   # Save + stop Codespace
git cs-stop        # Just stop Codespace
```

---

## 🧪 Usage

### Save and Stop

```bash
git cs-save-stop
```

- Commits changes + environment
- Pushes to `codespace-backup` branch
- Stops the active Codespace

### Stop Only (no save)

```bash
git cs-stop
```

---

### Restore After Restart

From a fresh Codespace or after a reset:

```bash
./scripts/restore-env.sh
```

- Checks out `codespace-backup`
- Restores all backed-up configs and packages

---

## 🪄 Managing the Backup Branch

To create and switch to the backup branch manually:

```bash
# Create the backup branch (only once)
git checkout -b codespace-backup

# Or switch to it if already created
git checkout codespace-backup

# Push it to GitHub
git push -u origin codespace-backup
```

Use this branch only for environment files and not your main project code.

---

## ⚙️ Prerequisites

- ✅ GitHub CLI (`gh`) must be installed and authenticated
- ✅ Internet access to install packages
- ✅ `codespace-backup` branch must exist (see above)

---

## 🛡️ Backup File Paths

Backups are stored under:

```
scripts/env-backup/
├── apt-packages-list.txt
├── python-packages.txt
└── git-aliases.txt
```

Optionally, add this folder to .gitignore to skip committing it on every update.

---

## 🧠 Pro Tips

- Run `git cs-save-stop` often to ensure minimal loss.
- Keep your `codespace-backup` branch clean — only track `.txt` or config files.
- You can add shell configs (e.g., `.bashrc`) to the backup if needed.

---

## 📜 License

This guide is released under the [MIT License](./LICENSE.md), unless otherwise noted.  
While the majority of this project is licensed under MIT, certain components — such as extracted sources in `gpl_sources/` (e.g., Kindle U-Boot or Linux) — remain under their original GPL licenses.

Please refer to each component’s source code and its accompanying `COPYING` file for complete licensing details.