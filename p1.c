/*************************************************************************
  > File Name: pthread_read_file.c
  > Author: 科林明伦
  > Mail: cui88777@163.com 
  > Created Time: 2023年03月03日 星期五 23时23分42秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <pthread.h>
#include <signal.h>

char bufferA[1024];
char bufferB[1024];
pthread_mutex_t lockA;
pthread_mutex_t lockB;
pthread_cond_t A_empty;
pthread_cond_t Anot_empty;
pthread_cond_t B_empty;

void * pthread_gets(void*arg)
{
	//printf("AA\n");
	FILE* fp=fopen("./ERROR.log","r");
	if(fp==NULL)
	{
		perror("fopen failed");
		exit(0);
	}
	while(1)
	{
		pthread_mutex_lock(&lockA);
		while(strlen(bufferA)!=0)
		{
			printf("%s\n",bufferA);
			pthread_cond_wait(&A_empty,&lockA);
		}
		fgets(bufferA,sizeof(bufferA),fp);
		pthread_cond_signal(&Anot_empty);
		pthread_mutex_unlock(&lockA);
	}
	fclose(fp);

}
void * pthread_find(void*arg)
{
	//printf("BB\n");
	while(1)
	{
		//读缓冲区A
		pthread_mutex_lock(&lockA);

		while(strlen(bufferA)==0)
		{
			pthread_cond_wait(&Anot_empty,&lockA);
		}
		if((strstr(bufferA,"E CamX")!=NULL)||(strstr(bufferA,"E CHIUSECASE")!=NULL))
		{
			//写缓冲区B   B的写和读是同步的，不是单独分开执行的，他会读A缓冲区，写入B缓冲区，B的写并不需要C的同步，仅需要互斥缓冲区B就能工作了
			pthread_mutex_lock(&lockB);
			strcpy(bufferB,bufferA);
			pthread_cond_signal(&B_empty);
			pthread_mutex_unlock(&lockB);
		}
		bzero(bufferA,sizeof(bufferA));
		pthread_cond_signal(&A_empty);
		pthread_mutex_unlock(&lockA);
	}
}
void * pthread_write(void*arg)
{
	umask(0000);
	int fd=open("result.log",O_RDWR|O_CREAT,0666);
	if(fd==-1)
	{
		perror("call open failed");
	}
	while(1)
	{
		//读缓冲区B
		pthread_mutex_lock(&lockB);
		while(strlen(bufferB)==0)
		{
			pthread_cond_wait(&B_empty,&lockB);
		}
		write(fd,bufferB,strlen(bufferB));
		printf("bufferB:%s\n",bufferB);
		bzero(bufferB,sizeof(bufferB));
		pthread_mutex_unlock(&lockB);
	}
	close(fd);
}
int main()
{
	bzero(bufferA,sizeof(bufferA));
	bzero(bufferB,sizeof(bufferB));
	pthread_mutex_init(&lockA,NULL);
	pthread_mutex_init(&lockB,NULL);
	pthread_cond_init(&A_empty,NULL);
	pthread_cond_init(&Anot_empty,NULL);
	pthread_cond_init(&B_empty,NULL);
	pthread_t tid[3];
	pthread_create(&tid[0],NULL,pthread_gets,NULL);
	pthread_create(&tid[1],NULL,pthread_find,NULL);
	pthread_create(&tid[2],NULL,pthread_write,NULL);
	while(1)
		sleep(1);
	return 0;
}
