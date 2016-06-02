#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h> 
#include <fcntl.h>
#include <string>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>
using namespace std;
//first line is the weight of the bag
//output ot file is: item#,item value,item weight
int main(int argc, char *argv[]){
	if(argc < 3){
		printf("datagenerator [number of items] [number of copies]");
		exit(1);
	}
	int filefd = open("tester.txt", O_WRONLY | O_CREAT | O_TRUNC);
	if(filefd < 0){
		perror("Couldn't create file.");
	}
	int values[atoi(argv[1])*atoi(argv[2])];
	int totalvalue = 0;
	int count = 0;
	srand(time(NULL));
	//generating items
	for(int index = 0; index < atoi(argv[1]); index++){
		//generating copies
		srand(time(NULL)+count+totalvalue+rand());
  		int value = rand() % 100 + 1;

		for(int inner = 0; inner < atoi(argv[2]); inner++){
  			totalvalue += value;
  			values[count++] = value;
  		}
	}
	count = 0;
	string result = to_string(totalvalue/2) + "\n";
	for( int counter = 0; counter < atoi(argv[1]); counter++ ){
		for( int inner = 0; inner < atoi(argv[2]); inner++){
			srand(time(NULL)+count+rand());
			result.append(to_string(counter) + "," + to_string(values[count++]) + "," + to_string(rand() % 100 + 1) + "\n");
			
		}
	}
	int size = write(filefd, result.c_str(), result.length());
	if(size < 0){
		perror("Couldn't write to file.");
	}
	close(filefd);
	return 0;
}