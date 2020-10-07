#include <iostream>
#include <cmath>
using namespace std;

double F(double u,double t, double r){
    return ;//equasion
}
int main () {
    double a=0; double b=1; double h=0.1;
    double n=(b-a)/h;
    double U[(int)n]; double T[(int)n]; double R[(int)n];
    U[0]=a; //T-R
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