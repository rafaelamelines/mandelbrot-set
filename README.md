# Mandelbrot Set
Performant rendering of the Mandelbrot Set using OpenGL.

## Controls
Scroll to zoom, click and drag to pan.

## Building
If you want to build the app yourself, you can use CMake.
```
mkdir build
cd build
cmake ..
```

## Dependencies
- OpenGL 3.3
- GLFW 3.4 (Included as a submodule)
- Glad (Included in the `vendor` directory)
- stb_image (Included in the `vendor` directory)