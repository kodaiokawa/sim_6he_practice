# sim_6he_practice
simulation practice of 6he experiment as my first project

## Assumption
* I assume that the size of Si detector is 5.0 cm x 5.0 cm and it has 16 strips in X and Y axis
* The beam and the center axis of the detector are aligned
* The program can consider two particle beam and two particle target if the cross section data is available
* The coordinates are set to (0,0,0) at the center of target, and the direction of z was in the direction of the beam
* All beams are assumed to be parallel

## algorithm
1. generate the beam
   1. Using random numbers to determine the type of particles
   2. I assume that the beam spread is according to the Gaussian with sigma=1.0
2. judge whether reaction is occur or not

prepareing...

## Usage
if you edit the CMakeLists.txt, prease command in /build directory
```console
cmake ..
```
and you edit some file, type
``` console
make
```
after that, I think the /build/a.out file is created, so the program can be done by
```console
./a.out
```
> the condition file is written in relative path, so please execute this command in /build directory

## root file
preparering...
