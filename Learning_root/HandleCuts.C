//
// Save and retrieve the cuts of exercise 4
//
// To use it, type
//	root[0] .L HandleCuts.C+
//	root[1] SaveCuts()          	--> to save your cuts
//	root[2] LoadCuts()		--> to load your cuts (if you lose them)
//

#include "TFile.h"
#include "TCutG.h"

void SaveCuts(void)
 {
 TFile *fi=new TFile("coupures.root","recreate"); // (re)create file for saving cuts
 fi->cd();					  // make it the current file/directory
 gROOT->FindObject("CUTEC")->Write();		  // write CUTEC
 gROOT->FindObject("CUTNI69")->Write();		  // write CUTNI69
 gROOT->FindObject("CUTNI70")->Write();		  // write CUTNI70
 delete fi;					  // close the file
 }

void LoadCuts(void)
 {
 TFile *fi=new TFile("coupures.root");		   // open file
 TCutG *CUTEC=(TCutG *)fi->Get("CUTEC");	   // read CUTEC
 TCutG *CUTNI69=(TCutG *)fi->Get("CUTNI69");	   // read CUTNI69
 TCutG *CUTNI70=(TCutG *)fi->Get("CUTNI70");	   // read CUTNI70
 delete fi;					   // close the file
 }						   
						   
