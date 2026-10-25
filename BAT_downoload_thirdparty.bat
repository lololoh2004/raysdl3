@echo off
chcp 65001 > nul


echo Cloning cGLM headers
git clone --depth 1 https://github.com/recp/cglm "lib/cglm"


echo Cloning SDL headers
git clone --depth 1 https://github.com/libsdl-org/SDL "lib/SDL3"
git clone --depth 1 https://github.com/libsdl-org/SDL_shadercross "lib/SDL3_shadercross"


echo Cloning my binary builds
set "SDL_VER=1.1"

curl -L -O "https://github.com/lololoh2004/sdl3_bin/releases/download/%SDL_VER%/win_x64.tar.gz"
curl -L -O "https://github.com/lololoh2004/sdl3_bin/releases/download/%SDL_VER%/lin_x64.tar.gz"

mkdir temp_bin

tar -xf win_x64.tar.gz -C temp_bin
tar -xf lin_x64.tar.gz -C temp_bin

move /y "temp_bin\win_x64\SDL3.dll" "."
move /y "temp_bin\win_x64\SDL3_shadercross.dll" "."
move /y "temp_bin\win_x64\SPIRV_cross.dll" "."
move /y "temp_bin\win_x64\libSDL3.dll.a" "."
move /y "temp_bin\win_x64\libSDL3_shadercross.dll.a" "."

rmdir /s /q temp_bin
del win_x64.tar.gz
del lin_x64.tar.gz


pause