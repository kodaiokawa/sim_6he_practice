#pragma once

#include<string>

using namespace std;

class Beam
{
    private:
        int num_cond = 9;
        double time, intensity, purity, thickness, density, strip_x, strip_y, strip_ang, particle_energy;
    public:
        void set_condition(string filepath);
        void print_cond();
        int get_ini_num();
        void generate_beam(double particle[5]);
        
        //it is proto type
        void reation_loc_target(double particle[5]);
        
        int judge_interact(double particle[5]);
        double generate_cm_angle(double energy, int reaction);
        void scatter(double angle, double particle1[5], double particle2[5]);
};



