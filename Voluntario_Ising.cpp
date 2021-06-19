#include <iostream>
#include <cmath>
#include <fstream>
#include <random>
#include <time.h>

#define N 22
#define P 3
#define T 0.0001

double CalcularP(int n,int m,double omega[N][N][N][N],double theta[N][N],double s[N][N]);


using namespace std;

int main(void)
{
    int i,j,k,l,n,m,mu,xi[N][N][P],contador;
    double num,chi,p,s[N][N],a[P],omega[N][N][N][N],theta[N][N];
    double aleatorio,number,sum;
    
    
    mt19937 semilla(time(NULL));
    uniform_real_distribution<double> numeroaleatorio_real(0.0,1.0);
    uniform_int_distribution<int> numeroaleatorio_entero(0,N-1);
    
    ifstream fo;

    fo.open("prueba.txt");

    ofstream da,re;

    da.open("datos'");
    re.open("posiciones2");
    
    //Hay que leer la imagen que queremos pintar
    
    i=j=mu=0;
    
    while(fo>>number)
    {
        xi[i][j][mu]=number;
        if(i==N-1)
        {
            mu++;
            i=j=0;
        }
        else
        {
            if(j==N-1)
            {
                j=0;
                i++;
            }
            else
                j++;
        }
            
    }

    for(mu=0; mu<P; mu++)
        a[mu]=0.0;
    
    for(mu=0; mu<P; mu++)
    {
        for(k=0; k<N; k++)
        {
            for(l=0; l<N; l++)
            {
                a[mu]=a[mu]+xi[k][l][mu];   
            }   
        }
        a[mu]=a[mu]/(N*N);
    }
 

    //Calculo omega

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            for(k=0; k<N; k++)
            {
                for(l=0; l<N; l++)
                {
                    if((i==k)&&(j==l))
                    {
                        omega[i][j][k][l]=0.;
                    }
                    else
                    {
                        sum=0.;

                        for(mu=0; mu<P; mu++)
                        {
                            sum=sum+((xi[i][j][mu]-a[mu])*(xi[k][l][mu]-a[mu]));
                        }
                        omega[i][j][k][l]=sum/(N*N);
                    }
                    
                    
                }
            }
        }
    }  

    //Calculamos theta

    sum=0.;
    
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {    
            for(k=0; k<N; k++)
            {
                for(l=0; l<N; l++)
                {
                    sum=sum+omega[i][j][k][l];
                }    
            }
            theta[i][j]=0.5*sum;
        }
    }   

    //Inicialicemos la matriz s aleatoriamente

    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            aleatorio=numeroaleatorio_real(semilla);
            if(aleatorio<=0.5)
                s[i][j]=1.0;
            else
                s[i][j]=0.0;
        }
    }
    
    for(k=0; k<150; k++)
    {
        //Dibujamos la imagen en un archivo .dat

            for(i=0; i<N; i++)
            {
                for(j=0; j<N; j++)
                {
                    if(j==N-1)
                        da<<s[i][j]<<endl;
                    else
                        da<<s[i][j]<<",";
                }
            }

            da<<endl;

        for(i=0;i<N*N;i++)
        {
            

            //Elegimos un elemento aleatorio de la matriz 

            n=numeroaleatorio_entero(semilla);
            m=numeroaleatorio_entero(semilla);


            //Evaluamos p=min(1,exip(-[E/T]))

            p=CalcularP(n,m,omega,theta,s);


            //Generamos un número aleatorio uniforme entre 0 y 1, y provamos si es menor que p

            chi=numeroaleatorio_real(semilla);
            

            if(chi<p)
            {
                if(s[n][m]==1.)
                    s[n][m]=0.;
                else
                    s[n][m]=1.;	
                
            }

        }
        

    }

    for(i=0; i<N; i++)
    {
        for(j=0;j<N;j++)
        {
            cout<<s[i][j]<<" ";
        }
        cout<<endl;
    }

    da.close();
    re.close();
    fo.close();
    
	
    return 0;
}


//Funcion para calcular p

double CalcularP(int n,int m,double omega[N][N][N][N],double theta[N][N],double s[N][N])
{    
    int i,j,k,l;
    double sum1,sum2,sum3,sum4,p,H,H_i,H_f,sprima[N][N];        
    
    //Calculamos la matriz auxialiar que vanmos a usar
    
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)  
        {
            if((i==n)&&(j==m))
            {
                if(s[n][m]==1.)
                    sprima[n][m]=0.;
                else
                    sprima[n][m]=1.;
            }
            else
                sprima[i][j]=s[i][j];
        }
    }

    //Calculamos el hamiltoniano

    sum1=0.; //Hamiltoniano s
    sum2=0.; //Hamiltoniano s'
    
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            for(k=0; k<N; k++)
            {
                for(l=0; l<N; l++)
                {
                    sum1=sum1+(omega[i][j][k][l]*s[i][j]*s[k][l]);
                    sum2=sum2+(omega[i][j][k][l]*sprima[i][j]*sprima[k][l]);
                }
            }
        }
    }
    
    sum3=0.; 
   
    for(i=0; i<N; i++)
    {
        for(j=0; j<N; j++)
        {
            sum3=sum3+(theta[i][j]*(sprima[i][j]-s[i][j]));
            
        }
    }

    H=-(0.5*sum2)+sum3+(0.5*sum1);
    //De modo que podemos calcular p

    p=min(1.0,exp(-H/T));


    return p;
}

