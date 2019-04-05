#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

pthread_t tid[5];
int WakeUp_Status=0,Spirit_Status=100,counterbangun=0,countertidur=0;
int cekAgmal=0,cekIraj=0;
int cekpilihan=0;

void* AgmalBangun(void *arg){
      while(1){
          if(cekAgmal==1){
            printf("Agmal Ayo Bangun disabled 10s\n");
            sleep(10);
            //printf("Cooldown Selesai\n");
            cekAgmal=0;
            cekpilihan=0;
          }
          else if(cekpilihan==1&&cekAgmal==0){
              cekpilihan=0;          
              WakeUp_Status=WakeUp_Status+15;
              counterbangun++;
              if(counterbangun!=0&&counterbangun%3==0){
               cekIraj=1;
        }
              //printf("WakeUp_Status= %d\n",WakeUp_Status);
          }
          if(WakeUp_Status>=100){printf("Agmal Terbangun,mereka bangun pagi dan berolahraga\n");exit(0);}
      }
      
}

void* IrajTidur(void *arg){
      while(1){
          if(cekIraj==1){
            printf("Fitur Iraj Ayo Tidur disabled 10 s\n");
            sleep(10);
            // printf("Cooldown Selesai\n");
            cekIraj=0;
            cekpilihan=0;
          }
          else if(cekpilihan==2&&cekIraj==0){
              cekpilihan=0;
              Spirit_Status=Spirit_Status-20;
              //printf("Spirit_Status= %d\n",Spirit_Status);
              countertidur++;
              if(countertidur!=0&&countertidur%3==0){
               cekAgmal=1;
            }
          }
          if(Spirit_Status<=0){printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");exit(0);}
      }
}
int main(){
     char input[25],i;

     pthread_create(&(tid[1]),NULL, AgmalBangun,NULL);
      pthread_create(&(tid[2]),NULL, IrajTidur,NULL);
   while(1){
     fgets(input,25,stdin);
      i = strlen(input)-1;
      if(input[i]== '\n') {input[i] = '\0';}
      if(strcmp(input,"All Status")==0){
          printf("Agmal WakeUp_Status = %d\n", WakeUp_Status);
          printf("Iraj Spirit_Status = %d\n", Spirit_Status);
      }
      else if(strcmp(input,"Agmal Ayo Bangun")==0){
       cekpilihan=1;
        
        
      }
      else if(strcmp(input,"Iraj Ayo Tidur")==0){
              cekpilihan=2;
            
      }
      else{printf("Input Salah\n");}
   }
    pthread_join(tid[1],NULL);
    pthread_join(tid[2],NULL);
}
