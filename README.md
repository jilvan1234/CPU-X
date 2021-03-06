
<p align="center"><img src="https://raw.githubusercontent.com/X0rg/CPU-X/master/data/pictures/CPU-X.png" alt="CPU-X"></p>

[![GitHub release](https://img.shields.io/github/release/X0rg/CPU-X.svg)](https://github.com/X0rg/CPU-X)
[![GitHub downloads](https://img.shields.io/github/downloads/X0rg/CPU-X/latest/total.svg)](https://github.com/X0rg/CPU-X)
[![GitHub issues](https://img.shields.io/github/issues/X0rg/CPU-X.svg)](https://github.com/X0rg/CPU-X/issues)

CPU-X is a Free software that gathers information on CPU, motherboard and more.  
CPU-X is similar to [CPU-Z (Windows)](http://www.cpuid.com/softwares/cpu-z.html), but CPU-X is designed for GNU/Linux; it can also works on *BSD and on OS X (some features are missing).  
This software is written in C programming language, and built with [CMake](http://www.cmake.org/).  
This is a graphical software (GTK is used), but it can be used from a shell by using Ncurses or by dumping data.

<p align="center"><img src="http://i.imgur.com/J6d04TP.png" alt="Screenshot"></p>

***

# Table of contents
* [Dependencies](#dependencies)
  * [Build-only dependencies](#build-only-dependencies)
  * [Build and run dependencies](#build-and-run-dependencies)
* [Download/Install](#downloadinstall)
  * [Download packages](#download-packages)
  * [Manual build](#manual-build)
  * [Portable version](#portable-version)
* [Usage](#usage)
* [Screenshots](#screenshots)
* [Translate/Contributions](#translatecontributions)
* [Troubleshooting](#troubleshooting)
* [Bugs/Improvements/Request features](#bugsimprovementsrequest-features)

***

## Dependencies

### Build-only dependencies

These dependencies are needed to **manually build** CPU-X (e.g you can safely remove them after build):
* [CMake](http://www.cmake.org/) (minimum version is 3.0, older aren't supported): needed to build CPU-X
* [Pkg-Config](http://www.freedesktop.org/wiki/Software/pkg-config/)/[Pkgconf](https://github.com/pkgconf/pkgconf): needed by CMake for libraries detection
* [NASM](http://www.nasm.us/): needed to build Libbandwidth


### Build and run dependencies

These dependencies are needed to **manually build** and **run** CPU-X (e.g you can't remove a dependency if CPU-X was built with):
* [GTK3+](http://www.gtk.org/) (minimum version is 3.8, version 3.14 or newer recommended): required to run CPU-X in GTK mode; **not** embedded in portable version (use system shared library)
* [Ncurses](http://www.gnu.org/software/ncurses/): required to run CPU-X in NCurses mode; embedded in portable version
* [Libcpuid](http://libcpuid.sourceforge.net/) (version 0.2.2 or newer is recommended): required to run CPU-X correctly; embedded in portable version
* [Libpci](http://mj.ucw.cz/sw/pciutils/): required to run CPU-X correctly; embedded in portable version
* [Procps-ng](http://sourceforge.net/projects/procps-ng/), provides *libsystem* (**Linux only**): required to run CPU-X correctly; embedded in portable version
* [Libstatgrab](http://www.i-scream.org/libstatgrab/), provides *libsystem* (replaces **Procps-ng** for **non-Linux OS**): required to run CPU-X correctly; embedded in portable version
* [Curl](http://curl.haxx.se/): optionnal, needed to check if CPU-X is up-to-date


## Download/Install

### Download packages

You can download binary packages to easily install CPU-X on your system. A lot of distributions are supported, click on your distro logo and follow instruction:  
[![Arch Linux](http://i.stack.imgur.com/ymaLV.png)](https://github.com/X0rg/CPU-X/wiki/%5BPackage%5D-Arch-Linux)
[![Debian](https://phrozensoft.com/uploads/2014/11/debian_logo.png)](https://github.com/X0rg/CPU-X/wiki/%5BPackage%5D-Debian)
[![Fedora](http://kivy.org/images/os_fedora.png)](https://github.com/X0rg/CPU-X/wiki/%5BPackage%5D-Fedora)
[![Gentoo](http://www.ltsp.org/images/distro/gentoo.png)](https://github.com/X0rg/CPU-X/wiki/%5BPackage%5D-Gentoo)
[![OpenSUSE](https://harmonyseq.files.wordpress.com/2010/10/opensuse-logo_design_mini.png)](https://github.com/X0rg/CPU-X/wiki/%5BPackage%5D-OpenSUSE)
[![Ubuntu](http://computriks.com/img/icon/ubuntu24.png)](https://github.com/X0rg/CPU-X/wiki/%5BPackage%5D-Ubuntu)

Note: only recent versions of distributions are supported due to CMake 3.0 is needed to *build* CPU-X but not available on old distributions. A package can be installed on non-supported versions if dependencies can be satisfied (CMake is a build dependency, not an install dependency).


### Manual build

For step-by-step guide, you can see the [wiki page](https://github.com/X0rg/CPU-X/wiki) (GNU/Linux, *BSD and OS X).  
First of all, you need to install [CMake](http://www.cmake.org/) (this is only needed for build).
GTK headers are needed to compile with GTK support.  
You can disable components in CPU-X before build by passing argument `-D<var>=0` when running CMake:  
`-DWITH_GTK=0` will disable support of GUI in GTK3+  
`-DWITH_NCURSES=0` will disable support of NCurses mode  
`-DWITH_LIBCPUID=0` will avoid calls to Libcpuid (not recommended)  
`-DWITH_LIBDMI=0` will not compile Libdmidecode and will avoid calls to Libdmidecode (not recommended)  
`-DWITH_LIBBDWT=0` will not compile Libbandwidth and will avoid calls to Libbandwidth (not recommended)  
`-DWITH_LIBPCI=0` will avoid calls to Libpci (not recommended)  
`-DWITH_LIBSYSTEM=0` will avoid calls to Libprocps/Libstatgrab (not recommended)  

* If you want to install CPU-X on your system, do:
```
mkdir build && cd build
cmake ..
make
make install
```
By default, CPU-X will be installed in */usr/local*. If you want to change it, add option `cmake -DCMAKE_INSTALL_PREFIX=<absolute_path> ..` on CMake invocation.

* If you want to build a portable binary, do:
```
mkdir ebuild && cd ebuild
cmake -DEMBED=1 ..
make
```

Note: portable binary is *accomplished/bin/cpu-x*, in directory *ebuild*. Don't do `make install` after.You can move this runnable file where you want.


### Portable version

CPU-X is available in a portable version (Linux 32/64-bit, FreeBSD 32-bit), like CPU-Z.  
Latest release is [HERE](https://github.com/X0rg/CPU-X/releases/latest), all releases are [here](https://github.com/X0rg/CPU-X/releases).  
Download file *CPU-X_vX.X.X_portable.tar.gz* or file *CPU-X_vX.X.X_portable_noGTK.tar.gz*, extract archive, and you can now run CPU-X portable.  
You can put these files on a USB stick for example.


## Usage

Start program with **root privileges** allow to use **Dmidecode** (Libdmi) and avoid empty labels.
Application is put in the desktop menus, in **System Tools** category: entry *CPU-X* run CPU-X as regular user, and entry *CPU-X (Root)* grant root privileges.  
Else, you can use command `cpu-x`, or double-click on `cpu-x` binary is also possible (if program won't start, check if file has executable bit set).  
If GTK and NCurses are supported, you can start CPU-X in NCurses mode by taping in a shell (as root) `cpu-x --ncurses`.  
Use `cpu-x --help` for other commands and help.


## Screenshots

You can see how CPU-X looks here:
https://github.com/X0rg/CPU-X/wiki/Screenshots


## Translate/Contributions

You want to have CPU-X in a foreign language but no translation exists? See the following wiki page:
https://github.com/X0rg/CPU-X/wiki/Translate  
You want to contribute to CPU-X? In the top-right corner of the page, click **Fork**.


## Troubleshooting

* **CPU-X won't start**: try to do a `chmod +x` on binary.
* **CPU-X still won't start**: run it from a shell, and look output.
* **Some labels are empty**: CPU-X needs root privileges to run fine. If you manually build CPU-X, check dependencies. Or else, if a label is still empty, your hardware isn't recognized by a library.


## Bugs/Improvements/Request features

Please [open a new issue](https://github.com/X0rg/CPU-X/issues/new).
