#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

void* Cyclic_task(void * arg);

int main()
{

	pthread_t thread_1;
	int res ;

	res = pthread_create(&thread_1,NULL,Cyclic_task,NULL);

	if(res)
	{
		perror("thread creation fail\n");
		exit(0);
	}

	res = pthread_join(thread_1,NULL);

	if(res)
	{
		perror("thread join fail\n");
		exit(0);
	}

	printf("done\n");
	return 0;
}
void * Cyclic_task(void* arg)
{
	struct timespec	mytimer,cal_timer[100];
	mytimer.tv_sec = 0;
	mytimer.tv_nsec = 10000000;
	int t =0;
	timer_t sec = 0;
	long usec = 0;
	printf("inside thread\n");
	while(t<100)
	{
		printf("in Cyclic task %d\n",t);
		clock_gettime(CLOCK_MONOTONIC,&cal_timer[t]);
		t++;
		if(t==1)
		{
			sec = (timer_t)(cal_timer[t].tv_sec);
			usec = (long)(cal_timer[t].tv_nsec)/1000;
			printf("the difference is %u sec and % us\n" ,sec,usec);
		}
		else if(t>1 && t<100)
		{
			sec =(timer_t) (cal_timer[t].tv_sec-cal_timer[t-1].tv_sec);
			usec = ((long)cal_timer[t].tv_nsec-(long)cal_timer[t-1].tv_nsec)/1000;
			printf("the difference is %u sec and %d us\n" ,sec,usec);
		}
		else
		{
			sec = (timer_t)(cal_timer[99].tv_sec-cal_timer[0].tv_sec);
			usec = (long)(cal_timer[99].tv_nsec-cal_timer[0].tv_nsec)/1000;
			printf("the difference between the 1st and last call of delay is %u sec and %d us\n" ,sec,usec);
		}
		nanosleep(&mytimer,NULL);
	}

}
