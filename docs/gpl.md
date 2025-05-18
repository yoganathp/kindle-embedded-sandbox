<!--
  📄 Kindle Embedded Sandbox Documentation
  File: gpl.md
  Description: Information about the GPL source code packages, their origin, extraction, and usage within the Kindle Embedded Sandbox project.
  Author: yoganathp
  Repository: https://github.com/yoganathp/kindle-embedded-sandbox
  License: MIT (with GPL components as noted)
-->

# 📦 GPL Source Code Packages

> ⚠️ This document is a living file and will be updated regularly as our understanding of the GPL source packages and their contents improves.

This document describes the GPL source code packages used in the **Kindle Embedded Sandbox** project. It includes the source origin, extraction process, directory structure, and relevant project references.

---

## Source Archive

The GPL source code packages were obtained from the official Kindle source release:

- Archive URL: [https://s3.amazonaws.com/kindle/Kindle_src_5.1.2_1679530004.tar.gz](https://s3.amazonaws.com/kindle/Kindle_src_5.1.2_1679530004.tar.gz)  
- Extracted to: [`gpl_sources/Kindle_src_5.1.2_1679530004/gplrelease/`](/gpl_sources/Kindle_src_5.1.2_1679530004/gplrelease)

---

## Directory Structure

Within the `gpl_sources` folder:

- `Kindle_src_5.1.2_1679530004/` contains the extracted source archive.
- Inside it, the `gplrelease/` directory contains multiple `.tar.gz` packages. These correspond to various components such as:
  - **Kernel source code:** The Linux kernel version used by the device.
  - **Bootloader packages:** U-Boot and related boot components.
  - **Driver sources:** For audio, touchscreen, eink display, and other hardware.
  - **User-space utilities:** Tools like busybox, alsa-utils, and other system utilities.
  - **Libraries:** Various open source libraries like glib, gnutls, etc.
  - **Other components:** Network stacks, system tools, and miscellaneous modules.

This structure is typical of embedded GPL source releases, separating components for easier maintenance and compliance.

---

## Extraction

To extract the `.tar.gz` packages inside `gplrelease/`, use the extraction script described in the [commands.md — Tar Commands section](commands.md#-tar-commands).

---

## Repository References

- [README.md](/README.md) — Project overview  
- [`docs/commands.md`](/docs/commands.md) — Terminal commands reference  

---

## Usage & Contribution

- These GPL source packages provide insight into the kernel, drivers, utilities, and other components of the Kindle Touch (Gen 4).
- They serve as the foundation for bare-metal and Linux kernel development within this sandbox.
- Contributions, bug reports, or improvements are welcome via issues or pull requests.
- See [CONTRIBUTING.md](/CONTRIBUTING.md) for contribution guidelines.

---

## Licensing

- The GPL source code packages are licensed under the GNU General Public License (GPL).  
- This project is licensed under the [MIT license](/LICENSE.md), with GPL components noted where applicable in the repository.

---

Please feel free to open issues or submit pull requests for any clarifications, additions, or corrections regarding the GPL sources.