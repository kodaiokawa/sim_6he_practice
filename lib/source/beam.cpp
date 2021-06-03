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
    thickness = input_data[3];
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
    cout << "target(C2H4) thickness : " << thickness << " mg/cm2" << endl;
    cout << "target density : " << density << " atoms/cm2" << endl;
    cout << "size of detector : " << strip_x << " x " << strip_y << " cm2" << endl;
    cout << "detector angle : " << strip_ang << " deg" << endl;
    cout << "particle energy : " << particle_energy << " MeV/u" << endl;
    cout << "*****************************" << endl;
    cout << endl;
}


void Beam::generate_beam(double particle[5])
{
    if(generate_standard()<purity){ particle[0]=1.0; }
    else{ particle[0]=-1.0; }
    particle[1] = particle_energy;
    particle[2] = generate_normal(0.0, 1.0); //cm
    particle[3] = generate_normal(0.0, 1.0);
    particle[4] = 0.0;
} 

void Beam::judge_interact(double hantei[6], double particle[5])
{
    if(particle[0] > 0){ //in case of 6he beam
        cout << "test 0" << endl;
    }else{ //in case of 3h beam
        cout << "test -1" << endl;
    }
}
