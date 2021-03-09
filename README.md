# PHSX815 Spring 2021 Week 5

## Rejection Sampling

This repository contains the following programs:
- `HW5/SinSim.x` : generates and visualizes a distribution according to the target
function (sin(x)) and the user's choice of three different proposal functions
then visualizes the results. [C++]
- `HW6/Integrate.x`: numerically integrates a fixed function and outputs relevant
results such as the comparison of values and errors of different methods
according to user input. [C++]

### Requirements

In order to compile and run `SinSim.x` (by typing `make`), you
need the ROOT package installed (for visualization):
- [ROOT](https://root.cern/) [C++]

Aside from a compiler and GNU make, `Integrate` has no excluded dependencies. [C++]

### Usage

All of the executables can be called from the command line with the `-h` or
`--help` flag, which will print the options.
