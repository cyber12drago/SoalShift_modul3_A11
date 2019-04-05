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

# Soal 3
3. Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:

a.Terdapat 2 karakter Agmal dan Iraj
b. Kedua karakter memiliki status yang unik
	- Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
	- Iraj memiliki Spirit_Status, di awal program memiliki status 100
	- Terdapat 3 Fitur utama
		- All Status, yaitu menampilkan status kedua sahabat
		- Ex: Agmal WakeUp_Status = 75 
        	- Iraj Spirit_Status = 30
		- “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
		- “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
	-Terdapat Kasus yang unik dimana:
		- Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
		- Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
  		- Program akan berhenti jika Salah Satu : WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
		  Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)


Syarat Menggunakan Lebih dari 1 Thread

'''
bash


