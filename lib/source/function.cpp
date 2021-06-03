#include"../include/function.h"
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;



void test() 
{
    cout << "This is a sample." << endl;
}

double generate_standard() 
{
    random_device rnd; 
    static mt19937 mt(rnd());
    uniform_real_distribution<double> get_rand_uni_real(0.0, 1.0);
    return get_rand_uni_real(mt);
}

double generate_normal(double mu, double sigma) //Box–Muller's method
{
    double value;
    double alpha = generate_standard();
    double beta = generate_standard();
    value = sqrt(-1.0*log(alpha*alpha))*sin(2*M_PI*beta);
    return value*sigma + mu;
}

double all_cross_section_6he_p()
{
    return 0.0;
}

double all_cross_section_6he_12c()
{
    return 0.0;
}

double all_cross_section_3h_p()
{
    return 0.0;
}

double all_cross_section_3h_12c()
{
    return 0.0;
}

