#include "../include/beam.h"
#include "../include/function.h"
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
        cout << "ERROR: failure to open file!" << endl;
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
    thickness = input_data[3] * 1.0e-4; //input_data -> um unit, thickness -> cm unit!
    density = input_data[4];
    strip_x = input_data[5];
    strip_y = input_data[6];
    strip_ang = input_data[7];
    particle_energy = input_data[8];
    R = input_data[9];
    detector_sigma = input_data[10];

    double tmp = density / ((28.0/6.0)/STANDARD::AVOGADRO);
    tmp *= thickness;
    h_density = tmp * (2.0/3.0); 
    c_density = tmp * (1.0/3.0);
}

void Beam::print_cond() 
{
    cout << endl;
    cout << "***** initial condition *****" << endl;
    cout << "experiment time  : " << time << " s" << endl;
    cout << "beam intensity : " << intensity << " pps" << endl;
    cout << "6He purity : " << purity * 100.0 << " %" << endl;
    cout << "target(C2H4) thickness : " << thickness * 1.0e+4 << " um" << endl;
    cout << "target density : " << density << " g/cm3" << endl;
    cout << "1H surface density : " << h_density << " atoms/cm2" << endl;
    cout << "12C surface density : " << c_density << " atoms/cm2" << endl;
    cout << "size of detector : " << strip_x << " x " << strip_y << " cm2" << endl;
    cout << "detector angle : " << strip_ang << " deg" << endl;
    cout << "particle energy : " << particle_energy << " MeV/u" << endl;
    cout << "distance between detector and target : " << R << " cm" << endl;
    cout << "Si detector sigma : " << detector_sigma << " MeV" << endl;
    cout << "*****************************" << endl;
    cout << endl;
}

int Beam::get_ini_num()
{
    return (int)(time * intensity);
}

void Beam::generate_beam(double particle[5])
{
    if(generate_standard()<purity){ particle[0]=1.0; } //particle[0]>0 : 6he
    else{ particle[0]=-1.0; }
    particle[1] = particle_energy; //MeV/u
    particle[2] = generate_normal(0.0, 1.0); //cm
    particle[3] = generate_normal(0.0, 1.0);
    particle[4] = -thickness/2.0;
} 

int Beam::judge_interact(double particle[5])
{
    if(particle[0] > 0){ //in case of 6he beam
        double ratio_reaction1 = all_cross_section(particle[1], 1) * h_density;
        double ratio_reaction2 = all_cross_section(particle[1], 2) * c_density;
        double judge = generate_standard();
        if(judge < ratio_reaction1){ return 1; }
        else if(judge < ratio_reaction1 + ratio_reaction2){ return 2; }
        else { return 0; }
    }else{ //in case of 3h beam
        double ratio_reaction3 = all_cross_section(particle[1], 3) * h_density;
        double ratio_reaction4 = all_cross_section(particle[1], 4) * c_density;
        double judge = generate_standard();
        if(judge < ratio_reaction3){ return 3; }
        else if(judge < ratio_reaction3 + ratio_reaction4){ return 4; }
        else { return 0; }
    }
}

//反応した時のtarget内での位置を指定し、エネルギー損失を考えた値を格納する(*** from lise++ value ***)
void Beam::reation_loc_target(double particle[5])
{
    double stop_length = generate_standard() * thickness; //cm
    particle[4] += stop_length;
    double energy_loss;
    double energy_straggling;
    if(particle[0] > 0.0){ //in case of 6he beam
        energy_loss = 0.02278 * (stop_length *1.0e+4);
        energy_straggling = generate_normal(0.0, 0.0059 * (stop_length*1.0e+4) / 50.0);
        particle[1] -= energy_loss/6.0 + energy_straggling;
    }else{ //in case of 3h beam
        energy_loss = 0.00566 * (stop_length*1.0e+4);
        energy_straggling = generate_normal(0.0, 0.00585 * (stop_length*1.0e+4) / 50.0);
        particle[1] -= energy_loss/3.0 + energy_straggling;
    }

}

//http://lambda.phys.tohoku.ac.jp/~miwa9/monte_carlo/kinematics.pdf
double Beam::scatter(int reaction, double particle[5], double particle1[7], double particle2[7])
{
    const double to_deg = 180.0 / M_PI;
    const double to_rad = M_PI / 180.0;

    double M1, M2, M3, M4;

    if(reaction == 1){
        M1 = M3 = MASS::MASS_6HE;
        M2 = M4 = MASS::MASS_p;
    }else if(reaction == 2){
        M1 = M3 = MASS::MASS_6HE;
        M2 = M4 = MASS::MASS_12C;
    }else if(reaction == 3){
        M1 = M3 = MASS::MASS_3H;
        M2 = M4 = MASS::MASS_p;
    }else if(reaction == 4){
        M1 = M3 = MASS::MASS_3H;
        M2 = M4 = MASS::MASS_12C;
    }else{
        cout << "ERROR" << endl;
        exit(1);
    }

    double Theta = generate_cm_angle(); // degree
    double E1; // MeV 実験室系のエネルギー
    if(reaction == 1 || reaction == 2){ E1 = particle[1]*6.0 + M1; }
    else if(reaction == 3 || reaction == 4){ E1 = particle[1]*3.0 + M1; }
    double E2 = 0.0 + M2; // MeV 実験室系のエネルギー
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
    }
    particle1[1] = E3 - M3;
    particle2[1] = E4 - M4; //MeV (x MeV/u)
    particle1[2] = particle[2];
    particle2[2] = particle[2];
    particle1[3] = particle[3];
    particle2[3] = particle[3];
    particle1[4] = particle[4];
    particle2[4] = particle[4];
    particle1[5] = theta;
    particle2[5] = phi;
    particle1[6] = 360.0*generate_standard();
    particle2[6] = particle1[6] - 180.0;  

    return Theta;
}

double Beam::nearest_distance(int reaction, double ang, double energy)
{
    double E = cm_energy(energy, reaction); 
    double rad_ang = ang * M_PI / 180.0;
    double value = (STANDARD::ALPHA * STANDARD::HBAR_C * (1.0 + 1.0/sin(rad_ang / 2.0)))/(2.0 * E);
    if(reaction == 1){
        value *= 2.0 * 1.0;
    }else if(reaction == 2){
        value *= 2.0 * 6.0;
    }else if(reaction == 3){
        value *= 1.0 * 1.0;
    }else if(reaction == 4){
        value *= 1.0 * 6.0;
    }else{
        cout << "ERROR : reaction_flag error" << endl;
        exit(1);
    }
    return value;
}


//(*** from lise++ value ***)
int Beam::leave_target(double particle[7]){
    int flag = 1;
    double del_z = thickness/2.0 - particle[4];
    double distance = del_z / cos(particle[5] * M_PI / 180.0);
    particle[2] += distance * sin(particle[5] * M_PI / 180.0) * cos(particle[6] * M_PI / 180.0);
    particle[3] += distance * sin(particle[5] * M_PI / 180.0) * sin(particle[6] * M_PI / 180.0);
    particle[4] += del_z; 

    double energy_loss, energy_straggling;
    if((int)particle[0] == 11){
        energy_loss = 1.2 * distance*1.0e+4 / 50.0;
        energy_straggling = generate_normal(0.0, 0.0059 * (distance * 1.0e+4) / 50.0) * 6.0;
    }else if((int)particle[0] == 12){
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

int Beam::judge_detector(double particle[7])
{
    int flag=0;
    double u = sin(particle[5] * M_PI / 180.0) * cos(particle[6] * M_PI / 180.0);
    double v = sin(particle[5] * M_PI / 180.0) * sin(particle[6] * M_PI / 180.0);
    double w = cos(particle[5] * M_PI / 180.0);

    double conv_x = particle[4]*sin(-strip_ang * M_PI / 180.0) + particle[2]*cos(-strip_ang * M_PI / 180.0);
    double conv_y = particle[3];
    double conv_z = particle[4]*cos(-strip_ang * M_PI / 180.0) - particle[2]*sin(-strip_ang * M_PI / 180.0);
    double conv_u = w*sin(-strip_ang * M_PI / 180.0) + u*cos(-strip_ang * M_PI / 180.0);
    double conv_v = v;
    double conv_w = w*cos(-strip_ang * M_PI / 180.0) - u*sin(-strip_ang * M_PI / 180.0);
    
    double factor = (R - conv_z) / conv_w;
    conv_x += factor*conv_u;
    conv_y += factor*conv_v;
    if(abs(conv_x) < strip_x && abs(conv_y) < strip_y){ flag = 1; }
    return flag;
}

double Beam::energy_detector(double energy)
{
    return generate_normal(energy, detector_sigma);
}
