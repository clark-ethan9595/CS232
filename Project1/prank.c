#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

char * temp_msg;
int temp_sec;
int new_time = 0;
int new_msg = 0;
int enable_int = 0;

void annoying_message(int sig) {

	if (new_msg == 1) {
		printf("%s\n", temp_msg);
	}
	else {
		printf("THIS MESSAGE IS ANNOYING\n");
	}

	if (new_time == 1) {
		alarm(temp_sec);
	}
	else {
		alarm(5);
	}
}

int main(int argc, char *argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "+i") == 0)
		{
			enable_int = 1;
			printf("Processed +i argument\n");
		}

		if (strcmp(argv[i], "-m") == 0)
		{
			temp_msg = argv[i+1];
			new_msg = 1;
		}

		if (strcmp(argv[i], "+t") == 0)
		{
			temp_sec = atoi(argv[i+1]);
			new_time = 1;
		}

	}

	signal(SIGALRM, annoying_message);
	signal(SIGINT, SIG_IGN);
	
	if (new_time == 1) {
		alarm(temp_sec);
	}
	else {
		alarm(5);
	}

	while(1);

}