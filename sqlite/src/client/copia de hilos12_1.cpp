#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <vector>
#include <algorithm>
#include <string.h>


using namespace std;

sem_t mutex1;
sem_t mutex2;
int num[2];
vector<char*> lista;
vector<int> contador;
int c = 5;

SocketDatagrama s(7777);

void *broadcast(void*)
{

   PaqueteDatagrama p((char *)num, sizeof(int)*2,"192.168.0.255", 7200);

   while(1)
   {

      sem_wait(&mutex1);
      printf("\n broadcast->Recibiendo... \n");
      
      s.envia(p);
      sleep(5);
      sem_post(&mutex2);
      //pthread_exit(0);

   }

}

void *ordena(void*)
{
   while(1)
   {

      sem_wait(&mutex2);
      printf(" ordena \n \t .:lista:. \n\n");

      sort(lista.begin(),lista.begin()+lista.size());

      for(int i=0;i<lista.size();i++)
      {

         printf("\t %s\n", lista[i]);

      }
      for(int i=0;i<contador.size();i++)
      {
cout << i<< endl;
         printf(" %s, ", contador[i]);

      }

      printf("\n Borrar lista \n");
      lista.clear();

      sem_post(&mutex1);
      //pthread_exit(0);
   
   }

}

void *recibe(void*)
{

   PaqueteDatagrama pr(sizeof(int));
   char ip[16];

   while(1)
   {

      //int c=0;

      printf("\n fee\n");

      if(s.recibe(pr))
      {

         
         printf("recibido: ");
         printf("\n %s \n",pr.obtieneDireccion());
         memcpy(ip,(char *)pr.obtieneDireccion(),16);  
         printf("\n %s \n",ip);
         lista.push_back(ip);
         contador.push_back( c);
         c++;

         //printf("\n %s \n",lista[c]);
      
      }

   }

}

int main(void)
{
   pthread_t th1, th2, th3;

   s.concurrente();
   // Inicializa los semaforos
   sem_init(&mutex1, 0, 1);
   sem_init(&mutex2, 0, 0);
   
   /* Se crean dos hilos con atributos predeterminados */
   
   pthread_create(&th1, NULL, &broadcast, NULL);
   pthread_create(&th2, NULL, &ordena, NULL);
   pthread_create(&th3, NULL, &recibe, NULL);
   
   //printf("El hilo principal espera a sus hijos\n");
   //}
   /* se espera su terminación */
   pthread_join(th1, NULL);
   pthread_join(th2, NULL);
   pthread_join(th3, NULL);
   printf("El hilo principal termina\n");
   
   exit(0);
}
