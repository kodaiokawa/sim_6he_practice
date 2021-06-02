#pragma once

#include<string>

using namespace std;




void test();
//void print_cond(double input[]);
double generate_standard();
double depth_scatter(int particle, int target); //target 1=p, 2=12C
double energyloss_target(int particle, int target);
double struggling_target(int particle, int target, double depth);
