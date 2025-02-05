# Dinosaur Planet: Recompiled
Dinosaur Planet: Recompiled is a static recompilation/native port of [Dinosaur Planet](https://www.rarewiki.com/wiki/Dinosaur_Planet) using the [N64: Recompiled](https://github.com/Mr-Wiseguy/N64Recomp) project.

This project **does not use emulation**. Instead, game code is ran natively on your system with graphics rendered by [RT64](https://github.com/rt64/rt64).

### **This repository and its releases do not contain game assets. The original game is required to build or run this project.**

## System Requirements
A GPU supporting Direct3D 12.0 (Shader Model 6) or Vulkan 1.2 is required to run this project. The oldest GPUs that should be supported for each vendor are:
* GeForce GT 630
* Radeon HD 7750 (the one from 2012, not to be confused with the RX 7000 series) and newer
* Intel HD 510 (Skylake)

A CPU supporting the AVX instruction set is also required (Intel Core 2000 series or AMD Bulldozer and newer).

If you have issues with crashes on startup, make sure your graphics drivers are fully up to date. 

## Known Issues
Please see [the GitHub issues](https://github.com/Francessco121/dino-recomp/issues) for a list of known issues with the project. Given the early state of Dinosaur Planet reverse engineering and the uniqueness of the game's code, this recomp has some notable issues and missing enhancements compared to other recomp projects.

## FAQ

#### What is static recompilation?
Static recompilation is the process of automatically translating an application from one platform to another. For more details, check out the full description of how this project's recompilation works here: [N64: Recompiled](https://github.com/Mr-Wiseguy/N64Recomp).

#### How is this related to the decompilation project?
Unlike traditional N64 ports, recompilation projects are not based on the source code of a related decompilation. However, the [Dinosaur Planet decompilation](https://github.com/zestydevy/dinosaur-planet) project plays a very important role in this recomp, by providing symbols, knowledge about game systems, and to a lesser extent actual decompiled code used in some patches.

If you would like to see this recomp improve, consider contributing to the decompilation! Progress made in the decompilation project opens the door for more and better enhancements/mods.

#### Where is the savefile stored?
- Windows: `%LOCALAPPDATA%\DinoPlanetRecompiled\saves`
- Linux: `~/.config/DinoPlanetRecompiled/saves`

## Modding
N64 recomp modding (`.nrm`) is fully supported by this project.

### Installing mods
> [!WARNING]
> Mods do not run in a sandbox! Please only install mods from trusted sources.

Mods can be installed by placing their `.nrm` files in:
- Windows: `%LOCALAPPDATA%\DinoPlanetRecompiled\mods`
- Linux: `~/.config/DinoPlanetRecompiled/mods`

### Creating mods
If you would like to create your own mods, please see the following resources:
- [N64 Recomp Modding documentation](https://hackmd.io/fMDiGEJ9TBSjomuZZOgzNg)
- [Dinosaur Planet: Recompiled Mod Template](https://github.com/Francessco121/dino-recomp-mod-template)
- [Dinosaur Planet: Recompiled Mod API](https://github.com/Francessco121/dino-recomp-mod-api)
- [An example mod](https://github.com/Francessco121/dino-recomp-example-mod)
- [N64Recomp](https://github.com/N64Recomp/N64Recomp) for the source code of `RecompModTool`.

## Building
For developers, please see [BUILDING.md](./BUILDING.md) for build and development environment setup instructions.

## Credits
* [Zelda64Recomp](https://github.com/Zelda64Recomp/Zelda64Recomp) for the base project. Much of this project is a direct fork of the Majora's Mask recomp.
* [N64Recomp](https://github.com/N64Recomp/N64Recomp) for static recompilation.
* [N64ModernRuntime](https://github.com/N64Recomp/N64ModernRuntime) for a reimplementation of libultra and general handling of common recomp tasks.
* [RT64](https://github.com/rt64/rt64) for the project's rendering engine.
* [Dinosaur Planet Decompilation](https://github.com/zestydevy/dinosaur-planet) for symbols, headers, and general knowledge about the game's internals.
* [RmlUi](https://github.com/mikke89/RmlUi) for building the menus and launcher.
* [lunasvg](https://github.com/sammycage/lunasvg) for SVG rendering, used by RmlUi.
* [FreeType](https://freetype.org/) for font rendering, used by RmlUi  .
* [moodycamel::ConcurrentQueue](https://github.com/cameron314/concurrentqueue) for semaphores and fast, lock-free MPMC queues.
* [Gamepad Motion Helpers](https://github.com/JibbSmart/GamepadMotionHelpers) for sensor fusion and calibration algorithms to implement gyro aiming.
* [Ares emulator](https://github.com/ares-emulator/ares) for RSP vector instruction reference implementations, used in RSP recompilation.
