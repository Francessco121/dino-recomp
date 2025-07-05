#!/bin/sh
make -C ../patches CC=clang LD=ld.lld
flatpak-builder --force-clean --user --install-deps-from=flathub --repo=repo --install builddir io.github.francessco121.dino_recomp.yml
flatpak build-bundle repo io.github.francessco121.dino_recomp.flatpak io.github.francessco121.dino_recomp --runtime-repo=https://flathub.org/repo/flathub.flatpakrepo
