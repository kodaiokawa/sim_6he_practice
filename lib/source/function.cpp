#include"../include/function.h"
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

const double STANDARD::HBAR_C = 197.327; //MeV fm
const double STANDARD::ALPHA = 1.0 / 137.036;

//unit of mass : MeV/c2
const double MASS::MASS_6HE = 6018885.889 * 1.0e-6 * 931.494013;
const double MASS::MASS_3H = 3016049.28132 * 1.0e-6 * 931.494013;
const double MASS::MASS_p = 1007825.031898 * 1.0e-6 * 931.494013;
const double MASS::MASS_12C = 12000000.0 * 1.0e-6 * 931.494013;

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

double cm_energy(double energy, int reaction) //particle 1=6He+p, 2=6He+12C, 3=3H+p, 4=3H+12C
{
    double mass_projectile;
    double mass_target;
    double E1;
    if(reaction == 1){
        mass_projectile = MASS::MASS_6HE;
        mass_target = MASS::MASS_p;
        E1 = energy*6.0 + mass_projectile;
    }else if(reaction == 2){
        mass_projectile = MASS::MASS_6HE;
        mass_target = MASS::MASS_12C;
        E1 = energy*6.0 + mass_projectile;
    }else if(reaction == 3){
        mass_projectile = MASS::MASS_3H;
        mass_target = MASS::MASS_p;
        E1 = energy*3.0 + mass_projectile;
    }else if(reaction == 4){
        mass_projectile = MASS::MASS_3H;
        mass_target = MASS::MASS_12C;
        E1 = energy*3.0 + mass_projectile;
    }else{
        cout << "ERROR" << endl;
        exit(1);
    }

    double E2 = 0.0 + mass_target; // MeV energy in LAB system
    double p1 = sqrt((E1)*(E1)-(mass_projectile)*(mass_projectile));
    double p2 = sqrt((E2)*(E2)-(mass_target)*(mass_target));
    double beta = (p1 + p2)/(E1 + E2);
    double gamma = 1.0/sqrt(1.0 - beta * beta);
    double E1_CM = gamma * E1 - beta * gamma * p1;
    double E2_CM = gamma * E2 - beta * gamma * p2;

    return (E1_CM + E2_CM) - (mass_projectile + mass_target);
}

double elastic_cross_section(double energy, int reaction) //cm2
{
    double E = cm_energy(energy, reaction);
    double value = 0.0;
    double factor = ((STANDARD::ALPHA*STANDARD::HBAR_C*1.0e-13) / (4.0*E) )*((STANDARD::ALPHA*STANDARD::HBAR_C*1.0e-13) / (4.0*E) );
    if(reaction == 1){
        factor *= (2.0 * 1.0) * (2.0 * 1.0);
    }else if(reaction == 2){
        factor *= (2.0 * 6.0) * (2.0 * 6.0);
    }else if(reaction == 3){
        factor *= (1.0 * 1.0) * (1.0 * 1.0);
    }else if(reaction == 4){
        factor *= (1.0 * 6.0) * (1.0 * 6.0);
    }else{
        cout << "ERROR" << endl;
        exit(1);
    }

    double del_angle = 0.1;
    double del_rad_angle = del_angle * M_PI / 180.0;
    for(double angle=1.0; angle<180.0; angle+=del_angle){
        double rad_angle = angle * M_PI / 180.0;
        value += (sin(rad_angle)/pow(sin(rad_angle/2.0), 4.0)) * del_rad_angle;
        //cout << angle << " : " << (1.0/pow(sin(rad_angle/2.0), 4.0)) * factor * 1e+27<< endl;
    }
    value *= factor * 2.0 * M_PI;
    return value;
}


double generate_cm_angle_elastic()
{
    double norm = 0.0;

    double del_angle = 0.1;
    double del_rad_angle = del_angle * M_PI / 180.0;
    for(double angle=1.0; angle<180.0; angle+=del_angle){
        double rad_angle = angle * M_PI / 180.0;
        norm += (sin(rad_angle)/pow(sin(rad_angle/2.0), 4.0)) * del_rad_angle;
    }

    double uni = generate_standard();
    double tmp = 0.0;
    double cm_angle;
    for(double angle=1.0; angle<180.0; angle+=del_angle){
        double rad_angle = angle * M_PI / 180.0;
        tmp += (sin(rad_angle)/pow(sin(rad_angle/2.0), 4.0)) * del_rad_angle / norm;
        if(tmp > uni){
            cm_angle = angle;
            break;
        }
    }
    return cm_angle;
}


