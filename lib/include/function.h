#pragma once

#include<string>

using namespace std;

struct STANDARD
{
  static const double HBAR_C;
  static const double ALPHA;
};

struct MASS
{
  static const double MASS_6HE;
  static const double MASS_3H;
  static const double MASS_p;
  static const double MASS_12C;
};

void test();

double generate_standard();
double generate_normal(double mu, double sigma);

double cm_energy(double energy, int reaction);
double all_cross_section(double energy, int reaction); //cm2


double depth_scatter(int particle, int target); //target 1=p, 2=12C
double energyloss_target(int particle, int target);
double struggling_target(int particle, int target, double depth);
