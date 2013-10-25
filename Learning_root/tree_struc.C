#include "Riostream.h"
#include "TFile.h"
#include "TTree.h"

void MakeTree(void)
{
// Example of a script which reads some data and fills a TTree
// with a branch for each variable describing the data

   //declaration of a structure for the data
   struct Mon_Event{
   	Int_t Mult;
      Float_t Z[50];
   	Float_t Theta[50];
      Float_t Energie[50];
   };
   
   Mon_Event event;
	
   // open the data file for reading
   ifstream file;
   file.open("tree_struc.data");
      
   UInt_t nevents = 100000;
   
   //open ROOT file to save the TTree in
   TFile *ftree = new TFile("tree_struc.root","recreate");
   
   //creation of TTree
   TTree *t = new TTree("t", "TTree avec une structure");
   
   //creation of branches to hold the variables of the structure
   t->Branch("M_part", &event.Mult, "Mult/I");
   t->Branch("Z_part", event.Z, "Z[Mult]/F");
   t->Branch("Th_part", event.Theta, "Theta[Mult]/F");
   t->Branch("E_part", event.Energie, "Energie[Mult]/F");
   
   //loop over the 'nevents' events
   while( (nevents--) > 0 ){
   	
      //read the multiplicity of the event
      file >> event.Mult;
      
      //loop over the particles of the event
      for(UInt_t i=0; i < event.Mult; i++){
      
      	//read the properties of each particle
         file >> event.Z[i];
         file >> event.Theta[i];
         file >> event.Energie[i];
      }
      
      //fill the tree
      t->Fill();
         
      if( !(nevents%1000) ) cout << "Events left = " << nevents << endl;
   }
   
   file.close();
   
   //write and close the ROOT file
   t->Write();
   delete ftree;
}
