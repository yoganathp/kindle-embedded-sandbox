<!--
  📄 Kindle Embedded Sandbox Documentation
  File: commands.md
  Description: Terminal command reference for repository setup, firmware handling, toolchain use, debugging, and development workflows. A living document updated alongside the project.
  Author: yoganathp
  Repository: https://github.com/yoganathp/kindle-embedded-sandbox
  License: MIT (with GPL components as noted)
-->

# 🛠️ Kindle Embedded Sandbox — Command Reference

This document logs the terminal commands used in this project — from repository management to firmware building. It's meant as a learning and operational reference for anyone working on or exploring the **Kindle Embedded Sandbox** project.

> 💡 This file will be updated continuously as the project progresses through bare-metal development, Linux kernel customization, and hardware hacking.

---

## 📑 Table of Contents

- [📁 Folder Structure & Setup](#-folder-structure--setup)
- [🧪 tar Commands](#-tar-commands)
- [🔧 Git Commands](#-git-commands)
  - [Repository Management](#repository-management)
  - [Staging & Committing](#staging--committing)
  - [Remote & Branches](#remote--branches)
- [📦 To Be Added](#-to-be-added)

---

## 📁 Folder Structure & Setup

### Create the full folder structure for the project

```bash
mkdir -p \
gpl_sources \
uboot \
linux-kernel \
rootfs \
baremetal/ultron_uart \
rtos \
drivers/eink \
drivers/audio \
drivers/touch \
apps \
docs
```

### Add `.gitkeep` files so Git tracks empty folders

```bash
find . -type d ! -path . -exec touch {}/.gitkeep \;
```

---

## 🧪 tar Commands

### Extract a `.tar.gz` archive in the current directory

```bash
tar -xzf archive.tar.gz
```

### Extract a `.tar.gz` archive to a specific folder

```bash
mkdir -p myfolder
tar -xzf archive.tar.gz -C myfolder
```

### Extract all .tar.gz files in a directory to separate folders
Useful for extracting multiple archives (e.g., in gpl_sources/Kindle_src_5.1.2_1679530004/gplrelease):

```bash
for file in *.tar.gz; do
  dirname="${file%.tar.gz}"
  mkdir -p "../sources/$dirname"
  tar -xzf "$file" -C "../sources/$dirname"
done
```

---

## 🔧 Git Commands

### Repository Management

#### Clone the repository

```bash
git clone https://github.com/your-username/kindle-embedded-sandbox.git
```

#### Check the status of your working tree

```bash
git status
```

#### Pull the latest changes from the remote repository

```bash
git pull origin main
```

### Staging & Committing

#### Add all files (including new folders and `.gitkeep`)

```bash
git add .
```

#### Commit changes with a message

```bash
git commit -m "Add project folder structure with .gitkeep placeholders"
```

#### Push changes to the remote repository

```bash
git push origin main
```

### Removing `.gitkeep`

When you add real files to a folder that previously contained only a `.gitkeep` file, remove `.gitkeep` to keep the repo clean.

**Remove `.gitkeep`:**

```bash
rm path/to/.gitkeep
```

### Remote & Branches

#### Check current Git branch

```bash
git branch
```

#### View remote URLs

```bash
git remote -v
```

---

## 📦 To Be Added

Coming soon:

- `loady` usage for uploading test binaries via UART
- `QEMU` emulation setup and run commands
- `dd` and `binwalk` for firmware image exploration
- Bare-metal toolchain build steps
- Linux kernel build & deploy

---

Feel free to contribute by adding new command examples, explanations, or suggestions via PR or issue!