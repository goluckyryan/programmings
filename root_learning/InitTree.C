//
// Open and create aliases for the tree "t" stored in "tree_struc.root"
// It returns the pointer to the TTree
//
// Usage:
//	.L InitTree.C+
//	TTree *aTree=InitTree()
//

#include "TFile.h"
#include "TTree.h"

TTree *InitTree(void)
 {
 TFile *f=(TFile *)gROOT->FindObject("tree_struc.root");
 if(!f)
  f=new TFile("tree_struc.root");
 TTree *a=(TTree *)f->Get("t");
 a->SetAlias("mass","2*Z*931.5"); 
 a->SetAlias("V","sqrt(2.*Energie/mass)*30."); 
 a->SetAlias("cost","cos(Theta*TMath::DegToRad())"); 
 a->SetAlias("sint","sin(Theta*TMath::DegToRad())"); 
 a->SetAlias("Vz","cost*V"); 
 a->SetAlias("Vt","sint*V"); 
 a->SetAlias("VzCm","Vz-3.33"); 
 a->SetAlias("VCm","sqrt(VzCm*VzCm+Vt*Vt)");
 a->SetAlias("costCm","VzCm/VCm");
 a->SetAlias("sintCm","Vt/VCm");
 a->SetAlias("ECm","mass*TMath::Pow(VCm,2)");
 a->SetAlias("ThetaCm","TMath::Acos(costCm)*TMath::RadToDeg()"); 
 a->SetAlias("PzTot","Sum$(Z*Vz)");
 a->SetAlias("Mleg","Sum$(Z<=2)");
 a->SetAlias("Mimf","Sum$(Z>2)");
 a->SetAlias("Etrans","Energie*sint*sint");
 a->SetAlias("Etrans12","Sum$(Etrans*(Z<=2))");
 a->SetAlias("EtransTot","Sum$(Etrans)");
 a->SetAlias("vseuil","2");
 a->SetAlias("indra","V>vseuil && Theta > 3 && Theta < 177");
 a->StartViewer();
 return a;
 }
