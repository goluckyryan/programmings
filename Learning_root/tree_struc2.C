#include "Riostream.h"
#include "TFile.h"
#include "TTree.h"

void MakeTree2(void)
{
// Example of a script which reads some data and fills a TTree
// with one branch containing a structure filled with the data

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
   TFile *ftree = new TFile("tree_struc2.root","recreate");
   
   //creation of TTree
   TTree *t = new TTree("t", "TTree avec une structure");
   
   //creation of 1 branch to hold the structure
   t->Branch("bEvent", &event, "Mult/I:Z[50]/F:Theta[50]/F:Energie[50]/F");
   
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
      for(UInt_t i=event.Mult; i < 50; i++){
      
      	//reset the variables
         event.Z[i]=-1;
         event.Theta[i]=-1;
         event.Energie[i]=-1;
      }
      
      //fill the tree
      t->Fill();
         
      if( !(nevents%1000) ) cout << "Events left = " << nevents << endl;
   }
   
   file.close();
   
   //write the tree in the ROOT file
   t->Write();
   //close the file
   delete ftree;
}
