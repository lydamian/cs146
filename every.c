#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

/* Description:
	
	functions needed: getenv, fopen, fread...
*/

/*	GLOBALS	  */
int M = 1;
int N = 1;


const char *DEFAULT_OPTIONS = "-1,1";

int raise_number(int power, int base)
{
    int value = 1;
    while(power != 0)
    {
        value = value * base;
        power--;
    }
	return value;
}

// checks if the given string is a number
int is_number(const char *str){
	for(int i = 0; str[i] != '\0'; i++){
		if(!isdigit(str[i])){
			return 0;
		}
	}
	return 1;
}

// return valid arguments from an array of strings
int process_options(char *argv[], const int argc){
	char delim[2] = ",";

	if(argc != 1){
		// follows the follwing ebnf: -M,N
		if(argv[1][0] == '-') {
			// parse options
			if(strchr(argv[1], ',')	== NULL){ // only n
				if(is_number((1+argv[1]))){
					char *ptr = ++argv[1];
					N = atoi(ptr);
					M = 1;
					printf("my n is: %d, my M is: %d\n", N, M);
				}
				else{
					printf("Invalid option, not a number\n");
					exit(1);
				}
				return 1;
			}
			else{ // also m
				char *num1 = strtok(++argv[1], delim);
				if(is_number(num1)){
					N = atoi(num1);
				}
				else{
					printf("Invalid option, not a number\n");
					exit(1);
				}
				char *num2 = strtok(NULL, delim);
				if(is_number(num2)){
					M = atoi(num2);
				}
				else{
					printf("Invalid option, not a number\n");
					exit(1);
				}
				return 1;
			}
		}
	}
	return 0;
}

int is_valid_options(int m, int n){
	if(m > 0 && n > 0 && m <= n){
		return 1;	
	}
	return 0;
}

// Check whether the every environment variable is specified
int is_every(){
	return -1;
}

// get file arguments
char **get_files(char *argv[]){
	return NULL;
}

int proc_stdin(char *options){
	return -1;
}

int main(int argc, char *argv[], char *envp[]){
	printf("Hello World, every.c here...\n");
	// local variables

	// check no args given
	if(argc == 1){ // process_stdin
		return 0;
	}

	// handle options
	if(process_options(argv, argc) == 1){ // there are options
		printf("The current options are: %d, %d\n", N, M);	
	}
	else if(is_every()){ // check is every env var is specified

	}
	else{ // default option settings

	}

	// handle each file appropriately
	if(1){
		printf("handling files...\n");
	}
	else if(0){ // process from stdin
		printf("reading from stdin\n");
	}
	return 0;
}
