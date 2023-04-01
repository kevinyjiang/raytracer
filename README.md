# raytracer
C++ raytracer implementation based on [Peter Shirley's books](https://raytracing.github.io/) and [Michael Reed's graphics course](http://www.cs.columbia.edu/~cs4160/).

## progress so far:
- recursive ray tracing capable of diffuse shading, metal reflection, refraction, motion blur, defocus blur
- optimized with BVH tree algorithm (bounding volume hierarchy) 
- basic anti-aliasing

## sample images:

![asdi](https://user-images.githubusercontent.com/24910768/177608805-b732432a-cc7e-439f-9417-be92d098376d.png)

![i23](https://user-images.githubusercontent.com/24910768/177240571-66356455-d02c-4e9e-be8d-e97b363d3126.png)

## todo:
- parser for scene text files, so we don't have to hardcode every object we want to render
- texture maps
- point/area lighting
- better output functionality, support PNG or JPG
- more sophisticated utility functions for procedurally generating scenes
