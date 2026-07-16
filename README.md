# OpenGame

这是一个拥有远大理想的项目，致力于打造一个可扩展，(山里)灵活的游戏引擎，  
目前深耕于STG类型
    by IceThorn ~~BakaTechnology~~

## 项目目标

由于个人的极强的类Suckless的理念追求和强烈的对兼容性的向往（以及对AI的强烈不信任），这个项目将会被打造成一个  
个人维护的大型项目。追求极致的内存安全，内存低消耗，性能高~~糕~~，不依赖标准C++组件（为以后的C++组件预留位置  
，以同时满足对多种标准C++库同时同等级支持做准备）。  

### 子项目

~~(总有几个会烂尾的，放心)~~

> OpenStg  
> OpenStg.Base  
> OpenStg.Graphics              (With SDL3)  
> OpenStg.Logic  
> OpenStg.Network               (Native)  
> OpenStg.DevelopTools  
> OpenStg.DevelopTools.Compiler (With Clang and LLVM)  
> OpenStg.RustBinding.Base  
> OpenStg.RustBinding.Graphics  
> OpenStg.RustBinding.Logic  
> OpenStg.RustBinding.Network  
> OpenStg.DotnetBinding.Base  
> OpenStg.DotnetBinding.Graphics  
> OpenStg.DotnetBinding.Logic  
> OpenStg.DotnetBinding.Network  
> OpenStg.ZigBinding.Base       (Laest,脱离zig标准库)  
> OpenStg.ZigBinding.Graphics  
> OpenStg.ZigBinding.Logic  
> OpenStg.ZigBinding.Network  
> OpenStgPlusPlus               (C++ 20)  
> OpenStgPlusPlus.Base  
> OpenStgPlusPlus.Graphics  
> OpenStgPlusPlus.Logic  
> OpenStgPlusPlus.Network  

## ~~获奖感言~~

你将会面对的是：  

- ~~一大坨屎山~~
  - ~~毫无意义的宏定义~~
  - ~~单纯反人类的代码风格~~
  - ~~无处不在的梗~~
  - ~~追求极端鲁棒性的神仙设计~~
  - ~~比你的生命周期都长的CMakeLists.txt~~
  - ~~神奇的理论兼容性~~
- ~~反复横跳的程序设计~~

## 配置开发环境

### ~~成为**BAKA**~~

~~大喊“我要获得琪露诺的智慧！”~~  
~~然后静待当前Linux发行版官方更新~~

### 使用**VCPKG**

[棺方文档](https://learn.microsoft.com/vcpkg/get_started/get-started)  
确保PATH环境变量中存在vcpkg(.exe)以及VCPKG_ROOT环境变量被正确设置即可开罐即食  
~~我不能保证你要等多久~~  
如果你在中国大陆地区不开(反向)代理的话还是算了

### ArchLinux / Manjaro / Archlinux(WSL)

``` bash
sudo pacman -S icu lua catch2 libxml2 libbsd cjson popt mongo-c-driver pcre2
# optional
sudo pacman -S vulkan-devel libc++ libc++abi gtk4 
# optional (client)
sudo pacman -S sdl3 sdl3_{image,ttf,mixer} 
```

### Windows-MSYS2

推荐使用CLANG64/UCRT64环境,此处以CLANG64环境为例

``` bash
pacman -S mingw-w64-clang-x86_64-{icu,lua,mcfgthread{,-libs},sdl3,libxml2,cjson,pcre2}
pacman -S mingw-w64-clang-x86_64-{catch,mongo-c-driver}
# optional
pacman -S mingw-w64-clang-x86_64-{vulkan-devel,gtk4,libdwarf}
# optional (client)
pacman -S mingw-w64-clang-x86_64-{sdl3{,-{image,ttf,mixer}}}
```

## 待定目标

> Stg基础功能  
> 使用Lua对项目进行拓展  
> ~~自由地拉屎~~  
> 制作一个三段式简易长矛
> 出去玩，出去玩。  
> 何意味
