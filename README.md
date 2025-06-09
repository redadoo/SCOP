# SCOP

![GitHub repo size](https://img.shields.io/github/repo-size/redadoo/scop)
![GitHub contributors](https://img.shields.io/github/contributors/redadoo/scop)
![GitHub stars](https://img.shields.io/github/stars/redadoo/scop?style=social)
![GitHub forks](https://img.shields.io/github/forks/redadoo/scop?style=social)

## Table of Contents

* [About](#about)
* [Project Requirements](#project-requirements)
* [Technical Constraints](#technical-constraints)
* [Usage](#usage)
* [Resources](#resources)

## About

This project is part of the 42 curriculum and was developed as an introduction to GPU-based 3D rendering using OpenGL or other GPU APIs.

The goal is to create a simple rendering engine capable of displaying and rotating a 3D object from a `.obj` file, rendered in perspective with basic interaction.

Read the [Subject](./en.subject.pdf) for more information.

## Project Requirements

* Display a 3D object from a `.obj` file in a perspective window.
* Object must rotate around its axis of symmetry.
* Colored faces to distinguish object sides.
* Controls to move the object along all 3 axes.

## Technical Constraints

* Language: C++
* API: Vulkan
* No libraries are allowed for loading the 3D object, creating matrices, or loading shaders
* Allowed: external libraries only for window & event management
* Makefile required

## Usage

To build the project:

```bash
make
```

To build and run the project:

```bash
make run
```
## Resources

* [GLFW](https://www.glfw.org/)
* [Vulkan Tutorial](https://vulkan-tutorial.com/Introduction)
* [matrices](https://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/)
