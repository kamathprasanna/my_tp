#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	pid_t ret;
	int i=0 ;

	while((i++) < 5)
	{
		ret = fork();//it would be interpreted as per break/continue put in child or parents process   
		sleep(1);
		if(ret <0)
		{
			perror("error in creation of thread\n");
			exit(-1);
		}
		if(ret > 0)
		{
			printf("in parent parent %d and pid %d \n",getppid(),getpid());
			//continue; //in order to have same parent to have a child
			break;
		}
		if(ret == 0)
		{
			printf("in child parent %d and pid %d \n",getppid(),getpid());
			//exit(0);//in order to have same parent to have a child
			continue; //in order to have child 's child
		}
	}

	if(ret >0) 
	{
		pid_t res ;
		int status;
		do
		{
			res =waitpid(-1,&status,0);
			if (res <0)
			{
				printf("no child left to process\n");
				break;
			}	
			else if(res == 0)
			{
				//it comes here only when WNOHANG is used instead of 0 is used 
				printf("waiting for child to end\n");

			}
			else
			{
				printf("child %d got ended\n",res);
				if(WIFEXITED(status))
				{
					printf("child ened normally\n");
				}
				else
				{
					printf("child ended abnormally\n");
				}
			}


		}while(1);
		
	}
	printf("done\n");
	return 0;
}