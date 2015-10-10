#include <stdio.h>
#include <cmath>

using namespace std;

int main(){
    const int NPlane = 3;
    int * fWeight = new int[NPlane];

    fWeight[0] = 1;
    fWeight[1] = 0;
    fWeight[2] = 1;

    int fNValidPlane = 0;
    for ( int i = 0; i < NPlane; i++){
        if (fWeight[i] != 0){
            fNValidPlane ++ ;
        }
    }

    printf("===================\n");
    for ( int i = 0; i < pow(2,fNValidPlane); i++ ){
        printf("%d |", i);
        for ( int j = 0; j < NPlane; j++){
            printf(" %f,", i>>j);
        }
        printf("\n");
    }



//------ Debug code
    printf("====\n");
    printf(" weight:");for (int i = 0; i< NPlane; i++) {printf(" %1d,",fWeight[i]);} printf("\n");
    printf(" ValidPlane: %d\n", fNValidPlane);


    delete fWeight;
    return 0;
}
