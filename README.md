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

