Before building the Flatpak, you must build the patches on the root directory first. **The LLVM Extension for freedesktop does not include the MIPS compiler and will fail to build the patches inside the flatpak**.
```sh
make -C patches CC=clang LD=ld.lld
```

Build
```sh
flatpak-builder --force-clean --user --install-deps-from=flathub --repo=repo --install builddir io.github.francessco121.dino_recomp.yml
```

Bundle
```sh
flatpak build-bundle repo io.github.francessco121.dino_recomp.flatpak io.github.francessco121.dino_recomp --runtime-repo=https://flathub.org/repo/flathub.flatpakrepo
```

