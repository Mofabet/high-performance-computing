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
    double x, t, fold;
    double C, D;
    double dx, dt, dtf;
   // double K1, K2;
    double T_l, T_r;
    int i, k, Ns, T_s;
    int A, B; // counters

    //U[(int)n]; double T[(int)n]; double R[(int)n]; // det n as a constant
    //U[0]=a; //T-R

    //определение переменных (вынести отдельно?)
    // cin - ввод с клав-ры

//расчет С


    //
    C = 2*D*(dt/dx/dx);
    cout << " The ratio of the densities of meshes: C = " << C << endl;

    if (C > 1) {
        //проверить устойчивость
        cout << " Courant coefficient C = " << C << " greater then 1 "<< endl;
        cout << " The scheme failed stability testing " << endl;
        goto skip;
    }
        else {
        cout << " The scheme passed stability testing " << endl;
    }

    Ns = x/dx;
    T_s = t/dt;
    double U[Ns][Ts];
    //явная////////////////////
    {
        // задание граничных условий 
        // Кельв1 - Tl, Кельв 2 - Tr
        U[0][0] = T_l; //??? 
        U[Ns-1][0] = T_r; // теперь оба не работают
    
        for(int i) i = 1; i <= Ns-1; i++){
             U[i][0] = 0;
             //Y[i]=Y[i-1]+h*F(X[i-1],Y[i-1]);
        }
        
        for (int k = 0; k <= A; k++){
            U[-1][k] = T_l; //??? 
            U[Ns-1][k] = T_r; // теперь оба не работают
            for (int i = 1; k = 1 < Ns-1; k++){
                //dtf = dt*???
                U[i][k+1]=(C/2)*U[i-1][k]+(1-C)*U[i][k]+(C/2)*U[i+1][k]+(dtf);
            }
        }
        // По какой то причине не определяется корректно
        // Определить порядок
        //for(int i=0; i <= Ns; i++){ 
        //    cout << "U["<<i<<"]="<<X[i] <<" ";
        //}
        cout << endl;
        for(int i=0; i <= Ns; i++){
            cout << "T["<<i<<"]="<<Y[i] << " "; //re all
        }
        for(int i=0; i <= Ns; i++){
            cout << "U["<<i<<"]="<<X[i] << " ";
            }
    }
    //неявная////////////////////////////////
    {
        double A, B, F, E; //много повторяется
        double alf_0, bet_0;
        double alf_i, bet_i;

        U[0][0] = T_l; //??? 
        U[Ns-1][0] = T_r;
        
        for(int i) i = 1; i <= Ns-1; i++){
             U[i][0] = 0;
             //Y[i]=Y[i-1]+h*F(X[i-1],Y[i-1]);
             //for(int i) i = 1; i <= Ns-1; i++){
             //U[i][0] = 0;
             ////Y[i]=Y[i-1]+h*F(X[i-1],Y[i-1]);
        }
        for(int i) i = 1; i <= Ns-1; i++){
             F[i][0] = 0;//F[i][k] 
             //Y[i]=Y[i-1]+h*F(X[i-1],Y[i-1]);
        }
        double hotfix;
        A = 0;
        B = 0;
        alf_0[0] = E/B;
        bet_0[0] = F[0][k]/B;

        alf_i = E/(B-A*alf_i[i-1]);
        bet_i = (F[i][k]-A*bet_i[i-1])/(B-A*alf_i[i-1]);
        
        //U*N[s-1][k+1] = bet*N[s-1]; ????????
        U[i][k+1] = bet_i[i]-alf_i[i]*u[i+1][k+1];//i = Ns-2 ... 0 можно поместить в один цикл
        for (int k = 0; k <= A; k++){
            U[-1][k] = T_l; //??? 
            U[Ns-1][k] = T_r; // теперь оба не работают
            for (int i = 1; k = 1 < Ns-1; k++){
                //dtf = dt*???
                U[i][k+1]=(C/2)*U[i-1][k]+(1-C)*U[i][k]+(C/2)*U[i+1][k]+(dtf);
            }
        }


    }
    skip:
    cout << "The scheme is unstable" << endl;
    return 0;
}
