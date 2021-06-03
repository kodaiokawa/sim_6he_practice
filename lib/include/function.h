#pragma once

#include<string>

using namespace std;




void test();
double generate_standard();
double generate_normal(double mu, double sigma);
double all_cross_section_6he_p();
double all_cross_section_6he_12c();
double all_cross_section_3h_p();
double all_cross_section_3h_12c();
double depth_scatter(int particle, int target); //target 1=p, 2=12C
double energyloss_target(int particle, int target);
double struggling_target(int particle, int target, double depth);
