#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define PERMS 0644
#define DEFNAME "temp"
#define DEFSIZE 256	

struct f_slice{
	char *m_in;
	char *m_out;
	char *m_dir;
	int m_size;
};


/******************** option *********************
 -n : file name if not input default value use
 -s : make file size option if not input default value use
 -o : [required] open file name
 -d : story directory option if ignore directory make directory, if not input
      excution directory
***************************************************/

void print_help();
int file_silce(struct f_slice* m_file);
int main(int argc, char **argv){
	int i, ch;
	struct f_slice f_s;
	f_s.m_size = DEFSIZE;
	strcpy(f_s.m_out, DEFNAME);
	if(argc < 3 || argc > 9 || argc%2 == 0){
		print_help();
		exit(1);
	}
	while((ch = getopt(argc, argv, "n:s:o:d:")) != -1){
		switch(ch){
		case 'n':
			strcpy(f_s.m_out, optarg);
			break;
		case 's':
			f_s.m_size = atoi(optarg);
			break;
		case 'o':
			strcpy(f_s.m_in, optarg);
			break;
		case 'd':
			strcpy(f_s.m_dir, optarg);
			break;
		default:
			print_help();
		}
	}
	if(strlen(f_s.m_in) < 1)
		print_help();

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

int file_silce(struct f_slice* m_file){
	int in_file, out_file;
	int i;
	if((in_file = open(*m_file->m_in, O_RDONLY)) == -1){
		fprintf(stderr, "file open error!\n");
		return 1;
	}

	if((out_file = open(*m_file->m_out, O_WRONLY|O_CREAT|O_TRUNC)) == -1){
		fprintf(stderr, "fileopen error!\n");
		return 1;
	}

	
	return 0;
}
