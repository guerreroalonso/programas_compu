#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    int i,j,k,n,n_max; //Contadores a utilizar a lo largo del programa
    long double m[2][2], g[2], maux[2][2], minf[2][2], inff, inf[2], supp, sup[2],alpha_num, aux1[2][2], aux2[2][2]; //Declaracion de las diferentes matrices a lo largo del programa
    long double alpha_anal, diferencia;
    
    //Declaramos el fichero de escritura
    ofstream datos;
    
    //Abrimos los ficheros de escritura de datos
        
    datos.open("datos_numericos_autovalor");
    
    
    //Inicializamos los datos de nuestra matriz principal a la cual calcularemos el autovalor maximo
    m[0][0]=0.64;
    m[0][1]=0.9;
    m[1][0]=0.9;
    m[1][1]=0.5;    
    //Inicializamos el contador n
    n=1;
    n_max=1000;
    
    for(n=1;n<n_max;n++)
    {
    
	    //matriz auxiliar m superior e inferior
	    //Al ser matrices auxiliares las inicializaremos cada vez que entre dentro del bucle
    	maux[0][0]=minf[0][0]=.64;   
    	maux[0][1]=minf[0][1]=0.5;
    	maux[1][0]=minf[1][0]=0.5;
    	maux[1][1]=minf[1][1]=0.3;
    
		//matriz gamma
    	g[0]=1.;               
    	g[1]=2.;
    
    	//matriz auxiliar gamma superior
    	sup[0]=inf[0]=1.;             
    	sup[1]=inf[1]=2.;	
    	
    	for(i=0; i<(2*n)+1; i++)
    	{
            aux1[0][0]=maux[0][0];
            aux1[1][0]=maux[1][0];
            aux1[0][1]=maux[0][1];
            aux1[1][1]=maux[1][1];

        	maux[0][0]=aux1[0][0]*m[0][0]+aux1[0][1]*m[1][0];
        	maux[0][1]=aux1[0][0]*m[0][1]+aux1[0][1]*m[1][1];
        	maux[1][0]=aux1[1][0]*m[0][0]+aux1[1][1]*m[1][0];
        	maux[1][1]=aux1[1][0]*m[0][1]+aux1[1][1]*m[1][1];
    
    	}
    	
    	//Matriz auxiliar gamma
    	sup[0]=maux[0][0]*g[0]+maux[0][1]*g[1]; 
    	sup[1]=maux[1][0]*g[0]+maux[1][1]*g[1];
    
    	supp=sup[0]*g[0]+sup[1]*g[1];
    
    
		//CALCULAMOS EL TERMINO DE LA DIVISION INFERIOR
    	for(i=0; i<(2*n); i++)
    	{
            aux2[0][0]=minf[0][0];
            aux2[1][0]=minf[1][0];
            aux2[0][1]=minf[0][1];
            aux2[1][1]=minf[1][1];
            
        	minf[0][0]=aux2[0][0]*m[0][0]+aux2[0][1]*m[1][0];
        	minf[0][1]=aux2[0][0]*m[0][1]+aux2[0][1]*m[1][1];
        	minf[1][0]=aux2[1][0]*m[0][0]+aux2[1][1]*m[1][0];
       	 	minf[1][1]=aux2[1][0]*m[0][1]+aux2[1][1]*m[1][1];
    
    	}
    
    	inf[0]=minf[0][0]*g[0]+minf[0][1]*g[1];
    	inf[1]=minf[1][0]*g[0]+minf[1][1]*g[1];
    
    	inff=inf[0]*g[0]+inf[1]*g[1];
    	
    	//Calculamos el alpha numerica
       	alpha_num=supp/inff;
       	
    	//Calculamos el alpha analitica
    	alpha_anal=0.5*((m[0][0]-m[1][1])+sqrt(((m[1][1]-m[0][0])*(m[1][1]-m[0][0]))+(4.*m[1][0]*m[1][0])))+m[1][1];
    	
    	diferencia=abs(alpha_num-alpha_anal);
    	
    	
    	//Escribimos los diferentes datos obtenidos en el fichero de datos 
    	//En primer lugar el valor del autovalor máximo de forma numerica, el numero de iteraciones, el autovalor maximo de forma analitica y la diferencia entre el valor analitico y numerico
    	
    	datos<<std::setprecision(20)<< alpha_num<<"\t"<<n<<"\t"<<alpha_anal<<"\t"<<diferencia<<endl;
    	
    	
	}	
  
    
    datos.close();
		
    return 0;
	}
    
    

