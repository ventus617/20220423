/*************************************************************************
	> File Name: fgets.c
	> Author: 科林明伦
	> Mail: cui88777@163.com 
	> Created Time: 2023年03月04日 星期六 17时00分53秒
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


int main(){
				FILE * fp;
				char buffer[1024];

				fp = fopen("ERROR.log","r");
				if(fp == NULL){
								perror("fopen Failed");
								exit(0);
				}
				while(fgets(buffer,sizeof(buffer),fp)!=NULL){
								printf("%s",buffer);
				}
				printf("\n");
				fclose(fp);
				return 0;
}
