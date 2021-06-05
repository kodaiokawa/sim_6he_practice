#include <function.h>
#include <beam.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TH1.h>

#include <iostream>
#include <cmath>

using namespace std;

int main( int argc, char **argv )
{
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
    cout << beam_test->get_ini_num() << endl;
    double particle[5];
    for(int loop=0; loop<beam_test->get_ini_num(); loop++){
        if((loop+1)%((int)(beam_test->get_ini_num()/1000))==0){
            cout << "\r" << "proceeding... " << 100.0 * (double)loop/(double)beam_test->get_ini_num() << " %" << string(20, ' ');
        }
        beam_test->generate_beam(particle);
        beam_test->reation_loc_target(particle);
        int reaction_frag = beam_test->judge_interact(particle);
        if(reaction_frag == 0){ continue; }
        //cout << reaction_frag << endl;

    }











    

    /* TApplication app2( "app2", &argc, argv );
    TCanvas *c = new TCanvas();
    c->Draw();

    TH1F *h2 = new TH1F( "h2", "", 100, -5, 5 );
    h2->Fill(generate_standard());
    h2->Draw();
 
    app2.Run(); */


    cout << endl;
    cout << "...simulation completed!" << endl;
    return 0;
}
