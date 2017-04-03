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
#include <unistd.h>

sem_t bakerSemaphore;
sem_t customerSemaphore;
sem_t storeSemaphore;
int loavesBaked = 0;
int loavesAvailable = 0;

void checkoutActions(long id_num) {

	fprintf(stderr, "Customer %ld is waiting to check out.\n", id_num);
	sem_wait(&bakerSemaphore);
	usleep(1000000);
	fprintf(stderr, "Customer %ld just checked out!\n", id_num);
	sem_post(&bakerSemaphore);

}

void* bakeBreadActions() {

	fprintf(stderr, "Store is open and baker is ready to bake!\n");
	while (loavesBaked < 10) {
		sem_wait(&bakerSemaphore);
		loavesAvailable += 1;
		loavesBaked += 1;
		fprintf(stderr, "Baker just baked loaf number %d.\n", loavesBaked);
		sem_post(&bakerSemaphore);
		usleep(1000000);
	}

	fprintf(stderr, "All bread has been baked!\n");

}

void* customerActions(void *id_num) {

	long id;
	id = (long)id_num;

	fprintf(stderr, "Customer %ld is waiting to get into the store.\n", id);
	sem_wait(&storeSemaphore);
	fprintf(stderr, "Customer %ld got into the store.\n", id);

	sem_wait(&customerSemaphore);
	while (loavesAvailable == 0) {
		usleep(1000000);
	}
	fprintf(stderr, "Customer %ld has a loaf of bread.\n", id);
	loavesAvailable -= 1;
	usleep(1000000);

	checkoutActions(id);

	fprintf(stderr, "Customer %ld has left the store.\n", id);
	sem_post(&customerSemaphore);
	sem_post(&storeSemaphore);

}

 int main(int argc, char *argv[]) {

 	sem_init(&bakerSemaphore, 0, 1);
 	sem_init(&customerSemaphore, 0, 1);
 	sem_init(&storeSemaphore, 0, 5);

 	pthread_t threads[10];
 	int bakerReturnValue;
 	int customerReturnValue;

 	pthread_t bakerThread;
 	bakerReturnValue = pthread_create(&bakerThread, NULL, bakeBreadActions, NULL);

 	if (bakerReturnValue) {
 		fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", bakerReturnValue);
 		exit(-1);
 	}

 	for (long i = 0; i < 10; i++) {
 		customerReturnValue = pthread_create(&threads[i], NULL, customerActions, (void *)i);
 		if (customerReturnValue){
       		fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", customerReturnValue);
       		exit(-1);
       	}
 	}

 	fprintf(stderr, "Bakery is now closed for the evening!");

 	pthread_exit(NULL);

 }