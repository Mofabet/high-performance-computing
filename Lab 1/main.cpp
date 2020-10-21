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
    double K1, K2;
    int A, B, C, Ns;
    int i, k;

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

    
    for(int i) i = 1; i <= Ns-1; i++){
         bigX[i] = 0;
         //Y[i]=Y[i-1]+h*F(X[i-1],Y[i-1]);
    }
    // задание граничных условий 
    // Кельв1 - Tl, Кельв 2 - Tr

    for (int k = 0; k <= A; k++){
        bigX[0][k] = K1; //??? 
        bigX[Ns-1][k] = K2; // теперь обане работают
        for (int i ...){
        //U[i]=(bigC/2)*U[i-1][k]+(1-bigC)*U[i][k]+(bigC/2)*U[i+1][k]+(dtf);
        }
    }

    for(int i=0; i <= Ns; i++){

        cout << "U["<<i<<"]="<<X[i] <<" ";
    }
    cout << endl;
    for(int i=0; i<=n; i++){
        cout << "T["<<i<<"]="<<Y[i] << " "; //re all
    }
    return 0;
}
