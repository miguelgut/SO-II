#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#define NUM_THREADS     2

int variavel_global;
pthread_mutex_t trava_programa;

void *PrintHello(void *threadid)
{
   long k, pontos;
   float r;
   long tid;
   tid = (long)threadid;


   printf("\nIniciou, thread #%ld!\n", tid);
   
   pontos=100000000000/NUM_THREADS;

   for (k=0; k<pontos; k++){
   r = sin(1.77)*cos(.99);
   }
    
/* Testa o mutex. Se liberado ativa o mutex e avanca */

    pthread_mutex_lock(&trava_programa);


   printf("Valor variavel_global = %d - Thread #%ld\n", variavel_global,tid);
   variavel_global = variavel_global +1;

   printf("Terminou, thread #%ld!\n", tid);

/* libera o mutex */

   pthread_mutex_unlock(&trava_programa); 

   pthread_exit(NULL);
}


int main (int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    long ti, tempo_global;
    void *status;
    pthread_attr_t attr;
    time_t inicio, fim, reghora;
    struct tm *tmptr;
    
    
    printf("\n\nPrograma principal iniciou\n\n");
    
    reghora = time(NULL);
    tmptr = localtime(&reghora);
    printf("horario inicio: %s\n", asctime(tmptr));
    
    
   inicio= time(NULL);

    if (pthread_mutex_init(&trava_programa, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }


/* Bloqueia o inicio das threads ateh que todas sejam criadas */

    pthread_mutex_lock(&trava_programa);


/* cria as threads */

   variavel_global = 0;

  pthread_attr_init(&attr);
   pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


   for(t=0; t<NUM_THREADS; t++){
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], &attr, PrintHello, (void *)t);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }
    

/* liberas as threads para iniciarem */
 
    pthread_mutex_unlock(&trava_programa);


/* Rotina para esperar que todas threads terminem */

 	pthread_attr_destroy(&attr);

	for(t=0; t<NUM_THREADS; t++){
	    pthread_join(threads[t], &status);
	}


    fim=time(NULL);
    
    reghora = time(NULL);
    tmptr = localtime(&reghora);
    printf("\nhorario fim: %s", asctime(tmptr));
    
    fprintf(stdout, "Tempo Gasto = %f\n\n", difftime(fim, inicio));

    pthread_exit(NULL);
    pthread_mutex_destroy(&trava_programa);
}
