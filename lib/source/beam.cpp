#include "../include/beam.h"
#include "../include/function.h"
#include "../include/mass.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <cmath>

using namespace std;


void Beam::set_condition(string filepath)
{
    double input_data[num_cond];
    ifstream fin_initial(filepath);
    cout << "...reading " << filepath << endl;
    if(!fin_initial){
        cout << "error: failure to open file" << endl;
        exit(1);
    }

    string str;
    getline(fin_initial, str);
    for(int i=0; i<num_cond; i++){
        fin_initial >> input_data[i];
    }
    time = input_data[0];
    intensity = input_data[1];
    purity = input_data[2];
    thickness = input_data[3] * 1.0e-4; // um -> cm
    target_purity = input_data[4];
    density = input_data[5];
    strip_x = input_data[6];
    strip_y = input_data[7];
    strip_ang = input_data[8];
    particle_energy = input_data[9];
    R = input_data[10];
    detector_sigma = input_data[11];
}


void Beam::print_cond() 
{
    cout << endl;
    cout << "***** initial condition *****" << endl;
    cout << "experiment time  : " << time << " s" << endl;
    cout << "beam intensity : " << intensity << " pps" << endl;
    cout << "purity of main beam : " << purity * 100.0 << " %" << endl;
    cout << "target thickness : " << thickness * 1.0e+4 << " um" << endl;
    cout << "purity of main target : " << target_purity * 100.0 << " %" << endl;
    cout << "target density : " << density << " atoms/cm2" << endl;
    cout << "size of strip : " << strip_x << " x " << strip_y << " cm2" << endl;
    cout << "size of whole detector : " << strip_x *16.0 << " x " << strip_y *16.0<< " cm2" << endl;
    cout << "detector angle : " << strip_ang << " deg" << endl;
    cout << "particle energy : " << particle_energy << " MeV/u" << endl;
    cout << "distance between detector and target : " << R << " cm" << endl;
    cout << "energy resolution : " << detector_sigma << " MeV" << endl;
    cout << "*****************************" << endl;
    cout << endl;
    cout << "Main beam   (A, Z) = " << "(" << main_beam->num << ", " << main_beam->num_z << ")" << endl;
    cout << "Sub beam    (A, Z) = " << "(" << sub_beam->num << ", " << sub_beam->num_z << ")" << endl;
    cout << "Main target (A, Z) = " << "(" << main_target->num << ", " << main_target->num_z << ")" << endl;
    cout << "Sub beam    (A, Z) = " << "(" << sub_target->num << ", " << sub_target->num_z << ")" << endl;
    cout << endl;
    cout << "Elastic scattering" << endl;
    cout << "1: (" << main_beam->num << ", " << main_beam->num_z << ") + (" << main_target->num << ", " << main_target->num_z << ")" << endl;
    cout << "2: (" << main_beam->num << ", " << main_beam->num_z << ") + (" << sub_target->num << ", " << sub_target->num_z << ")" << endl;
    cout << "3: (" << sub_beam->num << ", " << sub_beam->num_z << ") + (" << main_target->num << ", " << main_target->num_z << ")" << endl;
    cout << "4: (" << sub_beam->num << ", " << sub_beam->num_z << ") + (" << sub_target->num << ", " << sub_target->num_z << ")" << endl;
    cout << endl;
    cout << "Main reaction" << endl;
    cout << "10: (" << main_beam->num << ", " << main_beam->num_z << ") + (" << main_target->num << ", " << main_target->num_z << ") -> (" << out_beam->num << ", " << out_beam->num_z << ") + (" << out_target->num << ", " << out_target->num_z <<")" << endl;
    cout << endl;
}

int Beam::get_ini_num()
{
    return (int)(time * intensity);
}


void Beam::generate_beam(double particle[])
{
    if(generate_standard()<purity){ particle[0]=1.0; } //particle[0]>0 : main particle
    else{ particle[0]=-1.0; } // another particle
    particle[1] = particle_energy; // MeV/u
    particle[2] = generate_normal(0.0, 1.0); //cm
    particle[3] = generate_normal(0.0, 1.0);
    particle[4] = -thickness/2.0;
} 

//(from lise++ value)
//THIS FUNCTION HAS PROBLEM
void Beam::reation_loc_target(double particle[])
{
    double stop_length = generate_standard() * thickness; //cm
    particle[4] += stop_length;
    double energy_loss;
    double energy_straggling;
    if(particle[0] > 0.0){ //in case of main beam
        energy_loss = 0.02278 * (stop_length * 1.0e+4);
        energy_straggling = generate_normal(0.0, 0.0059 * (stop_length * 1.0e+4) / 50.0);
        particle[1] -= energy_loss/6.0 + energy_straggling;
    }else{ //in case of sub beam
        energy_loss = 0.00566 * (stop_length * 1.0e+4);
        energy_straggling = generate_normal(0.0, 0.00585 * (stop_length * 1.0e+4) / 50.0);
        particle[1] -= energy_loss/3.0 + energy_straggling;
    }

}

int Beam::judge_interact(double particle[], string datafile)
{
    if(particle[0] > 0){ //in case of main beam (6He)
        double ratio_reaction1 = elastic_cross_section(particle[1], 1) * density * target_purity;
        double ratio_reaction2 = elastic_cross_section(particle[1], 2) * density * (1.0 - target_purity);
        double ratio_main_reaction;

        ifstream fdata(datafile);
        if(!fdata){
          ratio_main_reaction = 0.0;
        }else{ ratio_main_reaction = list_cross_section(datafile) * density * target_purity; }

        double judge = generate_standard();
        if(judge < ratio_reaction1){ return 1; }
        else if(judge < ratio_reaction1 + ratio_reaction2){ return 2; }
        else if(judge < ratio_reaction1 + ratio_reaction2 + ratio_main_reaction){ return 10; }
        else { return 0; }
    }else{ //in case of another beam (3H)
        double ratio_reaction3 = elastic_cross_section(particle[1], 3) * density * target_purity;
        double ratio_reaction4 = elastic_cross_section(particle[1], 4) * density * (1.0 - target_purity);

        double judge = generate_standard();
        if(judge < ratio_reaction3){ return 3; }
        else if(judge < ratio_reaction3 + ratio_reaction4){ return 4; }
        else { return 0; }
    }
}

double Beam::scatter(int reaction, double particle[], double particle1[], double particle2[], string datafile)
{
    double M1, M2, M3, M4;

    if(reaction == 1){
        M1 = M3 = main_beam->mass;
        M2 = M4 = main_target->mass;
    }else if(reaction == 2){
        M1 = M3 = main_beam->mass;
        M2 = M4 = sub_target->mass;
    }else if(reaction == 3){
        M1 = M3 = sub_beam->mass;
        M2 = M4 = main_target->mass;
    }else if(reaction == 4){
        M1 = M3 = sub_beam->mass;
        M2 = M4 = sub_target->mass;
    }else if(reaction == 10){
        M1 = main_beam->mass;
        M2 = main_target->mass;
        M3 = out_beam->mass;
        M4 = out_target->mass;
    }else{
        cout << "ERROR : reaction problem (incorrect reaction_flag) : "<< reaction << endl;
        exit(1);
    }

    double Theta;
    if(reaction == 10) { Theta = generate_cm_angle_list(datafile); }
    else{ Theta = generate_cm_angle_elastic(); } // degree
    double E1; // MeV Lab system 
    if(reaction == 1 || reaction == 2){ E1 = particle[1]*main_beam->num + M1; }
    else if(reaction == 3 || reaction == 4){ E1 = particle[1]*sub_beam->num + M1; }
    double E2 = 0.0 + M2; // MeV Lab system
    double p1 = sqrt((E1)*(E1)-(M1)*(M1));
    double p2 = sqrt((E2)*(E2)-(M2)*(M2));

    double beta = (p1 + p2)/(E1 + E2);
    double gamma = 1.0/sqrt(1.0 - beta * beta);
    
    double E1_CM = gamma * E1 - beta * gamma * p1;
    double E2_CM = gamma * E2 - beta * gamma * p2;
    double p1_CM = -1.0 * beta * gamma * E1 + gamma * p1;
    double p2_CM = -1.0 * beta * gamma * E2 + gamma * p2;

    double E_CM = E1_CM + E2_CM;

    double E3_CM = (E_CM + (M3*M3 - M4*M4)/E_CM) / 2.0;
    double E4_CM = (E_CM - (M3*M3 - M4*M4)/E_CM) / 2.0;
    double p_CM = sqrt(E3_CM*E3_CM - M3*M3);

    if(E3_CM < M3 || E4_CM < M4){
        cout << "ERROR : in calculation of scattering" << endl;
        exit(1);
    }

    double E3 = gamma * E3_CM + beta * gamma * p_CM * cos(Theta * to_rad);
    double E4 = gamma * E4_CM - beta * gamma * p_CM * cos(Theta * to_rad);
    double p3 = sqrt((gamma * beta * E3_CM + gamma * p_CM * cos(Theta * to_rad))*(gamma * beta * E3_CM + gamma * p_CM * cos(Theta * to_rad)) + p_CM * p_CM * sin(Theta * to_rad) * sin(Theta * to_rad));
    double p4 = sqrt((gamma * beta * E4_CM - gamma * p_CM * cos(Theta * to_rad))*(gamma * beta * E4_CM - gamma * p_CM * cos(Theta * to_rad)) + p_CM * p_CM * sin(Theta * to_rad) * sin(Theta * to_rad));

    double theta = to_deg * asin((p_CM*sin(Theta * to_rad))/p3);
    double phi = to_deg * asin((p_CM*sin(Theta * to_rad))/p4);

    if(reaction == 1){
        particle1[0] = 11.0;
        particle2[0] = 13.0;
    }else if(reaction == 2){
        particle1[0] = 11.0;
        particle2[0] = 14.0;
    }else if(reaction == 3){
        particle1[0] = 12.0;
        particle2[0] = 13.0;
    }else if(reaction == 4){
        particle1[0] = 12.0;
        particle2[0] = 14.0;
    }else if(reaction == 10){
        particle1[0] = 15.0;
        particle2[0] = 16.0;
    } 
    particle1[1] = E3 - M3;
    particle2[1] = E4 - M4; //MeV (not MeV/u)
    particle1[2] = particle[2];
    particle2[2] = particle[2];
    particle1[3] = particle[3];
    particle2[3] = particle[3];
    particle1[4] = particle[4];
    particle2[4] = particle[4];
    particle1[5] = theta;
    particle2[5] = phi;
    particle1[6] = 360.0*generate_standard();
    if(particle1[6] > 180.0) { particle2[6] = particle1[6] - 180.0; }
    else{particle2[6] = particle1[6] + 180.0; }  

    return Theta;
}

//(*** from lise++ value ***)
//THIS FUNCTION GAS PROBLEMS
int Beam::leave_target(double particle[]){
    int flag = 1;
    double del_z = thickness/2.0 - particle[4];
    double distance = del_z / cos(particle[5] * to_rad);
    particle[2] += distance * sin(particle[5] * to_rad) * cos(particle[6] * to_rad);
    particle[3] += distance * sin(particle[5] * to_rad) * sin(particle[6] * to_rad);
    particle[4] += del_z; 

    double energy_loss, energy_straggling;
    if((int)particle[0] == 11 || (int)particle[0] == 15){
        energy_loss = 1.2 * distance*1.0e+4 / 50.0;
        energy_straggling = generate_normal(0.0, 0.0059 * (distance * 1.0e+4) / 50.0) * 6.0;
    }else if((int)particle[0] == 12 || (int)particle[0] == 16){
        energy_loss = 0.3 * distance*1.0e+4 / 50.0;
        energy_straggling = generate_normal(0.0, 0.00586 * (distance * 1.0e+4) / 50.0) * 3.0;
    }else if((int)particle[0] == 13){
        energy_loss = 0.3 * distance*1.0e+4 / 50.0;
        energy_straggling = generate_normal(0.0, 0.002 * (distance * 1.0e+4) / 50.0) * 1.0;
    }else if((int)particle[0] == 14){
        energy_loss = 12.0 * distance*1.0e+4 / 50.0;
        energy_straggling = generate_normal(0.0, 0.002 * (distance * 1.0e+4) / 50.0) * 12.0;
    }else{
        cout << "ERROR : the value of particle[0] " << particle[0] << endl;
        exit(1);
    }
    particle[1] -= energy_loss + energy_straggling;

    if(particle[1] < 0){ flag = 0; }
    return flag;
}

void Beam::judge_detector(double particle[], int tmp[])
{
    //unit direction vector (u, v, w)
    double u = sin(particle[5] * to_rad) * cos(particle[6] * to_rad);
    double v = sin(particle[5] * to_rad) * sin(particle[6] * to_rad);
    double w = cos(particle[5] * to_rad);

    double conv_x = particle[2];
    double conv_y = particle[3]*cos(-strip_ang * to_rad) - particle[4]*sin(-strip_ang * to_rad);
    double conv_z = particle[3]*sin(-strip_ang * to_rad) + particle[4]*cos(-strip_ang * to_rad);

    double conv_u = u;
    double conv_v = v*cos(-strip_ang * to_rad) - w*sin(-strip_ang * to_rad);
    double conv_w = v*sin(-strip_ang * to_rad) + w*cos(-strip_ang * to_rad);

    double factor = (R - conv_z) / conv_w;
    conv_x += factor*conv_u;
    conv_y += factor*conv_v;

    tmp[0] = 0;
    tmp[1] = 0;
    for(int i=1; i<17; i++){
      if(-strip_x*8.0 + strip_x*(i-1.0) < conv_x && -strip_x*8.0 + strip_x*i > conv_x){
        tmp[0] = 17 - i;
      }
      if(-strip_y*8.0 + strip_y*(i-1.0) < conv_y && -strip_y*8.0 + strip_y*i > conv_y){
        tmp[1] = 17 - i;
      }
    }
}

double Beam::energy_detector(double energy)
{
    return generate_normal(energy, detector_sigma);
}
