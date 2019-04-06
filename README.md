# AGRIO.CDT (Contract Development Toolkit)
## Version : 1.6.1

AGRIO.CDT is a toolchain for WebAssembly (WASM) and set of tools to facilitate contract writing for the AGRIO platform.  In addition to being a general purpose WebAssembly toolchain, [AGRIO](https://github.com/aggregion/agr) specific optimizations are available to support building AGRIO smart contracts.  This new toolchain is built around [Clang 7](https://github.com/aggregion/llvm), which means that AGRIO.CDT has the most currently available optimizations and analyses from LLVM, but as the WASM target is still considered experimental, some optimizations are not available or incomplete.

## Important!
AGRIO.CDT Version 1.3.x introduced quite a few breaking changes.  To have binary releases we needed to remove the concept of a core symbol from AGRIO.CDT. This meant drastic changes to symbol, asset and other types/functions that were connected to them. Since these changes would be disruptive, we decided to add as many disruptive changes needed for future contract writing, so that disruption should only occur once. Please read the **_Differences between Version 1.2.x and Version 1.3.x_** section of this readme.

### Binary Releases
AGRIO.CDT currently supports Mac OS X brew, Linux x86_64 Debian packages, and Linux x86_64 RPM packages.

**If you have previously installed AGRIO.CDT, please run the `uninstall` script (it is in the directory where you cloned AGRIO.CDT) before downloading and using the binary releases.**

#### Mac OS X Brew Install
```sh
$ brew tap agrio/agrio.cdt
$ brew install agrio.cdt
```
#### Mac OS X Brew Uninstall
```sh
$ brew remove agrio.cdt
```
#### Debian Package Install
```sh
$ wget https://github.com/aggregion/agrio.cdt/releases/download/v1.6.1/agrio.cdt_1.6.1-1_amd64.deb
$ sudo apt install ./agrio.cdt_1.6.1-1_amd64.deb
```
#### Debian Package Uninstall
```sh
$ sudo apt remove agrio.cdt
```

#### Fedora RPM Package Install
```sh
$ wget https://github.com/aggregion/agrio.cdt/releases/download/v1.6.1/agrio.cdt-1.6.1-1.fedora-x86_64.rpm
$ sudo yum install ./agrio.cdt-1.6.1-1.fedora-x86_64.rpm
```

#### Fedora RPM Package Uninstall
```sh
$ sudo yum remove agrio.cdt
```

#### Centos RPM Package Install
```sh
$ wget https://github.com/aggregion/agrio.cdt/releases/download/v1.6.1/agrio.cdt-1.6.1-1.centos-x86_64.rpm
$ sudo yum install ./agrio.cdt-1.6.1-1.centos-x86_64.rpm
```

#### Centos RPM Package Uninstall
```sh
$ sudo yum remove agrio.cdt
```

### Guided Installation (Building from Scratch)
```sh
$ git clone --recursive https://github.com/aggregion/agrio.cdt
$ cd agrio.cdt
$ ./build.sh
$ sudo ./install.sh
```

### Installed Tools
---
* agrio-cpp
* agrio-cc
* agrio-ld
* agrio-init
* agrio-abidiff
* agrio-wasm2wast
* agrio-wast2wasm
* agrio-ranlib
* agrio-ar
* agrio-objdump
* agrio-readelf
