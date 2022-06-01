# internal
A Geometry Dash Internal Cheat written in C++.

Contains a basic [SDK](https://github.com/reservedcloud/gd-internal/src/sdk/sdk.cpp) that interracts with game's variables, basic cheats, ImGui, unloading procedure.

The font used in the "custom" ImGui is [Comfortaa](https://www.dafont.com/comfortaa.font) and it's loaded into memory from [menu.cpp](https://github.com/reservedcloud/gd-internal/src/menu.cpp). Addons created by me for the UI can be found in [plugin.cpp](https://github.com/reservedcloud/gd-internal/src/hook/plugin.cpp)

Signatures are stored in [hookmgr.cpp](https://github.com/reservedcloud/gd-internal/src/hookmgr.cpp) (even tho, the developer won't probably update the game ever again).

# Spoiler
The cheat doesn't contain 100% internal procedures, more than 90% of the features are based on bytepatching opcodes.
The code that contains the bytepatching is not very clean as I couldn't think of something better at the moment.

# Compile
The solution and the minhook library are targeted to build on Visual Studio 2015, you can change that by downloading another version of minhook and by changing the solution settings.

Visual Studio's compiler likes to have fun with my projects, so that, when you build it you'll get linker errors.

To fix that I'm compiling the cheat once, then removing something, save changes, revert the changes and then compile again: https://youtu.be/DyBY5jIbkno


Cheat Showcase: https://youtu.be/lkCvsAqtocw

![image](https://user-images.githubusercontent.com/68382500/171502185-f41b2084-0dd2-4b4f-9ea2-60de5285879d.png)
