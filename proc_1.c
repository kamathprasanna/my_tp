#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
//#include<sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t ret;
	int n =0;
	//printf("%d\n",argc);
	if(argc > 1)
	{
		printf("%s\n",argv[1]);
	}
	ret = fork();
	if(ret<0)
	{
		perror("error in creation \n");
	}
	if(ret == 0)
	{
		printf("in child %d\n",ret);
		n=5;
	}
	if(ret > 0 )
	{
		printf("in parent %d\n",ret);
		n=1;

	}

//common for both channel and parent
	for(;n>0;n--)
	{
		printf("outside if %d\n",ret);
		sleep(1);
	}


	//the above program will help you understand the importance of wait 
	//my intention are simple face the problem in order to embrace the importance of preventing it

	if(ret >0)
	{
		int stat_val;
		pid_t child;

		printf("waitin for child to be finished\n");
		child = wait(&stat_val);		
		printf("child finished %d\n",child);
		if(WIFEXITED(stat_val))
			printf("child exited normally\n");
		else
			printf("child exited abnormally\n");
	}
	//exit(0);
	return 0;
}
