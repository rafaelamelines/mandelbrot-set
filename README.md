# Mandelbrot Set
Performant rendering of the Mandelbrot Set using OpenGL.

<img width="1448" height="1048" alt="mandelbrot" src="https://github.com/user-attachments/assets/aa600476-5698-449c-8bdb-615a13247abf" />

## Controls
Scroll to zoom, click and drag to pan.

## Building
If you want to build the app yourself, you can use CMake. Make sure you do a recursive clone.
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
