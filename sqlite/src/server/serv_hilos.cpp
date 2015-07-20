/* Servidor de archivos para probar código de los alumnos en lenguaje C++ 
 $ ./file_server_objetos1 7000
*/
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "header.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../sqlite_cpp.h"

using namespace std;



void *recibe(void*)
{
	cout << "Estoy en el hilo que recibe..." << endl;
	while(true){
		
	}
}

int main(int argc, char *argv[])
{
   if(argc != 2){
      cout << "Forma de uso: " << argv[0] <<  " puerto\n";
      exit(0);
   }

	pthread_t th1;
	
	/* Se crean dos hilos con atributos predeterminados */
   
   pthread_create(&th1, NULL, &recibe, NULL);
   
   //printf("El hilo principal espera a sus hijos\n");
   //}
   /* se espera su terminación */
   pthread_join(th1, NULL);
   
   printf("El hilo principal termina\n");

   struct pck_votos  mensEnv;
   struct pck_votos  mensRcb;
   int pid, estado, fileDescriptor;
      
   bzero((char *)&mensEnv, sizeof(pck_votos));
   bzero((char *)&mensRcb, sizeof(pck_votos));
   PaqueteDatagrama envio((char *)(&mensEnv), sizeof(pck_votos), "", 0);

   SocketDatagrama socketlocal(atoi(argv[1]));
   PaqueteDatagrama recepcion(sizeof(pck_votos));
   //Crea Demonio
   while(1){   
      pid = fork();
      switch(pid){
         case -1:
            perror("Error en el fork");
            socketlocal.~SocketDatagrama();         
            exit(-1);
            break;
         case 0: //Hijo                  
            while(1){                   
               cout << "\nEsperando solicitud ..." << endl;      
               socketlocal.recibe(recepcion);         
               cout << "In: " << recepcion.obtieneDireccion() << " : ";
               cout << recepcion.obtienePuerto() << endl;      
               memcpy((char *)&mensRcb, recepcion.obtieneDatos(), sizeof(mensRcb));
	
     //          cout << "CURP: " << mensRcb.CURP << endl;       
     
               envio.inicializaDatos((char *) &mensEnv);
               envio.inicializaIp(recepcion.obtieneDireccion());
               envio.inicializaPuerto(recepcion.obtienePuerto()); 
               socketlocal.envia(envio);                 
            }
            exit(0);
            break;
         default: //padre
            wait(&estado);
            cout << "Soy el padre y acaba de morir un proceso hijo. Se crea otro...\n";
            
      }
   }  
}
