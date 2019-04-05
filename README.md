# SoalShift_modul3_A11

# Soal 1

1. Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
	./faktorial 5 3 4
	3! = 6
	4! = 24
	5! = 120

```bash
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

    return 0;
}
```

- Ubahlah char menjadi integer menggunakan 
  > atoi(argv[i]);
- Setelah itu urutkan isi array menggunakan algoritma selection sort
- Setelah itu setiap case, create thread baru.
  > pthread_create(&(tid[i]),NULL,cek_factorial, (void*)(intptr_t) A[i]);
- Setiap thread menjalankan fungsi factorial dan mengeluarkan hasilnya
- Setelah berhasi create thread lansung join agar bisa synchron
  > pthread_join(tid[i], NULL);


