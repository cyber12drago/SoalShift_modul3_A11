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

#Soal 3
Agmal dan Iraj merupakan 2 sahabat yang sedang kuliah dan hidup satu kostan, sayangnya mereka mempunyai gaya hidup yang berkebalikan, dimana Iraj merupakan laki-laki yang sangat sehat,rajin berolahraga dan bangun tidak pernah kesiangan sedangkan Agmal hampir menghabiskan setengah umur hidupnya hanya untuk tidur dan ‘ngoding’. Dikarenakan mereka sahabat yang baik, Agmal dan iraj sama-sama ingin membuat satu sama lain mengikuti gaya hidup mereka dengan cara membuat Iraj sering tidur seperti Agmal, atau membuat Agmal selalu bangun pagi seperti Iraj. Buatlah suatu program C untuk menggambarkan kehidupan mereka dengan spesifikasi sebagai berikut:

a. Terdapat 2 karakter Agmal dan Iraj
b. Kedua karakter memiliki status yang unik
	- Agmal mempunyai WakeUp_Status, di awal program memiliki status 0
	- Iraj memiliki Spirit_Status, di awal program memiliki status 100
	- Terdapat 3 Fitur utama
		- All Status, yaitu menampilkan status kedua sahabat
		- Ex: Agmal WakeUp_Status = 75 
      		- Iraj Spirit_Status = 30
		- “Agmal Ayo Bangun” menambah WakeUp_Status Agmal sebesar 15 point
		- “Iraj Ayo Tidur” mengurangi Spirit_Status Iraj sebanyak 20 point
  	- Terdapat Kasus yang unik dimana:
	- Jika Fitur “Agmal Ayo Bangun” dijalankan sebanyak 3 kali, maka Fitur “Iraj Ayo Tidur” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Fitur Iraj Ayo Tidur disabled 10 s”)
	- Jika Fitur  “Iraj Ayo Tidur” dijalankan sebanyak 3 kali, maka Fitur “Agmal Ayo Bangun” Tidak bisa dijalankan selama 10 detik (Dengan mengirim pesan ke sistem “Agmal Ayo Bangun disabled 10 s”)
	- Program akan berhenti jika Salah Satu :
	  - WakeUp_Status Agmal >= 100 (Tampilkan Pesan “Agmal Terbangun,mereka bangun pagi dan berolahraga”)
          - Spirit_Status Iraj <= 0 (Tampilkan Pesan “Iraj ikut tidur, dan bangun kesiangan bersama Agmal”)

- Syarat Menggunakan Lebih dari 1 Thread

```
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
```

- Kami membuat dua thread yang satu untuk Aqmal dan yang satu untuk Siraj
- fgets digunakan untuk menginput string kalimat. 
> fgets(input,25,stdin);
- Setiap menjalankan perintah Agmal Ayo Bangun atau Iraj Ayo Tidur maka nilai status mereka akan bertambah kecuali jika misalkan Agmal Ayo Bangun selama 3 kali maka tidak bisa menjalankan Iraj Ayo tidur selama 10 detik. Begitu Sebaliknya.
- Jika misalkan casenya "Agmal Ayo Bangun" sebanyak 3 kali dan akan keluar kalimat "Fitur Iraj Ayo Tidur disabled 10 s" Lalu  menjalakan perintah "Iraj Ayo Tidur" sebanyak 3 kali dalam 10 detik. Maka tidak keluar kalimat "Agmal Ayo Bangun disabled 10 s" karena variable countertidur tidak bertambah.
	


# Soal 4
Buatlah sebuah program C dimana dapat menyimpan list proses yang sedang berjalan (ps -aux) maksimal 10 list proses. Dimana awalnya list proses disimpan dalam di 2 file ekstensi .txt yaitu  SimpanProses1.txt di direktori /home/Document/FolderProses1 dan SimpanProses2.txt di direktori /home/Document/FolderProses2 , setelah itu masing2 file di  kompres zip dengan format nama file KompresProses1.zip dan KompresProses2.zip dan file SimpanProses1.txt dan SimpanProses2.txt akan otomatis terhapus, setelah itu program akan menunggu selama 15 detik lalu program akan mengekstrak kembali file KompresProses1.zip dan KompresProses2.zip 
Dengan Syarat : 
- Setiap list proses yang di simpan dalam masing-masing file .txt harus berjalan bersama-sama
- Ketika mengkompres masing-masing file .txt harus berjalan bersama-sama
- Ketika Mengekstrak file .zip juga harus secara bersama-sama
- Ketika Telah Selesai melakukan kompress file .zip masing-masing file, maka program akan memberi pesan “Menunggu 15 detik untuk mengekstrak kembali”
Wajib Menggunakan Multithreading
Boleh menggunakan system

## Langkah-langkah
1. Membuat command untuk menyimpan list proses
```
strcpy(input1, "ps -aux | head -n 11 > /home/diondevara/Documents/FolderProses1/SimpanProses1.txt" );
strcpy(input2, "ps -aux | head -n 11 > /home/diondevara/Documents/FolderProses2/SimpanProses2.txt" );
```
> ps -aux untuk melihat list proses yang berjalan
head -n untuk membatasi row
2. Membuat command untuk mengkompress file
```
strcpy(compress1, "zip -j -m /home/diondevara/Documents/FolderProses1/KompresProses1.zip /home/diondevara/Documents/FolderProses1/SimpanProses1.txt");
strcpy(compress2, "zip -j -m /home/diondevara/Documents/FolderProses2/KompresProses2.zip /home/diondevara/Documents/FolderProses2/SimpanProses2.txt");
```
>zip untuk compress file
-m untuk delete original file
-j untuk mengkompres file tanpa mengikutsertakan path
3. Membuat command untuk mengekstrak file
```
strcpy(extract1, "unzip /home/diondevara/Documents/FolderProses1/KompresProses1.zip -d /home/diondevara/Documents/FolderProses1/");
strcpy(extract2, "unzip /home/diondevara/Documents/FolderProses2/KompresProses2.zip -d /home/diondevara/Documents/FolderProses2/");
```
> unzip -d untuk mengekstrak file ke direktori yang ditentukan
4. Membuat fungsi untuk menyimpan list proses
```
void* input(void *arg)
{
    pthread_t id=pthread_self();
    if(pthread_equal(id,tid1[0])) 
    {
        system(input1);		
    }
    if(pthread_equal(id,tid1[1]))
    {
	system(input2);
    } 
}
```
5. Membuat fungsi untuk mengkompress file
```
void* compress(void *arg)
{
    pthread_t id=pthread_self();
    if(pthread_equal(id,tid1[0])) 
    {
        system(compress1);
    }
    if(pthread_equal(id,tid1[1]))
    {
	system(compress2);
    }    
}
```
6. Membuat fungsi untuk mengekstrak file 
```
void* extract(void *arg)
{
    pthread_t id=pthread_self();
    if(pthread_equal(id,tid1[0])) 
    {
	system(extract1);		 
    }
    if(pthread_equal(id,tid1[1]))
    {
	system(extract2);
    }
}
```

