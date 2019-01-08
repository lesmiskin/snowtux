**IMPORTANT:** This project is currently a *work-in-progress*, and certain files will not be of final quality in terms of content and structure. Please keep this in mind when examining the source code.

---

# Introduction
An easy-to-understand 3D game engine, for *learning and experimenting*. Forking and hacking the code for your own project is also encouraged :)

<img src="docs/screenshot.png" width="50%">

**Note:** The engine is currently only buildable on Windows systems.

# Getting Started

1. Install [Visual Studio Community Edition](https://visualstudio.microsoft.com)
    - Remember to toggle the `Desktop development with C++` feature.
2. Download the following files fom the [SDL web site](https://www.libsdl.org/download-2.0.php):
    - Under `Runtime Binaries : Windows`, click the `32-bit Windows` link.
    - Under `Development Libraries : Windows`, click the `Visual C++ 32/64-bit` link.
3. Download the following file from the [GLEW web site](http://glew.sourceforge.net/):
    - Under `Downloads : Binaries`, click the `Windows 32-bit and 64-bit` link.
4. Extract the downloaded files as follows:
    - Extract the `SDL2.DLL` file from `Runtime Binaries` to `C:\Windows`.
    - Extract `Development Libraries` to `C:\SDK`.
    - Extract `GLEW` to `C:\SDK`.
7. Open the `easy-3d-engine.sln` solution file (assuming you have already downloaded / cloned this repo).
8. From Visual Studio, start the engine by clicking on the `Debug` menu, then `Start Without Debugging`.
9. Once the engine has started, use the arrow keys to move the camera around, and press `ESC` to quit.

# Technical notes
* For simplicity we standardise on 32-bit for the build, and third-party libraries.
* As a starting point, we use the (now deprecated) Fixed Function Pipeline approach for OpenGL. We will move to the modern shader-driven approach as time permits.
