#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <pthread.h>

using namespace std;

#define TAM 1024 
 

void generaInfo(char info[],int cuenta);

int main(int argc, char const *argv[])
{
	int  pto;
	char numregistros[1];
	pto = atoi(argv[1]);

	char nreg[5]	;
	
	cout<<"Servidor iniciado, esperando paquetes....";
	//cout<<"tamaño " <<sizeof(&nreg);

	cout<<"\n socket creado";
	//int numeropaquete=0,i,npaquetes=0,pto;
	//char npa[5]	;
	//char* direccion;
	//strcpy(direccion,(char*)"127.0.0.1");
	//cout<<"Direccion "<<direccion<<"\n";

	
	

	//cout<<"Numero de registros "<< numregistros;


/*
	while(1){
	 

		strcpy(numregistros,p1->obtieneDatos());

	cout<<"Numero de registros "<< numregistros;

}
*/

/*
	//pto= atoi(argv[1]);
	int cuenta=1,incremento=0;
	//Genera la informacion
	char info[1024];		

	//npaquetes=atoi(argv[2]);	   
	    
while(1) {
	//while(incremento<npaquetes){
		p1= new PaqueteDatagrama(sizeof(int));
		s1.recibe(*p1);	
		strcpy(npa,p1->obtieneDatos());
		npaquetes=atoi(npa);

		cout<<"npaquetes: "<<npaquetes;
		generaInfo(info,cuenta);		
		cout<<"NUMERO DE PAQUETES: "<<npaquetes<<"\n";
		p2= new PaqueteDatagrama((char *)&info, sizeof(&info), (char*)direccion, pto );
		s1.envia(*p2);
		sleep(2);
		cuenta++;

	 //}
	 	if(incremento==npaquetes)
	 		exit(0);

	}
*/
	return 0;
}


