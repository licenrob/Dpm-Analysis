//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun  7 17:56:17 2018 by ROOT version 5.34/36
// from TTree Dpm_sig/Dpm_sig
// found on file: result_2_2.5.root
//////////////////////////////////////////////////////////

#ifndef a_h
#define a_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class a {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         flag;
   Float_t         D_mass;
   Float_t         D_pt;
   Float_t         BDTresponse;

   // List of branches
   TBranch        *b_flag;   //!
   TBranch        *b_D_mass;   //!
   TBranch        *b_D_pt;   //!
   TBranch        *b_BDTresponse;   //!

   a(TTree *tree=0);
   virtual ~a();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef a_cxx
a::a(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("result_2_2.5.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("result_2_2.5.root");
      }
      f->GetObject("Dpm_sig",tree);

   }
   Init(tree);
}

a::~a()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t a::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t a::LoadTree(Long64_t entry)
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

void a::Init(TTree *tree)
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

   fChain->SetBranchAddress("flag", &flag, &b_flag);
   fChain->SetBranchAddress("D_mass", &D_mass, &b_D_mass);
   fChain->SetBranchAddress("D_pt", &D_pt, &b_D_pt);
   fChain->SetBranchAddress("BDTresponse", &BDTresponse, &b_BDTresponse);
   Notify();
}

Bool_t a::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void a::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t a::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef a_cxx