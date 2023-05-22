# BlendURMap

## Introduction

This project developped by EPITA' students in S4 (4th semester).

## Dependences

The project needs gcc, SDL2 and SDL2_image, libmaths and the C language (standard libraries)
You must install the font present in UI/fonts/ folder

## Build

You can build the program using the given Makefile for the command-line execution. To do so, go to `./Generation/` and compile the project using `make -j`. Once it's compiled, launch the program using the `./main` program.

`./main -h` To see all available options

`./main -simplex` Generate a simplex noise in 1920x1080

`./main -perlin` Generate a perlin noise in 1920x1080

`./main -diamond_square` Generate a diamond square noise in 1920x1080

`./main -map` Generate a map in 1920x1080

`./main -perso` Generate an personnalized map

For the GUI usage, the program can be compiled in `./UI/` using `make -j`, and then executing the `./BlendURMap` program. When launched you will be able to modify the options for generation (part of them are still WIP) and also preview the 2D and 3D model using `feh` and `f3d` (you can install feh via your package manager and f3d can be found here https://f3d.app/).


## Authors

thomas.marmaroli (@Brome78)

florent.marechaux (@Florent)

antoine.thomas (@GRADUSKA)

alexandre.leclaire (@Alexandre-Leclaire)
