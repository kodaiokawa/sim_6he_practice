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
        void generate_beam(double particle[5]);
        void judge_interact(double hantei[6], double particle[5]);
};



