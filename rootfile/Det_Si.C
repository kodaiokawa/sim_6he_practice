#define Det_Si_cxx
#include "Det_Si.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void Det_Si::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Det_Si.C
//      root> Det_Si t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;

   TRandom3 *rnd = new TRandom3();
   TGraph2D *gr1 = new TGraph2D();
   gr1->SetTitle("10 degree");
   gr1->SetMarkerColor(2);
   gr1->SetMarkerSize(0.5);
   gr1->SetMarkerStyle(6);
   int num_gr1 = 0;
   TH1F *h = new TH1F( "h", "h", 100, 0., 50.0 );
   TH1F *h_1 = new TH1F( "h_1", "h_1", 100, 0., 50.0 );
   h_1->SetLineColor(2);
   TH1F *h_2 = new TH1F( "h_2", "h_2", 100, 0., 50.0 );
   h_2->SetLineColor(3);
   TH1F *h_3 = new TH1F( "h_3", "h_3", 100, 0., 50.0 );
   h_3->SetLineColor(4);
   TH1F *h_4 = new TH1F( "h_4", "h_4", 100, 0., 50.0 );
   h_4->SetLineColor(6);

   double pi = 4.0 * atan(1.0);
   double angle = 10.0 * (pi / 180.0); //strip angle


   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      //if(flag_reac != 1) continue;

      double tmp1_x = part1_z*sin(angle) + part1_x*cos(angle);

      if(part1_z > 0.1 && abs(tmp1_x) < 5.0/32.0 && abs(part1_y) < 2.5){
         gr1->SetPoint(num_gr1, part1_x, part1_z, part1_y);
         num_gr1++;
         double tmp_ene = rnd->Gaus(part1_det_energy, 0.05 * part1_det_energy);
         if(flag_reac == 1){ h_1->Fill(tmp_ene); }
         else if(flag_reac == 2){ h_2->Fill(tmp_ene); }
         else if(flag_reac == 3){ h_3->Fill(tmp_ene); }
         else if(flag_reac == 4){ h_4->Fill(tmp_ene); }
         h->Fill(tmp_ene);
      }

      double tmp2_x = part2_z*sin(angle) + part2_x*cos(angle);

      if(part2_z > 0.1 && abs(tmp2_x) < 5.0/32.0 && abs(part2_y) < 2.5){
         gr1->SetPoint(num_gr1, part2_x, part2_z, part2_y);
         num_gr1++;
         double tmp_ene = rnd->Gaus(part2_det_energy, 0.05 * part2_det_energy);
         if(flag_reac == 1){ h_1->Fill(tmp_ene); }
         else if(flag_reac == 2){ h_2->Fill(tmp_ene); }
         else if(flag_reac == 3){ h_3->Fill(tmp_ene); }
         else if(flag_reac == 4){ h_4->Fill(tmp_ene); }
         h->Fill(tmp_ene);
      }
   }
   gr1->SetPoint(num_gr1, -15.0, 0.0, -5.0);
   gr1->SetPoint(num_gr1+1, -15.0, 0.0, 5.0);
   gr1->SetPoint(num_gr1+2, -15.0, 20.0, 5.0);
   gr1->SetPoint(num_gr1+3, -15.0, 20.0, -5.0);
   gr1->SetPoint(num_gr1+4, 15.0, 0.0, -5.0);
   gr1->SetPoint(num_gr1+5, 15.0, 0.0, 5.0);
   gr1->SetPoint(num_gr1+6, 15.0, 20.0, 5.0);
   gr1->SetPoint(num_gr1+7, 15.0, 20.0, -5.0);
   gr1->Draw();


}
