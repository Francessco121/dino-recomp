#!/bin/sh
make -C ../../patches CC=clang LD=ld.lld
flatpak-builder --force-clean --user --install-deps-from=flathub --repo=repo builddir io.github.dinosaurplanetrecomp.dino_recomp.yml
flatpak build-bundle repo io.github.dinosaurplanetrecomp.dino_recomp.flatpak io.github.dinosaurplanetrecomp.dino_recomp --runtime-repo=https://flathub.org/repo/flathub.flatpakrepo
# Uncomment to bundle the debug extension
# flatpak build-bundle repo io.github.dinosaurplanetrecomp.dino_recomp.Debug.flatpak io.github.dinosaurplanetrecomp.dino_recomp.Debug --runtime-repo=https://flathub.org/repo/flathub.flatpakrepo --runtime
