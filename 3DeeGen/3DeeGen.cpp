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

using namespace std;

void make_infile(int MA, float Ta, int N, int L, float J, float BE, float Tc, float theta_c, float theta_d);
void read_outfile();
string symbolL(int L);

double xsec,PWIA,DWIA,A00n0;

int main(int argc, char *argv[]){
     time_t Tstart=time(0);

     if(argc < 7) {
 	cout << "===============Generating Oxygen (p,pn) knockout data======================" << endl
 	     << "          Only for O(p,pn)O knockout [A(a,cd)b]" << endl
	     << "Usage: ./3DeeGee.o MA N L J BE Tc " << endl
	     << "     MA = Mass number of Oxygen isotop" << endl
	     << "     Ti = incident K.E of proton" << endl
	     << "  N L J = shell number for orbital neutron" << endl
	     << "     BE = binding energy of orbital neutron" << endl
	     << "     Tc = K.E. of knockouted neutron" << endl
	     << "  **** (p,2p) or others setting, change infile.temp"<< endl << endl;
	exit(0);
    }

    int MA = atoi(argv[1]);
    float Ti=atof(argv[2]);
    int N = atoi(argv[3]);
    int L =atoi(argv[4]);
    float J = atof(argv[5]);
    float BE = atof(argv[6]);
    float Tc = atof(argv[7]);


    ofstream paraOut;
    paraOut.open("paraOut.dat");

    paraOut << " ##### " << MA << "O(p,pn)" << MA-1 << "O    " << N << symbolL(L) << J << " BE=" <<BE << ", Tc=" <<Tc <<endl;



    for (float theta_c=20; theta_c <=70; theta_c++){
        for (float theta_d=-70; theta_d <=-20; theta_d++){

            // make_infile
                cout << "making infile :" << BE << ","<< Tc << "," << theta_c <<","<< theta_d<<endl;
            make_infile(MA, Ti, N, L, J, BE, Tc, theta_c, theta_d);

            paraOut << theta_c << "\t" << theta_d << "\t";

            // run 3Dee code
            system("./threedee infile");

            // read_outfile : xsec + A00n0
            read_outfile();
                //cout << " Cross Section = " << xsec  << " [mb]" << endl ;
                //cout << " PWIA x-Section = " << PWIA  << " [mb]" << endl;
                //cout << " DWIA x-Section = " << DWIA  << " [mb]" << endl ;
                //cout << " PWIA A00n0 = " << A00n0  << endl ;

            // save parameters + readout
                //cout << "saving parameters" << endl << "**********************" <<endl;
            paraOut << xsec << "\t" << PWIA << "\t" << DWIA <<"\t" << A00n0 << endl;

            //Delete outfile
            remove("outfile");
        }
        paraOut << endl;
    }

    paraOut.close();

    time_t Tend=time(0);
    cout << "=======================Totol run time " << difftime(Tend,Tstart) <<" s ============================" << endl
         << "  generated data from angle " << 20 << " to " << 70 << " step 1 "<< endl
         << "  condition " << MA << "O(p,pn)" << MA-1 << "O    " << N << symbolL(L) << J << "   Tc =" << Tc << endl
         << "  assume Binding energy of orbital neutron is " << BE << endl
         << "in file : paraOut.dat" << endl
         << "  theta_c  theta_d  xsec  PWIA   DWIA   A00n0 "<< endl;

    return 0;

}

//************************************************
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
        xsecstr=str.substr(found+10,10);
        xsec= atof(xsecstr.c_str()) ;
        //cout << " Cross Section = " << xsec  << " [mb]" << endl << endl;
    }

    found=str.find("PWIA");
    if (found!=string::npos){
        PWIAstr=str.substr(found+11,10);
        PWIA= atof(PWIAstr.c_str()) ;
        //cout << " PWIA x-Section = " << PWIA  << " [mb]" << endl << endl;
    }

    found=str.find("DWIA");
    if (found!=string::npos){
        DWIAstr=str.substr(found+11,10);
        DWIA= atof(DWIAstr.c_str()) ;
        //cout << " DWIA x-Section = " << DWIA  << " [mb]" << endl << endl;
    }

    found=str.find("A00n0");
    if (found!=string::npos){
        A00n0str=str.substr(found+5,10);
        A00n0= atof(A00n0str.c_str()) ;
        //cout << " PWIA A00n0 = " << A00n0  << endl << endl;
    }

	file_in.close();

}
