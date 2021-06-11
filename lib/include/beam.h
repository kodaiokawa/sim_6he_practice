#pragma once

#include<string>

using namespace std;

class Beam
{
    private:
        int num_cond = 11;
        double time, intensity, purity, thickness, density;
        double strip_x, strip_y, strip_ang, particle_energy;
        double R, detector_sigma;
        double h_density, c_density; //not include num_cond
    public:
        void set_condition(string filepath);
        void print_cond();
        int get_ini_num();
        void generate_beam(double particle[5]);
        
        //it is proto type
        void reation_loc_target(double particle[5]);
        
        int judge_interact(double particle[5]);
        double scatter(int reaction, double particle[5], double particle1[7], double particle2[7]);
        double nearest_distance(int reaction, double ang, double energy);

        //it is proto type
        int leave_target(double particle[7]);

        int judge_detector(double particle[7]);
        void to_detector(double particle[7]);
        double energy_detector(double energy);
};



