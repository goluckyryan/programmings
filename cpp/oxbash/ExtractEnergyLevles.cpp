/***********************************************************************
 * 
 *  This is ExtractEnergyLevels for *.lpe files for Oxbash
 * 
 * -----------------------------------------------------
 *  compilation:
 *  g++ ExtractEnergyLevels.cpp -o ExtractEnergyLevelsr
 *
 * ------------------------------------------------------
 *  created by Ryan (Tsz Leung) Tang, Jan-15, 2019
 *  email: goluckyryan@gmail.com
 * ********************************************************************/

#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <dirent.h>

using namespace std;

int checkExistElement(vector<string> vec, string data){
	for( int i = 0 ; i < vec.size() ; i++){
		if( data == vec[i] ) return 1;
	}
	
	return 0;
}	

vector<double> SplitStr(string tempLine, string splitter, double maxEnergy){

  vector<double> output;

  size_t pos;
  do{
    pos = tempLine.find(splitter, 1); // fine space
    if( pos == 1 ){ //check if it is space again
      tempLine = tempLine.substr(pos+1);
      continue;
    }

    string secStr;
    if( pos == string::npos ){
      secStr = tempLine;
    }else{
      secStr = tempLine.substr(0, pos);
      tempLine = tempLine.substr(pos);
    }

    //check if secStr is begin with space
    if( secStr.substr(0, 1) == " "){
      secStr = secStr.substr(1);
    }

	double energy = atof(secStr.c_str());
	
	if( energy < maxEnergy ) output.push_back(energy);
    //printf(" |%s---\n", secStr.c_str());
    
  }while(pos != string::npos );

  return output;
}

vector<double> combineDoubleVectors(vector<double> vec1, vector<double> vec2){
	vector<double> output;
	output.reserve(vec1.size() + vec2.size());
	output.insert(output.end(), vec1.begin(), vec1.end());
	output.insert(output.end(), vec2.begin(), vec2.end());
	
	return output;
}

vector<string> combineStringVectors(vector<string> vec1, vector<string> vec2){
	vector<string> output;
	output.reserve(vec1.size() + vec2.size());
	output.insert(output.end(), vec1.begin(), vec1.end());
	output.insert(output.end(), vec2.begin(), vec2.end());
	
	return output;
}

vector<double> readFile(string readFile, double maxEnergy){
	
	//--- open file.out
	ifstream file_in;
	file_in.open(readFile.c_str(), ios::in);
	if( !file_in){
		printf("Unable to open %s \n", readFile.c_str());
		exit(1);
	}
	
	vector<double> energy;
	
	string line;
	int lineNum = 0;
	bool startExtractFlag = false;
	while(getline(file_in, line)){
		lineNum ++;
		//printf("%d , %s\n", lineNum, line.c_str());
		
		size_t pos;
		string findStr;
		int findLen;
		
		//---- find start line
		findStr = " energy levels : ";
		findLen = findStr.length();
		pos = line.find(findStr);
		
		if( pos != string::npos){
			startExtractFlag = true;
			continue;
		}
		
		//---- find end line
		findStr = " components greater than";
		findLen = findStr.length();
		pos = line.find(findStr);
		
		if( pos != string::npos){
			startExtractFlag = false;
			break;
		}
		
		//---- extract
		if( startExtractFlag ){
			if( line.length() < 2 ) continue;
			
			vector<double> temp = SplitStr( line, " ", maxEnergy);
			vector<double> oldEnergy = energy;
			energy.clear();
			
			energy = combineDoubleVectors(oldEnergy, temp);
			
			continue;
		}
    }
	
	file_in.close();
	//for( int i = 0; i < energy.size() ; i++){
	//	printf(" %3d | energy : %f \n", i, energy[i]);
	//}
	
	return energy;
}

int main(int argc, char * argv[]){
	
	if( argc < 2 || argc > 3 ) {
		printf("Usage: ./ExtractEnergyLevels directory maxEnergy\n");
		return 1;
	}
	string directory = argv[1];
	double maxEnergy = 1000.;
	if( argc == 3 ) maxEnergy = atof(argv[2]);
	
	//=========== Get file list;
	vector<string> fileList;
	printf("---- opening directory : %s \n", directory.c_str());
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (directory.c_str())) != NULL) {
	  /* print all the files and directories within directory */
	  int count = 0;
	  while ((ent = readdir (dir)) != NULL) {
		string file = (string) ent->d_name;
		int len = file.length();
		if( len < 10 ) continue;
		string ext = file.substr(len - 3);
		if( ext == "lpe" ) {
			fileList.push_back(file);
			count ++;
			//printf ("%3d | %s \n", count, file.c_str());
		}
	  }
	  closedir (dir);
	  
	  //printf("-------------- total # of file : %d \n", (int)fileList.size());
	  
	} else {
	  /* could not open directory */
	  perror ("");
	  return EXIT_FAILURE;
	}
	
	//============= Seperate different group of files
	int count = 0;
	vector<string> calList;
	for( int i = 0 ; i < fileList.size(); i++){
		string model = fileList[i].substr(0,1);
		string isospin = fileList[i].substr(2,1);
		string nParticle = fileList[i].substr(4,1);
		string interaction = fileList[i].substr(5,1);
		string cal = model + isospin + nParticle + interaction;
		int check = checkExistElement(calList, cal);

		//printf(" isospin: %s | %d \n", cal.c_str(), check);
		
		if( check == 0 ){
			calList.push_back(cal);
		}		
	}
	
	const int sizeOfCal = calList.size();
	printf("number of particle in same model space and interaction : %d \n", sizeOfCal);
	
	vector<string> fileArray[sizeOfCal];
	for( int i = 0 ; i < fileList.size(); i++){
		string model = fileList[i].substr(0,1);
		string isospin = fileList[i].substr(2,1);
		string nParticle = fileList[i].substr(4,1);
		string interaction = fileList[i].substr(5,1);
		string cal = model + isospin + nParticle + interaction;
			
			
		for( int j = 0 ; j < calList.size(); j++){
			if( cal == calList[j] ) {
				fileArray[j].push_back(fileList[i]);
			}
		}
	}
	
	for(int i = 0 ; i < sizeOfCal; i++){
		printf("--------- group %d \n", i);
		for( int j = 0; j < fileArray[i].size(); j++){
			printf(" %3d |  %s \n", j+1, fileArray[i][j].c_str());
		}
	}
	
	printf("====================== Maximum Energy : %f \n", maxEnergy);
	//=========== extract energy levels for same group of files
	vector<double> energyLevels [sizeOfCal];
	vector<string> spinParity [sizeOfCal];
	vector<double> bindingEnergy [sizeOfCal];
	//---------- read energy levels
	for( int i = 0 ; i < sizeOfCal ; i ++){
		//printf("--------- group %d \n", i);
		for(int j = 0 ; j < fileArray[i].size() ; j ++){
			string filePath = directory + "/" + fileArray[i][j];
			string spin = fileArray[i][j].substr(1,1);
			string parity = fileArray[i][j].substr(3,1);
			string sp;
			if( parity == "0" || parity == "2" ) {
				if( spin.compare("a") == 0 ) spin = "10";
				if( spin.compare("b") == 0 ) spin = "11";
				if( spin.compare("c") == 0 ) spin = "12";
				if( spin.compare("d") == 0 ) spin = "13";
				if( spin.compare("e") == 0 ) spin = "14";
				if( spin.compare("f") == 0 ) spin = "15";
				if( spin.compare("g") == 0 ) spin = "16";
				if( spin.compare("h") == 0 ) spin = "17";
				if( spin.compare("i") == 0 ) spin = "18";
				if( spin.compare("j") == 0 ) spin = "19";
				if( spin.compare("k") == 0 ) spin = "20";
				if( spin.compare("l") == 0 ) spin = "21";
				if( spin.compare("m") == 0 ) spin = "22";
				if( spin.compare("n") == 0 ) spin = "23";
				if( spin.compare("o") == 0 ) spin = "24";
            if( atoi(spin.c_str()) % 2 == 0 ){
					sp = to_string(atoi(spin.c_str())/2) + "+";
				}else{
					sp = spin + "/2+";
				}
			}
			if( parity == "1" ){
				if( atoi(spin.c_str()) % 2 == 0 ){
					sp = to_string(atoi(spin.c_str())/2) + "-";
				}else{
					sp = spin + "/2-";
				}
			}	
			vector<double> energyList  = readFile(filePath, maxEnergy);
			vector<string> spList;
			for( int i = 0; i < energyList.size(); i++){
				spList.push_back(sp);
			}
			
			vector<double> oldEnergy = energyLevels[i];
			energyLevels[i].clear();
			energyLevels[i] = combineDoubleVectors(oldEnergy, energyList);

			vector<string> oldsp = spinParity[i];
			spinParity[i].clear();
			spinParity[i] = combineStringVectors(oldsp, spList);
						
		}
		
		//for( int j = 0; j < energyLevels[i].size() ; j++){
		//	printf(" %3d | energy : %9f %s \n", j, energyLevels[i][j], spinParity[i][j].c_str());
		//}
	}
	
	//=========== sorting energy
	for( int i = 0 ; i < sizeOfCal ; i ++){
		for( int p = 0 ; p < energyLevels[i].size() - 1; p ++){
			for( int q = 0 ; q < energyLevels[i].size() - p - 1; q++){
				if( energyLevels[i][q] > energyLevels[i][q+1]){
					double temp = energyLevels[i][q];
					energyLevels[i][q] = energyLevels[i][q+1];
					energyLevels[i][q+1] = temp;
					
					string tempSp = spinParity[i][q];
					spinParity[i][q] = spinParity[i][q+1];
					spinParity[i][q+1] = tempSp;
				}
			}	
		}
		
	}
	
	//=========== offset
	for( int i = 0 ; i < sizeOfCal ; i ++){
		if( energyLevels[i][0] == 0 ) continue;
		double refEnergy = energyLevels[i][0];
		for( int j = 0; j < energyLevels[i].size() ; j++){
			energyLevels[i][j] = energyLevels[i][j] - refEnergy;
		}
	}

	//=========== check if energy > maxEnergy;
	for( int i = 0 ; i < sizeOfCal ; i ++){
		for( int j = energyLevels[i].size() - 1; j >= 0  ; j--){
			if( energyLevels[i][j] > maxEnergy) energyLevels[i].erase(energyLevels[i].begin() + j );
		}
	}
	
  printf("first 5 levels and spin-parity\n");
	for( int i = 0 ; i < sizeOfCal ; i ++){
		printf("------------------ group %d \n", i);
		int nDisplay = 5;
		if ( energyLevels[i].size() < 5) nDisplay = energyLevels[i].size();
		for( int j = 0; j < nDisplay ; j++){
			printf(" %3d | energy : %9f j_pi: %s \n", j, energyLevels[i][j], spinParity[i][j].c_str());
		}
		if( energyLevels[i].size() > 5 ) printf(" .... %d in total \n", (int) energyLevels[i].size() );
	}
	
	printf("======================\n");
	//=========== save into files
	for( int i = 0 ; i < sizeOfCal ; i++){
		FILE * file_out;
		string outFileName = fileArray[i][0].substr(0,6);
		outFileName.replace(1,1, "X");
		outFileName.replace(3,1, "X");
		string outFilePath = directory + "/" + outFileName + ".txt"; 
		file_out = fopen(outFilePath.c_str(), "w+");
		printf(" group %i saved to : %s \n", i, outFilePath.c_str());
		for( int j = 0; j < energyLevels[i].size(); j++){
			fprintf(file_out, " %3d | %9f %s \n", j, energyLevels[i][j], spinParity[i][j].c_str());
		}
		fclose(file_out);
	}
	
	
	return 0;
}

