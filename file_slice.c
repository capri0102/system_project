#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define PERMS 0644
#define DEFAULTNAME	TEMP
#define DEFAULTSIZE	10

/******************** option *********************
 -n : file name if not input default value use
 -s : make file size option if not input default value use
 -o : [required] open file name
 -d : story directory option if ignore directory make directory, if not input
      excution directory
***************************************************/

void print_help();
void file_silce(char* infile, char* outfile, int size, char* directory);
int main(int argc, char **argv){
	int option[4] = {0};	// 0 : -o, 1 : -n, 2 : -s, 3 : -d
	int i;
	char s_option[4][100] = {0};
	printf("argc : %d\n", argc);
	if(argc < 3 || argc > 9 || argc%2 == 0){
		print_help();
		exit(1);
	}
	for(i=1;i<argc;i++){
		printf("argv[%d] : %s\n", i, argv[i]);
		if(strcmp(argv[i], "-o") == 0)		option[0] = i++;
		else if(strcmp(argv[i], "-n") == 0)	option[1] = i++;
		else if(strcmp(argv[i], "-s") == 0)	option[2] = i++;
		else if(strcmp(argv[i], "-d") == 0)	option[3] = i++;
		else{
			print_help();
			exit(1);
		}
	}
	if(option[0] == 0){
		print_help();
		exit(1);
	}

	if(option[1] != 0){
		if(option[2] != 0){
			if(option[3] != 0){
				file_slice(argv[option[0]], argv[option[1]], argv[option[2]], argv[option[3]]);	
			}
			else{
				
				file_slice(argv[option[0]], argv[option[1]], argv[option[2]], NULL);	
			}
		}
		else{
			if(option[3] != 0){
				file_slice(argv[option[0]], argv[option[1]], 0, argv[option[3]]);
			}
			else{
				file_slice(argv[option[0]], argv[option[1]], 0, NULL);	
			}
		}
	}
	else{
		if(option[2] != 0){
			if(option[3] != 0){
			}
			else{
			}
		}
		else{
			if(option[3] != 0){
			}
			else{
			}
		}
	}	
	
	return 0;
}

void print_help(){
	fprintf(stdout, "Usage: fslice [OPTION]... FILE...\n");
	fprintf(stdout, "OPTION\n");
	fprintf(stdout, " -o\tDestination filename\n");
	fprintf(stdout, " -n\tOutput file name\n");
	fprintf(stdout, " -s\tSlice file size\n");
	fprintf(stdout, " -d\tstory directory\n");
}

void file_silce(char* infile, char* outfile, int size, char* directory){
}
