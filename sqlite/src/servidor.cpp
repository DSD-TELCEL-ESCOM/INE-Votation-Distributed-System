/* Servidor de archivos para probar código de los alumnos en lenguaje C++ 
 $ ./file_server_objetos1 7000
*/
#include "../h/PaqueteDatagrama.h"
#include "../h/SocketDatagrama.h"
#include "../h/header.h"
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
#include "../h/sqlite_cpp.h"
#include <vector>


using namespace std;

vector<struct pck_votos> votos_vector;

void *consultar_voto( void* )
{
	struct pck_votos  mensEnv;
	struct pck_votos  mensRcb;
	
	bzero((char *)&mensEnv, sizeof(pck_votos));
	bzero( (char *)&mensRcb, sizeof(pck_votos) );
	
	SocketDatagrama socketlocal( 7782 );
	
	PaqueteDatagrama envio((char *)(&mensEnv), sizeof(pck_votos), "", 0);
	PaqueteDatagrama recepcion( sizeof(pck_votos) );
	
	while(true){
		sqlite_cpp *db = new sqlite_cpp("dbs/elecciones.db");	
		cout << "\nEsperando sconsulta ..." << votos_vector.size() << endl;      
		socketlocal.recibe(recepcion);         
		memcpy((char *)&mensRcb, recepcion.obtieneDatos(), sizeof(mensRcb));
		memcpy((char *)&mensEnv, recepcion.obtieneDatos(), sizeof(mensRcb));
	if( db->consultar_voto(mensRcb.CURP,mensRcb.celular, mensEnv.partido ) == 0 ){
			cout << "curp= " << mensEnv.CURP << ". cel= " << mensEnv.celular << ". par= " << mensEnv.partido << endl;
		}else{
			strcpy(mensEnv.CURP,"NULL");
			strcpy(mensEnv.celular,"NULL");
			strcpy(mensEnv.partido,"NULL");
			cout << "curp= " << mensEnv.CURP << ". cel= " << mensEnv.celular << ". par= " << mensEnv.partido << endl;
		}
		db->cerrar_db();
	}
}

void *estado_votos(void*)
{
	struct pck_estado_votos  mensEnv;
	struct pck_sol_estado  mensRcb;
	
	bzero((char *)&mensEnv, sizeof(pck_estado_votos));
	bzero( (char *)&mensRcb, sizeof(pck_sol_estado) );
	
	SocketDatagrama socketlocal( 7781 );
	
	PaqueteDatagrama envio((char *)(&mensEnv), sizeof(pck_estado_votos), "", 0);
	PaqueteDatagrama recepcion( sizeof(pck_sol_estado) );
	
	while(true){
		sqlite_cpp *db = new sqlite_cpp("dbs/elecciones.db");	
		cout << "\nEsperando peticion ..." << endl;      
		socketlocal.recibe(recepcion);      
		int cont = 0;
		mensEnv.votos[0] = db->consulta_partido( "PRI" );
		cont += mensEnv.votos[0];
		mensEnv.votos[1] = db->consulta_partido( "PAN" );
		cont += mensEnv.votos[1];
		mensEnv.votos[2] = db->consulta_partido( "PRD" );
		cont += mensEnv.votos[2];
		mensEnv.votos[3] = db->consulta_partido( "P_T" );
		cont += mensEnv.votos[3];
		mensEnv.votos[4] = db->consulta_partido( "VDE" );
		cont += mensEnv.votos[4];
		mensEnv.votos[5] = db->consulta_partido( "MVC" );
		cont += mensEnv.votos[5];
		mensEnv.votos[6] = db->consulta_partido( "NVA" );
		cont += mensEnv.votos[6];
		mensEnv.votos[7] = db->consulta_partido( "MOR" );
		cont += mensEnv.votos[7];
		mensEnv.votos[8] = db->consulta_partido( "HUM" );
		cont += mensEnv.votos[8];
		mensEnv.votos[9] = db->consulta_partido( "ENC" );
		cont += mensEnv.votos[9];
		mensEnv.votos[10] = db->consultar_registros() - cont;
		mensEnv.fraude = 0;
		
		envio.inicializaDatos((char *) &mensEnv);
      envio.inicializaIp(recepcion.obtieneDireccion());
      envio.inicializaPuerto(recepcion.obtienePuerto()); 
      socketlocal.envia(envio);
      db->cerrar_db();
	}
}

void *recibe_voto(void*)
{
	struct pck_votos  mensRcb;
	bzero( (char *)&mensRcb, sizeof(pck_votos) );
	SocketDatagrama socketlocal( 7780 );
	PaqueteDatagrama recepcion( sizeof(pck_votos) );
	while(true){
		sqlite_cpp *db = new sqlite_cpp("dbs/elecciones.db");	
		cout << "\nEsperando solicitud ..." << votos_vector.size() << endl;      
		socketlocal.recibe(recepcion);         
		memcpy((char *)&mensRcb, recepcion.obtieneDatos(), sizeof(mensRcb));
		if( db->add_voto(mensRcb.CURP,mensRcb.celular,mensRcb.partido) == 0 )
			votos_vector.push_back(mensRcb); 
		db->cerrar_db();
	}
}

int main(int argc, char *argv[])
{
   if(argc != 2){
      cout << "Forma de uso: " << argv[0] <<  " puerto\n";
      exit(0);
   }

	pthread_t th1, th2, th3;
	
	/* Se crean dos hilos con atributos predeterminados */
   
   pthread_create(&th1, NULL, &recibe_voto, NULL);
   pthread_create(&th2, NULL, &estado_votos, NULL);
   pthread_create(&th3, NULL, &consultar_voto, NULL);
   
   //printf("El hilo principal espera a sus hijos\n");
   //}
   /* se espera su terminación */
   pthread_join(th1, NULL);
   pthread_join(th2, NULL);
   pthread_join(th3, NULL);
   
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
