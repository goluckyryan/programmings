#include "matrix4D.h"
#include "vector4D.h"
#include "fourVector.h"

int main(){

   Matrix4D mat1(1,2,3,4,10,3,4,5,3,4,5,6,4,5,6,7);
   

   double mass[3]; 
   mass[0] = 1000, mass[1] = 1, mass[2] = 2;
   
   FourVector v1(1, mass, 250, 0, 0);
   Vector4D vk(1,0,1,0);
   
   mat1.print("mat1");
   v1.print("v1","\n");
   vk.print("vk");
   
   (mat1^vk).print("mat.v1");
   
   
   return 0;

}
