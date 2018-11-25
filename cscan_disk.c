#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<math.h>
int a[10];
int front;
int rear;
int count;
int cap;
int d=0;
int curr;
int tot;
int dir;
int dequeue()
{
	int min=1000,ans,f=0;
	for(int i=0;i<10;i++)
	{
		if(a[i]!=100&&curr!=a[i]&&(a[i]-curr)>0&&min>abs(a[i]-curr))
		{
			min=abs(a[i]-curr);
			ans=i;
			f=1;
		}
	}
	if(f==0)
	{
		int cur=-1;
		tot+=abs(31-curr);
		for(int i=0;i<10;i++)
		{
			if(a[i]!=100&&cur!=a[i]&&(a[i]-cur)>0&&min>abs(a[i]-cur))
			{
				min=abs(a[i]-cur);
				ans=i;
				f=1;
			}
		}
		tot+=a[ans];
		tot-=abs(curr-a[ans]);
	}
	int e=a[ans];
	a[ans]=100;
	count--;
	return e;
}
void enqueue(int x)
{
	for(int i=0;i<10;i++)
	{
		if(a[i]==100)
		{
			a[i]=x;
			break;
		}
	}
	count++;
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
		tot+=abs(r-curr);
		curr=r;
		sleep(1);
		printf("Processed %d\n",r);
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
	curr=15;
	tot=0;
	cap=10;
	front=0;
	rear=-1;
	count=0;
	dir=1;
	printf("Forward direction\n");
	for(int i=0;i<10;i++)
	{
		a[i]=100;
	}
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