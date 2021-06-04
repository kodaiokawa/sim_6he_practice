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
    double particle[5];
    beam_test->generate_beam(particle);
    cout << particle[2] << endl;
    cout << particle[4] << endl;

    //hantei[0]: which reaction occur 
    //              0: no reaction 1: 2: 3: 4: 5:
    //hantei[1]: incident particle energy
    //particle[2]: location_x (cm)
    //particle[3]: location_y
    //particle[4]: location_z
    double hantei[6];
    beam_test->judge_interact(hantei, particle);












    

    /* TApplication app2( "app2", &argc, argv );
    TCanvas *c = new TCanvas();
    c->Draw();

    TH1F *h2 = new TH1F( "h2", "", 100, -5, 5 );
    h2->Fill(generate_standard());
    h2->Draw();
 
    app2.Run(); */




    return 0;
}
