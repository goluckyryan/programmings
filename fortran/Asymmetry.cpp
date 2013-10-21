#include <iostream>
#include <unistd.h>
#include "TH1F.h"
#include "TCanvas.h"
#include "TRandom.h"

double pi = acos(-1.0);
double deg = 180/pi;
double rad = pi/180; 

double Asymmetry(int YL, int YR){

	return (double)(YL-YR)/(YL+YR);


}

double DeltaAsy(int YL, int YR){

	return 2*sqrt( (YL*YR)/pow(YL+YR,3) );

}

void Gausshist(int n){
	TH1F* histo = new TH1F ( "hpp", "pp elastics", 10, 20, 70);
	TCanvas* canvas = new TCanvas("c1", "pp elastics", 100, 250, 500, 500);
	canvas->Draw();
	canvas->cd();
	for (int i = 1; i <= n ; i++){
		Float_t ran = gRandom->Gaus(45,10); 
		histo->Fill(ran);
		cout << ran << "\t";
		if ( i % 10  == 0){ 
			cout << endl;
			sleep(1);
		}
		histo->Draw();
		canvas->Update();
	}
	canvas->Update();

}

void Customhist(int n=2000, int bin = 5){

	TH1F* histo =(TH1F*) gROOT->FindObject("hpp");
	if (histo){
		histo -> Reset();
		//histo = new TH1F( "hpp", "pp elastics", bin, 20, 70);
	}else {
		histo = new TH1F ( "hpp", "pp elastics", bin, 20, 70);
	}
	TCanvas* canvas = new TCanvas("c1", "pp elastics Yield", 600, 400);
	canvas->Draw();
	canvas->cd();
	gStyle -> SetOptStat("neimr"); // set the statistic display
	histo -> GetXaxis() -> SetTitle("angle");
	histo -> GetYaxis() -> SetTitle("Yield");
	histo -> SetFillColor(3);
	histo -> SetMinimum(0);
	for (int i = 1; i <= n ; i++){
		Float_t ran = gRandom->Uniform(20,70); // uniform distribution
		double f = (1-0.5*ran/70)*(1+0.3*cos(2*ran*rad)); // custom pdf
		histo->Fill(ran, f);
		if ( i % 10  == 0){ 
			histo->Draw();
			canvas->Update();
		}

	}
	canvas->Update();

}

