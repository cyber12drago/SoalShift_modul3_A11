#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<termios.h>
#include<sys/ipc.h>
#include<sys/shm.h>

int *shop_stock;
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

int main(void)
{
    system("clear");
    char choices;
    key_t key=1234;
    int shmid=shmget( key , sizeof(int), IPC_CREAT | 0666);
    shop_stock=shmat(shmid,NULL,0);
    system("clear");
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
}
