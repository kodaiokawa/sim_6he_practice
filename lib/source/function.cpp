#include <iostream>
#include <random>
using namespace std;

void test() {
    cout << "This is a sample." << endl;
}

void print_cond(double input[]) {
    cout << endl;
    cout << "***** initial condition *****" << endl;
    cout << "experiment time  : " << input[0] << " s" << endl;
    cout << "beam intensity : " << input[1] << " pps" << endl;
    cout << "6He purity : " << input[2] * 100.0 << " %" << endl;
    cout << "target(C2H4) thickness : " << input[3] << " mg/cm2" << endl;
    cout << "target density : " << input[4] << " atoms/cm2" << endl;
    cout << "size of detector : " << input[5] << " x " << input[6] << " cm2" << endl;
    cout << "detector angle : " << input[7] << " deg" << endl;
    cout << "*****************************" << endl;
    cout << endl;
}

double generate_standard() {
    random_device rnd; 
    static mt19937 mt(rnd());
    uniform_real_distribution<double> get_rand_uni_real(0.0, 1.0);
    return get_rand_uni_real(mt);

}
