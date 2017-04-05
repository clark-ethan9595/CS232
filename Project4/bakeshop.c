/*
 * bakeshop.c simulates a bread shop with a baker
 *
 * CS 232 - Project 4
 * Ethan Clark
 * April 4, 2017
 */

// Includes section
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Declare semaphores
sem_t bakerSemaphore;
sem_t customerSemaphore;
sem_t storeSemaphore;

// Declare various global counting variables
int loavesBaked = 0;
int loavesAvailable = 0;
int loavesGiven = 0;
int customersCheckedout = 0;
long threadReadyCheckout;

/*
 * checkoutActions() is the function for thread checkoutThread
 *
 * While the baker has not checked out all 10 customers
 *	If the baker has given out more loaves than he has customers checked out
 *		Grab the customer and baker semaphores
 *		Check ou the customer
 *		Release the customer semaphore
 *		Increment customersCheckedOut by 1
 *		Release the baker semaphore
 */
void* checkoutActions() {

	while (customersCheckedout < 10) {

		if (loavesGiven > customersCheckedout) {

			sem_wait(&customerSemaphore);

			fprintf(stderr, "Customer %ld is waiting to check out.\n\n", threadReadyCheckout);

			sem_wait(&bakerSemaphore);

			// One second delay
			usleep(1000000);

			fprintf(stderr, "Customer %ld paid for the loaf.\n\n", threadReadyCheckout);
			fprintf(stderr, "Baker printed out recipt for customer %ld.\n\n", threadReadyCheckout);
			fprintf(stderr, "Customer %ld just got a recipt!\n\n", threadReadyCheckout);
			customersCheckedout += 1;

			sem_post(&bakerSemaphore);

			sem_post(&customerSemaphore);
		}
	}

	fprintf(stderr, "******All customers have checked out and gotten recipts!******\n\n");
}

/*
 * bakeBreadActions() is the function for thread bakeThread
 *
 * Begin by announcing the bake shop to be open
 * While the loavesBaked is less than 10
 *	Try and grab the baker Semaphore
 * 	Bake a loaf of bread
 *	Increment loavesBaked and loavesAvailable by 1
 * 	Output that loaf number X was made.
 *	Release baker semaphore
 *	Delay
 * Once all 10 loaves have been baked, announce all bread has been baked. 
 */
void* bakeBreadActions() {

	fprintf(stderr, "\n*******Store is open and baker is ready to bake!*********\n\n");
	while (loavesBaked < 10) {

		sem_wait(&bakerSemaphore);

		loavesAvailable += 1;
		loavesBaked += 1;

		fprintf(stderr, "Loaf %d is baked and available for sale.\n\n", loavesBaked);

		sem_post(&bakerSemaphore);

		// One second delay
		usleep(1000000);
	}

	fprintf(stderr, "******All bread has been baked!*******\n\n");

}

/*
 * customerActions(id_num) is the function for all the customer threads
 *
 * Customer tries to get into the store
 * Grab store semaphore
 * Once inside, customer waits for bread to be available.
 * Grab customer sempahore
 * Update loavesAvailable, loavesGiven, and update the thread id for the thread that is ready to checkout
 * Delay
 * Grab customer semaphore
 * Leave the store
 * Release customer semaphore
 * Release store semaphore
 */
void* customerActions(void *id_num) {

	// Convert the void argument back into a long integer
	long id;
	id = (long)id_num;

	fprintf(stderr, "Customer %ld is waiting to get into the store.\n\n", id);

	sem_wait(&storeSemaphore);

	fprintf(stderr, "Customer %ld entered the store.\n\n", id);

	sem_wait(&customerSemaphore);

	while (loavesAvailable == 0) {
		// One second delay
		usleep(1000000);
	}

	fprintf(stderr, "Customer %ld has a loaf of bread.\n\n", id);

	sem_post(&customerSemaphore);

	loavesAvailable -= 1;
	loavesGiven += 1;
	threadReadyCheckout = id;

	// One second delay
	usleep(1000000);

	sem_wait(&customerSemaphore);

	fprintf(stderr, "Customer %ld has left the store.\n\n", id);

	sem_post(&customerSemaphore);
	sem_post(&storeSemaphore);

}

/*
 * main() initializes the three semaphores; creates the baking Thread, checkout Thread, and customer Threads;
 *		and then waits until all threads have been completed before terminating.
 */
 int main() {

 	sem_init(&bakerSemaphore, 0, 1);
 	sem_init(&customerSemaphore, 0, 1);
 	sem_init(&storeSemaphore, 0, 5);

 	// Create two threads: bakeThread and checkoutThread
 	pthread_t bakeThread;
 	pthread_t checkoutThread;

 	// Create an array of 10 threads for the customers
 	pthread_t threads[10];

 	// Declare integer thread return values in case of error
 	int bakerReturnValue;
 	int customerReturnValue;
 	int checkoutReturnValue;


 	bakerReturnValue = pthread_create(&bakeThread, NULL, bakeBreadActions, NULL);

 	// If pthreads couldn't make bakerThread for whatever reason
 	if (bakerReturnValue) {
 		fprintf(stderr, "ERROR; return code from bakeThread pthread_create() is %d\n\n", bakerReturnValue);
 		exit(-1);
 	}

 	checkoutReturnValue = pthread_create(&checkoutThread, NULL, checkoutActions, NULL);

 	// If pthreads couldn't make checkoutThread for whatever reason
 	if (checkoutReturnValue) {
 		fprintf(stderr, "ERROR: return code from checkoutThread pthread_create() is %d\n\n", checkoutReturnValue);
 		exit(-1);
 	}

 	for (long i = 0; i < 10; i++) {

 		// Section to change the priority of the last customer thread to very high
 		/*
 		if (i == 9) {
 			pthread_setschedprio(threads[9], 99);
 		}
 		*/

 		customerReturnValue = pthread_create(&threads[i], NULL, customerActions, (void *)i);

 		// If pthreads couldn't make customer Thread for whatever reason
 		if (customerReturnValue){
       		fprintf(stderr, "ERROR; return code from customerThread pthread_create() is %d\n\n", customerReturnValue);
       		exit(-1);
       	}
 	}

 	pthread_exit(NULL);

 }