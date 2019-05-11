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
const int BUF_LEN = 100;

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

// gets the environment variable every
char *get_every(){
	return getenv("EVERY");
}

int proc_stdin(int m, int n){
	char buf[BUF_LEN];
	int bVal = 1;

	while(bVal){
		if(fgets(buf, BUF_LEN, stdin) == NULL){
			return 1;
		}
		printf("%s", buf);
	}
	return 1;
}

void pnl(){
	printf("\n");
}

int print_n(FILE *in, int n){
	char buf[BUF_LEN];
	for(int i = 0; i < n; i++){
		if(fgets(buf, BUF_LEN, in) == NULL){
			return 0;
		}
		printf("%s",buf);
	}
	return 1;
	
}

int skip_n(FILE *in, int n){
	char buf[BUF_LEN];
	for(int i = 0; i < n; i++){
		if(fgets(buf, BUF_LEN, in) == NULL){
			return 0;
		}
	}
	return 1;
}

// prints m lines out of every n, until EOF is reached
// return values: 1 for EOF, -1 for error
int print_lines(char *filename, int n, int m){
	//local variables
	FILE *in = NULL;
	int bVal = 1;
	int diff = n-m ;
	
	// try opening file
	in = fopen(filename, "r");
	if(in == NULL){
		return -1;
	}
	
	// print m our of n
	printf("%s exists\n", filename);
	while(bVal){
		if(print_n(in, m) == 0){
			return 1;
			bVal = 0;
		}
		if(skip_n(in, diff) == 0){
			return 1;
			bVal = 0;
		}
	}
	return 1;
}

int main(int argc, char *argv[], char *envp[]){
	printf("Hello World, every.c here...\n");
	// local variables
	int is_option = 0;
	int curr_position = 0;
	int buf_len = 100;
	char buf[buf_len];

	// handle options
	if(process_options(argv, argc) == 1){ // there are options
		printf("The current options are: %d, %d\n", N, M);	
		if(!is_valid_options(M,N)){
			printf("Invalid Options\n");
			exit(1);
		}
		is_option = 1;
	}
	else if(get_every() != NULL){ // check is every env var is specified
		printf("EVERY is %s\n", get_every());	
		char *every_args[3];
		every_args[0] = "";
		every_args[1] = get_every();
		every_args[2] = NULL;

		if(process_options(every_args, 2) == 1){ // there are options
			printf("The current options are: %d, %d\n", N, M);	
			if(!is_valid_options(M,N)){
				printf("Invalid Options\n");
				exit(1);
			}
		}
	}
	else{ // default option settings
		printf("Default options: m = %d, n = %d\n", M, N);
		if(!is_valid_options(M,N)){
			printf("Invalid default Options, fix the code, stupid programmer\n");
			exit(1);
		}
	}

	// get the list of files
	printf(" ---- printing files ---- \n");

	pnl();

	// handle each file appropriately
	if(argv[is_option+1] != NULL){
		printf("handling files...\n");
		for(int i = is_option+1; argv[i] != NULL; i++){
			printf("%s ", argv[i]);
			if(print_lines(argv[i], N, M) < 0){
				printf("Error, reading from file, mabye doesnt exist?\n");
				exit(1);
			}
		}
	}
	else{ // process from stdin
		printf("reading from stdin\n");
		proc_stdin(M, N);
	}
	return 0;
}
