#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

void pl();
char *get_trash();
int are_options(char *argv[]);
int is_option(char *arg); 

int main(){
	printf("Hello from srm.c\n");
	//local variables
	char *trash;
	struct dirent *de;
	DIR *dir;
	int is_option;

	// check  if trash variable defined
	if((trash = get_trash()) == NULL){
		printf("Error, TRASH environment variable not defined\n");
	}

	// check if trash is a valid directory
	if((dir = opendir(trash)) == NULL){
		printf("ERROR, invalid TRASH environment variable\n");
	}

	// check if there are options

	

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

// checks if at least one option exists 
int are_options(char *argv[]){

}

// checks if the given char array is an option
int is_option(char *arg){

}
