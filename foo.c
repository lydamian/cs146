#include <stdio.h>

int main(int argc, char *argv[]){
	printf("Hi i am foo\n");
	for(int i = 0; i < argc; i++){
		printf("%s\n", argv[i]);
	}
}
