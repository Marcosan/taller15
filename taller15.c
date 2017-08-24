#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
int main(int argc, char* argv[]){
	FILE *fp= NULL;
	char *buf = malloc(sizeof(char));
	pid_t process_id = 0;
	pid_t sid = 0;

	process_id = fork();
	if (process_id < 0){
		printf("Fork fallo\n");
		exit(1);
	}
	if (process_id > 0){
		printf("ID del hijo: %d \n", process_id);
		exit(0);
	}
	umask(0);
	sid = setsid();
	if(sid < 0){
		exit(1);
	}
	
	return (0);
}