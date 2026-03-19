# Mandelbrot Set
[![Linux](https://github.com/rafaelamelines/mandelbrot-set/actions/workflows/linux.yml/badge.svg)](https://github.com/rafaelamelines/mandelbrot-set/actions/workflows/linux.yml)
[![MacOS](https://github.com/rafaelamelines/mandelbrot-set/actions/workflows/macos.yml/badge.svg)](https://github.com/rafaelamelines/mandelbrot-set/actions/workflows/macos.yml)
[![Windows](https://github.com/rafaelamelines/mandelbrot-set/actions/workflows/windows.yml/badge.svg)](https://github.com/rafaelamelines/mandelbrot-set/actions/workflows/windows.yml)

Performant rendering of Mandelbrot and Julia sets using OpenGL.

<img width="1448" height="1048" alt="mandelbrot" src="https://github.com/user-attachments/assets/aa600476-5698-449c-8bdb-615a13247abf" />

## Controls
Scroll to zoom, click and drag to pan, right click to view the Julia set for a particular point.

## Building
If you want to build the app yourself, you can use CMake. Make sure you do a recursive clone, as some of the dependencies are included as submodules.
```
mkdir build
cd build
cmake ..
```

## Dependencies
- OpenGL 3.3
- GLFW 3.4 (Included as a submodule)
- Dear ImGui 1.92.5 (Included as a submodule)
- glad (Included in the `vendor` directory)
- stb_image (Included in the `vendor` directory)
