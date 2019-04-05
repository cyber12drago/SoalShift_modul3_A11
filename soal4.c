#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h> 
#include<sys/types.h>
#include<sys/wait.h>

 
pthread_t tid[3];//inisialisasi array untuk menampung thread dalam kasus ini ada 3 thread
char input1[100];
char input2[100];
char compress1[200];
char compress2[200];
char extract1[200];
char extract2[200];

void* playandcount(void *arg)
{
    strcpy(input1, "ps -aux | head -n 11 > /home/diondevara/Documents/FolderProses1/SimpanProses1.txt" );
    strcpy(input2, "ps -aux | head -n 11 > /home/diondevara/Documents/FolderProses2/SimpanProses2.txt" );
    //ps -aux untuk melihat list proses yang berjalan
    //head -n untuk membatasi row
    strcpy(compress1, "zip -j -m /home/diondevara/Documents/FolderProses1/KompresProses1.zip /home/diondevara/Documents/FolderProses1/SimpanProses1.txt");
    strcpy(compress2, "zip -j -m /home/diondevara/Documents/FolderProses2/KompresProses2.zip /home/diondevara/Documents/FolderProses2/SimpanProses2.txt");
    //zip untuk compress file
    //-m untuk delete original file
    //-j untuk mengkompres file tanpa path
    strcpy(extract1, "unzip /home/diondevara/Documents/FolderProses1/KompresProses1.zip -d /home/diondevara/Documents/FolderProses1/");
    strcpy(extract2, "unzip /home/diondevara/Documents/FolderProses2/KompresProses2.zip -d /home/diondevara/Documents/FolderProses2/");
    //unzip -d untuk mengekstrak file ke direktori yang ditentukan
    

    unsigned long i=0;
    pthread_t id=pthread_self();
    
     
   
    
    if(pthread_equal(id,tid[0])) 
    {
        //system(create1);
	//system(create2);
        system(input1);
	system(input2);
	      	
         
    }
    sleep(1);//delay untuk menunggu pembuatan file
    if(pthread_equal(id,tid[1])) 
    {
        system(compress1);
      	system(compress2);
        printf("Menunggu 15 detik untuk mengekstrak kembali\n");

    }
    //printf("Menunggu 15 detik untuk mengekstrak kembali\n");
    sleep(15);//delay 15 detik
    if(pthread_equal(id,tid[2])) 
    {
	system(extract1);
	system(extract2); 
    }

	return NULL;
}

int main(void)
{
	int i=0;
	int err;
	while(i<3) 
	{
		err=pthread_create(&(tid[i]),NULL,&playandcount,NULL); //membuat thread 
		if(err!=0) //cek error
		{
			printf("\n can't create thread : [%s]",strerror(err));
		}
		else
		{
			printf("\n create thread success\n");
		}
		i++;
	}
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	exit(0);
	return 0;
}
