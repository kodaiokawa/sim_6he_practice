# sim_6he_practice
(simulation practice of 6he experiment as my first project)

This program performs Monte Carlo simulations of two-body nuclear reactions. Elastic scattering is calculated by considering the main beam and up to one background beam as the incident beam and the main component and up to one background component as the target.
The inelastic scattering you want to study can be calculated simultaneously with the elastic scattering by entering the angular dependence of the reaction cross section of the CM system in the file.

Please note that some of the calculations are still not working.

## Assumption
* I assume that the size of Si detector is 5.0 cm x 5.0 cm and it has 16 strips in X and Y axis
* The beam and the center axis of the detector are aligned
* The program can consider two particle beam and two particle target if the cross section data is available
* The coordinates are set to (0,0,0) at the center of target, and the direction of z was in the direction of the beam
* All beams are assumed to be parallel

preparing...

## algorithm
1. generate the beam
   1. Using random numbers to determine the type of particles
   2. I assume that the beam spread is according to the Gaussian with sigma=1.0
2. judge whether reaction is occur or not

preparing...

## Problems
1. The position (depth) where the particle stops in the sample is assumed to be uniform
2. I don't consider beam bending (deflection?) in the target
3. Initial energy of the beam (MeV/u) is fixed (but it is possible to give fluctuation in main.cpp)

## Usage
This program requires **cmake** and **root** to be installed.
If you use MacOS and brew installed, it is easy to install.
```console
brew cmake
brew root
```
Next, prease make build directory and run **cmake** in this directory.
```console
mkdir build
cd build
cmake ..
```
if you get some error, I think it is necessary to edit the CMakeLists.txt or the installation of cmake(root) is not working.

### Change the parameter
In this program, you should edit four files to change the parameter
* ./condition/input.txt
* ./lib/source/mass.cpp
* ./database/cross_section/-----.txt
* ./main.cpp

In **input.txt**, you can change the experiment parameters.
And **mass.cpp**, you can input information of beam and target particle.
lastly, **-----.txt**, you should make textfile of the cross section of the inelastic scattering from other reference. 
After that, the name of created textfile is needed to write in **main.cpp**.

In the current version, the calculation of energy loss is ambiguous.
So, the **./database/energyloss** directory is not used in this version.


When you changed the parameter, type below command in the **./build** directory
``` console
make
```
after that, I think the **a.out** file is created (in MacOS case?), so the program can be done by
```console
./a.out
```
if you have some error, please check that the directory is **./build** when the command is typed.
After that, **./simulation.root** is created, so you can use it to analyse.

## Root file
preparering...


## Reference
* [MASS OF NUCLEI](http://amdc.impcas.ac.cn/index.html)
* [kinematics (in Japanese)](http://lambda.phys.tohoku.ac.jp/~miwa9/monte_carlo/kinematics.pdf)
