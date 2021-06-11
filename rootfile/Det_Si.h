//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jun 11 09:57:08 2021 by ROOT version 6.22/08
// from TTree tree/elastic scattering
// found on file: simulation.root
//////////////////////////////////////////////////////////

#ifndef Det_Si_h
#define Det_Si_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Det_Si {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           ini_particle;
   Double_t        ini_x;
   Double_t        ini_y;
   Double_t        ini_z;
   Double_t        ini_energy;
   Int_t           flag_reac;
   Double_t        scat_x;
   Double_t        scat_y;
   Double_t        scat_z;
   Double_t        scat_energy;
   Double_t        cm_ang;
   Double_t        r_min;
   Double_t        part1_theta;
   Double_t        part1_phi;
   Double_t        part1_energy;
   Double_t        part1_det_energy;
   Double_t        part1_x;
   Double_t        part1_y;
   Double_t        part1_z;
   Double_t        part2_theta;
   Double_t        part2_phi;
   Double_t        part2_energy;
   Double_t        part2_det_energy;
   Double_t        part2_x;
   Double_t        part2_y;
   Double_t        part2_z;

   // List of branches
   TBranch        *b_ini_particle;   //!
   TBranch        *b_ini_x;   //!
   TBranch        *b_ini_y;   //!
   TBranch        *b_ini_z;   //!
   TBranch        *b_ini_energy;   //!
   TBranch        *b_flag_reac;   //!
   TBranch        *b_scat_x;   //!
   TBranch        *b_scat_y;   //!
   TBranch        *b_scat_z;   //!
   TBranch        *b_scat_energy;   //!
   TBranch        *b_cm_ang;   //!
   TBranch        *b_r_min;   //!
   TBranch        *b_part1_theta;   //!
   TBranch        *b_part1_phi;   //!
   TBranch        *b_part1_energy;   //!
   TBranch        *b_part1_det_energy;   //!
   TBranch        *b_part1_x;   //!
   TBranch        *b_part1_y;   //!
   TBranch        *b_part1_z;   //!
   TBranch        *b_part2_theta;   //!
   TBranch        *b_part2_phi;   //!
   TBranch        *b_part2_energy;   //!
   TBranch        *b_part2_det_energy;   //!
   TBranch        *b_part2_x;   //!
   TBranch        *b_part2_y;   //!
   TBranch        *b_part2_z;   //!

   Det_Si(TTree *tree=0);
   virtual ~Det_Si();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Det_Si_cxx
Det_Si::Det_Si(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("simulation.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("simulation.root");
      }
      f->GetObject("tree",tree);

   }
   Init(tree);
}

Det_Si::~Det_Si()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Det_Si::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Det_Si::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Det_Si::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("ini_particle", &ini_particle, &b_ini_particle);
   fChain->SetBranchAddress("ini_x", &ini_x, &b_ini_x);
   fChain->SetBranchAddress("ini_y", &ini_y, &b_ini_y);
   fChain->SetBranchAddress("ini_z", &ini_z, &b_ini_z);
   fChain->SetBranchAddress("ini_energy", &ini_energy, &b_ini_energy);
   fChain->SetBranchAddress("flag_reac", &flag_reac, &b_flag_reac);
   fChain->SetBranchAddress("scat_x", &scat_x, &b_scat_x);
   fChain->SetBranchAddress("scat_y", &scat_y, &b_scat_y);
   fChain->SetBranchAddress("scat_z", &scat_z, &b_scat_z);
   fChain->SetBranchAddress("scat_energy", &scat_energy, &b_scat_energy);
   fChain->SetBranchAddress("cm_ang", &cm_ang, &b_cm_ang);
   fChain->SetBranchAddress("r_min", &r_min, &b_r_min);
   fChain->SetBranchAddress("part1_theta", &part1_theta, &b_part1_theta);
   fChain->SetBranchAddress("part1_phi", &part1_phi, &b_part1_phi);
   fChain->SetBranchAddress("part1_energy", &part1_energy, &b_part1_energy);
   fChain->SetBranchAddress("part1_det_energy", &part1_det_energy, &b_part1_det_energy);
   fChain->SetBranchAddress("part1_x", &part1_x, &b_part1_x);
   fChain->SetBranchAddress("part1_y", &part1_y, &b_part1_y);
   fChain->SetBranchAddress("part1_z", &part1_z, &b_part1_z);
   fChain->SetBranchAddress("part2_theta", &part2_theta, &b_part2_theta);
   fChain->SetBranchAddress("part2_phi", &part2_phi, &b_part2_phi);
   fChain->SetBranchAddress("part2_energy", &part2_energy, &b_part2_energy);
   fChain->SetBranchAddress("part2_det_energy", &part2_det_energy, &b_part2_det_energy);
   fChain->SetBranchAddress("part2_x", &part2_x, &b_part2_x);
   fChain->SetBranchAddress("part2_y", &part2_y, &b_part2_y);
   fChain->SetBranchAddress("part2_z", &part2_z, &b_part2_z);
   Notify();
}

Bool_t Det_Si::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Det_Si::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Det_Si::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Det_Si_cxx
