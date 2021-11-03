#include"../include/function.h"
#include"../include/mass.h"
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

using namespace std;


const double hbar_c = 197.327; //MeV fm
const double alpha_const = 1.0 / 137.036;
const double to_rad = M_PI / 180.0;
const double to_deg = 180.0 / M_PI;


void test() 
{
    cout << "This is a test function." << endl;
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
        mass_projectile = main_beam->mass;
        mass_target = main_target->mass;
        E1 = energy*main_beam->num + mass_projectile;
    }else if(reaction == 2){
        mass_projectile = main_beam->mass;
        mass_target = sub_target->mass;
        E1 = energy*main_beam->num + mass_projectile;
    }else if(reaction == 3){
        mass_projectile = sub_beam->mass;
        mass_target = main_target->mass;
        E1 = energy*sub_beam->num + mass_projectile;
    }else if(reaction == 4){
        mass_projectile = sub_beam->mass;
        mass_target = sub_target->mass;
        E1 = energy*sub_beam->num + mass_projectile;
    }else{
        cout << "ERROR : reaction problem (incorrect reaction_flag)" << endl;
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
    double factor = ((alpha_const * hbar_c * 1.0e-13) / (4.0*E) )*((alpha_const *  hbar_c * 1.0e-13) / (4.0*E) );
    if(reaction == 1){
        factor *= pow(main_beam->num_z + main_target->num_z, 2.0);
    }else if(reaction == 2){
        factor *= pow(main_beam->num_z + sub_target->num_z, 2.0);
    }else if(reaction == 3){
        factor *= pow(sub_beam->num_z + main_target->num_z, 2.0);
    }else if(reaction == 4){
        factor *= pow(sub_beam->num_z + sub_target->num_z, 2.0);
    }else{
        cout << "ERROR : reaction problem (incorrect reaction_flag)" << endl;
        exit(1);
    }

    double del_angle = 0.1;
    double del_rad_angle = del_angle * to_rad;
    for(double angle=1.0; angle<180.0; angle+=del_angle){
        double rad_angle = angle * to_rad;
        value += (sin(rad_angle)/pow(sin(rad_angle/2.0), 4.0)) * del_rad_angle;
    }
    value *= factor * 2.0 * M_PI;
    return value;
}


double generate_cm_angle_elastic()
{
    double norm = 0.0;

    double del_angle = 0.1;
    double del_rad_angle = del_angle * to_rad;
    for(double angle=1.0; angle<180.0; angle+=del_angle){
        double rad_angle = angle * to_rad;
        norm += (sin(rad_angle)/pow(sin(rad_angle/2.0), 4.0)) * del_rad_angle;
    }

    double uni = generate_standard();
    double tmp = 0.0;
    double cm_angle;
    for(double angle=1.0; angle<180.0; angle+=del_angle){
        double rad_angle = angle * to_rad;
        tmp += (sin(rad_angle)/pow(sin(rad_angle/2.0), 4.0)) * del_rad_angle / norm;
        if(tmp > uni){
            cm_angle = angle;
            break;
        }
    }
    return cm_angle;
}


double list_cross_section(string datafile) //cm2
{
  ifstream fdata(datafile);
  if(!fdata){
    cout << "ERROR: failure to open " << datafile << endl;
    exit(1);
  }

  double all_cs = 0.0;
  string str;
  getline(fdata, str);
  int num = atoi(str.c_str());
  double width = 180.0/num;
  double ang, dif_cs;
  while(fdata >> ang >> dif_cs){
    all_cs += dif_cs * width * to_rad;
  }
  return all_cs * 2.0 * M_PI * 1.0e-27;
}


double generate_cm_ange_list(string datafile)
{
  ifstream fdata(datafile);
  if(!fdata){
    cout << "ERROR: failure to open " << datafile << endl;
    exit(1);
  }
  string str;
  getline(fdata, str);
  const int num = atoi(str.c_str());
  double width = 180.0/num;
  double cs[2][num];
  double ang, dif_cs, tmp=0.0;
  for(int i=0; i<num; i++){
    fdata >> ang >> dif_cs;
    tmp += dif_cs;
    cs[0][i] = ang;
    cs[1][i] = tmp;
  }

  double judge = cs[1][num-1] * generate_standard();
  double cm_ang;
  for(int i=0; i<num; i++){
    if(judge < cs[1][i]){
      if(i==0){ cm_ang = 0.5 * width * generate_standard(); }
      else if(i==num-1){ cm_ang = 180.0 - 0.5 * width * generate_standard(); }
      else{ cm_ang = (cs[0][i] - 0.5 * width) + width * generate_standard(); } 
      break;
    }
  }

  return cm_ang;
}
