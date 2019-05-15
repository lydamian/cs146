#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

void pl();
char *get_trash();
int are_options(char *argv[]);
int is_option(char *arg); 
int safe_rm(char *file);
int regular_rm(char *file);

// GLOBALS
char *TRASH;

int main(int argc, char *argv[]){
	printf("Hello from srm.c\n");
	//local variables
	struct dirent *de;
	DIR *dir;
	int option; // boolean value

	// check  if trash variable defined
	if((TRASH = get_trash()) == NULL){
		printf("Error, TRASH environment variable not defined\n");
	}

	// check if trash is a valid directory
	if((dir = opendir(TRASH)) == NULL){
		printf("ERROR, invalid TRASH environment variable\n");
	}

	for(int i = 1; argv[i] != NULL; i++){
		if(!is_option(argv[i])){
			if(safe_rm(argv[i]) < 0){
				printf("Error, safe removing file: %s\n", argv[i]);
				exit(1);
			}
		}
	}
	
	// closing the directory
	closedir(dir);

	return 0;
}

void pl(){
	printf("\n");
}

char *get_trash(){
	return getenv("TRASH");
}


/* NOTE
if you use "global trash directory", then
   remember that "srm" must work even if you're srm'ing a file that is
      not on the same mounted file 
*/
int safe_rm(char *file){
	printf("safe removing %s\n", file);
	char *newpath = strcat(get_trash(), "/");
	newpath = strcat(newpath, file);
	printf("the new path is: %s\n", newpath);
	if(rename(file, newpath) < 0){
		return -1;
	}
	return 0;
}

int regular_rm(char *file){
	printf("regular removing %s\n", file);
}

// checks if at least one option exists 
int are_options(char *argv[]){
	for(int i = 1; argv[i] != NULL; i++){
		if(is_option(argv[i])){
			return 1;
		}
	}
	return 0;
}

// checks if the given char array is an option
int is_option(char *arg){
	if(arg[0] == '-'){
		return 1;
	}
	return 0;
}
