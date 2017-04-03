/*
 * bakeshop.c simulates a bread shop with a baker
 *
 * CS 232 - Project 4
 * Ethan Clark
 * March 27, 2017
 */

#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

sem_t bakingSemaphore;
sem_t customerSemaphore;
sem_t storeSemaphore;
int loavesBaked = 0;
int loavesAvailable = 0;

void *PrintHello(void *threadid)
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   pthread_exit(NULL);
}

void checkoutActions() {

	fprintf(stderr, "Customer %d is waiting to check out...", pthread_self());
	sem_wait(&bakerSemaphore);
	usleep(1);
	fprintf(stderr, "Customer %d just checked out!", pthread_self());
	sem_post(&bakerSemaphore);

}

void bakeBreadActions() {

	fprintf(stderr, "Store is open and baker is ready to bake!");
	while (loavesBaked < 11) {
		sem_wait(&bakerSemaphore);
		loavesAvailable += 1;
		loavesBaked += 1;
		fprintf(stderr, "Baker just baked a loaf of bread...");
		sem_post(&bakerSemaphore);
		usleep(1);
	}

}

void customerActions() {

	fprintf(stderr, "Customer %d is waiting to get into the store...", pthread_self());
	sem_wait(&storeSemaphore);
	fprintf(stderr, "Customer %d got into the store...", pthread_self());

}

 int main(int argc, char *argv[]) {

 	sem_init(&bakerSemaphore, 0, 1);
 	sem_init(&customerSemaphore, 0, 1);
 	sem_init(&storeSemaphore, 0, 5);

 	pthread_t threads[10];
 	int bakerReturnValue;
 	int customerReturnValue;

 	pthread_t bakerThread;
 	bakerReturnValue = pthread_create(&bakerThread, NULL, bakeBreadActions, (void *));

 	if (bakerReturnValue) {
 		fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", bakerReturnValue);
 		exit(-1);
 	}

 	for (int i = 0; i < 10; i++) {
 		customerReturnValue = pthread_create(&threads[i], NULL, PrintHello, (void *)i);
 		if (customerReturnValue){
       		fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", customerReturnValue);
       		exit(-1);
       	}
 	}

 	pthread_exit(NULL);

 }