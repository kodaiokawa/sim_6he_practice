#include "../include/beam.h"
#include "../include/function.h"
#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;


void Beam::set_condition(string filepath)
{
    double input_data[num_cond];
    //write a path to condition directry
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
    thickness = input_data[3] * 1.0e-4;
    density = input_data[4];
    strip_x = input_data[5];
    strip_y = input_data[6];
    strip_ang = input_data[7];
    particle_energy = input_data[8];
}


void Beam::print_cond() 
{
    cout << endl;
    cout << "***** initial condition *****" << endl;
    cout << "experiment time  : " << time << " s" << endl;
    cout << "beam intensity : " << intensity << " pps" << endl;
    cout << "6He purity : " << purity * 100.0 << " %" << endl;
    cout << "target(C2H4) thickness : " << thickness * 1.0e+4 << " um" << endl;
    cout << "target density : " << density << " atoms/cm2" << endl;
    cout << "size of detector : " << strip_x << " x " << strip_y << " cm2" << endl;
    cout << "detector angle : " << strip_ang << " deg" << endl;
    cout << "particle energy : " << particle_energy << " MeV/u" << endl;
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
    particle[1] = particle_energy;
    particle[2] = generate_normal(0.0, 1.0); //cm
    particle[3] = generate_normal(0.0, 1.0);
    particle[4] = -thickness/2.0;
} 

//もし、反応したと仮定した時のtarget内での位置を指定し、エネルギー損失を考えた値を格納する(*** from lise++ value ***)
void Beam::reation_loc_target(double particle[5])
{
    double stop_length = generate_standard() * thickness; //um
    particle[4] += stop_length;
    double energy_loss;
    double energy_straggling;
    if(particle[0] > 0.0){ //in case of 6he beam
        energy_loss = 0.02278 * (stop_length * 1.0e+4);
        energy_straggling = generate_normal(0.0, 0.0059 * (stop_length * 1.0e+4) / 50.0);
        particle[1] -= energy_loss/6.0 + energy_straggling;
    }else{ //in case of 3h beam
        energy_loss = 0.00566 * (stop_length * 1.0e+4);
        energy_straggling = generate_normal(0.0, 0.00585 * (stop_length * 1.0e+4) / 50.0);
        particle[1] -= energy_loss/3.0 + energy_straggling;
    }

}

int Beam::judge_interact(double particle[5])
{
    if(particle[0] > 0){ //in case of 6he beam
        double ratio_reaction1 = all_cross_section(particle[1], 1) * density * (2.0/3.0);
        double ratio_reaction2 = all_cross_section(particle[1], 2) * density * (1.0/3.0);
        double judge = generate_standard();
        if(judge < ratio_reaction1){ return 1; }
        else if(judge < ratio_reaction1 + ratio_reaction2){ return 2; }
        else { return 0; }
    }else{ //in case of 3h beam
        double ratio_reaction3 = all_cross_section(particle[1], 3) * density * (2.0/3.0);
        double ratio_reaction4 = all_cross_section(particle[1], 4) * density * (1.0/3.0);
        double judge = generate_standard();
        if(judge < ratio_reaction3){ return 3; }
        else if(judge < ratio_reaction3 + ratio_reaction4){ return 4; }
        else { return 0; }
    }
}

double Beam::generate_cm_angle(double energy, int reaction)
{
    double uni = generate_standard();
    return 0.0;
}