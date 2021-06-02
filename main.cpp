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

    //particle[0]: particle type
    //particle[1]: particle energy
    //particle[2]: location_x
    //particle[3]: location_y
    //particle[4]: location_z
    double particle[5];
    beam_test->generate_beam(particle);
    for(int i=0; i<5; i++){
        cout << particle[i] << endl;
    }
    cout << endl;














    test();

    for(int i=0; i<10; i++){
        cout << generate_standard() << endl;
    }

    

    /* TApplication app2( "app2", &argc, argv );
    TCanvas *c = new TCanvas();
    c->Draw();

    TH1F *h2 = new TH1F( "h2", "", 100, -5, 5 );
    h2->Fill(generate_standard());
    h2->Draw();
 
    app2.Run(); */




    return 0;
}
