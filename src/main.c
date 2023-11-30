#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdbool.h>

int main(int argc, char** argv){

	bool verboseFlag = false;
	
	int c;
	while((c = getopt(argc, argv, "v")) != -1){
		switch(c){
			case 'v':
				verboseFlag = true;
				break;
			default:
				break;
		}
	}
	if(verboseFlag)
		printf("verbose...\n");
		
	printf("argumento sin -: %s\n", argv[optind]);
	return EXIT_SUCCESS;
}
