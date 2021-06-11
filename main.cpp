#include <function.h>
#include <beam.h>
#include <TH1.h>
#include <TTree.h>
#include <TFile.h>
#include <TString.h>

#include <iostream>
#include <cmath>

using namespace std;

int main( int argc, char **argv )
{
    //prepare for rootfile
    int ini_particle;
    double ini_x, ini_y, ini_z, ini_energy;
    int flag_reac;
    double scat_x, scat_y, scat_z, scat_energy;
    double cm_ang, part1_theta, part1_phi, part2_theta, part2_phi;
    double part1_energy, part1_det_energy, part2_energy, part2_det_energy;
    double part1_x, part1_y, part1_z, part2_x, part2_y, part2_z;
    double r_min;

    TTree *tree = new TTree("tree", "elastic scattering");
    tree->Branch("ini_particle", &ini_particle, "ini_particle/I");
    tree->Branch("ini_x", &ini_x, "ini_x/D");
    tree->Branch("ini_y", &ini_y, "ini_y/D");
    tree->Branch("ini_z", &ini_z, "ini_z/D");
    tree->Branch("ini_energy", &ini_energy, "ini_energy/D");
    tree->Branch("flag_reac", &flag_reac, "flag_reac/I");
    tree->Branch("scat_x", &scat_x, "scat_x/D");
    tree->Branch("scat_y", &scat_y, "scat_y/D");
    tree->Branch("scat_z", &scat_z, "scat_z/D");
    tree->Branch("scat_energy", &scat_energy, "scat_energy/D");
    tree->Branch("cm_ang", &cm_ang, "cm_ang/D");
    tree->Branch("r_min", &r_min, "r_min/D");
    tree->Branch("part1_theta", &part1_theta, "part1_theta/D");
    tree->Branch("part1_phi", &part1_phi, "part1_phi/D");
    tree->Branch("part1_energy", &part1_energy, "part1_energy/D");
    tree->Branch("part1_det_energy", &part1_det_energy, "part1_det_energy/D");
    tree->Branch("part1_x", &part1_x, "part1_x/D");
    tree->Branch("part1_y", &part1_y, "part1_y/D");
    tree->Branch("part1_z", &part1_z, "part1_z/D");
    tree->Branch("part2_theta", &part2_theta, "part2_theta/D");
    tree->Branch("part2_phi", &part2_phi, "part2_phi/D");
    tree->Branch("part2_energy", &part2_energy, "part2_energy/D");
    tree->Branch("part2_det_energy", &part2_det_energy, "part2_det_energy/D");
    tree->Branch("part2_x", &part2_x, "part2_x/D");
    tree->Branch("part2_y", &part2_y, "part2_y/D");
    tree->Branch("part2_z", &part2_z, "part2_z/D");


    Beam *beam_test = new Beam();
    //write an input file
    string filename("/Users/okawa/work/crib/lise++/6He/pre-analysis/simulation/condition/input.txt");
    beam_test->set_condition(filename);
    beam_test->print_cond();

    //particle[0]: particle type >6he <3H
    //particle[1]: particle energy
    //particle[2]: location_x (cm)
    //particle[3]: location_y
    //particle[4]: location_z
    double particle[5], particle1[7], particle2[7];
    //TH1F *h_strip = new TH1F( "h_strip", "", 100, 0., 50.0 );


    for(int loop=0; loop<beam_test->get_ini_num(); loop++){
        ini_particle = -9999;
        ini_x=-9999.0, ini_y=-9999.0, ini_z=-9999.0, ini_energy=-9999.0;
        flag_reac=-9999;
        scat_x=-9999.0, scat_y=-9999.0, scat_z=-9999.0, scat_energy=-9999.0;
        cm_ang=-9999.0, r_min=-9999.0, part1_theta=-9999.0, part1_phi=-9999.0, part2_theta=-9999.0, part2_phi=-9999.0;
        part1_energy=-9999.0, part1_det_energy=-9999.0, part2_energy=-9999.0, part2_det_energy=-9999.0;

        if((loop+1)%10==0){
            cout << "\r" << "proceeding... " << 100.0 * (double)(loop+1)/(double)beam_test->get_ini_num() << " %" << string(20, ' ');
        }

        beam_test->generate_beam(particle);
        if(particle[0] > 0.0){ ini_particle = 0;}
        else { ini_particle = 1; }
        ini_x = particle[2];
        ini_y = particle[3];
        ini_z = particle[4];
        ini_energy = particle[1];

        int reaction_flag = beam_test->judge_interact(particle);
        flag_reac = reaction_flag;
        if(reaction_flag == 0){
            //tree->Fill();
            continue;
        }
        beam_test->reation_loc_target(particle);
        
        scat_x = particle[2];
        scat_y = particle[3];
        scat_z = particle[4];
        scat_energy = particle[1];

        double ang = beam_test->scatter(reaction_flag, particle, particle1, particle2);
        double min_distance = beam_test->nearest_distance(reaction_flag, ang, particle[1]);
        cm_ang = ang;
        r_min = min_distance;
        part1_theta = particle1[5];
        part1_phi = particle1[6];
        part2_theta = particle2[5];
        part2_phi = particle2[6];
        part1_energy = particle1[1];
        part2_energy = particle2[1];

        int flag1, flag2;
        flag1 = beam_test->leave_target(particle1);
        if(flag1 == 1){
            part1_det_energy = particle1[1];
            beam_test->to_detector(particle1);
            part1_x = particle1[2];
            part1_y = particle1[3];
            part1_z = particle1[4];

            int flag1_detector;
            flag1_detector = beam_test->judge_detector(particle1);
            //if(flag1_detector == 1){ h_strip->Fill(beam_test->energy_detector(particle1[1])); }
        }else{
            part1_det_energy = 0.0;
            part1_x = 0.0;
            part1_y = 0.0;
            part1_z = 0.0;
        }
        flag2 = beam_test->leave_target(particle2);
        if(flag2 == 1){
            part2_det_energy = particle2[1];
            beam_test->to_detector(particle2);
            part2_x = particle2[2];
            part2_y = particle2[3];
            part2_z = particle2[4];

            int flag2_detector;
            flag2_detector = beam_test->judge_detector(particle2);
            //if(flag2_detector == 1){ h_strip->Fill(beam_test->energy_detector(particle2[1])); }
        }else{
            part2_det_energy = 0.0;
            part2_x = 0.0;
            part2_y = 0.0;
            part2_z = 0.0;
        }
        tree->Fill();

    }

    TString ofn = "../rootfile/simulation.root";
    TFile *fout = new TFile(ofn, "recreate");
    tree->Write();
    //h_strip->Write();
    fout->Close();

    cout << endl;
    cout << endl;
    cout << "<Created> ../rootfile/simulation.root" << endl;
    cout << "...simulation completed!" << endl;
    return 0;
}
