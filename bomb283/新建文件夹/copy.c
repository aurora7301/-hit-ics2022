#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h>

int main(int argc,char *argv[]){
	int i;

	if(argc!=4){
		printf("用法: Hello 学号 姓名 秒数！\n");
		exit(1);
	}
	for(i=0;i<8;i++){
		printf("Hello %s %s\n",argv[1],argv[2]);
		sleep(atoi(argv[3]));
	}
	getchar();
	return 0;
}
