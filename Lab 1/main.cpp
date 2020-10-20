#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

//double *U=new double[n]; выделение памяти в куче
// delta = div * grad
// f
// u



int main () {
    double F(double u,double t, double r);
    double x, t, f, bigD, bigC, bigX;
    double dx, dt;
    double K, K1, K2;
    int A, B, C, N;

    //U[(int)n]; double T[(int)n]; double R[(int)n]; // det n as a constant
    //U[0]=a; //T-R

    //определение переменных (вынести отдельно?)
    // cin - ввод с клав-ры

//расчет С


    //
    bigC = 2*bigD*(dt/dx/dx);
    cout << " The ratio of the densities of meshes: C = " << bigC << endl;

    if (bigC > 1) {
        //проверить устойчивость
    }

    
    for(int i) i = 1; i <= N-1; i++){
         bigX[i] = 0;
         //Y[i]=Y[i-1]+h*F(X[i-1],Y[i-1]);
    }

    for(int i=0; i <= N; i++){

        cout << "U["<<i<<"]="<<X[i] <<" ";
    }
    cout << endl;
    for(int i=0; i<=n; i++){
        cout << "T["<<i<<"]="<<Y[i] << " "; //re all
    }
    return 0;
}
