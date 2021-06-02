#include"../include/function.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;



void test() 
{
    cout << "This is a sample." << endl;
}

double generate_standard() {
    random_device rnd; 
    static mt19937 mt(rnd());
    uniform_real_distribution<double> get_rand_uni_real(0.0, 1.0);
    return get_rand_uni_real(mt);
}

