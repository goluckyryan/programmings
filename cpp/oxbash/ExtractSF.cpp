/***********************************************************************
 * 
 *  This is ExtractSF for *.lpe files for Oxbash
 * 
 * 
 * -----------------------------------------------------
 *  compilation:
 *  g++ ExtractSF.cpp -o ExtractSF
 *
 * ------------------------------------------------------
 *  created by Ryan (Tsz Leung) Tang, Jan-16, 2019
 *  email: goluckyryan@gmail.com
 * ********************************************************************/

#include <fstream>
#include <stdlib.h>
#include <stdio.h>
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

string StateConvertor(int n, int l, int j){

  string output;

  string lStr;
  switch(l){
    case 0: lStr = "s"; break;
    case 1: lStr = "p"; break;
    case 2: lStr = "d"; break;
    case 3: lStr = "f"; break;
    case 4: lStr = "g"; break;
    case 5: lStr = "h"; break;
    case 6: lStr = "i"; break;
    case 7: lStr = "j"; break;
    case 8: lStr = "k"; break;
  }

  output =  to_string(n) + lStr + to_string(j);
  
  return output;

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

vector< vector<double> > combineDoubleVectorsVectors(vector< vector<double> > vec1, vector< vector<double> > vec2){
  vector< vector<double> > output;
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

class CombineVectors{
public:
  CombineVectors(){
    combinedSPO.clear();
    combinedEnergySF.clear();
    numberOfAdd = 0;
  };
  ~CombineVectors(){};

  vector<string> combinedSPO;
  vector< vector<double> > combinedEnergySF;
  
  void PrintSPO(){
    for(int i = 0; i < combinedSPO.size(); i++){
      printf("%8s, \n", combinedSPO[i].c_str()); 
    }
  }
  
  void PrintDoubleVector(vector<double> vec){
    for(int j = 0; j < vec.size(); j++){
      printf("%8.3f, ", vec[j]); 
    }
    printf("\n");
  } 
  
  void PrintIntVector(vector<int> vec){
    for(int j = 0; j < vec.size(); j++){
      printf("%8d, ", vec[j]); 
    }
    printf("\n");
  }  
  
  void PrintStringVector(vector<string> vec){
    for(int j = 0; j < vec.size(); j++){
      printf("%8s, ", vec[j].c_str()); 
    }
    printf("\n");
  }
  
  void Print(){
    
    printf("--------------- number of adding %d\n", numberOfAdd);
    
    printf("%8s  ", "");
    printf("%8s  ", "");
    for( int i = 0 ; i < combinedSPO.size(); i++){
      printf("%8s, ", combinedSPO[i].c_str());
    }
    printf("\n");
    
    for( int i = 0 ; i < combinedEnergySF.size(); i++){
      for( int j = 0 ; j < combinedEnergySF[i].size(); j++){
        printf("%8.3f, ", combinedEnergySF[i][j]);
      }
      printf("\n");
    }
    printf("---------------------------------\n");
  }
  
  void AddVector(vector<string> SPO, vector< vector<double> > energySF){
    if( numberOfAdd == 0 ){
      combinedSPO = SPO;
      combinedEnergySF = energySF;
      
    }else{
    
    int numNewSPO = 0; 
      for( int i = 0;  i < SPO.size(); i++){
    bool matchedFlag = false;
    for( int j = 0 ; j < combinedSPO.size(); j++){
      //printf("%d|%s|%d|%s|\n", i, combinedSPO[i].c_str(), j, SPO[j].c_str());
          if( combinedSPO[j].compare(SPO[i]) == 0 ) {
         matchedFlag = true;
       break;
      }
        }
    if(!matchedFlag){
      numNewSPO++;
      combinedSPO.push_back(SPO[i]);
    }
      }

    //reconstruct the new coming energySF 
      vector< vector<double> > temp;
      for( int i = 0; i < energySF.size(); i++){
        vector< double> zero;
        temp.push_back(zero);
        temp[i].push_back(energySF[i][0]); //put back the spin
        temp[i].push_back(energySF[i][1]); //put back the energy
    for( int j = 0; j < combinedSPO.size(); j++){
      bool matchedFlag = false;
      for( int k = 0; k < SPO.size(); k++){
        if( combinedSPO[j].compare(SPO[k]) == 0 ){
          temp[i].push_back(energySF[i][k+2]);
          matchedFlag = true;
          break;
        }
      }
      if( !matchedFlag ) temp[i].push_back(0);
      
      
    }
    
      }
    
    // add zero in existing vector
      for( int i = 0 ; i < combinedEnergySF.size(); i++){
        for( int j = 0; j < numNewSPO; j++){
          combinedEnergySF[i].push_back(0);
        }
      }
    
    // add new energySF
      combinedEnergySF = combineDoubleVectorsVectors(combinedEnergySF, temp);
      
    }
    
    numberOfAdd++;
   
  }
  
  void SortEnergy(){
    for( int p = 0; p < combinedEnergySF.size() - 1; p++){
    for( int q = 0; q < combinedEnergySF.size() - p-1; q++){
      if( combinedEnergySF[q][1] > combinedEnergySF[q+1][1]){
        //swap
        vector<double> temp = combinedEnergySF[q];
        combinedEnergySF[q] = combinedEnergySF[q+1];
        combinedEnergySF[q+1]= temp;
      }
    }  
    }
  }

  void GroundStateEnergyReset(){
    double refEnergy = combinedEnergySF[0][1];
    if( refEnergy == 0 ) return;
    
    for( int p = 0; p < combinedEnergySF.size(); p++){
      combinedEnergySF[p][1] = combinedEnergySF[p][1] - refEnergy;
    }
  }

  
private:

  int numberOfAdd;
  
};

class ReadLSFFile{
public:
  ReadLSFFile(string readFile, double maxEnergy, double minSF, int mode);
  ~ReadLSFFile(){};
  
  int numState;
  
  vector< vector<double> > energySF; // SF[energyID][stateID], SF[energyID][0] = energy
  vector<string> SPO;
  
  void Print(){
    printf("%10s","");
    for( int i = 0; i < SPO.size(); i++){
      printf("%10s", SPO[i].c_str()); 
    }
    printf("\n");
    for( int i = 0 ; i < energySF.size(); i++){
      for( int j = 0 ; j < energySF[i].size(); j++){
        printf("%10.3f", energySF[i][j]);
      }
      printf("\n");
    }
  }
private:
  
};

ReadLSFFile::ReadLSFFile(string readFile, double maxEnergy, double minSF, int mode){

  //--- open file.out
  ifstream file_in;
  file_in.open(readFile.c_str(), ios::in);
  if( !file_in){
    printf("Unable to open %s \n", readFile.c_str());
    exit(1);
  }
  
  energySF.clear();
  SPO.clear();
  numState = 0;
  
  //printf("----------------- %s \n", readFile.c_str());
  vector<double> temp;
  
  string line;
  int lineNum = 0;
  bool startExtractFlag = false;
  size_t pos, pos2;
  string findStr;
  int findLen;
  int stateLineNum = 0;
  while(getline(file_in, line)){
    lineNum ++;

    //---- find single-particle-state
    pos = line.find("(");
    pos2 = line.find(")", pos);
    if( pos != string::npos ) stateLineNum ++;
    while(pos2 != string::npos && pos != string::npos){
      
      string state = line.substr(pos+1, pos2-pos-1);
      numState ++;
      int n = atoi(state.substr(0,1).c_str()) - 1;
      int l = atoi(state.substr(2,1).c_str());
      int j = atoi(state.substr(4,2).c_str());
      state = StateConvertor(n, l, j);
      //printf("%d |%s\n", numState, state.c_str());
      SPO.push_back(state);
      pos = line.find("(", pos2);
      pos2 = line.find(")", pos2+1); 

    };
  
    if( lineNum < 3 + stateLineNum ) continue;
    
    //printf("%d |%s\n", lineNum, line.c_str());
    startExtractFlag = true;
    temp.clear();
    
    //---- find end line
    findStr = " total =";
    findLen = findStr.length();
    pos = line.find(findStr);
    
    if( pos != string::npos){
      startExtractFlag = false;
      break;
    }
    
    //---- extract
    if( startExtractFlag ){
      if( line.length() < 2 ) continue;
      
      double twoSpin;
      double eng;
      if( mode == 0 ){
        eng = atof(line.substr(29, 8).c_str());
        twoSpin = atof(line.substr(19,2).c_str());
      }else{
        eng = atof(line.substr(11, 8).c_str());
        twoSpin = atof(line.substr(1,2).c_str());
      }
      
      if( eng > maxEnergy ) continue;
      
      //printf(" 2*spin: %f , energy %f \n", twoSpin, eng);
      
      temp.push_back(twoSpin);
      temp.push_back(eng);
      for( int i = 0; i < numState; i++){
        double sfvalue = atof(line.substr(37 + 9 * i, 9).c_str());
        temp.push_back(sfvalue);
      }
    
      energySF.push_back(temp);
      
      continue;
    }
    
  }
  
  //---- delete SF < minSF
  for( int i = energySF.size() - 1 ; i > 0 ; i--){ // keep the lowest state, us eto calculate the g.s. energy
    // find maxSF, if maxSF < minSF, erase that row
    double maxSF = 0;
    for( int j = 2; j < energySF[i].size(); j++){
      if( energySF[i][j] > maxSF ) maxSF = energySF[i][j];
    }
    if( maxSF < minSF ) {
      energySF.erase(energySF.begin()+i);
    }
  }
  

  //for( int i = 0; i < energySF.size() ; i++){
  //  printf(" %3d | energy : %f |", i, energySF[i][0]);
  //  for( int j = 0; j < numState; j++){
  //    printf(" %f,", energySF[i][j+1] );
  //  }
  //  printf("\n");
  //}
}

//######################## Main ###################
int main(int argc, char * argv[]){
  
  if( argc < 2 || argc > 5 ) {
    printf("Usage: ./ExtractSF directory maxEnergy\n");
    return 1;
  }
  string directory = argv[1];
  double maxEnergy = 1000.;
  double minSF = 0.001;
  int mode = 0;  // group based on 1,2 letter of the filename
                 // group based on 6,7 letter of the filename
  if( argc >= 3 ) maxEnergy = atof(argv[2]);
  if( argc >= 4 ) minSF = atof(argv[3]);
  if( argc >= 5 ) mode = atoi(argv[4]);
  
  printf("############## Max Energy : %6.2f MeV\n", maxEnergy);
  printf("##############     Min SF : %6.4f\n", minSF);
  printf("##############       Mode : %6d\n", mode);
  
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
      if( ext == "lsf" ) {
        fileList.push_back(file);
        count ++;
      }
    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
    return EXIT_FAILURE;
  }
  
  //for( int i = 0 ; i < fileList.size(); i++){
  //  printf("%2d | %s \n", i, fileList[i].c_str());
  //}
  
  //============= Seperate different group of files
  int count = 0;
  vector<string> calList;
  for( int i = 0 ; i < fileList.size(); i++){
    string model, spin, isospin, nParticle, interaction;
    model = fileList[i].substr(0,1);
    nParticle = fileList[i].substr(4,1);
    interaction = fileList[i].substr(5,1);
    
    if( mode ==  0 ){
      spin  = fileList[i].substr(1,1);
      isospin = fileList[i].substr(2,1);
    }else{
      spin  = fileList[i].substr(6,1);
      isospin = fileList[i].substr(7,1);
    }
    string cal = model + spin + isospin + nParticle + interaction;
    int check = checkExistElement(calList, cal);

    //printf(" isospin: %s | %d \n", cal.c_str(), check);
    
    if( check == 0 ){
      calList.push_back(cal);
    }    
  }
  
  
  const int sizeOfCal = calList.size();
  //printf("number of Type of overlap : %d \n", sizeOfCal);
  //for( int i = 0 ; i < sizeOfCal; i++){
  //  printf("%2d | %s \n", i, calList[i].c_str());
  //}
  
  vector<string> fileArray[sizeOfCal];
  for( int i = 0 ; i < fileList.size(); i++){
    string model, spin, isospin, nParticle, interaction;
    model = fileList[i].substr(0,1);
    nParticle = fileList[i].substr(4,1);
    interaction = fileList[i].substr(5,1);
    
    if( mode ==  0 ){
      spin  = fileList[i].substr(1,1);
      isospin = fileList[i].substr(2,1);
    }else{
      spin  = fileList[i].substr(6,1);
      isospin = fileList[i].substr(7,1);
    }
    
    string cal = model + spin + isospin + nParticle + interaction;
      
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
  
  //=========== extract energy levels for same group of files
  //---------- read energy levels
  CombineVectors energySF[sizeOfCal];
  for( int i = 0 ; i < sizeOfCal ; i ++){
    
    //printf("--------- group %d \n", i);
    
    for(int j = 0 ; j < fileArray[i].size() ; j ++){
      string filePath = directory + "/" + fileArray[i][j];
      
      ReadLSFFile readFile(filePath, maxEnergy, minSF, mode);
      //readFile.Print();
      energySF[i].AddVector(readFile.SPO, readFile.energySF);
      //energySF[i].Print();
    }
  energySF[i].SortEnergy();
  energySF[i].GroundStateEnergyReset();
  //energySF[i].Print();
 
  }
  
  
  printf("======================\n");
  //=========== save into files
  for( int i = 0 ; i < sizeOfCal ; i++){
    FILE * file_out;
    string outFileName = fileArray[i][0].substr(0,9);
    if( mode == 0 ) {
      outFileName.replace(6,1, "X");
    }else{
      outFileName.replace(1,1, "X");
    }
    string outFilePath = directory + "/" + outFileName + ".txt"; 
    file_out = fopen(outFilePath.c_str(), "w+");
    printf(" group %i saved to : %s \n", i, outFilePath.c_str());
  
  fprintf(file_out, "%8s,", "spin");
  fprintf(file_out, "%8s,", "energy");
  for( int k = 0; k < energySF[i].combinedSPO.size() - 1; k++){
    fprintf(file_out, "%6s/2,", energySF[i].combinedSPO[k].c_str());
  }
  fprintf(file_out, "%6s/2\n", energySF[i].combinedSPO.back().c_str());
  
  for( int j = 0; j < energySF[i].combinedEnergySF.size(); j++){
    double twoSpin = energySF[i].combinedEnergySF[j][0];
    if( fmod(twoSpin, 2) == 0.0 ){
      fprintf(file_out, "%8.0f,", twoSpin/2.);
    }else{
      fprintf(file_out, "%6.0f/2,", twoSpin);
    }
    for( int k = 1; k < energySF[i].combinedEnergySF[j].size() - 1; k++){
      fprintf(file_out, "%8.3f,", energySF[i].combinedEnergySF[j][k]);
    }
    fprintf(file_out, "%8.3f\n", energySF[i].combinedEnergySF[j].back());
  }
    fclose(file_out);
  }
  
  return 0;
}

