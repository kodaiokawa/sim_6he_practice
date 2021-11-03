#include <function.h>
#include <beam.h>
#include <TH1.h>
#include <TTree.h>
#include <TFile.h>
#include <TString.h>

#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int main( int argc, char **argv )
{
    //prepare datafile
    string datafile_cs("../database/cross_section/cs_6he_d_Ecm10MeV.txt");
    cout << "...reading " << datafile_cs << endl;
    ifstream fdata(datafile_cs);
    if(!fdata){
      cout << " CANNOT USE " << datafile_cs << endl;
    }

    //prepare for rootfile
    int ini_particle;
    double ini_x, ini_y, ini_z, ini_energy;
    int flag_reac;
    double scat_x, scat_y, scat_z, scat_energy;
    double cm_ang, part1_theta, part1_phi, part2_theta, part2_phi;
    double part1_energy, part1_det_energy, part2_energy, part2_det_energy;

    TTree *tree = new TTree("tree", "scattering test");
    tree->Branch("ini_particle", &ini_particle, "ini_particle/I");
    tree->Branch("ini_x", &ini_x, "ini_x/D");
    tree->Branch("ini_y", &ini_y, "ini_y/D");
    tree->Branch("ini_z", &ini_z, "ini_z/D");
    tree->Branch("ini_energy", &ini_energy, "ini_energy/D");
    tree->Branch("flag_reac", &flag_reac, "flag_reac/I");
    tree->Branch("scat_x", &scat_x, "scat_x/D");
    tree->Branch("scat_y", &scat_x, "scat_y/D");
    tree->Branch("scat_z", &scat_x, "scat_z/D");
    tree->Branch("scat_energy", &scat_energy, "scat_energy/D");
    tree->Branch("cm_ang", &cm_ang, "cm_ang/D");
    tree->Branch("part1_theta", &part1_theta, "part1_theta/D");
    tree->Branch("part1_phi", &part1_phi, "part1_phi/D");
    tree->Branch("part2_theta", &part2_theta, "part2_theta/D");
    tree->Branch("part2_phi", &part2_phi, "part2_phi/D");
    tree->Branch("part1_energy", &part1_energy, "part1_energy/D");
    tree->Branch("part1_det_energy", &part1_det_energy, "part1_det_energy/D");
    tree->Branch("part2_energy", &part2_energy, "part2_energy/D");
    tree->Branch("part2_det_energy", &part2_det_energy, "part2_det_energy/D");



    //generate beam
    Beam *beam_test = new Beam();
    string filename("../condition/input.txt");
    beam_test->set_condition(filename);
    beam_test->print_cond();


    //Put the initial particle information into the particle[]
    //the particle after reaction is particle1[] and particle2[]
    
    //particle[0]: particle type >6he <3H
    //particle[1]: particle energy
    //particle[2]: location_x (cm)
    //particle[3]: location_y
    //particle[4]: location_z
    double particle[5], particle1[7], particle2[7];
    TH1F *h_strip = new TH1F( "h_strip", "", 100, 0., 50.0 );


    for(int loop=0; loop<beam_test->get_ini_num(); loop++){
        ini_particle = -9999;
        ini_x=-9999.0, ini_y=-9999.0, ini_z=-9999.0, ini_energy=-9999.0;
        flag_reac=-9999;
        scat_x=-9999.0, scat_y=-9999.0, scat_z=-9999.0, scat_energy=-9999.0;
        cm_ang=-9999.0, part1_theta=-9999.0, part1_phi=-9999.0, part2_theta=-9999.0, part2_phi=-9999.0;
        part1_energy=-9999.0, part1_det_energy=-9999.0, part2_energy=-9999.0, part2_det_energy=-9999.0;

        if((loop+1)%10==0){
            cout << "\r" << "proceeding... " << 100.0 * (double)(loop+1)/(double)beam_test->get_ini_num() << " %" << string(20, ' ');
        }

        beam_test->generate_beam(particle);
        if(particle[0] > 0.0){ ini_particle = 0;}
        else { ini_particle = 1; }
        ini_energy = particle[1]; //MeV/u it is possible to give fluctuation here
        ini_x = particle[2];
        ini_y = particle[3];
        ini_z = particle[4];

        int reaction_flag = beam_test->judge_interact(particle, datafile_cs);
        flag_reac = reaction_flag;
        //flag_reac=0 : no reaction
        //flag_reac=1 : elastic main beam + main target
        //flag_reac=2 : elastic main beam + sub target
        //flag_reac=3 : elastic sub beam + main target
        //flag_reac=4 : elastic sub beam + sub target
        //flag_reac=10 : inelastic scattering (reaction of interest)
        if(reaction_flag == 0){
            //tree->Fill();
            continue;
        }
        
        beam_test->reation_loc_target(particle);

        switch(reaction_flag){
        case 10: // inelastic scattering
          break;

        default: // elastic scattering

          scat_energy = particle[1];
          scat_x = particle[2];
          scat_y = particle[3];
          scat_z = particle[4];

          double ang = beam_test->elastic_scatter(reaction_flag, particle, particle1, particle2);
          cm_ang = ang;
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
            int flag1_detector;
            flag1_detector = beam_test->judge_detector(particle1);
            if(flag1_detector == 1){ h_strip->Fill(beam_test->energy_detector(particle1[1])); }
          }
          flag2 = beam_test->leave_target(particle2);
          if(flag2 == 1){
            part2_det_energy = particle2[1];
            int flag2_detector;
            flag2_detector = beam_test->judge_detector(particle2);
            if(flag2_detector == 1){ h_strip->Fill(beam_test->energy_detector(particle2[1])); }
          }
          tree->Fill();
          break;
        }
    }

    TString ofn = "../simulation.root";
    TFile *fout = new TFile(ofn, "recreate");
    tree->Write();
    h_strip->Write();
    fout->Close();

    cout << endl;
    cout << endl;
    cout << "<Created> ./simulation.root" << endl;
    cout << "...simulation completed!" << endl;
    return 0;
}
