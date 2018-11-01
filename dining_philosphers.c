#include <pthread.h>  
#include <semaphore.h>  
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

enum States { THINKING, HUNGRY, EATING };  

sem_t chopsticks[5];
enum States state[5];
enum States prev_state[5];
char names[5][20] = {"Aristole", "Pythogorus", "Archimedes", "Plato", "Socrates"};
clock_t t[5];

void* thread(void* args)
{ 
	int *n = (int*)args;
	state[*n] = THINKING;	
	t[*n] = clock();
	printf("%s(%ld): THINKING\n", names[*n], t[*n]);
	sleep(1);

	while(1)
	{

		t[*n] = clock();
		printf("%s(%ld): HUNGRY\n", names[*n], t[*n]);
		{ 
			if((*n+1)%5>*n)
			{ 
				sem_wait(&chopsticks[(*n+1)%5]);
				sem_wait(&chopsticks[(*n)%5]);
			}
			else
			{ 
				sem_wait(&chopsticks[(*n)%5]);
				sem_wait(&chopsticks[(*n+1)%5]);
			}

			state[*n] = EATING;
			t[*n] = clock();
			printf("%s(%ld): EATING\n", names[*n], t[*n]);  
			sleep(1);

			sem_post(&chopsticks[(*n+1)%5]);
			sem_post(&chopsticks[*n]);

			state[*n] = THINKING;
			t[*n] = clock();
			printf("%s(%ld): THINKING\n", names[*n], t[*n]);  
			sleep(1);

		}
	}
	return NULL;
}

int main()
{
	pthread_t philosphers[5];
	int i, arr[] = {0, 1, 2, 3, 4};

	for(i = 0;i < 5;i++)
		sem_init(&chopsticks[i], 0, 1);

	for(i = 0;i < 5;i++)
		pthread_create(&philosphers[i], NULL, thread, &arr[i]);
	for(i = 0;i < 5;i++)
		pthread_join(philosphers[i], NULL);

	for(i = 0;i < 5;i++)
		sem_destroy(&chopsticks[i]);

	return 0;
}
