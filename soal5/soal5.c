#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<termios.h>
#include<sys/ipc.h>
#include<sys/shm.h>


pthread_t tid1[4];

char monster_name[100];
int hunger_stat=200;
int hygiene_stat=100;
int health=300;
int player_food=100;
int *shop_stock;
int cooldown=0;
int enemy_health;
int standby=1;
char choices; 
void stand_by();
void battle();
void shop(); 

int input(void)
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
			if(enemy_health<1)
			{
				printf("You Win\n");
				sleep(1);
				system("clear");
				standby=1;
				stand_by();
			}
			if(health<1)
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

void* waktu(void* arg)//waktu yang berlalu
{
    cooldown=0;
    while(1)
    {
		cooldown=cooldown+1;
		sleep(1);
    }
}

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

int main(void)
{
    system("clear");
    printf("Monster name : ");
    scanf("%s", monster_name);
    key_t key=1234;
    int shmid=shmget(key,sizeof(int),IPC_CREAT | 0666);
    shop_stock=shmat(shmid,NULL,0);
    pthread_create(&(tid1[0]),NULL,&waktu,NULL);
    pthread_create(&(tid1[0]),NULL,&hunger,NULL);
    pthread_create(&(tid1[0]),NULL,&hygiene,NULL);
    pthread_create(&(tid1[0]),NULL,&regen_health,NULL);
    stand_by();
    exit(0);
    return 0;
}
