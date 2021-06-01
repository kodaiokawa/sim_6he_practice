#include <function.h>
#include <TCanvas.h>
#include <TApplication.h>
#include <TH1.h>

#include <iostream>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;

int main( int argc, char **argv )
{
    double time, intensity, purity, thickness, density, strip_x, strip_y, strip_ang;
    const int num_cond=8;
    double input_data[num_cond];
    ifstream fin_initial("/Users/okawa/work/crib/lise++/6He/pre-analysis/simulation/condition/input.txt");
    cout << "...reading input.txt" << endl;
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

    print_cond(input_data);

    //memo 5/31
    //粒子の種類、粒子のエネルギー、位置_x, 位置_yの入射粒子配列を生成する関数を作りたい
 



    cout << "This is a sample." << endl;
    test();
    for(int i=0; i<10; i++){
        cout << generate_standard() << endl;
    }

    

    TApplication app2( "app2", &argc, argv );
    TCanvas *c = new TCanvas();
    c->Draw();

    TH1F *h2 = new TH1F( "h2", "", 100, -5, 5 );
    h2->Fill(generate_standard());
    h2->Draw();
 
    app2.Run();




    return 0;
}
