#!/bin/sh
cd src
clang -Wall -Wextra -O2 --target=wasm32 --no-standard-libraries -Wl,--export-all -Wl,--no-entry -Wl,--allow-undefined -Wno-incompatible-library-redeclaration -fuse-ld=ld -o main.wasm main.c