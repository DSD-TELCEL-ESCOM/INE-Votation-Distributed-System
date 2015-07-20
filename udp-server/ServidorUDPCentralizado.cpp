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
char *ip="127.0.0.1";   
			
//Se crean los paquetes para envio y recepcion
struct registro Envreg;
struct registro Recreg;
//struct registro envPila;

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
      		//puerto=pr.obtienePuerto();
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