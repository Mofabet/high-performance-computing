int main()
{
  int i=0, j=0;
  double T=1, taymin=0.001, taymax=0.2, min=0, max=0, eps=0;
  double *u=new double[n];
  double *f=new double[n];
  double *tk=new double[n];
  double *Q1=new double[n];
  double **yk=new double*[n+1];
 
    for(int i=0;i<n+1;i++)
        yk[i]=new double[n];
    double *tay=new double[n+1];
 
    ofstream outfile("myfile1.txt");
 
    for(int i=0;i<n;i++)
    {
        cout<<"u[i]=";
        cin>>u[i];
    }
 
    for(int i=0;i<n+1;i++)
    {
        tay[i]=taymin;
    }
 
    for(int i=0;i<n+1;i++)
        for(int j=0;j<n;j++)
            yk[i][j]=u[j];
    tk[0]=0.001;
 
 
    do
    {   
        tk[1]=tk[0]+tay[1];
        nie(yk,tk,tay);
        for(int i=0;i<n;i++)
        {
            double r=(-1)*tay[1]/(tay[1]+tay[0]);
            double r1=(tay[1]/tay[0]);
            double r2=(yk[1][i]-yk[0][i]);
            Q1[i]=r*(yk[2][i]-yk[1][i]-r1*r2);
        }
 
        max=fabs(Q1[0]);
        {
          for(int i=1;i<n;i++)
            if(max<fabs(Q1[i]))
                max=fabs(Q1[i]);
        }
        eps=max;
        if (fabs(eps)>Q)
            {
                tay[1]/=2;
                tk[1]=tk[0];
                for(int j=0;j<n;j++)
                    yk[2][j]=yk[1][j];
                continue;
            }
 
        if(fabs(eps)>Q)
            tay[2]=tay[1]/2;
        else
            if(fabs(eps)>(Q/4)||fabs(eps)<=Q)
                tay[2]=tay[1];
            else 
                if(fabs(eps)<=(Q/4))
                    tay[2]=2*tay[1];
        if(tay[2]>taymax)
            tay[2]=taymax;
 
        for(int j=1;j<n;j++)
            outfile<<yk[2][j-1]<<"      "<<yk[2][j]<<"      "<<tk[j]<<endl;
    
        for(int j=0;j<n;j++)
        {
            yk[0][j]=yk[1][j];
            yk[1][j]=yk[2][j];
        }
        tay[0]=tay[1];
        tay[1]=tay[2];
        tk[0]=tk[1];
    }
    while(tk[0]<T);
    return 0;
}
double funcia(double**yk,double* tk)
{   
    return -yk[2][0]*yk[2][1]+sin(tk[1])/tk[1];
}
double funcia1(double**yk,double* tk)
{
    return (-1)*yk[2][1]*yk[2][1]+a*tk[1]/(1+tk[1]*tk[1]);
}
void gaus(double j[n][n],double b[n],double deltax[n])
{
    double mnog=0, max=0, *k=0, g=0;
    int h=0, t=0, d=0, p=0;
    double **a=new double*[n];
 
    for(int i=0;i<n;i++)
        a[i]=new double[n];
 
    for( int i=0;i<n;i++)
        for(int k=0;k<n;k++)
            a[i][k]=j[i][k];
 
    for(int i=0;i<n;i++)
        {
        p=0;
        //Нахождение мах
        max=fabs(a[i][i]);
        for(int l=i+1;l<n;l++)
        {
            if(fabs(a[l][i])>max)
            {
                max=fabs(a[l][i]);
                p=l-i;
            }
            else if(max==fabs(a[i][i]))
                    p=0;
        }
            //Перестановка строк
        k=0;double r=0;
        
        if(p>0)
        {
            
                k=a[i];
                a[i]=a[i+p];
                a[i+p]=k;
                r=b[i];
                b[i]=b[p+i];
                b[p+i]=r;
        }
        
        cout<<endl;
        double del=a[i][i];
        h=i;
        if (del==0)
        {
            cout<<"delitb na 0 nelbzia";
            exit(0);
        }
        if ((h+1)==n)
        {
            a[i][i]/=del;
            b[i]/=del;
        }
    
    for(int h=i;h<n;h++)
        {   
            if  ( n>(h+1))      
            {
                mnog=a[h+1][i];
                
                if(g==0)
                {
                    b[i]=b[i]/del;
                }
                    b[h+1]=b[h+1]+(-1)*mnog*b[i];
                    g++;
                
                for(int k=i;k<n;k++)
                {   
                    if(t==0)
                    {
                    a[i][k]/=del;
                    
                    }
                    a[h+1][k]=a[h+1][k]+(-1)*a[i][k]*mnog;  
                }
            }
            else
                continue;
            
            t++;
        }
        t=0;
        g=0;
    }
 
double sum=0;
 
for(int i=n-1;i>-1;i--)
{   
    deltax[i]=b[i];
    for(int j=n-1;j>i;j--)
    deltax[i]-=a[i][j]*deltax[j];   
}
}
void nie(double **yk,double* tk,double *tay)
{
    double (*a[n]) (double**,double*)={funcia,funcia1};
    double *b=new double[n];
    double *o=new double[n];
    double j[n][n];
    double f[n];
    double deltax[n];
    int i=0, k=0, t=0, d=0, maxiter=30;
    double y=0, sigma1=0, sigma2=0, max=0;
    
    do
    {   
        if(maxiter<t)
            break;
        for(int i=0;i<n;i++)
            f[i]=(-1)*(yk[2][i]-yk[1][i]-tay[1]*(*a[i])(yk,tk));
        max=fabs(f[0]);
 
        for(int i=1;i<n;i++)
            if(fabs(f[i])>max)
                max=fabs(f[i]);
        sigma1=max;
 
        for(int i=0;i<n;i++)
            for(int k=0;k<n;k++)
            {
                y=yk[2][i]-yk[1][i]-tay[1]*(*a[i])(yk,tk);
                yk[2][k]+=Q;
                j[i][k]=((yk[2][i]-yk[1][i]-tay[1]*(*a[i])(yk,tk))-y)/Q;
                yk[2][k]-=Q;
            }
        
        gaus(j,f,deltax);
 
        for(int i=0;i<n;i++)
            b[i]=yk[2][i];
 
        for(int i=0;i<n;i++)
            yk[2][i]+=deltax[i];
    
    for(int i=0;i<n;i++)
    {
        if(yk[2][i]<1)
        {
                b[i]=fabs(yk[2][i]-b[i]);
                o[i]=b[i];
        }
        else 
        {
                b[i]=fabs((yk[2][i]-b[i])/yk[2][i]);
                o[i]=b[i];
        }
    }
 
    max=o[0];
 
    for(int i=1;i<n;i++)
        if (max<o[i])
            max=o[i];
        
    t++;
    }
    while(sigma1>Q||max>Q);
}