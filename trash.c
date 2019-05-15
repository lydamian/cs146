#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

// Deleting all files in the trash folder


int is_regular_file(const char *path);
int isDirectory(const char *path);
char *get_trash();

int main(int argc, char *argv[]){
	printf("Hello, from trash.c\n");
	// local variables
	DIR *d;
	struct dirent *dir;
	char path[200];

	// check  if trash variable defined
	if((get_trash()) == NULL){
		printf("Error, TRASH environment variable not defined\n");
	}

	// check if trash is a valid directory
	if((d = opendir(get_trash())) == NULL){
		printf("ERROR, invalid TRASH environment variable\n");
	}

	while ((dir = readdir(d)) != NULL) {
		if((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0)){
			sprintf(path, "%s/%s", get_trash(), dir->d_name);	
			printf("%s\n", path);
			// checking if directory or regular file remove
			if(isDirectory(dir->d_name)){
				printf("%s is a directory\n", path);
			}
			else if(is_regular_file(dir->d_name)){
				printf("%s is a regular file\n", path);
			}
			else{
				printf("WHAT KIND OF FILE IS THIS????\n");
				exit(1);
			}
		}
	}

	closedir(d);
	return 0;
}


int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

int is_regular_file(const char *path)
{
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
    return S_ISREG(statbuf.st_mode);
}

char *get_trash(){
	return getenv("TRASH");
}
