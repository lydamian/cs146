#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int main(int argc,char * argv[]){
	printf("Hello from a c program");
	char *filename = argv[1];
	char buf[100];
	FILE *in  = fopen(filename, "w");
	for(int i = 0; i < 50; i++){
		sprintf(buf, "line: %d This is some random text...\n", i);
		fputs(buf, in);
	}
	fclose(in);
}
