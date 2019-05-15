#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
/*
 *	Description: unremove all the files/directories in the trash
 *	and put them into the current directory
 * 
 */

void pl();
char *get_trash();
int are_options(char *argv[]);
int is_option(char *arg); 
int safe_rm(char *file);
int regular_rm(char *file);
int unrm(char *curr_dir);
int naming_collision(char *filename);

// GLOBALS
char *TRASH;

int main(int argc, char *argv[]){
	printf("Hello from unrm.c\n");
	//local variables
	DIR *dir;

	// check  if trash variable defined
	if((TRASH = get_trash()) == NULL){
		printf("Error, TRASH environment variable not defined\n");
	}

	// check if trash is a valid directory
	if((dir = opendir(TRASH)) == NULL){
		printf("ERROR, invalid TRASH environment variable\n");
	}

	// mv all the files in the trash to the current directory
	// handle the case of overwrriting someone else's files
	unrm(".");
	
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

// checks if the given char array is an option
int is_option(char *arg){
	if(arg[0] == '-'){
		return 1;
	}
	return 0;
}

int unrm(char *curr_path){
	DIR *dir;
	struct dirent *p;;
	char response;
	char *temp = strcat(TRASH, "/");

	// opening directory
	dir = opendir(TRASH);
	if(!dir){
		printf("error, opening directory\n");
		exit(1);
	}

	// iterating through all files int the directory
	while((p = readdir(dir)) != NULL){
		if((strcmp(p->d_name, ".") != 0) && (strcmp(p->d_name, "..") != 0)){
			char *oldpath = strcat(temp, p->d_name);		
			if(naming_collision(p->d_name)){
				printf("File '%s' already exists in current directory overwrite? y/n\n", p->d_name);
				scanf("%c", &response);
				if(response == 'y'){
					printf("overwritting\n");		
					if(rename(oldpath, p->d_name) < 0){
						printf("Error unremoving\n");
						return -1;
					}
				}
			}
			else{
				printf("there is no naming collision\n");
				printf("%s \n", p->d_name);
				if(rename(oldpath, p->d_name) < 0){
					printf("error removing\n");
					return -1;
				}
			}
		}
	}

	closedir(dir);
	return 1;
}

int naming_collision(char *filename){
	if(access(filename, F_OK) == 0){
		return 1;
	}
	return 0;
}
