{
    //double pi = 4.0 * atan(1.0);
    //double tmp = 6.0 * (4.0 * atan(1.0) / 180.0); //strip angle
    //cout << sin(tmp) << endl;

    //TString conv_x = "part1_z*sin(angle) + part1_x*cos(angle)";

    //tree->SetAlias("detector", "part1_z*sin(angle) + part1_x*cos(angle) < 5.0/32.0 && part1_z*sin(angle) + part1_x*cos(angle) > -5.0/32.0 && part1_y < 2.5 && part1_y > -2.5");

    //tree->Draw("part1_x:part1_y:part1_z", "flag_reac == 1 && part1_z>1.0 && part1_z*sin(tmp) + part1_x*cos(tmp) < 5.0/32.0 && part1_z*sin(tmp) + part1_x*cos(tmp) > -5.0/32.0 && part1_y < 2.5 && part1_y > -2.5");


    double tmp = 45.0 * (4.0 * atan(1.0) / 180.0); //strip angle
    tree->SetMarkerStyle(6);
    tree->Draw("part1_y:part1_z:part1_x>>h", "flag_reac == 1 && part1_z>1.0 && (part1_z*sin(pi) + part1_x*cos(pi)) < 5.0/32.0 && (part1_z*sin(pi) + part1_x*cos(pi)) > -5.0/32.0 && part1_y < 2.5 && part1_y > -2.5");


}