#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
int main(int argc, char* argv[]){
	FILE *fp= NULL;
	FILE *in= NULL;
	int tam = 100;
	char *buf = (char*) malloc(sizeof(char)*tam);

	memset(buf, 0, sizeof(char)*tam);
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
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	in = fopen ("Log.log", "w+");
	
	while (1){
		sleep(1);
		fp = popen("top -bn2 | grep 'Cpu' | tail -1", "r");
		fread(buf,100,1, fp);
		
		fwrite(buf, strlen(buf), 1, in);
		
		fflush(in);
		memset(buf, 0, sizeof(char)*tam);
	}
	fclose(in);
	return (0);
}