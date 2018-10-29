#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define UPPER 10
#define LOWAR 1

int shared_variable[5];
char available = 0;
sem_t mutex;

void* producer(void* arg)
{
	int p, i = 0;

	while(1)
	{
		if(!available)
		{
			sem_wait(&mutex);

			p = rand();
			p = p%(UPPER - LOWAR + 1) + LOWAR;
			printf("Produced: %d\n", p);	
			fflush(stdout);
			shared_variable[i] = p;
			i++;

			if(i >= 5)
			{
				available++;
//				i = 0;
			}

			sem_post(&mutex);
		}
		if(i >= 5)
			return NULL;
	}
}

void* consumer(void* arg)
{
	int c, i = 4;

	while(1)
	{
		if(available)
		{
			sem_wait(&mutex);

			c = shared_variable[i];
			printf("\t\tConsumed: %d\n", c);
			fflush(stdout);
			i--;

			if(i < 0)
			{
				available--;
//				i = 4;
			}

			sem_post(&mutex);
		}
		if(i < 0)
			return NULL;
	}
}

void main()
{
	pthread_t p_thread, c_thread;

	sem_init(&mutex, 0, 1);

	pthread_create(&p_thread, NULL, producer, NULL);
	pthread_create(&c_thread, NULL, consumer, NULL);		

	pthread_join(p_thread, NULL);
	pthread_join(c_thread, NULL); 

	sem_destroy(&mutex); 
}
