#include "Matrix.h"

int main(int argc, char *argv[])
{
  // below some demonstration of the usage of the Matrix class
  try
  {
    // create an empty matrix of 3x3 (will initially contain zeros)
    int cols = 3;
    int rows = 3;
    Matrix A = Matrix(cols, rows);

    // fill in some values in matrix a
    int count = 0;
    for (int r = 1; r <= rows; r++)
    {
      for (int c = 1; c <= cols; c++)
      {
        count ++;
        A(r, c) = count;
      }
    }

    // adjust a value in the matrix (indexes are one-based)
    A(2,1) = 1.23;

    // read a value from the matrix (indexes are one-based)
    double centervalue = A(2,2);
    printf("centervalue = %f \n", centervalue);
    printf("\n");

    // print the whole matrix
    printf("A = \n");
    A.Print();
    printf("\n");

    Matrix B = Ones(rows, cols) + Diag(rows);
    printf("B = \n");
    B.Print();
    printf("\n");

    Matrix B2 = Matrix(rows, 1);    // a vector
    count = 1;
    for (int r = 1; r <= rows; r++)
    {
      count ++;
      B2(r, 1) = count * 2;
    }
    printf("B2 = \n");
    B2.Print();
    printf("\n");

    Matrix C;
    C = A + B;
    printf("A + B = \n");
    C.Print();
    printf("\n");

    C = A - B;
    printf("A - B = \n");
    C.Print();
    printf("\n");

    C = A * B2;
    printf("A * B2 = \n");
    C.Print();
    printf("\n");

    // create a diagonal matrix
    Matrix E = Diag(B2);
    printf("E = \n");
    E.Print();
    printf("\n");

    // calculate determinant
    Matrix D = Matrix(2, 2);
    D(1,1) = 2;
    D(1,2) = 4;
    D(2,1) = 1;
    D(2,2) = -2;
    printf("D = \n");
    D.Print();
    printf("Det(D) = %f\n\n", Det(D));

    printf("A = \n");
    A.Print();
    printf("\n");
    printf("Det(A) = %f\n\n", Det(A));

    Matrix F;
    F = 3 - A ;
    printf("3 - A = \n");
    F.Print();
    printf("\n");

    // test inverse
    Matrix G = Matrix(2, 2);
    G(1, 1) = 1;
    G(1, 2) = 2;
    G(2, 1) = 3;
    G(2, 2) = 4;
    printf("G = \n");
    G.Print();
    printf("\n");
    Matrix G_inv = Inv(G);
    printf("Inv(G) = \n");
    G_inv.Print();
    printf("\n");

    Matrix A_inv = Inv(A);
    printf("Inv(A) = \n");
    A_inv.Print();
    printf("\n");

    Matrix A_A_inv = A * Inv(A);
    printf("A * Inv(A) = \n");
    A_A_inv.Print();
    printf("\n");

    Matrix B_A = B / A;
    printf("B / A = \n");
    B_A.Print();
    printf("\n");

    Matrix A_3 = A / 3;
    printf("A / 3 = \n");
    A_3.Print();
    printf("\n");

    rows = 2;
    cols = 5;
    Matrix H = Matrix(rows, cols);
    for (int r = 1; r <= rows; r++)
    {
      for (int c = 1; c <= cols; c++)
      {
        count ++;
        H(r, c) = count;
      }
    }
    printf("H = \n");
    H.Print();
    printf("\n");
  }
  catch (Exception err)
  {
    printf("Error: %s\n", err.msg);
  }
  catch (...)
  {
    printf("An error occured...\n");
  }

  printf("\n");
  //PAUSE;

  return EXIT_SUCCESS;
}
