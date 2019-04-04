#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[105];
 
void* cek_factorial(void *arg){
     int i,n;
     n= (intptr_t) arg;
     long long hasil=1;
     for(i=1;i<=n;i++){
         hasil=hasil*i;
     }
      printf("%d!= %lld\n",n,hasil);
     return NULL;
}

void sorting(int a[], int n){
    int i,j,temp;
    for(i=1;i<n;i++){
       for(j=i+1;j<n;j++){
            if(a[i] > a[j]){
                 temp=a[i];
                 a[i]=a[j];
                 a[j]=temp;
	    }
	}
     }
}

int main(int argc, char *argv[]){
    
    int  A[105],i,temp,j,err;
    for(i=1;i<argc;i++){
      A[i]=atoi(argv[i]);
    }
    
    sorting(A,argc);

    for(i=1;i<argc;i++){
           pthread_create(&(tid[i]),NULL,cek_factorial, (void*)(intptr_t) A[i]); //membuat thread
	   pthread_join(tid[i], NULL);

	}
}
