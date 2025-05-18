# 🧠 Kindle Embedded Sandbox

Welcome to **Kindle Embedded Sandbox** — a hands-on learning lab built around the **Amazon Kindle Touch (Gen 4)**.

This repository is part of a personal, self-learning journey into embedded Linux and bare-metal development, using the Kindle as a real-world hardware sandbox.  
Instead of using it just for reading, I’m diving deep into reverse-engineering its internals, hijacking UART, building custom firmware, and documenting every step.

📚 **What this is:**  
A full-stack embedded Linux exploration — from low-level bare-metal firmware to Linux drivers and applications — all tested on Kindle hardware (with QEMU assist when needed).  
📄 **See [SUMMARY.md](./SUMMARY.md)** for an overview of the project structure and learning phases.  
🤝 **Want to contribute?** See [CONTRIBUTING.md](./CONTRIBUTING.md)

🛠️ **What to expect:**  
- Reverse engineering and U-Boot hacking  
- Bare-metal experiments and RTOS trials  
- Custom Linux kernel and driver development  
- A growing public notebook of failures, breakthroughs, and everything in between  

💡 **This is not a finished product** — it’s a learning sandbox and a growing documentation hub to inspire and help others explore hardware hacking and low-level systems programming.

---

## 🛠️ **Reviving a Kindle Touch (Gen 4) with UART & U-Boot Debugging**

It all started with an old Kindle stuck on the boot screen—plugged it in countless times, no luck. Initially, I just wanted to replace the battery, but it quickly turned into a deep dive into embedded Linux, bootloaders, and low-level debugging 🧠⚙️

To my surprise, it’s powered by a **Freescale i.MX508 ARM Cortex-A8 SoC**—perfect for exploring U-Boot and embedded Linux internals.

Here’s what unfolded:

- 🔍 **Found UART pads** by manually probing the PCB
- ⚡ **Built a safe 1.8V UART interface** using TXS0108E
- 🔌 **Hooked up via CH340 USB-UART bridge**
- 🖥️ **Opened PuTTY—and U-Boot logs came alive** 🎉

But then:

- ❌ **Error:** `can't get kernel image!`
- Looks like a bad firmware update bricked the boot flow

This Kindle became my embedded learning playground:

- ✅ Bootloader & kernel debugging
- ✅ Power subsystem quirks (BQ27xxx)
- ✅ Reverse engineering without schematics

📖 **Read full article:**  
[🔗 Bringing a Dead Kindle Touch Back to Life (LinkedIn)](https://www.linkedin.com/pulse/bringing-dead-kindle-touch-back-life-hands-on-yoganath-prabhakar-ljtcc)

---

## 🎯 **Project Goals**

- Learn embedded Linux **without Yocto**, starting from vendor GPL sources
- Build everything manually: **bootloader → kernel → rootfs → drivers → apps**
- Use **UART** and **U-Boot loady** to load test code without flashing
- Experiment with **bare-metal**, **RTOS**, and **custom Linux drivers**
- Document and reverse engineer Kindle’s hardware (E-Ink, audio, touchscreen)
- Use **QEMU** to test before deploying to real hardware

---

## 🧩 Learning Roadmap

1. ✅ **Gain UART access** to the Kindle bootloader (U-Boot)  
2. 🔄 **Use GPL source** to understand and rebuild U-Boot & Linux (ongoing)  
3. 🔜 **Write bare-metal code**: hijack UART from U-Boot and print message  
4. 🔜 **Write bare-metal drivers** for Kindle peripherals (E-Ink, audio, touch)  
5. 🔜 **Run a lightweight RTOS** on Kindle hardware for custom demos  
6. 🔜 **Build Linux drivers** (using/adapting bare-metal code)  
7. 🔜 **Build a minimal Linux system** with BusyBox and rootfs  
8. 🔜 **Create user-space apps** for Kindle with custom GUI/CLI  

---

## 📁 Project Structure

This repository is structured to mirror a full-stack embedded Linux learning journey — starting from low-level bare-metal firmware up to building Linux drivers and user-space applications, all on the Kindle Touch (Gen 4) hardware.

```plaintext
kindle-embedded-sandbox/
├── gpl_sources/         → Amazon’s GPL source code for U-Boot and Linux (starting point)
├── uboot/               → U-Boot rebuilds, configs, and environment reverse engineering
├── linux-kernel/        → Custom Linux kernel builds, Kindle-specific patches
├── rootfs/              → Minimal Linux root filesystems (BusyBox, initramfs, etc.)
├── baremetal/           → Bare-metal development, low-level code for direct hardware control
│   └── ultron_uart/     → Bare-metal UART hijack: send custom message via U-Boot's loady
├── rtos/                → Real-Time Operating System (FreeRTOS/Zephyr) experiments with custom drivers
├── drivers/             → Hardware drivers for Kindle’s peripherals (E-Ink, audio, touch)
│   ├── eink/            → E-Ink display drivers (bare-metal and Linux port)
│   ├── audio/           → Audio codec interfacing and driver logic
│   └── touch/           → Touchscreen controller drivers
├── apps/                → Custom Linux user-space apps built for Kindle hardware
├── docs/                → Documentation: memory map, NAND layout, reverse-engineering details
├── SUMMARY.md           → Project summary and overview
├── CONTRIBUTING.md      → Guidelines for contributing to the project
├── LICENSE              → Project license (MIT) and GPL components
└── README.md            → Project documentation
```
> 📌 **Note**: Many directories are planned for future expansion and are included as part of the project roadmap. This sandbox is a long-term learning environment and will grow over time as development progresses.

### 🧠 Learning Path via Structure

| Phase                         | Folders Used                       |
|-------------------------------|------------------------------------|
| Hardware Reverse Engineering  | `gpl_sources/`, `docs/`            |
| Bootloader Exploration        | `uboot/`                           |
| Linux Kernel Understanding    | `linux-kernel/`, `rootfs/`         |
| Bare-Metal Firmware           | `baremetal/ultron_uart/`           |
| Peripheral Driver Development | `drivers/`, `baremetal/`           |
| RTOS Integration              | `rtos/`, `drivers/`                |
| Linux Driver Porting          | `drivers/`, `linux-kernel/`        |
| Application Layer (Userland)  | `apps/`                            |

---

## 🧰 Tools & Setup

### 🛠️ Toolchains

- `arm-none-eabi-gcc` – For bare-metal development on ARM Cortex-A8  
- `gcc-arm-linux-gnueabi` – For Linux kernel and user-space development  

### ⚙️ Hardware Tools

- **CH340 USB-to-UART bridge** (for serial access)  
- **TXS0108E level shifter** (1.8V logic level safe)  
- **Kindle Touch Gen 4** (Freescale i.MX508 ARM Cortex-A8 SoC)  

### 💻 Software Tools

- `loady` – YMODEM transfer to U-Boot  
- `binwalk`, `dd` – Firmware analysis, NAND flash image extraction  
- `QEMU` – Emulate ARM for pre-deployment tests  
- `PuTTY`, `screen`, `minicom` – UART/serial terminal tools  

---

## 🔗 Resources

📦 **Amazon GPL Source Drops**  
[Amazon GPL Source Drops](https://www.amazon.com/gp/help/customer/display.html?nodeId=200203720)

📘 **elinux.org** — Embedded Linux Wiki  
[elinux.org](https://elinux.org/)

📚 **U-Boot Documentation**  
[U-Boot Main Docs](https://www.denx.de/wiki/U-Boot)

📖 **Linux Kernel ARM Docs**  
[Linux ARM Docs](https://docs.kernel.org/arch/arm)

🧪 **QEMU Documentation**  
[QEMU Wiki](https://wiki.qemu.org/Documentation)

🧠 **NAND Reverse Engineering**  
[Binwalk GitHub](https://github.com/ReFirmLabs/binwalk)

💬 **MobileRead Kindle Dev Forum**  
[Kindle Hacking](https://www.mobileread.com/forums/forumdisplay.php?f=150)

---

## 🌿 Branches Overview

- **main** — Primary branch with core project source code, builds, and documentation.  
- **codespace-backup** — Branch for backing up extracted GPL sources and Codespace environment files that are ignored in `main`.  
  Used to preserve large extracted files and environment setup logs from your Codespace sessions.

For detailed instructions on using the `codespace-backup` branch and managing your Codespace environment, see [Codespace Backup Guide](https://github.com/yoganathp/kindle-embedded-sandbox/blob/codespace-backup/kindle-embedded-sandbox/docs/codespace-backup-guide.md).

---

## 📜 License

This project is released under the [MIT License](./LICENSE.md).

✅ **Original work** (bare-metal code, Linux drivers, tools, documentation):  
Licensed under MIT — feel free to use, modify, and distribute.

🧩 **GPL components** (e.g., Amazon’s Kindle U-Boot/Linux GPL drops in `gpl_sources/`):  
These remain under their original GPLv2 licenses. Refer to each component’s source and COPYING file for details.

📌 **Disclaimer**:  
This repository is an educational, self-learning project and is not affiliated with or endorsed by Amazon.  
All product names, logos, and brands are property of their respective owners.  
**Use at your own risk.**

---

## 🙋‍♂️ Contribute / Connect

Got ideas, tips, or hardware hacks?  
Feel free to open issues, fork the repo, or just say hi on [LinkedIn](https://www.linkedin.com/in/yoganathp/).  
Let’s learn and build cool things together 🚀

For build instructions, toolchain setup, and contribution guidelines, see the [CONTRIBUTING.md](./CONTRIBUTING.md) file.
