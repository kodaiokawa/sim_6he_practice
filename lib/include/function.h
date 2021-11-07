#pragma once

#include<string>

using namespace std;


extern const double hbar_c;
extern const double alpha_const;
extern const double to_rad;
extern const double to_deg;
extern const double c_const;

void test();

double generate_standard();
double generate_normal(double mu, double sigma);

double cm_energy(double energy, int reaction);
double elastic_cross_section(double energy, int reaction); //cm2
double generate_cm_angle_elastic();

double list_cross_section(string datafile);
double generate_cm_angle_list(string datafile);



