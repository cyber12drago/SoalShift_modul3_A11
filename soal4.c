#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h> 
#include<sys/types.h>
#include<sys/wait.h>

 
pthread_t tid1[2];//inisialisasi array untuk menampung thread 
char input1[100];
char input2[100];
char compress1[200];
char compress2[200];
char extract1[200];
char extract2[200];

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

int main(void)
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
    int i=0;
    int err;
    while(i<2)
    {
	err=pthread_create(&(tid1[i]),NULL,&input,NULL); //membuat thread 
    	i++;
    }
    i=0;
    pthread_join(tid1[0],NULL);
    pthread_join(tid1[1],NULL);
    while(i<2) 
    {
	err=pthread_create(&(tid1[i]),NULL,&compress,NULL); //membuat thread 
        i++;
    }
    i=0;
    pthread_join(tid1[0],NULL);
    pthread_join(tid1[1],NULL); 
    printf("Menunggu 15 detik untuk mengekstrak kembali\n"); 
    sleep(15);
    while(i<2) 
    {
	err=pthread_create(&(tid1[i]),NULL,&extract,NULL); //membuat thread
	i++; 
    }
    i=0;
    pthread_join(tid1[0],NULL);
    pthread_join(tid1[1],NULL);
    exit(0);
    return 0;
}
