
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

using namespace std;

sem_t mutex1;
sem_t mutex2;

int numregistro[0];

struct registro
{
	char celular[11];
	char CURP[19];
	char partido[4];
	char opcion[1];
}; 

vector<registro> pilaregistro;

int puerto1=8888;
int puerto2=7777;
int contador=0;

char *ip="127.0.0.2";

SocketDatagrama socketudpcliente(puerto1);
SocketDatagrama socketudpserverc(puerto2);
			
//Se crean los paquetes para envio y recepcion
struct registro Envreg;
struct registro Recreg;
//struct registro envPila;
int er=0;

char* toJSON()
{
	char * super_string=NULL;

	super_string = (char*)malloc(64*sizeof(char));

	
	memcpy(&(super_string[0]),"{\"curp\":\"",9); 
	memcpy(&(super_string[9]),Recreg.CURP,18); 
	memcpy(&(super_string[27]),"\",\"phone\":\"",11); 
	memcpy(&(super_string[38]),Recreg.celular,10); 

	memcpy(&(super_string[48]),"\",\"party\":\"",11); 
	memcpy(&(super_string[59]),Recreg.partido,3); 
	memcpy(&(super_string[62]),"\"}",2);
	
/*
	memcpy(&(super_string[0]),"{\"curp\":\"",9); 
	memcpy(&(super_string[10]),Recreg.CURP,19); 
	memcpy(&(super_string[28]),"\",\"phone\":\"",12); 
	memcpy(&(super_string[39]),Recreg.celular,11); 

	memcpy(&(super_string[49]),"\",\"party\":\"",11); 
	memcpy(&(super_string[60]),Recreg.partido,3); 
	memcpy(&(super_string[63]),"\"}",2);
*/
	return super_string;
}

void *ReciboUDPServer(void*)
{
	PaqueteDatagrama pr(sizeof(registro));
	PaqueteDatagrama paquete((char *)&Envreg, sizeof(registro),ip, puerto1);

   	while(1)
   	{
   		sem_wait(&mutex1);
      	if(socketudpcliente.recibe(pr))
      	{
	        //dir.s_addr = inet_addr(pr.obtieneDireccion()); //DUDA AQUI
	        memcpy((char*)&Recreg, pr.obtieneDatos(), sizeof(Recreg));
		    //pr.obtieneDatos();

	        cout << "Celular: " << Recreg.celular << endl;
			cout << "Curp:  " << Recreg.CURP << endl;
			cout << "Partido: " << Recreg.partido << endl;		    
	        //pilaregistro.push_back(Recreg);
      	}
      	sem_post(&mutex2);
   	}
}

void *EnvioWebServer(void*)
{   	
	
   	while(1)
   	{
      	sem_wait(&mutex2);
      	
      	//cout<<pilaregistro.size();

		//while (!pilaregistro.empty())
		//{  		
      	int valorRecvfrom;
		cout<<"\nEnvioWebServer\n";
		//envPila=pilaregistro.back();
		

		//PaqueteDatagrama paquete((char *)&Recreg, sizeof(registro),"192.168.43.220", puerto2);
		//PaqueteDatagrama paqueteR(tamr);
		//Estructura para reenvio de paquetes 

	    //struct timeval tiempoFuera;
	    //bzero((char *)&tiempoFuera, sizeof(struct timeval));
	    //tiempoFuera.tv_sec = 0;
	    //tiempoFuera.tv_usec = 500000;

		//socketudpserverc.setTiempo(tiempoFuera);
		
		//Se envia el paquete
    	//cout<<"si envio"<<endl<<endl;
    	//pilaregistro.pop_back();
		//}

		char* vote = toJSON();
		PaqueteDatagrama paquete(vote, sizeof(char)*64, "192.168.43.220", puerto2);
		socketudpserverc.envia(paquete);
		contador++;
		cout<<"Numero de envios"<<contador<<endl;
		
		//PaqueteDatagrama recepcion(sizeof(char)*2);
		//socketudpserverc.recibe(recepcion);

      	sem_post(&mutex1);
   }
   
}

void *ReciboServerCentralizado(void*)
{
   /*int num[0];
   char *ip="127.0.0.1";
   //PaqueteDatagrama p((char *)(&Recreg), sizeof(registro),ip, puerto2);
   PaqueteDatagrama pr(sizeof(int));

   while(1)
   {
      sem_wait(&mutex1);
      printf("\n ReciboServerCentralizado.. \n");  
      
		if(socketudpserverc.recibe(pr) != -1)
		{
			//emcpy(ip,(char *)&dir.s_addr,4);  
         	pr.obtieneDatos();
         	memcpy(&num[0], pr.obtieneDatos(), sizeof(int));
         	cout<<"Numero de registros que llegaron: "<<num[0]<<endl;
		}

      sleep(10);
   }*/
}

int main(void)
{
   pthread_t th1, th2, th3;

   	bzero((char*)&Envreg, sizeof(struct registro));
	bzero((char*)&Recreg, sizeof(struct registro));
	//bzero((char*)&envPila, sizeof(struct registro));
   //s.concurrente();
   // Inicializa los semaforos
   sem_init(&mutex1, 0, 1);
   sem_init(&mutex2, 0, 0);
   
   /* Se crean dos hilos con atributos predeterminados */
   pthread_create(&th1, NULL, &ReciboUDPServer, NULL);
   pthread_create(&th2, NULL, &EnvioWebServer, NULL);
   pthread_create(&th3, NULL, &ReciboServerCentralizado, NULL);
   
   //printf("El hilo principal espera a sus hijos\n");
   //}
   /* se espera su terminación */
   pthread_join(th1, NULL);
   pthread_join(th2, NULL);
   pthread_join(th3, NULL);
   printf("El hilo principal termina\n");
   
   exit(0);

   return(0);
}



/*
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <vector>
#include <algorithm>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"

using namespace std;

struct registro
{
	char celular[11];
	char CURP[19];
	char partido[4];
	char opcion[1];
}; 

vector<registro> pilaregistro;

int puerto2=8888;

//SocketDatagrama socketudpcliente(puerto1);
SocketDatagrama socketudpserver(puerto2);
char *ip="127.0.0.2";   
			
//Se crean los paquetes para envio y recepcion
struct registro Envreg;
struct registro Recreg;
//struct registro envPila;

char* toJSON()
{
	char * super_string=NULL;

	super_string = (char*)malloc(64*sizeof(char));

	memcpy(&(super_string[0]),"{\"curp\":\"",9); 
	memcpy(&(super_string[9]),regis.CURP,18); 
	memcpy(&(super_string[27]),"\",\"phone\":\"",11); 
	memcpy(&(super_string[38]),regis.celular,10); 

	memcpy(&(super_string[48]),"\",\"party\":\"",11); 
	memcpy(&(super_string[59]),regis.partido,3); 
	memcpy(&(super_string[62]),"\"}",2);

	return super_string;
}

int main(void)
{
	bzero((char*)&Recreg, sizeof(struct registro));
	PaqueteDatagrama pr(sizeof(registro));	
	PaqueteDatagrama envio((char*)(&Envreg), sizeof(registro), ip, puerto2);

	int destino,puerto;

   	while(1)
   	{
      	if(socketudpserver.recibe(pr))
      	{
      		puerto=pr.obtienePuerto();
      		//if((socketudpserver.inicializaPuerto(pr.obtienePuerto()))=8888)
      		//if(puerto==8888)
      		//{
	        //dir.s_addr = inet_addr(pr.obtieneDireccion()); //DUDA AQUI
	        memcpy((char*)&Recreg, pr.obtieneDatos(), sizeof(Recreg));
		    //pr.obtieneDatos();
	        //if((destino = open("servidorvotos.txt", O_WRONLY|O_TRUNC|O_CREAT, 0666)) == -1)
			//{
			//	perror("servidorvotos.txt");
			//	exit(-1);
			//}
	        cout << "Celular: " << Recreg.celular << endl;
			cout << "Curp:  " << Recreg.CURP << endl;
			cout << "Partido: " << Recreg.partido << endl;		    
	        //pilaregistro.push_back(Recreg);
	        //write(destino,  &Recreg, sizeof(registro));
		    //}
      	}
   	}
}
*/