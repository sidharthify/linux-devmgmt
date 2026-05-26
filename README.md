<div align="center">

  # linux-devmgmt
  <i>The Windows Device Manager, on Linux</i>

  <p>
    A faithful recreation of the Windows Device Manager built with Qt6 and real hardware backends via sysfs/procfs. Best enjoyed with <a href="https://github.com/Zren/plasma-applet-lib">AeroThemePlasma</a>.
  </p>

</div>
<br>

> [!NOTE]
> **Built for CachyOS / Arch Linux.**<br>Some features (DKMS uninstall, driver date lookup) depend on `dkms` and `pacman`. Other distros may need minor adjustments.

## Building

```bash
sudo pacman -S qt6-base cmake
cmake -B build
cmake --build build -j
./build/devmgmt
```

## Runtime dependencies

| Tool | Purpose |
|------|---------|
| `pkexec` | Privilege escalation for enable/disable/uninstall |
| `modinfo` | Driver details |
| `dkms` | *(optional)* DKMS driver management |
| `pacman` | *(optional)* Package date lookup |

## Features

- Full two-level device tree (by type) backed by real sysfs/procfs data
- Per-device Properties dialog with General, Driver, Details, and Resources tabs
- Enable / disable devices via kernel module blacklisting
- Uninstall DKMS drivers
- Update Driver wizard
- Driver Details viewer (`modinfo` output)
- Scan for hardware changes
