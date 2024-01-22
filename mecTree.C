#define mecTree_cxx
#include "mecTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>


bool isIon(int pdgCode){
  int kIonBase = 1000000000;
  int kIonEnd  = 2000000000;
  return (pdgCode > kIonBase) && (pdgCode < kIonEnd);

}

bool isBaryon(int pdgCode){

  return pdgCode/1000%10;

}

bool isMuon(int pdgCode){
  int kMuon = 13;

  return (pdgCode == kMuon || pdgCode == -kMuon);

}


void mecTree::Loop()
{
//   In a ROOT session, you can do:
//      root> .L mecTree.C
//      root> mecTree t
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


   const int kPdgProton           =  2212; //
   const int kPdgAntiProton       = -2212; //
   const int kPdgNeutron          =  2112; //
   const int kPdgAntiNeutron      = -2112; //
   const int kPdgPiP              =   211; // pi+
   const int kPdgPiM              =  -211; // pi-
   const int kPdgPi0              =   111; // pi0
   const int kPdgKP               =   321; // K+
   const int kPdgKM               =  -321; // K-
   const int kPdgK0               =   311; // K0
   const int kPdgAntiK0           =  -311; // \bar{K0}

   const int kPdgElectron         =  11;   //
   const int kPdgPositron         = -11;   //

   const int kPdgGamma            =    22; // photon

   double neutronMass = 0.939565;
   double protonMass  = 0.938272;
   double pionMass    = 0.139570;
   double kaonMass    = 0.493677;
   double kaon0Mass   = 0.497611;

   double e_h = 1.27;
   
   Double_t Eavail;
   Double_t Eshw;
   Double_t EshwMINOS;
   Double_t Ehad;
   Double_t Ehadstar;
   Double_t hMass;

   bool saw_mu2 = false;
   Double_t Emu2;

   //TODO: reinstate the bEavail branch?
   //TBranch* bEavail = fChain->Branch("Eavail",&Eavail,"Eavail/D");
   TBranch* bEmu2   = fChain->Branch("Emu2",&Emu2,"Emu2/D");
   TBranch* bEshwMINOS = fChain->Branch("EshwMINOS",&EshwMINOS,"EshwMINOS/D");
   TBranch* bEshw   = fChain->Branch("Eshw",&Eshw,"Eshw/D");
   TBranch* bEhad   = fChain->Branch("Ehad",&Ehad,"Ehad/D");
   TBranch* bEhadstar = fChain->Branch("Ehadstar",&Ehadstar,"Ehadstar/D");
   
   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      Eavail=calresp0;
      Eshw=0.;
      EshwMINOS=0;
      Ehad=0;
      Ehadstar=0;
      Emu2 = 0.;
      saw_mu2 = false;
      
      for(int j = 0; j < nf; j++)
        {
	  hMass = TMath::Sqrt(Ef[j]*Ef[j] - pf[j]*pf[j]);
	  if(isBaryon(pdgf[j]) || isIon(pdgf[j])){
	    EshwMINOS += (Ef[j] - hMass);
	  }
	  else if( isMuon(pdgf[j]) && !saw_mu2){
	    saw_mu2 = true;
	    Emu2 = Ef[j];
	  }
	  else if (isMuon(pdgf[j]) && saw_mu2 && Ef[j] > Emu2){
	    EshwMINOS += Emu2;
	    Emu2 = Ef[j];
	  }
	  else{
	    EshwMINOS += Ef[j];

	  }
	  /*
	  if (isMuon(pdgf[j]) && cc){
	    std::cout << "Hadronic system contains a muon ... index = " << j << std::endl;
	    std::cout << "El = " << El << " and Emu = " << Ef[j] << std::endl;
	    if (El < Ef[j]){
	      std::cout << "Ev  = " << Ev  << std::endl;
	      std::cout << "QE  = " << qel << std::endl;
	      std::cout << "RES = " << res << std::endl;
	      std::cout << "MEC = " << mec << std::endl;
	      std::cout << "DIS = " << dis << std::endl;
	      std::cout << "COH = " << coh << std::endl;
	    }
	  }
	  */
	  Ehad += Ef[j];
	  if ( pdgf[j] == kPdgProton)
	  {
	    Eshw += 1./e_h* (Ef[j] - protonMass);
	    Ehadstar += (Ef[j] - protonMass);
	  }
	  else if ( pdgf[j] == kPdgAntiProton)
	  {
	    Eshw += (1./e_h* Ef[j] + 2.*protonMass);
	    Ehadstar += Ef[j];
	  }
          else if ( pdgf[j] == kPdgNeutron)
	  {
	    Eavail -= (Ef[j] - neutronMass);
	    Eshw   += 1./(e_h)* (Ef[j] - neutronMass);
	    Ehadstar += (Ef[j] - neutronMass);
	  }
	  else if ( pdgf[j] == kPdgAntiNeutron)
	  {
	    Eshw   += (1./(e_h)* Ef[j] + 2.* neutronMass);
	    Ehadstar   += Ef[j];
	  }
	  else if ( pdgf[j] == kPdgPiP )
	  {
	    Eshw += 1./e_h * (Ef[j] - pionMass);
	    Ehadstar += Ef[j] - pionMass;
	  }
	  else if ( pdgf[j] == kPdgPiM )
	  {
	    Eshw += 1./e_h * (Ef[j] - pionMass);
	    Ehadstar += Ef[j] - pionMass;
	  }
	  else if ( pdgf[j] == kPdgPi0 )
	  {
	    Eavail -= 0.3 * Ef[j];
	    Eshw   += Ef[j];
	    Ehadstar   += Ef[j];
	  }
	  else if (pdgf[j] == kPdgKP)
	  {
	    Eshw += 1./e_h * (Ef[j] - kaonMass);
	    Ehadstar += (Ef[j] - kaonMass);
	  }
	  else if (pdgf[j] == kPdgKM)
	  {
	    Eshw += 1./e_h * (Ef[j] - kaonMass);
	    Ehadstar += (Ef[j] - kaonMass);
	  }
	  else if (pdgf[j] == kPdgK0)
	  {
	    Eshw += 1./e_h * (Ef[j] - kaon0Mass);
	    Ehadstar += (Ef[j] - kaon0Mass);
	  }
	  else if (pdgf[j] == kPdgAntiK0)
	  {
	    Eshw += 1./e_h * (Ef[j] - kaon0Mass);
	    Ehadstar += (Ef[j] - kaon0Mass);
	  }	  
	  else if ( pdgf[j] == kPdgGamma )
	  {
	    Eavail -= 0.3 * Ef[j];
	    Eshw   += Ef[j];
	    Ehadstar   += Ef[j];
	  }
	  else if ( pdgf[j] == kPdgElectron )
	  {
	    Eavail -= 0.3 * Ef[j];
	    Eshw   += Ef[j];
	    Ehadstar   += Ef[j];
	  }
	  else if ( pdgf[j] == kPdgPositron )
	  {
	    Eavail -= 0.3 * Ef[j];
	    Eshw   += Ef[j];
	    Ehadstar   += Ef[j];
	  }
	  else{

	    Eshw += Ef[j] - hMass;
	    Ehadstar += Ef[j] - hMass;

	  }

        }
      bEhad->Fill();
      bEhadstar->Fill();
      bEshw->Fill();
      bEmu2->Fill();
      bEshwMINOS->Fill();
   }

   fChain->Write();
   
}
