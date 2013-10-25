#include <iostream>
#include "TH1F"
#include "TCanvas"
#include "TObjArray"

void test(){

	char name[10], title[20]; 
	TObjArray Hlist(0);
	TH1F* h;	// create a pointer to a histogram 
	TCanvas* canvas = new TCanvas;
	h = new TH1F("","",100,-4,4); 
	// make and fill 15 histograms and add them to the object array 
	for (Int_t i = 0; i < 15; i++) {
	   h->Reset();
		sprintf(name,"h%d",i); 
		sprintf(title,"histo nr:%d",i);
		h->SetName(name);
		h->SetTitle(title);
		h->FillRandom("gaus",1000);
		h->Draw();
		canvas->Update();
	}
	TFile f("demo.root","recreate");
	Hlist->Write();
	f.Close();
	
}

