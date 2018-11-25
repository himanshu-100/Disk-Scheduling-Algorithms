#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
int a[10];
int front;
int rear;
int count;
int cap;
int d=0;
int tot=0;
int curr;
int dequeue()
{
	if(count!=0)
	{
		int r=a[front];
	front=(front+1)%cap;
		count--;
		return r;
	}
}
void enqueue(int x)
{
	if(count<cap)
	{
		rear=(rear+1)%cap;
		a[rear]=x;
		count++;
	}
}
void* serve_request(void* param)
{
	while(d!=1)
	{
		while(count==0&&d==0);
		if(d==1)
		{
			break;
		}
		int r=dequeue();
		tot+=abs(curr-r);
		curr=r;
		sleep(1);
		printf("%d\n",r);
	}
	pthread_exit(0);
}
void* add_request(void* param)
{
	for(int i=0;i<5;i++)
	{
		int x=1+rand()%30;
		printf("Added request for %d\n",x);
		enqueue(x);
		sleep(3);
	}
	d=1;
	pthread_exit(0);
}
int main()
{
	srand(time(NULL));
	cap=10;
	front=0;
	rear=-1;
	count=0;
	curr=15;
	for(int i=0;i<5;i++)
	{
		int x=1+rand()%30;
		printf("Added request for %d\n",x);
		enqueue(x);
	}
	pthread_t p1,p2;
	pthread_create(&p1,NULL,serve_request,NULL);
	pthread_create(&p2,NULL,add_request,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	printf("Total head movement %d\n",tot);
	return 0;
}