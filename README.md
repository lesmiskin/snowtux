# "Easy 3D Engine" by Les Miskin
An easy-to-understand 3D game engine, for learning and experimenting. Forking and hacking the code for your own project is encouraged :)

# Installation
1. Download two files from https://www.libsdl.org/download-2.0.php:
    - Runtime Binaries (for 32-bit Windows)
    - Development Libraries (for Windows and Visual C++)
2. Download GLEW from http://glew.sourceforge.net/
3. From the Runtime Binaries file, extract the `SDL2.0.DLL` file to your `C:\Windows` directory.
4. Extract the Development Libraries file to `C:\SDK` (e.g. `C:\SDK\SDL2-2.0.9`).
5. Extract the GLEW file to `C:\SDK` (e.g. `C:\SDK\glew-2.1.0`).

# Technical notes
* For simplicity we standardise on 32-bit for the build, and third-party libraries.
* As a starting point, we use the (now deprecated) Fixed Function Pipeline approach for OpenGL. We will move to the modern shader-driven approach as time permits.

# Contributor guidelines

## Coding style
* Emphasise "straightforward" code: brevity with clear names.
* Judicious comments (be aware they add cognitive overhead).
