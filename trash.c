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
int remove_directory(const char *directory);

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
			if(isDirectory(path) > 0){
				printf("%s is a directory\n", path);
				remove_directory(path);
			}
			else if(is_regular_file(path) > 0){
				printf("%s is a regular file\n", path);
				unlink(path);
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
	struct stat sb;
	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		return 1;
	}
	return 0;
}

int is_regular_file(const char *path)
{
	struct stat sb;
	if (stat(path, &sb) == 0 && S_ISREG(sb.st_mode))
	{
		return 1;
	}
	return 0;
}
//  Delete the directories by recursion, files straight away.
int remove_directory(const char *directory){
	//local variables
	DIR *d;
	struct dirent *dir;
	char path[200];

	if((d = opendir(directory)) < 0){
		return -1;
	}

    //for every item in d:
	while((dir = readdir(d)) != NULL){
		sprintf(path, "%s/%s", directory, dir->d_name);

		//    if item is a directory: delDir (item)
		if(isDirectory(path)){
			printf("this is a directory\n");
			remove_directory(path);
		}
		else{
			printf("this is a regular file");
		}
	}

    //rmdir(directory);
	return 1;
}

char *get_trash(){
	return getenv("TRASH");
}
