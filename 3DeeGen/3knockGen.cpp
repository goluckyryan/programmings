/*-----------

this program is used for generate the cross section and analysis power by the code 3Dee

the reaction is (p,pn) knockout in invert kinematics, which means
in the lab frame, the Oxygen nucleus is moving while the proton is target,
the reaction in lab frame is p( , )pn

the input parameters are:

1) MA : mass number of Oxygen isotope (i just wrote the code the oxygen, 
                            for other nucleus, the spin has to be change)
2) N L J : the shell number of orbital neutron
3) TiL : (same as TA in 3Dee code) incident energy if oxygen isotopes in Lab frame
4) BE : guess binding energy of the orbital nuetron

//// the flow of this program
1) from the input parameters, MA and Ti, it looping the momentum of the orbital nuetron, k; 
   the angle just before coilld with proton theta_k and 
   the CM frame scattered angle theta_NN 
2) it call the "knockoutLibrary.h", which calculate the kinetmatic by impulse approximation
3) the "knockoutLibrary.h" has globel varibale of the necleons momemtums in diffference frame
4) the 3Dee code run in Oxygen frame, thus we use the momentum in Oxygen frame calculated 
   by knockout, which are Tc (scattered neutron KE), theta_c (out-going angle of scattered neutron)
   and theta_d (scattered proton)
5) using the parameters MA, N L J, Tc, BE, theta_c and theta_d to generate a infile.
6) the infile will be feeded to 3Dee code and generated outfile
7) read out the outfile for the cross section and analysising power
8) save the parameters


*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <stdio.h>
#include <ctime>
#include <cstring>
#include "knockoutLibrary.h" // constains function to calaculate the kinematics

using namespace std;

void make_infile(int MA, float Ta, int N, int L, float J, float BE, float Tc, float theta_c, float theta_d);
void read_outfile();
string symbolL(int L);

double xsec,PWIA,DWIA,A00n0;

int main(int argc, char *argv[]){
     time_t Tstart=time(0);

     //the input is MA, N L J Ti,  BE
     // the program run k, theta_k, and theta_NN

     //Check input
    if(argc < 6) {
 	cout << "===============Generating Oxygen (p,pn) knockout data======================" << endl
 	     << "          Only for p(O,O*)pn neutron knockout [A(a,cd)b]" << endl
	     << "Usage: ./3knockGee.o MA N L J Ti BE " << endl
	     << "     MA = Mass number of Oxygen isotop" << endl
	     << "  N L J = shell number for orbital neutron" << endl
	     << "     Ti = incident energy of Oxygen MeV/A (auto-roundoff to interger)" << endl
	     << "     BE = binding enegry of orbital neutron (auto-roundoff the XX.X)" << endl
	     << "  **** (p,2p) or others setting, change infile.temp or change the 3knockGee.cpp"<< endl << endl;
	exit(0);
    }

    int MA = atoi(argv[1]);
    ma_num=MA;
    int N = atoi(argv[2]);
    int L =atoi(argv[3]);
    float J = atof(argv[4]);
    float TiL = atof(argv[5]);
    float BE = atof(argv[6]);

    float Tc, theta_c, Td, theta_d;

    string filename;
    stringstream tempfilename;
    tempfilename << MA << "O_" << N << symbolL(L) << 2*J << "_BE" << BE << "_TiL" << TiL << ".dat";
    filename =tempfilename.str();
    
    ofstream paraOut;
    paraOut.open(filename.c_str());

    paraOut << " ##### " << MA << "O(p,pn)" << MA-1 << "O    " << N << symbolL(L) << J << " BE=" <<BE << " TiL=" << TiL <<endl;
    paraOut << " k\ttheta_\tthet_NN\tT1L\ttheta_1L\tT2L\ttheta_2L\tTc\ttheta_c\ttd\ttheta_d\t\txsec\tPWIA\t\tDWIA\tA00n0 "<< endl;
    paraOut << " c1 \tc2 \tc3 \tc4 \tc5 \t\tc6 \tc7 \tc8 \t\tc9 \tc10 \tc11 \tc12 \t\tc13 \t\tc14 \tc15"<< endl;
    
    int kstep=5;
    int kstart=10/kstep, kend=100/kstep;
    int istep=5;
    int istart=10/istep, iend=175/istep;
    int jstep=5;
    int jstart=10/jstep, jend=175/jstep;
    int counter=0;

    for (int kk=kstart; kk<=kend; kk++){
    
        k = kk*kstep;
    
        if (k==0){
            for(int j=jstart; j<=jend;j++){


            Theta_k=90*pi/180;
            Theta_NN=j*jstep*pi/180;

            Simulation(MA, TiL, k, Theta_k, 0, Theta_NN, 0, BE);
            
            //Display();
            
            Tc=FindT(P2,m2);
            theta_c= Theta(P2)*180/pi;
            Td=FindT(P1,m1);
            theta_d=-Theta(P1)*180/pi;
            T1L=FindT(P1L,m1);
            theta_1L= -Theta(P1L)*180/pi;
            T2L=FindT(P2L,m2);
            theta_2L=-Theta(P2L)*180/pi;
            
            

            cout << "Setting : k=" << k << ", theta_k=" << Theta_k*180/pi << ", theta_NN=" << Theta_NN*180/pi << " | ";

            // make_infile
            cout << "mk infile :" << Tc << ", "  <<theta_c <<", "<< theta_d<<endl;
            make_infile(MA, TiL, N, L, J, BE, Tc, theta_c, theta_d);

            paraOut << k << "\t" << Theta_k*180/pi << "\t" << Theta_NN*180/pi << "\t" << T1L << "\t" <<theta_1L << "\t"  << T2L << "\t" << theta_2L  << "\t" << Tc << "\t" <<theta_c << "\t"  << Td << "\t" << theta_d << "\t";

            // run 3Dee code
            system("./threedee infile");
            counter=counter+1;

            // read_outfile : xsec + A00n0
            read_outfile();

            // save parameters + readout
            paraOut << xsec << "\t" << PWIA << "\t" << DWIA <<"\t" << A00n0 << endl;

            //Delete outfile
            remove("outfile");

            }
            paraOut<< endl;
        
        }else {
        
        for (int i=istart; i<=iend; i++){
            for(int j=jstart; j <=jend;j++){


            Theta_k=i*istep*pi/180;
            Theta_NN=j*jstep*pi/180;

            Simulation(MA, TiL, k, Theta_k, 0, Theta_NN, 0, BE);
            
            //Display();
            
            Tc=FindT(P2,m2);
            theta_c= Theta(P2)*180/pi;
            Td=FindT(P1,m1);
            theta_d=-Theta(P1)*180/pi;
            T1L=FindT(P1L,m1);
            theta_1L= -Theta(P1L)*180/pi;
            T2L=FindT(P2L,m2);
            theta_2L=-Theta(P2L)*180/pi;
            
            

            cout << "Setting : k=" << k << ", theta_k=" << Theta_k*180/pi << ", theta_NN=" << Theta_NN*180/pi << " | ";

            // make_infile
            cout << "mk infile :" << Tc << ", "  <<theta_c <<", "<< theta_d<<endl;
            make_infile(MA, TiL, N, L, J, BE, Tc, theta_c, theta_d);

            paraOut << k << "\t" << Theta_k*180/pi << "\t" << Theta_NN*180/pi << "\t" << T1L << "\t" <<theta_1L << "\t"  << T2L << "\t" << theta_2L  << "\t" << Tc << "\t" <<theta_c << "\t"  << Td << "\t" << theta_d << "\t";

            // run 3Dee code
            system("./threedee infile");
            counter=counter+1;

            // read_outfile : xsec + A00n0
            read_outfile();

            // save parameters + readout
            paraOut << xsec << "\t" << PWIA << "\t" << DWIA <<"\t" << A00n0 << endl;

            //Delete outfile
            remove("outfile");
            
            }
            paraOut<< endl;
        }
        paraOut << endl;
        }
    }

    paraOut.close();
   

    time_t Tend=time(0);
    double deltatime=0;
    deltatime=difftime(Tend,Tstart);
    double min=0, sec=0;
    sec=fmod(deltatime,60);
    min=(deltatime-sec)/60;
    cout << "==========  Totol run time " << deltatime << " sec = "<< min << " mins " << sec <<" sec ================" << endl
         << "         total number calaculated " << counter << ", number per sec = " << (double)counter/difftime(Tend,Tstart) << endl
         << "        k =(" << kstart << "," <<kend << "," << kstep << ") theta_k=(" << istart*istep << "," << iend*5 << "," << istep <<") thet_NN=(" << jstart*jstep <<"," << jend*jstep <<"," <<jstep <<")" << endl
         << "           condition " << MA << "O(p,pn)" << MA-1 << "O    " << N << symbolL(L) << J << endl
         << "     assume Binding energy of orbital neutron is " << BE << endl
         << "output file :" << filename  << endl
         << "  k  theta_k theta_NN  Tc  theta_c Td theta_d  xsec  PWIA   DWIA   A00n0 "<< endl;

    return 0;

}

//**************functions**********************************
string symbolL(int L){

    switch (L){
    	case 0: return "s";break;
    	case 1: return "p";break;
    	case 2: return "d";break;
    	case 3: return "f";break;
    	case 4: return "g";break;
    	case 5: return "h";break;
    	case 6: return "i";break;
    }
}


void make_infile(int MA, float Ta, int N, int L, float J, float BE, float Tc, float theta_c, float theta_d){

    stringstream MAstr, Tastr, Nstr, Lstr, Jstr, BEstr, Tcstr, theta_cstr,theta_dstr;
    MAstr << MA;
    Tastr<<Ta;
    Nstr << N;
    Lstr <<L;
    Jstr <<J;
    BEstr <<BE;
    Tcstr<<Tc;
    theta_cstr<<theta_c;
    theta_dstr<<theta_d;


    if(theta_c <0){
        cout << " ### theta_c should be positive. " << endl;
        exit(0);
    }
    if(MA <14 || MA>24 ){
        cout << " only Oxygen 14 to 24 !! " << endl;
        exit(0);
    }
    if((10*MA)%10 !=0 ) {
        cout << " Mass number (int) is enought ." << endl;
        exit(0);
    }
    if((10*N)%10 !=0 || (10*L)%10 != 0 || fmod(J*10,5) !=0 || abs(L-J) != 0.5 ){
        cout << "N L J is not well defined" << endl;
        exit(0);
    }


    //read infile.temp___________________
    string line[19];
    ifstream file_in;
    file_in.open("infile.temp");

    if (!file_in) {
        cerr << "Unable to open file infile";
        exit(1);   // call system to stop
    }

    for(int i=1; i<=18; i++){
        getline(file_in,line[i]);
        //cout << "line " << i << "\t: " << line[i] << endl;
    }
    file_in.close();

    //modify___________________________

    std::ostringstream line1;
    line1 << MA << "O(p,pn)" << MA-1 << "O    " << N << symbolL(L) << J << "   Relativitic, Ta =" << Ta ;
    line[1]= line1.str();

    // string.replace( start pos, number of pos, string )
    line[4]=line[4].replace(10,1,Nstr.str());
    line[4]=line[4].replace(20,1,Lstr.str());
    line[4]=line[4].replace(30,3,Jstr.str());

    line[5]=line[5].replace(0,2,MAstr.str());
    int lengthTa=(Tastr.str()).length();
    if (lengthTa >10){
        cout << "Ta is larger then 8 digit." << endl;
        exit(4);
    }
    line[5]=line[5].replace(40,10,"          "); //reset;
    line[5]=line[5].replace(40,lengthTa,Tastr.str());

    std::stringstream MBstr;
    MBstr << MA-1;
    line[8]=line[8].replace(0,2,MBstr.str()) ;


    //MA , JA, JB
    string JA,JB;

    switch(MA){
    	case 14: JA="0. "; JB="0.5";break;
    	case 15: JA="1.5"; JB="0. ";break;
    	case 16: JA="0. "; JB="1.5";break;
        case 17: JA="2.5"; JB="0. ";break;
        case 18: JA="0. "; JB="2.5";break;
        case 19: JA="2.5"; JB="0. ";break;
        case 20: JA="0. "; JB="2.5";break;
        case 21: JA="2.5"; JB="0. ";break;
        case 22: JA="0. "; JB="1.5";break;
        case 23: JA="1.5"; JB="0. ";break;
        case 24: JA="0. "; JB="1.5";break;
    }
    line[3]=line[3].replace(0,3,JA);
    line[3]=line[3].replace(10,3,JB);


    //line14 BE
    int lengthBE=(BEstr.str()).length();
    line[14]=line[14].replace(0,10,"          "); //reset
    line[14]= line[14].replace(40,lengthBE,BEstr.str());


    //line17 Tc, theta_c, theta_d
    int lengthTc=(Tcstr.str()).length();
    int lengththeta_c=(theta_cstr.str()).length();
    int lengththeta_d=(theta_dstr.str()).length();
    line[17]=line[17].replace(0,10,"          "); //reset
    line[17]=line[17].replace(10,10,"          "); //reset
    line[17]=line[17].replace(20,10,"          "); //reset
    line[17]=line[17].replace(0,lengthTc,Tcstr.str());
    line[17]=line[17].replace(10,lengththeta_c,theta_cstr.str());
    line[17]=line[17].replace(20,lengththeta_d,theta_dstr.str());

    ofstream file_out;
    file_out.open("infile");

    for(int i=1; i<=18; i++){
        file_out << line[i] << endl;
        //cout << "line " << i << " : " << line[i] << endl;
    }
    file_out.close();

}


void read_outfile(){ //copy from read_out.cpp

    string x,str;
    string xsecstr,PWIAstr,DWIAstr,A00n0str;

    ifstream file_in;
    file_in.open("outfile");

    if (!file_in) {
        cerr << "Unable to open file outfile";
        exit(1);   // call system to exit
    }

    //cout << "outfile opened." << endl;

    while(file_in >> x){
        str = str+x;
    }

    size_t found;
    found=str.find("Cross");
    if (found!=string::npos){
        xsecstr=str.substr(found+10,20);
        xsec= atof(xsecstr.c_str()) ;
        //cout << " Cross Section = " << xsec  << " [mb]" << endl << endl;
    }

    found=str.find("PWIA");
    if (found!=string::npos){
        PWIAstr=str.substr(found+11,20);
        PWIA= atof(PWIAstr.c_str()) ;
        //cout << " PWIA x-Section = " << PWIA  << " [mb]" << endl << endl;
    }

    found=str.find("DWIA");
    if (found!=string::npos){
        DWIAstr=str.substr(found+11,20);
        DWIA= atof(DWIAstr.c_str()) ;
        //cout << " DWIA x-Section = " << DWIA  << " [mb]" << endl << endl;
    }

    found=str.find("A00n0");
    if (found!=string::npos){
        A00n0str=str.substr(found+5,20);
        A00n0= atof(A00n0str.c_str()) ;
        //cout << " PWIA A00n0 = " << A00n0  << endl << endl;
    }

	file_in.close();

}
