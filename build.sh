#!/bin/sh
cd src
clang -Wall -Wextra -O2 --target=wasm32 --no-standard-libraries -Wl,--export-all -Wl,--no-entry -Wl,--allow-undefined -fuse-ld=ld -o main.wasm main.c