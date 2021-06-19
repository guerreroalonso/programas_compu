//	PROGRAMA OBLIGATORIO NUMERO 3 SCHRÖDINGER


//BIBLIOTECAS
#include <iostream>
#include <cmath>
#include <fstream>
#include "complex.hpp"

//CONSTANTES
#define pi 3.141592
#define N 400		//ITERACIONES QUE REALIZA EL PROGRAMA
#define nciclos 40	//NUMERO DE CICLOS PARA EL TIEMPO
#define lambda 0.8  //PARÄMETRO QUE NOS DA CUENTA DE LA BARRERA DE POTENCIAL
#define h 0.05		

//DEFINO LAS DIFERENTES FUNCIONES NECESARIAS PARA EL PROGRAMA
double Potencial(int j,double k);
void CalcularAlfa(double s,double V[N],fcomplex gamma[N],fcomplex alfa[N]);
void CalcularBeta(fcomplex gamma[N],fcomplex b[N], fcomplex beta[N]);
void CalcularChi(fcomplex alfa[N],fcomplex beta[N],fcomplex chi[N]);
void CalcularPhi(fcomplex chi[N],fcomplex phi[N]);

using namespace std;

int main()
{
    int i,j,t;
    double s,k,V[N],norma;       
    fcomplex cero,imaginario,gamma[N],b[N],alfa[N],beta[N],chi[N],phi[N];

    ofstream sch,pot,norm;
    
    
    //ABRO LOS DIFERE
    sch.open("datos_sch");   
    norm.open("Norma");
    
    
	//DEFINO LOS NUMERO IMAGINARIOS BASE
    cero.r=0.0;
    cero.i=0.0;

    imaginario.r=0.0;
    imaginario.i=1.0;

	//PROPORCIONO EL VALOR INICIAL A LAS DIFERENTES VARIABLES
    k=2*pi*nciclos/N;

    s=1./(4.*k*k);

    for(j=0; j<N; j++)
        V[j]=Potencial(j,k);
        

     
	//INICIALIZAMOS PHI PROPORCIONANDOLE A DICHA VARIABLE EL VALOR EN EL PRIMER INSTANTE DE TIEMPO
    phi[0]=cero;
    phi[N-1]=cero;

    norma=0.;
    
    for(j=1; j<N-1; j++)
    {    
        phi[j]=Cgauss((k*j),exp((-8.*(4.*j-N)*(4.*j-N))/(N*N)));
        norma=norma+Cabs(Cpow(phi[j],2));         
    }
    
   

    //NORMALIZAMOS LA FUNCION DE ONDA   
    for(j=0;j<N;j++)
    {
        phi[j]=RCmul(1./sqrt(norma),phi[j]);
        sch<<j+1<<","<<Cabs(Cpow(phi[j],2))<<","<<V[j]<<endl;    
    }
    sch<<endl;
    
	//CALCULAMOS ALFA
    CalcularAlfa(s,V,gamma,alfa);
    

    
	//PARTE DEL PROGRAMA QUE CONSISTE EN ITERAR E IR CALCULANDO LOS DIFERENTES PARÁMETROS
	//LA t SERÁN A GROSO MODO EL NUMERO DE ITERACIONES QUE REALIZARA NUESTRO PROGHRAMA PARA
	//LA FUNCIÓN DE ONDA    
    for(t=0; t<4000;t++)
    {
        for(j=0; j<N; j++)
            b[j]=Cmul(RCmul(4./s,imaginario),phi[j]);
                    
        //CALCULAMOS LOS DIFERENETS PARÁMETROS
        CalcularBeta(gamma,b,beta);
        CalcularChi(alfa,beta,chi);
        CalcularPhi(chi,phi);
        norma=0.;

        for(j=0;j<N;j++)
        {
            sch<<j+1<<","<<Cabs(Cpow(phi[j],2))<<","<<V[j]<<endl;
            norma=norma+Cabs(Cpow(phi[j],2));
        }
        sch<<endl;
        norm<<norma<<endl;

    }

    sch.close();
    norm.close();


    return 0;
}

//#################################################################################################################
//#################################################################################################################
//#################################################################################################################
//#################################################################################################################
//#################################################################################################################

//DIFERENTES FUNCIONES UTILIZADAS EN EL PROGRAMA

//FUNCION QUE LE DA VALOR A NUESTRO PTENCIAL EL CUAL PODREMOS VARIAR A PARTIR DE LAMBDA
double Potencial(int j,double k)
{
    int a, b;
    double Vol;

    a=(int)(2*N/5);
    b=(int)(3*N/5);

    if((j>=a)&&(j<=b))
        Vol=lambda*k*k;

    else
        Vol=0.0;

    return Vol;
}

//FUNCION ALFA

void CalcularAlfa(double s, double V[N],fcomplex gamma[N],fcomplex alfa[N])
{
    int j;
    fcomplex aux,A0[N],cero,uno,imaginario;

    cero.r=0.0;
    cero.i=0.0;

    uno.r=1.0;
    uno.i=0.0;

    imaginario.r=0.0;
    imaginario.i=1.0;

    alfa[N-1]=cero;

    for(j=N-1;j>=1;j--)
    {
        aux.r=V[j]+2.;
        aux.i=0.0;
        A0[j]=Csub(RCmul(2./s,imaginario),aux);
        gamma[j]=Cdiv(uno,Cadd(A0[j],alfa[j]));

        alfa[j-1].r=-gamma[j].r;
        alfa[j-1].i=-gamma[j].i;
       
    }
   

    return;
}

//FUNCION BETA

void CalcularBeta(fcomplex gamma[N],fcomplex b[N],fcomplex beta[N])
{
    int j;
    fcomplex cero;

    cero.r=0.0;
    cero.i=0.0;

    beta[N-1]=cero;

        for(j=N-1;j>=1;j--)
            beta[j-1]=Cmul(gamma[j],(Csub(b[j],beta[j])));

    return;
}


//FUNCION CHI
void CalcularChi(fcomplex alfa[N],fcomplex beta[N],fcomplex chi[N])
{
    int j;
    fcomplex cero;

    cero.r=0.0;
    cero.i=0.0;

    chi[0]=cero;

    for(j=0;j<N-1;j++)
        chi[j+1]=Cadd(Cmul(alfa[j],chi[j]),beta[j]);

    return;
}


//FUNCION PHI
void CalcularPhi(fcomplex chi[N],fcomplex phi[N])
{
    int j;

    for(j=0;j<N;j++)
    {
        phi[j]=Csub(chi[j],phi[j]);
        
    }
    

    return;
}
