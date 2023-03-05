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
		//fgets肯定是循环读的， 每次一行到buffer， 然后控制他挂起， 别人处理完唤醒他继续走循环再读一行
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
			//也就是说 ABC模型 A和B同步 B和C同步 B的操作是读写一起进行的 A来引导B的运行 如果C运行过快则B线程会因为被互斥而阻塞挂起（既不读也不写）
			//直到C运行完成后，由于buffer被清空 导致C挂起释放互斥锁 B则可以继续写入，写完后来唤醒C
			//这个模型即传递读写功能,属于经典生产者消费者问题，注意这里B既是生产者也是消费者，但B是由A来唤醒消费功能，再执行生产功能来唤醒C，C是消费者，消费完成后告诉B
			//A和B是生产者消费者，由于B被A唤醒，因此不需要C的介入，即仅需要B来唤醒C即可
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
