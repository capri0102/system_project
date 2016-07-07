#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define PERMS 0644

int main(int argc, char** argv){
	int filedes, file_len, i;
	char *buffer;
	char *m_filename = "temp";
	if(argc > 4 || argc != 2){
		printf("Usage: [File length] [FileName]\n");
		exit(1);
	}
	file_len = atoi(argv[1]);
	buffer = (char *)malloc(file_len);	
	if(argc == 3){
		if((filedes = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, PERMS)) == -1){
			fprintf(stderr, "Couldn't create %s\n", argv[1]);
			exit(1);
		}
	}
	else{
		if((filedes = open(m_filename, O_WRONLY|O_CREAT|O_TRUNC, PERMS)) == -1){
			fprintf(stderr, "Couldn't create %s\n", m_filename);
			exit(1);
		}
	}
	for(i=0;i<file_len;i++){
		buffer[i] = (rand() %10)+97;
	}
	if(write(filedes, buffer, strlen(buffer)) < strlen(buffer))
		fprintf(stderr, "Write ERROR!\n");
	free(buffer);
	close(filedes);
	return 0;
}
