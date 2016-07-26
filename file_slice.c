#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#define PERMS 0777
#define DEFNAME "temp"
#define DEFSIZE 256	


/******************** option *********************
 -n : file name if not input default value use
 -s : make file size option if not input default value use
 -o : [required] open file name
 -d : story directory option if ignore directory make directory, if not input
      excution directory
***************************************************/
void print_help();
int dir_make(char* m_dir);
int file_slice(char* m_in, char* m_out, char* m_dir, int m_size);

static  int check_dir = 0;
static char* dir = NULL;
int main(int argc, char **argv){
	int i, ch, size;
	char *in = NULL, *out = DEFNAME;
	
	size = DEFSIZE;

	if(argc < 3 || argc > 9 || argc%2 == 0){
		print_help();
		exit(1);
	}
	while((ch = getopt(argc, argv, "n:s:o:d:")) != -1){
		switch(ch){
		case 'n':
			out = optarg;
			break;
		case 's':
			size = atoi(optarg);
			break;
		case 'o':
			in = optarg;
			break;
		case 'd':
			check_dir = 1;
			dir = optarg;
			break;
		default:
			print_help();
		}
	}

	if(!in)
		print_help();

	if(file_slice(in, out, dir, size) == 0)
		fprintf(stdout, "Complete...\n");

	return 0;
}

void print_help(){
	fprintf(stdout, "Usage: fslice [OPTION]... FILE...\n");
	fprintf(stdout, "OPTION\n");
	fprintf(stdout, " -o\tDestination filename\n");
	fprintf(stdout, " -n\tOutput file name\n");
	fprintf(stdout, " -s\tSlice file size\n");
	fprintf(stdout, " -d\tstory directory\n");
	exit(1);
}
int dir_make(char* m_dir){
	int retval;
	int err;
	retval = mkdir(m_dir, 0777);
	if(retval == 0)
		return 0;
	else if(retval == -1){
		if(errno == EEXIST)
			return 0;
		else
			return 1;
	}	
}
int file_slice(char* m_in, char* m_out, char* m_dir, int m_size){
	int in_file, out_file;
	int i = 0;
	char* outname = (char *)malloc((strlen(m_out)+5));
	char* buffer = (char *)malloc(m_size);
	ssize_t n1, w1;
	if(m_dir){
		if(dir_make(m_dir) == 1){
			fprintf(stderr, "directory make error!\n");
			return 1;
		}
	}
	if((in_file = open(m_in, O_RDONLY)) == -1){
		fprintf(stderr, "file open error!\n");
		free(outname);
		free(buffer);
		return 1;
	}
	while((n1 = read(in_file, buffer, m_size)) > 0){
		if(check_dir == 0)
			sprintf(outname, "%s_%d", m_out, i++);
		else
			sprintf(outname, "./%s/%s_%d", m_dir, m_out, i++);

		printf("Result File name : %s\n", outname);
		if((out_file = open(outname, O_WRONLY|O_CREAT|O_TRUNC, PERMS)) == -1){
			fprintf(stderr, "fileopen error!\n");
			free(outname);
			free(buffer);
			return 1;
		}
		if(write(out_file, buffer, n1) < n1){
			fprintf(stderr, "filewrite error!\n");
			free(outname);
			free(buffer);
			return 1;
		}
		close(out_file);
	}
	close(in_file);
	free(outname);
	free(buffer);
	return 0;
}
