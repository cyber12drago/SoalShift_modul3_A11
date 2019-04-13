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
# Soal 2

# Soal 3
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
# Soal 5
Angga, adik Jiwang akan berulang tahun yang ke sembilan pada tanggal 6 April besok. Karena lupa menabung, Jiwang tidak mempunyai uang sepeserpun untuk membelikan Angga kado. Kamu sebagai sahabat Jiwang ingin membantu Jiwang membahagiakan adiknya sehingga kamu menawarkan bantuan membuatkan permainan komputer sederhana menggunakan program C. Jiwang sangat menyukai idemu tersebut. Berikut permainan yang Jiwang minta. 
Pemain memelihara seekor monster lucu dalam permainan. Pemain dapat  memberi nama pada monsternya.
Monster pemain memiliki hunger status yang berawal dengan nilai 200 (maksimalnya) dan nanti akan berkurang 5 tiap 10 detik.Ketika hunger status mencapai angka nol, pemain akan kalah. Hunger status dapat bertambah 15 apabila pemain memberi makan kepada monster, tetapi banyak makanan terbatas dan harus beli di Market.
Monster pemain memiliki hygiene status yang berawal dari 100 dan nanti berkurang 10 tiap 30 detik. Ketika hygiene status mencapai angka nol, pemain akan kalah. Hygiene status' dapat bertambah 30 hanya dengan memandikan monster. Pemain dapat memandikannya setiap 20 detik(cooldownnya 20 detik).
Monster pemain memiliki health status yang berawal dengan nilai 300. Variabel ini bertambah (regenerasi)daa 5 setiap 10 detik ketika monster dalam keadaan standby.
Monster pemain dapat memasuki keadaan battle. Dalam keadaan ini, food status(fitur b), hygiene status'(fitur c), dan ‘regenerasi’(fitur d) tidak akan berjalan. Health status dari monster dimulai dari darah saat monster pemain memasuki battle. Monster pemain akan bertarung dengan monster NPC yang memiliki darah 100. Baik monster pemain maupun NPC memiliki serangan sebesar 20. Monster pemain dengan monster musuh akan menyerang secara bergantian. 
Fitur shop, pemain dapat membeli makanan sepuas-puasnya selama stok di toko masih tersedia.
Pembeli (terintegrasi dengan game)
Dapat mengecek stok makanan yang ada di toko.
Jika stok ada, pembeli dapat membeli makanan.
Penjual (terpisah)
Bisa mengecek stok makanan yang ada di toko
Penjual dapat menambah stok makanan.
	Spesifikasi program:
Program mampu mendeteksi input berupa key press. (Program bisa berjalan tanpa perlu menekan tombol enter)
Program terdiri dari 3 scene yaitu standby, battle, dan shop.
Pada saat berada di standby scene, program selalu menampilkan health status, hunger status, hygiene status, stok makanan tersisa, dan juga status kamar mandi (“Bath is ready” jika bisa digunakan, “Bath will be ready in [bath cooldown]s” jika sedang cooldown). Selain itu program selalu menampilkan 5 menu, yaitu memberi makan, mandi, battle, shop, dan exit. Contoh :

Standby Mode
Health : [health status]
Hunger : [hunger status]
Hygiene : [hygiene status]
Food left : [your food stock]
Bath will be ready in [cooldown]s
Choices
Eat
Bath
Battle
Shop
Exit

Pada saat berada di battle scene, program selalu menampilkan health status milik pemain dan monster NPC. Selain itu, program selalu menampilkan 2 menu yaitu serang atau lari. Contoh :

Battle Mode
Monster’s Health : [health status]
Enemy’s Health : [enemy health status]
Choices
Attack
Run

Pada saat berada di shop scene versi pembeli, program selalu menampilkan food stock toko dan milik pemain. Selain itu, program selalu menampilkan 2 menu yaitu beli dan kembali ke standby scene. Contoh :

		Shop Mode
		Shop food stock : [shop food stock]
		Your food stock : [your food stock]
		Choices
Buy
Back

Pada program penjual, program selalu menampilkan food stock toko. Selain itu, program juga menampilkan 2 menu yaitu restock dan exit. Contoh :

Shop
Food stock : [shop food stock]
Choices
Restock
Exit

Pastikan terminal hanya mendisplay status detik ini sesuai scene terkait (hint: menggunakan system(“clear”))

## Langkah-langkah 
### Untuk soal5.c
1. Buat fungsi input tanpa menekan "enter"
```
int input(void)//input tanpa enter
{
	struct termios oldt, newt;
	int in;
	tcgetattr( STDIN_FILENO, &oldt );
	newt=oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	in=getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return in;
}
```
2. Buat fungsi cooldown bath
```
void* waktu(void* arg)//waktu yang berlalu
{
    cooldown=0;
    while(1)
    {
		cooldown=cooldown+1;
		sleep(1);
    }
}
```
3. Buat fungsi hunger status
```
void* hunger(void *arg)//hunger 
{
    while(1)
    {
		while(standby=0)
		{
		}
		sleep(10);
		hunger_stat=hunger_stat-5;
		
	}
}
```
4. Buat fungsi hygene status
```
void* hygiene(void *arg)//hygiene
{
    while(1)
    {
		while(standby=0)
		{
		}
		sleep(30);
		hygiene_stat=hygiene_stat-10;
		
    }
}
```
5. Buat fungsi regenerasi
```
void* regen_health(void *arg)//regenerasi
{
    while(1)
    {
		while(standby=0)
		{
		}
		sleep(10);
		health=health+5;
    }
}
```
6. Buat fungsi standby
```
void stand_by()
{
    while(1)
    {	
		system("clear");
			if(hunger_stat<1 || hygiene_stat<1)//cek hunger dan hygene status
			{
				printf("You Died\n");
				sleep(1);
				exit(0);
			}
			printf("Standby Mode\n");
			printf("Health : %d\n", health);
			printf("Hunger : %d\n", hunger_stat);
			printf("Hygiene : %d\n", hygiene_stat);
			printf("Food left : %d\n", player_food);
			if(cooldown>=20)//cek cooldown
			{
				printf("Bath is ready\n");
			}
			else
			{
				printf("Bath will be ready in %ds\n",20-cooldown);
			}
			printf("Choices\n");
			printf("1. Eat\n");
			printf("2. Bath\n");
			printf("3. Battle\n");
			printf("4. Shop\n");
			printf("5. Exit\n");
			choices=input();
			if(choices=='1')//eat
			{
				if(player_food<1) //cek stock
				{
					printf("Stock Empty\n");
				}
				else
				{
					player_food=player_food-1;
					hunger_stat=hunger_stat+15;
					if(hunger_stat>200)//mencegah melebihi 200
					{
						hunger_stat=200;
					}
				}

			}
			else if(choices=='2')//bath
			{
				if(cooldown>=20)
				{
					cooldown=0;
					printf("Bath is ready\n");
					hygiene_stat=hygiene_stat+30;
				}
				else
				{
					printf("Bath will be ready in %ds\n", 20-cooldown);
				}
			}
		else if(choices=='3')//battle
		{
			enemy_health=100;
			system("clear");
			standby=0;
			battle();
		}
		else if(choices=='4')//shop
		{
			system("clear");
			standby=0;
			shop();
	 	}
		else if(choices=='5')//exit
		{
			system("clear");
			exit(0);
		}
		system("clear");
	}    
}
```
7. Buat fungsi battle
```
void battle()
{
    while(1)
    {
    	system("clear");
		printf("Battle Mode\n");
		printf("Monster's Health : %d\n", health);
		printf("Enemy's Health : %d\n", enemy_health);
		printf("Choices\n");
		printf("1. Attack\n");
		printf("2. Run\n");
		choices=input();
		if(choices=='1')//attack
		{
			health=health-20;
			enemy_health=enemy_health-20;
			if(enemy_health<1)//cek health musuh
			{
				printf("You Win\n");
				sleep(1);
				system("clear");
				standby=1;
				stand_by();
			}
			if(health<1)//cek health player
			{
				printf("You Died\n");
				sleep(1);
				system("clear");
				exit(0);
			}			
		}
		else if(choices=='2')//run
		{
			system("clear");
			stand_by();
		}
		system("clear");
	}
}
```
8. Buat fungsi shop
```
void shop()
{
    while(1)
    {	
    	system("clear");
		printf("Shop Mode\n");
		printf("Shop food stock : %d\n",*shop_stock);
		printf("Your food stock : %d\n",player_food);
		printf("Choices\n");
		printf("1. Buy\n");
		printf("2. Back\n");
		choices=input();
		if(choices=='1')//buy
		{
		    if(*shop_stock<0)
		    {
				printf("Stock Empty\n");
		    }
		    else
		    { 
				*shop_stock=*shop_stock-1;
				player_food=player_food+1;
		    }
		}
		else if(choices=='2')//back
		{
		    system("clear");
		    standby=1;
		    stand_by();
		}
		system("clear");
	}
}
```
9. Untuk stock shop digunakan shared memory
```
key_t key=1234;
int shmid=shmget(key,sizeof(int),IPC_CREAT | 0666);
shop_stock=shmat(shmid,NULL,0);
```
### Untuk soal5shop.c
1. Buat fungsi input tanpa menekan "enter"
```
int input(void)//input tanpa enter
{
	struct termios oldt, newt;
	int in;
	tcgetattr( STDIN_FILENO, &oldt );
	newt=oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	in=getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return in;
}
```
2. Digunakan shared memory untuk restock
```
while(1)
    {
		printf("Shop\n");
		printf("Food stock : %d\n", *shop_stock);
		printf("Choices\n");
		printf("1. Restock\n");
		printf("2. Exit\n");
		choices=input();
		if(choices=='1')//restock
		{
			*shop_stock=*shop_stock+1;
		}
		else if(choices=='2')//back
		{
			system("clear");
			exit(0);
		}
		system("clear");
	}
	return 0;
```
