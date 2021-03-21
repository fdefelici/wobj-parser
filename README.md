# Wavefront Obj Parser
A simple parser for Wavefront Obj in C.

# Usage
Just include [wobj.h](./wobj.h) in your project and load obj models like this:

```c
wobj* obj = wobj_from_file("resources/quad.obj");
```

then access obj data reading individually obj components such as vertex position, normals, texture coordinates or read then in form of triangles

> Look at the [unit tests](./tests) for usage insight 

# Development
* C11 compliant
* Unit Test written using [clove](https://github.com/fdefelici/clove) library
* Project managed with [cmake](https://cmake.org/)
