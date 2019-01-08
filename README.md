# "Easy 3D Engine" by Les Miskin
An easy-to-understand 3D game engine, for **learning and experimenting**. Forking and hacking the code for your own project is also encouraged :)

<img src="docs/screenshot.png" width="50%">

# Getting Started
To compile and run the engine, you must have a compatible development environment and a few supporting libraries installed.

**Note: These instructions are only applicable for Windows computers**

1. Clone or download the `easy-3d-engine` repository to a location on your computer.
2. If you don't already have it, download and install [Visual Studio Community Edition](https://visualstudio.microsoft.com).
3. Download the [SDL support files](https://www.libsdl.org/download-2.0.php):
    - Under `Runtime Binaries : Windows`, click the `32-bit Windows` link.
    - Under `Development Libraries : Windows`, click the `Visual C++ 32/64-bit` link.
4. Download the [GLEW support file](http://glew.sourceforge.net/)
    - Under `Downloads : Binaries`, click the `Windows 32-bit and 64-bit` link.
5. Extract the `Runtime Binaries` file into `C:\Windows`.
6. Extract the `Development Libraries` file into `C:\SDK`.
7. Extract the `GLEW` file into `C:\SDK`.

You are now ready to run the engine from your development environment.

# Running the engine
1. Open the `easy-3d-engine.sln` file from the `easy-3d-engine` repository folder on your computer.
2. Once the solution has loaded in Visual Studio, start the program by clicking on the `Debug` menu, then `Start Without Debugging` (you can also use the keyboard shortcut `CTRL`+`F5`).
3. Use the arrow keys to move the camera around, or press `ESC` to quit.

# Technical notes
* For simplicity we standardise on 32-bit for the build, and third-party libraries.
* As a starting point, we use the (now deprecated) Fixed Function Pipeline approach for OpenGL. We will move to the modern shader-driven approach as time permits.

# Contributor guidelines

## Coding style
* Emphasise "straightforward" code: brevity with clear names.
* Judicious comments (be aware they add cognitive overhead).
