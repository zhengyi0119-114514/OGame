# OpenGame

这是一个拥有远大理想的项目，致力于打造一个可扩展，灵活的游戏引擎，  
目前深耕于STG类型

## 配置开发环境

### ArchLinux / Manjaro

本项目严重依赖C11的SafeCLib,但AUR的**aur/libsafec 1:3.7.1-1**无法使用,所以请自行安装:  
[LibSafeC](https://github.com/rurban/safeclib)
(妈的这库的.pc文件安装位置不规范，害得我找了老半天)

``` bash
sudo pacman -S gtest qt6 boost lua
```

SDL3 :**若要添加测试性的SDL3支持，请安装包 sdl3_image(AUR),sdl3_ttf(AUR),sdl3**

``` bash
sudo pacman -S sdl3
yay -S sdl3_image sdl3_ttf
```

### OpenSUSE Tumbleweed

本项目严重依赖C11的SafeCLib,无法在官方仓库找到,所以请自行安装:  
[LibSafeC on Build Service](https://build.opensuse.org/package/show/home:PerryWerneck/libsafec)

```bash
sudo zypper install sdl2-compat-devel SDL2_image-devel SDL2_mixer-devel gtest qt6-base-common-devel lua boost-devel
```

SDL3 : OpenSUSE Tumbleweed对新的SDL3及其附加组建支持良好  
**要不是OpenSUSE的中文支持（尤其是输入法）跟狗屎一样，我可能就要离开Arch的怀抱了**

```bash
sudo zypper install SDL3-devel SDL3_image-devel SDL3_ttf-devel
```

## 开发小记

英文不好，注释先用中文了

:**MD，GTK3贼TM复杂，不干了**
