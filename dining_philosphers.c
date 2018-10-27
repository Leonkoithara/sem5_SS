#include <pthread.h>  
#include <semaphore.h>  
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
 
enum States { THINKING, HUNGRY, EATING };  
 
sem_t chopsticks[5];
enum States state[5];
enum States prev_state[5];
char *names[] = {"Aristole", "Pythogorus", "Archimedes", "Plato", "Socrates"};

void* thread(void* args)
{ 

	int p;
	int *n = args;
	char *name = names[*n];
	state[*n] = THINKING;	

	while(1)
	{ 
		p = rand()%5;
		if(p == 0)
			state[*n] = HUNGRY;	

		if(state[*n] == HUNGRY)
		{  
			sem_wait(&chopsticks[(*n+1)%5]);
			sem_wait(&chopsticks[*n]);
 
			state[*n] = EATING;
			sleep(100);

			sem_post(&chopsticks[(*n+1)%5]);
			sem_post(&chopsticks[*n]);

			state[*n] = THINKING;
		}
	}
}

int if_change()
{ 
	int i;

	for(i = 0;i < 5;i++)
	{ 
		if(prev_state[i] != state[i])
			return 1;
	}
	for(;i < 5;i++)
		prev_state[i] == state[i];

	return 0;
}
 
void main()
{
	pthread_t philosphers[5];
	int i;

	for(i = 0;i < 5;i++)
		sem_init(&chopsticks[i], 0, 1);

	for(i = 0;i < 5;i++) 
		pthread_create(&philosphers[i], NULL, thread, &i);

	while(1)
	{ 
		if(if_change())
		{ 
			for(i = 0;i < 5;i++)
				printf("%s : %d\n", names[i], state[i]);
		}
	}
}
