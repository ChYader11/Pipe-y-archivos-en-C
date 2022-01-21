#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void){

     int fd[2];
     pid_t pidC;
     char buf[4];
     char cad[10];

     pipe(fd);
     pidC = fork();
     switch(pidC)
     {
         case 0:  /* HIJO */
            close(fd[1]);
            read(fd[0], buf, sizeof(buf) );
            close(fd[0]);
            int número=strtol(buf,NULL,10);
            if (número>=500)
               printf("Hola, soy el Hijo, el número (%d) generado por mi padre es mayor que 500 \n", número);
            else
               printf("Hola, soy el Hijo, el número (%d) generado por mi padre es menor que 500 \n", número);
            break;
         case -1:
             /* ERROR */
            break;
         default:  /* PADRE */
            srand(time(NULL));
            int r=1+rand()%(1000);printf("Hola, soy el Padre, acabo de generar aleatoriamente el número: %d \n",r);
            sprintf(cad,"%d",r);
            close(fd[0]);
            write(fd[1], cad, 4);
           close(fd[1]);
           exit(0);
            break;
      }
      return 0;
}
