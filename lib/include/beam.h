#pragma once

#include<string>

using namespace std;

class Beam
{
    private:
        int num_cond = 12;
        double time, intensity, purity, thickness, target_purity, density, strip_x, strip_y, strip_ang, particle_energy;
        double R, detector_sigma;
    public:
        void set_condition(string filepath);
        void print_cond();
        int get_ini_num();
        void generate_beam(double particle[]);
        void reation_loc_target(double particle[]); //problem
        int judge_interact(double particle[], string datafile);
        double scatter(int reaction, double particle[], double particle1[], double particle2[], string datafile);
        int leave_target(double particle[]); //problem
        void judge_detector(double particle[], int tmp[]);
        double energy_detector(double energy);
};



