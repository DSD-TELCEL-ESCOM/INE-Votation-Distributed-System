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

using namespace std;

int main( int argc, char *argv[] )
{
   if(argc != 4)
   {
	   cout << "Forma de uso: " << argv[0] << " [DIR_IP] " << "[PORT]" << "[NO_PCK]" << endl;
	   exit(0);
   }
   SocketDatagrama s(7780);
   struct pck_votos msg;
   struct pck_votos res;
   
   bzero((char *)&msg, sizeof(pck_votos));
   bzero((char *)&res, sizeof(pck_votos));
  
   strcpy(msg.CURP,"000000000000000002");
   strcpy(msg.celular,"0000000002");
   strcpy(msg.partido,"PRD");
   
   PaqueteDatagrama mensaje((char *)&msg, sizeof(pck_votos),argv[1], atoi(argv[2]));
   PaqueteDatagrama respuesta(sizeof(pck_votos));
   s.envia( mensaje );
    
	s.recibe( respuesta );
	memcpy( (char *)&res, respuesta.obtieneDatos(), sizeof(res) );
	cout << "in: " << res.CURP << ", " << sizeof(res) << " bytes" << endl;
	cout << "in: " << res.celular << ", " << sizeof(res) << " bytes" << endl;
	   
   exit(0);
}
