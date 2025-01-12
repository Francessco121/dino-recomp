# Building Guide

This guide will help you build the project on your local machine. The process will require you to provide the ROM released by Forest of Illusion on Feb. 20, 2021.

These steps cover: patching the ROM, running the recompiler, and finally building the project.

## 1. Clone the dino-recomp Repository
This project makes use of submodules so you will need to clone the repository with the `--recurse-submodules` flag.

```bash
git clone --recurse-submodules
# if you forgot to clone with --recurse-submodules
# cd /path/to/cloned/repo && git submodule update --init --recursive
```

## 2. Install Dependencies

### Linux
For Linux the instructions for Ubuntu are provided, but you can find the equivalent packages for your preferred distro.

```bash
# For Ubuntu, simply run:
sudo apt-get install cmake ninja-build libsdl2-dev libgtk-3-dev lld llvm clang
```

### Windows
You will need to install [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/).
In the setup process you'll need to select the following options and tools for installation:
- Desktop development with C++
- C++ Clang Compiler for Windows
- C++ CMake tools for Windows

> [!NOTE]
> You do not necessarily need the Visual Studio UI to build/debug the project but the above installation is still required. More on the different build options below. 

The other tool necessary will be `make` which can be installe via [Chocolatey](https://chocolatey.org/):
```bash
choco install make
```

## 3. Patching the target ROM
You will need to patch the ROM (md5: 49f7bb346ade39d1915c22e090ffd748) before running the recompiler.

This can be done by using the `tools/recomp_rom_patcher.py` script found in the [Dinosaur Planet Decompilation repository](https://github.com/zestydevy/dinosaur-planet). You can either clone the repository or use the submodule provided by this repository at `lib/dinosaur-planet`.

> [!IMPORTANT]
> The Python dependency `capstone` must be installed to run this script.

For example, using the decomp submodule, run:
```bash
python3 ./lib/dinosaur-planet/tools/recomp_rom_patcher.py -o baserom.patched.z64 baserom.z64
```

Once done, place the patched ROM in the root of this repository and rename it to `baserom.patched.z64` if necessary.

## 4. Generating the C code

Now that you have the required files, you must build [N64Recomp](https://github.com/Mr-Wiseguy/N64Recomp) and run it to generate the C code to be compiled. The building instructions can be found [here](https://github.com/Mr-Wiseguy/N64Recomp?tab=readme-ov-file#building). That will build the executables: `N64Recomp` and `RSPRecomp` which you should copy to the root of this repository.

After that, go back to the repository root, and run the following commands:
```bash
./N64Recomp dino.toml
./RSPRecomp aspMain.toml
```

## 5. Building the Project

This project uses CMake for builds. There's a few ways to run this depending on your preferences.

### Visual Studio (recommended)

Open the repository as a folder with Visual Studio. In the top toolbar, select `DinoRecomp` as the target. You can now simply build and debug like normal.

Builds will be output to `out/build/x64-[Configuration]`.

### Visual Studio Code

The extensions [ms-vscode.cpptools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) and [ms-vscode.cmake-tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) are needed to build/debug in Visual Studio Code.

1. Add `"cmake.generator": "Ninja"` to your workspace configuration.
2. (**Windows Only**) Make sure your local CMake Kits contain a kit for "Clang (MSVC CLI)". One of these kits must be used to ensure `clang-cl` on Windows is ran with the correct Visual C++ environment. See https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/kits.md for more information.
3. In the CMake tab, under Configure, select Clang as the compiler (must be Clang (MSVC CLI) on Windows).
4. If the CMake extension automatically created a build folder, you may need to delete it and re-configure to ensure Ninja is being used as the generator.
5. In the CMake tab, under Build (and Debug/Launch), set the build target to `DinoRecomp`.
6. Using the CMake extension, you now should be able to build and debug the project!

If you prefer to debug using a `launch.json` file, see https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/debug-launch.md for information on how to set up a launch configuration for the CMake extension.

You also likely want to configure the `.vscode/c_cpp_properties.json` file if the extension didn't do so for you. 

Builds will be output to `build`.

### CLI

If you prefer the command line you can build the project using CMake:

```bash
cmake -S . -B build-cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang -G Ninja -DCMAKE_BUILD_TYPE=Release # or Debug if you want to debug
cmake --build build-cmake --target DinoRecomp -j$(nproc) --config Release # or Debug
```

Builds will be output to `build-cmake`.

## 6. Success

Voilà! You should now have a `DinoRecomp` executable in the build directory! You will need to run the executable out of the root folder of this project or copy the assets folder to the build folder to run it.

> [!IMPORTANT]  
> In the game itself, you should be using a standard ROM, not the patched one.
