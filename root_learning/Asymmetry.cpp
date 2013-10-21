#include <iostream>
#include "Riostream.h"
#include <unistd.h>
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TPad.h"

const double pi = acos(-1.0);
const double deg = 180/pi;
const double rad = pi/180; 
const double mp=938.272046;

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
	TCanvas* canvas = new TCanvas("c1", "pp elastics Yield", 670, 0, 600, 370);
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
		//cout << f;
		histo->Fill(ran, f);
		if ( i % 10  == 0){ 
			histo->Draw();
			canvas->Update();
		}

	}
	canvas->Update();

}


double ppCheck(double T1, double theta_1, double T){

//(double error,double T1, double theta_1, double T2, double theta_2){
	
//	double T=300;
	double S;
	double b = sqrt(2*mp*T+T**2)/(mp+T);
	double g = 1/sqrt(1-b**2);
	
	theta_1=theta_1*rad;
//	theta_2=theta_2*rad;
	
//	double momentum_1=sqrt(2*mp*T1+T1**2);
//	double momentum_2=sqrt(2*mp*T2+T2**2);
	
//	S = mp - g*mp - g*(T1+T2) + g*b*(momentum_1*cos(theta_1)+momentum_2*cos(theta_2));
	
	double temp0,temp1;
	
	temp0 = tan(theta_1)**2;
	temp1 = 2*mp+2*mp*temp0+T*temp0;
	
	S = T1- 2*mp*T/temp1;
		
	return S;
}

double ppCheck2(double T, double T1, double theta_1, double T2, double theta_2){
	
	double S;
	double b = sqrt(2*mp*T+T**2)/(mp+T);
	double g = 1/sqrt(1-b**2);
	
//	theta_1=theta_1*rad;
//	theta_2=theta_2*rad;
	
	double momentum_1=sqrt(2*mp*T1+T1**2);
	double momentum_2=sqrt(2*mp*T2+T2**2);
	
	S = mp - g*mp - g*(T1+T2) + g*b*(momentum_1*cos(theta_1)+momentum_2*cos(theta_2));
		
	return S;
}

TH1F* createHisto(char* name, char* title){

	TH1F* hist =(TH1F*) gROOT->FindObject(name);
	if (hist){
		hist -> Reset();
	}else {
		hist = new TH1F ( name, title, 100, 20, 70);
	}
	gStyle -> SetOptStat("neimr"); // set the statistic display
	hist -> GetXaxis() -> SetTitle("angle");
	hist -> GetYaxis() -> SetTitle("Yield");
	hist -> SetFillColor(3);
	hist -> SetMinimum(0);

	return hist;
}

void Genpp(int n=100){

	TCanvas* canvaspp = new TCanvas("cpgen", "Simulation pp elastics Yield", 10, 370, 600, 370);
	canvaspp->Draw();
	canvaspp->cd();
	TH1F* pphist = createHisto("ppPhy", "Physical pp sepctrum ");
	double T, theta_NN, T1, theta_1, T2, theta_2 , theta_d;
	double temp, temp2;
	double ran_T ; 		
	double ran_thetaNN ; 
	// Generaget random event
	for (int i = 1; i <= n ; i++){
		ran_T = gRandom->Uniform(295,305); 		
		ran_thetaNN = gRandom->Uniform(-180,180); 
		
		T = ran_T;
		theta_NN = ran_thetaNN*rad;
		
		T1= T*cos(theta_NN/2)**2;
		theta_1 = atan(sqrt(2*mp*T/(2*mp*T+T**2))*tan(theta_NN/2));
	
        	temp  = tan(theta_1)**2;
   		temp2 = 2*mp-T1*temp;
        	T     = (2*T1*mp*(1+temp))/temp2;
	
		T2 = T*(sin(theta_NN/2))**2;
		theta_2 = atan(sqrt(2*mp*T/(2*mp*T+T**2))/tan(theta_NN/2));
		
		theta_d = atan((2*mp*T+T**2)/(sin(theta_NN)*T**2));


//		cout << T1 << "\t" << theta_1*deg << "\t" << T2 << "\t" << theta_2*deg << "\t"
//		     << "\t|" << T << "\t" << theta_NN*deg << "\t" << theta_d*deg << endl;
		pphist->Fill(theta_1*deg, theta_2*deg); 		
		pphist->Draw();
		canvaspp->Update();
	
	}
	canvaspp->Update();

}



void SimppExp(int n=10000, double error=0.1){

	TH1F* pphist = createHisto("ppMonete", "Monete Carlo pp gate check");
	TH2F* Tanghist = new TH2F("T-ang", "K.E. - angle", 100, 20, 70, 300, 0, 300);
	TCanvas* canvas = new TCanvas("pExp", "Test pp elastics Yield", 670, 0, 600, 370);
	TCanvas* canvas2 = new TCanvas("pExp2", "K.E. - angle of particle 1", 0, 0, 600, 370);
	canvas->Draw();
	canvas2->Draw();
	
	for (int i = 1; i <= n ; i++){
		double ran_Eng1 = gRandom->Uniform(0,350); 
		double ran_Eng2 = gRandom->Uniform(0,350);
		double ran_theta1 = gRandom->Uniform(20,70); 
		double ran_theta2 = gRandom->Uniform(20,70); 
		//double f = (1-0.5*ran/70)*(1+0.3*cos(2*ran*rad)); // custom pdf	
		
		     		
		// dedecue Kinematics
		double T, theta_NN, T1, theta_1, T2, theta_2 , theta_d, p1, p2;
		double temp, temp2;
		
		T1 = ran_Eng1;
		theta_1 = ran_theta1*rad;
		
		
	
        	temp  = tan(theta_1)**2;
   		temp2 = 2*mp-T1*temp;
        	T     = (2*mp*T1*(1+temp))/temp2;        //1
        	theta_NN = atan(sqrt(((T1+2*mp)*temp)/temp2))*2; //2
	
		T2 = T*(sin(theta_NN/2))**2;
		theta_2 = atan((2*mp/(2*mp+T))/tan(theta_1));  //3
		
		p1 = sqrt(2*mp*ran_Eng1+ran_Eng1**2);
		p2 = sqrt(2*mp*ran_Eng2+ran_Eng2**2);
/*		
		cout << "Eng1" << "\t" << "theta1" << "\t" 
			     << "Eng2" << "\t" << "theta2" << "\t"
		     	     << "th1+th2" << "\t" << "Eng1+Eng2" << "\t| " 
		     	     << "T" << "\t" << "Eng2-T2" << "\t"<< "th_2-ran_theta2"<< "\t" //<< theta_NN*deg <<"\t" 
		     	     << ppCheck(ran_Eng1, ran_theta1,300) << "\t"
		     	     << ppCheck2(ran_Eng1,ran_theta1,ran_Eng2,ran_Eng2)<< endl;
*/		
		
//		if ((abs(ran_Eng1+ran_Eng2-T)<5) &&  (abs(ran_theta1+ran_theta2-87.5)<2.5)){

//		if ((abs(ppCheck(ran_Eng1, ran_theta1,300)) < 2)  && (abs(ran_Eng1+ran_Eng2-300)<10) && (abs(ran_theta1+ran_theta2-87)<3) ){

		if ((abs(T-300) < 5)  && (abs(ran_Eng1+ran_Eng2-300)<10) && (abs(ran_theta1+ran_theta2-87.5)<2.5) ){

//		if ((abs(ran_Eng1+ran_Eng2-300) < 5) && (abs(p1*sin(ran_theta1*rad)-p2*sin(ran_theta2*rad)) < 10) && (abs(p1*cos(ran_theta1*rad)+p2*cos(ran_theta2*rad)-sqrt(2*mp*300+300**2)) < 10)){

//		if ((abs(T-300)<5) && (abs(theta_2*deg-ran_theta2) < 1) && (abs(ran_Eng1+ran_Eng2-300)<5)){

//		if ((abs(ran_Eng1+ran_Eng2-300)<5) &&  (abs(ran_theta1+ran_theta2-87.5)<2.5)){

//		if ((abs(ran_Eng1+ran_Eng2-300)<5) && (abs(ran_theta1+ran_theta2-87)<3) && (abs(ppCheck2(ran_Eng1,ran_theta1,ran_Eng2,ran_Eng2))<1)){
			cout << ran_Eng1 << "\t" << ran_theta1 << "\t" 
			     << ran_Eng2 << "\t" << ran_theta2 << "\t"
		     	     << ran_theta1+ran_theta2 << "\t" << ran_Eng1+ ran_Eng2 << "\t| " 
		     	     << T << "\t" << ran_Eng2-T2 << "\t"<< theta_2*deg-ran_theta2<< "\t" //<< theta_NN*deg <<"\t" 
		     	     << ppCheck(ran_Eng1, ran_theta1,300) << "\t"
		     	     << ppCheck2(ran_Eng1,ran_theta1,ran_Eng2,ran_Eng2)<< endl;
			pphist->Fill(ran_theta1); 
			Tanghist -> Fill(ran_theta1,ran_Eng1);
			canvas->cd();
			pphist->Draw();
			canvas2->cd();
			Tanghist->Draw();
			canvas->Update();
			canvas2->Update();		
		}


	}
	canvas->Update();
	canvas2->Update();

}

void ppAcc(int n=1000, double ran_precent=1, double sigma_T=5, double sigma_theta=2.5){

	TH1F* pphist = createHisto("ppMonete", "Monete Carlo pp gate check");
	TH2F* Tanghist = new TH2F("T-ang", "K.E. - angle", 100, 20, 70, 300, 0, 300);
	TCanvas* canvas = new TCanvas("pExp", "Test pp elastics Yield", 670, 0, 600, 370);
	TCanvas* canvas2 = new TCanvas("pExp2", "K.E. - angle of particle 1", 0, 0, 600, 370);
	canvas->Draw();
	canvas2->Draw();
	
	int true_event = 0;
	int count_event = 0;
	int ran_event = 0;
	int count_true = 0;
	int count_ran = 0;
	int missed_true = 0;
	int missed_ran = 0;
	
	for (int i = 1; i <= n ; i++){
		double ran_T = gRandom->Uniform(295,305); 
		double ran_thetaNN = gRandom->Uniform(43,142);
		//double f = (1-0.5*ran/70)*(1+0.3*cos(2*ran*rad)); // custom pdf	
		
		true_event = true_event +1 ;
		
	//generate "real event"
		ran_thetaNN = ran_thetaNN*rad;
		double ran_Eng1, ran_theta1, ran_Eng2, ran_theta2;
		ran_Eng1= ran_T*cos(ran_thetaNN/2)**2;
		ran_theta1 = atan(sqrt(2*mp/(2*mp+ran_T))*tan(ran_thetaNN/2))*deg;
		ran_Eng2= ran_T*sin(ran_thetaNN/2)**2;
		ran_theta2 = atan(-sqrt(2*mp/(2*mp+ran_T))/tan(ran_thetaNN/2))*deg;
		
	// energy lose
//	    cout << ran_Eng1*0.1*sin(ran_theta1*rad) <<"\t"<< ran_theta1 << "\t"
//	         << ran_Eng2*0.1*sin(abs(ran_theta2*rad)) <<"\t"<< ran_theta2 << "\t";
	    ran_Eng1 = ran_Eng1-gRandom->Uniform(0,10);
	    ran_Eng2 = ran_Eng2-gRandom->Uniform(0,10);
	    ran_theta1 = ran_theta1+gRandom->Uniform(-1,1);
	    ran_theta2 = ran_theta2+gRandom->Uniform(-1,1);
	//random event 
		double ran_gen = gRandom->Uniform(0,100);
		if (ran_gen <= ran_precent){
			true_event = true_event -1;
			ran_event = ran_event +1;
			ran_Eng1 = gRandom->Uniform(0,300); 
			ran_Eng2 = gRandom->Uniform(0,300);
			ran_theta1 = gRandom->Uniform(20,70); 
			ran_theta2 = gRandom->Uniform(-70,-20); 
		}
	// noise
		//ran_Eng2 = ran_Eng2 + gRandom->Uniform(-5,0);
		
	// dedecue Kinematics
		double T, theta_NN, T1, theta_1, T2, theta_2 , theta_d, theta_d, p1, p2;
		double temp, temp2;
		
		// test "event"
		T1 = ran_Eng1;
		theta_1 = ran_theta1*rad;
		
	
        	T     = 2*mp/((2*mp/T1+1)*cos(theta_1)**2-1) ;        //1 calculated incident energy from T1 and theta_1
        	theta_NN = atan2(sqrt((2*mp/T1+1)*sin(theta_1)**2),sqrt((2*mp/T1+1)*cos(theta_1)**2-1))*2; //2 calculated com angle
        	theta_d  = atan2(sqrt(8*(2*mp+T)*mp),(sin(theta_NN)*T));
	
		T2 = T*(sin(theta_NN/2))**2;
		theta_2 = atan2(-(2*mp/(2*mp+T)),tan(theta_1));  //3
		
	// checking the calculation	
//		cout << ran_thetaNN*deg << "\t" << theta_NN*deg << "\t" <<  ran_thetaNN*deg - theta_NN*deg << endl;
//		cout << 2*mp/((2*mp/T1+1)*cos(theta_1)**2-1) << "\t" <<2*mp/((2*mp/T2+1)*cos(theta_2)**2-1) << endl; 
//        cout << theta_NN*deg << "\t" << atan2(sqrt((2*mp/T2+1)*cos(theta_2)**2-1),sqrt((2*mp/T2+1)*sin(theta_2)**2))*2*deg <<endl;
		
		
//		p1 = sqrt(2*mp*ran_Eng1+ran_Eng1**2);
//		p2 = sqrt(2*mp*ran_Eng2+ran_Eng2**2);
		
		Tanghist -> Fill(ran_theta1,T1);
		canvas2->cd();
		Tanghist->Draw("colz");
		canvas2->Update();
		
	// ( total energy - incident enegry ) and opening angle
		if ((abs(ran_Eng1+ran_Eng2-T)<sigma_T) &&  (abs(ran_theta1-ran_theta2-theta_d*deg)<sigma_theta)){
	// T1, theta_1 relations , total energy , opening angle
//		if ((abs(ppCheck(ran_Eng1, ran_theta1,300)) < 2)  && (abs(ran_Eng1+ran_Eng2-300)<10) && (abs(ran_theta1+ran_theta2-87)<3) ){
	// incident energy, total energy, openejing angle
//		if ((abs(T-300) <= 5)  && (abs(ran_Eng1+ran_Eng2-300)<10) && (abs(ran_theta1-ran_theta2-87.5)<2.5) ){
	// total energy , momentum 
//		if ((abs(ran_Eng1+ran_Eng2-300) < 5) && (abs(p1*sin(ran_theta1*rad)-p2*sin(ran_theta2*rad)) < 10) && (abs(p1*cos(ran_theta1*rad)+p2*cos(ran_theta2*rad)-sqrt(2*mp*300+300**2)) < 10)){
	// incident energy , angle 2 diff , total enegry
//		if ((abs(T-300)<5) && (abs(theta_2*deg+ran_theta2) < 4) && (abs(ran_Eng1+ran_Eng2-300)<5)){
	// total energy , opening angle
//		if ((abs(ran_Eng1+ran_Eng2-300)<sigma_T) &&  (abs(ran_theta1-ran_theta2-87.5)<sigma_theta)){
	// total enegry , opening angle , ppcheck2
//		if ((abs(ran_Eng1+ran_Eng2-300)<5) && (abs(ran_theta1+ran_theta2-87)<3) && (abs(ppCheck2(ran_Eng1,ran_theta1,ran_Eng2,ran_Eng2))<1)){
			count_event = count_event +1 ;
			count_true = count_true +1;
			pphist->Fill(theta_1*deg); 
			//Tanghist -> Fill(ran_theta1,ran_Eng1);
			canvas->cd();
			pphist->Draw();
			//canvas2->cd();
			//Tanghist->Draw();
			canvas->Update();
			//canvas2->Update();
			if (ran_gen <= ran_precent){
				count_true = count_true -1 ;
				count_ran = count_ran +1;
				cout << "\033[1;34m";
			}
			cout << ran_Eng1 << "\t" << ran_theta1 << "\t" 
			     << ran_Eng2 << "\t" << ran_theta2 << "\t"
		     	     << ran_theta1-ran_theta2 << "\t" << ran_Eng1+ ran_Eng2 << "\t| " 
		     	     << T << "\t" << theta_d*deg << "\t" 
		     	     << ran_Eng2-T2 << "\t"<< theta_2*deg-ran_theta2<< "\t" 
		     	     << ppCheck2(ran_Eng1+ran_Eng2,ran_Eng1,ran_theta1*rad,ran_Eng2,ran_theta2*rad)<< endl;	
		     	cout << "\033[0m";
		     		
		}else{
			cout << "\033[1;31m";
			missed_ran = missed_ran + 1;
			if (ran_gen >= ran_precent){
				missed_ran = missed_ran -1;
				missed_true = missed_true +1;
				cout << "\033[1;33m";
			}
			cout << ran_Eng1 << "\t" << ran_theta1 << "\t" 
			     << ran_Eng2 << "\t" << ran_theta2 << "\t"
		     	     << ran_theta1-ran_theta2 << "\t" << ran_Eng1+ ran_Eng2 << "\t| " 
		     	     << T << "\t" << theta_d*deg << "\t" 
		     	     << ran_Eng2-T2 << "\t" << theta_2*deg-ran_theta2<< "\t" 
		     	     << ppCheck2(ran_T,ran_Eng1,ran_theta1,ran_Eng2,ran_theta2*rad) << endl;	
			cout << "\033[0m";
		}


	}
	canvas->Update();
	canvas2->Update();
	double accurate = 1 - ((double )count_ran+missed_true)/((double )count_true+missed_ran);
	cout << " ------------------------------------------ " << endl;
	cout << " Counted event : " << count_event << "  | real event  : " << true_event << "   | random event : " << ran_event << endl;
	cout << " Counted True  : " << count_true <<  "  | Counted Ran : " << count_ran <<  "   | Rejected true  : " << missed_true << "  | Rejected Ran : " << missed_ran << endl;
	cout << " Accept Rate = " << (double) count_event/true_event*100 << "%  | Accuracy = " << (double) accurate*100 << "%"<<endl;
	
}

	


