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
    double x, t, f, bigD, bigC;
    double dx, dt;
    double K, K1, K2;
    int A, B, c;

    //U[(int)n]; double T[(int)n]; double R[(int)n]; // det n as a constant
    //U[0]=a; //T-R

//расчет С


    bigC = 2*bigD*(dt/dx/dx);
    cout << " The ratio of the densities of meshes: C = " << bigC << endl;

    if (bigC > 1) {
        //проверить устойчивость
    }

    
    for(int i) i=1; i<=n; i++){
         X[i]=a+i*h;
         Y[i]=Y[i-1]+h*F(X[i-1],Y[i-1]);
    }
    for(int i=0; i<=n; i++){
        cout << "U["<<i<<"]="<<X[i] <<" ";
    }
    cout << endl;
    for(int i=0; i<=n; i++){
        cout << "T["<<i<<"]="<<Y[i] << " ";
    }
    return 0;
}
