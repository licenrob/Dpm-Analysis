#define a_cxx
#include "a.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void a::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L a.C
//      Root > a t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
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

   TFile *f = new TFile("Dpm_cuts.root","RECREATE");

   TNtuple *ntp_Dpm = new TNtuple("Dpm","DMeson Tree","D_mass:D_pt:BDTresponse");

    


   int const n_bin = 22;
   float bdtRange[n_bin] = {0., 0.025, 0.05, 0.075, 0.1, 0.125, 0.15, 0.175, 0.2, 0.225, 0.25, 0.275, 0.3, 0.31, 0.32, 0.33, 0.34, 0.35, 0.36, 0.37, 0.38};
   string bdtRange_str[n_bin] = {"0", "0.025", "0.05", "0.075", "0.1", "0.125", "0.15", "0.175", "0.2", "0.225", "0.25", "0.275", "0.3", "0.31", "0.32", "0.33", "0.34", "0.35", "0.36", "0.37", "0.38"};


   TH1D *his[n_bin];
   //TCanvas* c_p[14];
   //TLegend *leg[4][14];
   
   //gStyle->SetOptStat(0);

   for(int i = 0; i < n_bin; i++)
   {
      TString histname = "Dpm_mass_";
      histname += bdtRange_str[i];
      his[i] = new TH1D(histname, "D_mass;m [GeV]", 50, 1.7, 2.1);
      his[i]->Sumw2(); 
   }

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   if(jentry%(nentries/100)==0) std::cout<<100*jentry/(nentries)<<"%"<<std::endl;   
   	  int ii = 0;
      float var[3];

      var[0]=D_mass;
      var[1]=D_pt;
      var[2]=BDTresponse;

      ntp_Dpm->Fill(var);

      for(int i = 0; i < n_bin; i++)
   {
      if(BDTresponse>bdtRange[i])
      	his[i]->Fill(D_mass);
   }
   }

   for(int i = 0; i < n_bin; i++)
   {
   his[i]->Write();
	}
   ntp_Dpm->Write();
   f->Close();
}
