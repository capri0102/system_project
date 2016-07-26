#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ftw.h>
#include <errno.h>

#define PERMS 0777
#define DEFNAME "TEMP_ADD"


/******************** option *********************
 -n : file name if not input default value use
 -s : make file size option if not input default value use
 -o : [required] open file name
 -d : story directory option if ignore directory make directory, if not input
      excution directory
***************************************************/
void print_help();
int file_add(char* m_in, char* m_out, char* m_dir);

static int check_del = 0;
static char* dir = NULL;
int main(int argc, char **argv){
	int i, ch;
	char *in = NULL, *out = DEFNAME;
	
	if(argc < 3 || argc > 8){
		print_help();
		exit(1);
	}
	while((ch = getopt(argc, argv, "n:o:d:x")) != -1){
		switch(ch){
		case 'n':
			out = optarg;
			break;
		case 'x':
			check_del = 1;
			break;
		case 'o':
			in = optarg;
			break;
		case 'd':
			dir = optarg;
			break;
		default:
			print_help();
		}
	}

	if(!in)
		print_help();

	if(file_add(in, out, dir) == 0){
		printf("Result File : %s\n", out);
		fprintf(stdout, "Complete...\n");
	}
	return 0;
}

void print_help(){
	fprintf(stdout, "Usage: fslice [OPTION]... FILE...\n");
	fprintf(stdout, "OPTION\n");
	fprintf(stdout, " -o\tDestination filename\n");
	fprintf(stdout, " -n\tOutput file name\n");
	fprintf(stdout, " -x\tDelete original file\n");
	fprintf(stdout, " -d\tstory directory\n");
	exit(1);
}
int file_add(char* m_in, char* m_out, char* m_dir){
	int in_file, out_file;
	int i = 0;
	char buffer[512];
	char* inname = (char *)malloc((strlen(m_out)+5));
	ssize_t n1, w1;
	if((in_file = open(m_out,O_WRONLY|O_CREAT|O_TRUNC, PERMS)) == -1){
		fprintf(stderr, "file open error!\n");
		free(inname);
		return 1;
	}
	if(m_dir)
		sprintf(inname, "./%s/%s_%d", m_dir, m_in, i++);
	else
		sprintf(inname, "%s_%d", m_in, i++);
	while((out_file = open(inname, O_RDONLY)) != -1){
		printf("Read file : %s\n", inname);
		while((n1 = read(out_file, buffer, 512))> 0){
			if(write(in_file, buffer, n1) < n1){
				fprintf(stderr, "file write error!\n");
				free(inname);
				return 1;
			}
		}
		close(out_file);
		if(check_del != 0){
			if(remove(inname) == -1){
				fprintf(stderr, "file remove error!\n");
				free(inname);
				return 1;
			}
		}	
		if(m_dir)
			sprintf(inname, "./%s/%s_%d", m_dir, m_in, i++);
		else
			sprintf(inname, "%s_%d", m_in, i++);
	}
	close(in_file);
	free(inname);
	return 0;
}
