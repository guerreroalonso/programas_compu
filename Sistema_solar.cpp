//PROGRAMA_OBLIGATORIO_SISTEMA_SOLAR

//Diferentes bibliotecas que declaro para hacer el programa
#include <iostream>
#include <cmath>
#include <fstream>


//Definimos las diferentes constantes que utilizaremos a lo largo del programa
#define Msol 1.98847e30	//MASA SOLAR
#define G 6.67e-11		//CONSTANTE G
#define c 1.496e11		//DISTANCIA ENTRE TIERRA Y SOL
#define N 10			//NUMERO DE PLANETAS 
#define h 0.01			//EL PASO TEMPORAL DE NUESTRO PROGRAMA

//INICIO CODIGO DEL PROGRAMA
using namespace std;
int main(void)
{
    long double masa[N],velocidad[2][N], posicion[2][N], aceleracion[2][N], omega[2][N], norma,t;
    int i,j,k,n,contador,mercurio,venus,tierra,marte,jupiter,saturno,urano,neptuno,pluton;
    
    //CONTADOR QUE NOS HACE SALTAR CADA X DATOS PARA QUE EL GIF VAYA MAS RAPIDO
    contador=0;
    
    // Diferentes contadores para cada planeta para calcular en el bucle if el periodo de 
    // cada planeta del sistema solar
    mercurio=1;
    venus=1;
    tierra=1;
    marte=1;
    jupiter=1;
    saturno=1;
    urano=1;
    neptuno=1;
    pluton=1;
    
    // Inicializamos el tiempo y el número de iteraciones de nuestro programa para despues calcular el 
    // periodo de cada planeta 
    n=0;
    t=0.0;
    
	// Abrimos los diferentes archivos de texto referentes a los datos de la masa, posicion inicial, velociadad inicial
	// siendo mi el de la mas , pi posiciones iniciales, vi velociadades iniciales de cada planeta
    ifstream mi, vi, pi; 
    mi.open("masa");
    pi.open("posicion");
    vi.open("velocidad");
    
    // Abrimos los diferentes archivos de texto para copiar los datos resultantes del programa referentes a la 
    // posicion final de cada planeta para posteriormente ser ploteados siendo pf el de posiciones finales
    // y el de T el de los periodos
    ofstream pf,T,pt;
    pf.open("posicion_final");
    T.open("periodos_planetas");
    pt.open("posicion_tolomeo");
    
    
    // Introducimos las masas a nuestro vector de masas del fichero de datos que previamente hemos buscado 
	// en internet    
    if(mi.is_open() ==true)
    {
        
        for(i=0; i<N; i++)
         {
            mi>>masa[i];
            masa[i]=masa[i]/Msol;
          
         }  
    
    }
    
    // Introducimos las posiciones iniciales de cada planeta en nuestro vector de posicion inicial que previamente
    // hemos buscado en interntet 
    if(pi.is_open() ==true)
    {
       
        for(i=0; i<N; i++)
        {
            pi>>posicion[0][i]; //eje x
	        posicion[0][i]=posicion[0][i]/c;
            posicion[1][i]=0.0; //eje y
            pf<<posicion[0][i]<<","<<posicion[1][i]<<endl;
        }  

        pf<<endl;
    
    }
    
    //Introducimos las velocidades iniciales de cada planeta en nuestro vector de velocidad inicial que previamente
    // hemos buscado en interntet
    if(vi.is_open() ==true)
    {
        
        for(i=0; i<N; i++)
        {
            velocidad[0][i]=0.0; //eje x
            vi>>velocidad[1][i]; //eje y
            velocidad[1][i]=velocidad[1][i]*sqrt(c/(G*Msol));
        }  
    
    }
    
    //Calculamos la aceleracion inicial de nuestro programa
    for(i=0; i<N; i++)
    {
	    aceleracion[0][i]=0.0;
	    aceleracion[1][i]=0.0;

	    for(j=0; j<N; j++)
	    {
		    if(i!=j)
		    {	
			    norma=sqrt(((posicion[0][i]-posicion[0][j])*(posicion[0][i]-posicion[0][j]))+((posicion[1][i]-posicion[1][j])*(posicion[1][i]-posicion[1][j])));
			    aceleracion[0][i]=aceleracion[0][i]-((masa[j]*(posicion[0][i]-posicion[0][j]))/(norma*norma*norma));
			    aceleracion[1][i]=aceleracion[1][i]-((masa[j]*(posicion[1][i]-posicion[1][j]))/(norma*norma*norma));
		    }
	    }
    }			
	
	
	// CICLOS DE ITERACION DEL PROGRAMA QUE CALCULA LAS POSISCIONES FINALES DE LOS DIFERENTES PROGRAMAS
	// Y LOS PERIODOS DE LOS DIFERENTES PLANETAS		
    for(n=0; n<100000;n++)
    { 
        //A continuación, calculamos las nuevas posiciones y omegas.

        posicion[0][0]=0.0;
        posicion[1][0]=0.0;
        
        for(i=1; i<N; i++)
        {
            posicion[0][i]=posicion[0][i]+(h*velocidad[0][i])+(h*h*0.5*aceleracion[0][i]);
		    posicion[1][i]=posicion[1][i]+(h*velocidad[1][i])+(h*h*0.5*aceleracion[1][i]);

		    omega[0][i]=velocidad[0][i]+(h*0.5*aceleracion[0][i]);
            omega[1][i]=velocidad[1][i]+(h*0.5*aceleracion[1][i]);
        }
        
        //Ahora calculamos la nueva aceleracion con la nueva posicion
        for(i=0; i<N; i++)
    	{
    
    		aceleracion[0][i]=0.0;
    		aceleracion[1][i]=0.0;
    
    		for(j=0; j<N; j++)
    		{							
    		    if(i!=j)
    		    {													       
    			    norma=sqrt(((posicion[0][i]-posicion[0][j])*(posicion[0][i]-posicion[0][j]))+((posicion[1][i]-posicion[1][j])*(posicion[1][i]-posicion[1][j])));												
    				aceleracion[0][i]=aceleracion[0][i]-((masa[j]*(posicion[0][i]-posicion[0][j]))/(norma*norma*norma));
    				aceleracion[1][i]=aceleracion[1][i]-((masa[j]*(posicion[1][i]-posicion[1][j]))/(norma*norma*norma));
    			}
    		}
    	}
  
        
        //Y finalmente, la nueva velocidad

        velocidad[0][0]=0.0;
        velocidad[1][0]=0.0;
        
        for(i=1; i<N; i++)
        {
            velocidad[0][i]=omega[0][i]+(h*0.5*aceleracion[0][i]);
		    velocidad[1][i]=omega[1][i]+(h*0.5*aceleracion[1][i]);
        }
        
        
        //Sacamos a un fichero de texto las nuevas posiciones de los planetas
        t=t+h;
        
        
        //ESTE IF ES PARA QUE SOLO COJA 1 DE CADA MIL DATOS PARA QUE VAYA MAS RAPIDO EL GIF 
        //POR ESO HACEMOS CONTADOR IGUAL A 0 CADA VEZ QUE ESCRIBE UN DATO
		if(contador==20)
		{
			for(i=0; i<N; i++)
        	{
            	pf<<posicion[0][i]<<","<<posicion[1][i]<<endl;
                pt<<posicion[0][i]-posicion[0][3]<<","<<posicion[1][i]-posicion[1][3]<<endl;              
        	}
            
        	pf<<endl;
			contador=0;	
		}	    
        
        
        contador++;
        
       
        // CONDICION IF QUE NOS DARA EL VALOR DEL PERIODO DE CADA PLANETA
        // ENTRA EN EL BUCLE IF POR LA CONDICION QUE LE HEMOS DADP INCIALMENTE A CADA PLANETA Y TRAS ENTRAR
        // EN LA CONDICION CAMBIAMOS DICHO VALOR DE 1 A DOS PARA QUE NO VUELVA A ENTRAR EN LA CONDICION
        // MAS DE UNA VEZ Y NO SAQUE POR PANTALLA LOS PERIODOS DE LOS PLANETAS CONSTANTEMENTE

        if((posicion[1][1]<0.0)&&(mercurio==1))
        {
            mercurio=2;
            cout<<"Mercurio: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;
			T<<"Mercurio:"<<"\t"<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;        
        }
        
    
        if((posicion[1][2]<0.0)&&(venus==1))
        {
            venus=2;
            cout<<"Venus:"<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;
			T<<"Venus:"<<"\t"<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;        
        }  

        if((posicion[1][3]<0.0)&&(tierra==1))
        {
            tierra=2;
            cout<<"Tierra: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;
			T<<"Tierra:"<<"\t"<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;        
        }    

        if((posicion[1][4]<0.0)&&(marte==1))
        {
            marte=2;
            cout<<"Marte: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;
			T<<"Marte:"<<"\t"<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;        
        }
    
        if((posicion[1][5]<0.0)&&(jupiter==1))
        {
            jupiter=2;
            cout<<"Jupiter: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;
			T<<"Jupiter:"<<"\t"<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;        
        }  

        if((posicion[1][6]<0.0)&&(saturno==1))
        {
            saturno=2;
            cout<<"Saturno: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;
			T<<"Saturno:"<<"\t"<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;        
        }

        if((posicion[1][7]<0.0)&&(urano==1))
        {
            urano=2;
            cout<<"Urano: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;
			T<<"Urano:"<<"\t"<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;        
        }
    
        if((posicion[1][8]<0.0)&&(neptuno==1))
        {
            neptuno=2;
            cout<<"Neptuno: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;
			T<<"Neptuno:"<<"\t"<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;        
        }  

        if((posicion[1][9]<0.0)&&(pluton==1))
        {
            pluton=2;
            cout<<"Pluton: "<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;
			T<<"Pluton:"<<"\t"<<2*t/(60*60*24*sqrt((G*Msol)/(c*c*c)))<<"\t"<<"dias"<<endl;        
        }
        
        //TERMINA LA CONDICION DEL IF AQUI
        //EL CODIGO SEGUIRIA OPERANDO TANTAS VECES COMO LE HAYAMOS PUESTO DE VALOR A LA n

    }    
    //TERMINA EL BUCLE FOR AQUI
    
    //CERRAMOS TODOS LOS ARCHIVOS UTILIZADOS EN NUESTRO PROGRAMA
    mi.close(); 
    pi.close();
    vi.close();
    pf.close();
    T.close();
    pt.close();
    
    
    return 0;
}
