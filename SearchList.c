#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// Program: searches an array of integers to find a given integer.
// Returns: prints -1 if not found, else prints the index of the found integer 

// The program should print out the array index where the given integer is found, or it
// should print -1 to indicate that the integer was not found in the array. Array indices
// begin at 0. Your program will accept two arguments at the command line, 1) the
// name of the array file which contains the array, and 2) the integer to search for in
// the array. Give your executable the name MySearch. The following is an example
// of how your code will work when it is called with an array file called arr_file.txt which
// contains the following array, 5 6 7 8 9. 

// In this example, we assume that the linux prompt is the symbol ‘$’.

// must run in the following way:
// gcc this_file's_name.c -o MySearch
// ./MySearch file_name_containing_array.txt number_to_search



void MySearch(int arrayStart, int arrayEnd, int searchKey, int * array, int * fd, int *counter){

    if (array == NULL ) {
    	perror("empty file!");
	    exit(0);
    }

	int status1, status2;
	pid_t leftHalf, rightHalf;
    // leftHalf = fork();

    if(arrayStart == arrayEnd){
    	if(*(array + arrayEnd) == searchKey){
    	//if (array[arrayEnd] == searchKey){
      		printf("%d\n", arrayEnd ); 
      		//*counter++;
    		close(fd[0]);
    		write(fd[1], &counter, sizeof(counter));  	
    	}
    	exit(0);
  	} 

  	else {
  		leftHalf = fork();
	  	if( leftHalf < 0 ){
	    	perror("fork error");
	    	exit(EXIT_FAILURE);
	    }

	    else if (leftHalf == 0){
	    	//printf("%s\n", "LEFT" );
	     	int leftHalfSize = (int)ceil((arrayStart+arrayEnd)/2); // get the size of left half of array
			// MySearch(arrayStart, leftHalfSize, searchKey, array, fd);
			// wait(NULL);
			// exit(0);
			MySearch(arrayStart, leftHalfSize, searchKey, array, fd, counter); // replace lefthalfsize with arrayStart+arrayEnd)/2 if ceil error
			exit(0);
		} 
		else if (leftHalf > 0) { 
			rightHalf = fork();
			if( rightHalf < 0 ){
	    		perror("fork error");
	    		exit(EXIT_FAILURE);
	    	}
			if (rightHalf == 0) {
				//printf("%s\n", "RIGHT" );
			    int rightHalfSize = (int)floor((arrayStart+arrayEnd)/2) + 1;
				// MySearch(rightHalfSize, arrayEnd, searchKey, array, fd);
				// wait(NULL);
				// exit(0);
				MySearch(rightHalfSize, arrayEnd, searchKey, array, fd, counter); // replace righthalfsize with (arrayStart+arrayEnd)/2 + 1 if floor error
				exit(0);
		    }
		    // this else may be unnecessary
		    else {
		    	waitpid(leftHalf, &status1, 0);
			    waitpid(rightHalf, &status2, 0);
			    if(WEXITSTATUS(status1)==0 || WEXITSTATUS(status2) == 0)
			    	exit(0);
				else{
			   		exit(-1);
				}
			}
		}
	}
}


int main(int argc, char * argv[]){
	char * fileName = argv[1];
	char * key = argv[2];

	char line[80]; // first line of file
	int searchKey = atoi(key); // number to look for in the array
	FILE *fp = fopen(fileName, "r");
	FILE *fp2 = fopen(fileName, "r");
	FILE *fp3 = fopen(fileName, "r");
	int arraySize = 0; // number of elements in file txt

	// makes sure it is ran with name of function + file name + search key
	if (argc != 3){
		perror ("Too (many/few) arguments");
		exit(-1);
	}

	// // double checks if file is valid
	if (fp == NULL) {
		perror ("Error opening file");
		exit(1);
	}

	// // reads file array into char array
	fgets(line, 20, fp);

	// gets the amount of integers (elements) in array file
	int c;
    for( ;; )
    {
        c = fgetc( fp2 );
        if( c == EOF || c == '\n' )
            break;
        if (c == ' ')
        	++arraySize;
    }
    arraySize++;

    // file should only have 10 elements max
    if (arraySize > 10){
    	perror ("Over 10 elements (not allowed)");
		exit(1);
    }

	int array[arraySize]; // file's array to search in

	// turns each element into a int and puts it into the array
	for (int i = 0; i < arraySize; i++){
		if (fscanf(fp3, "%d ", &array[i]) != 1){
			printf("array file is not in correct format\n");
				return 0;
		}
	}

    fclose(fp);
    fclose(fp2);
    fclose(fp3);

    int fd[2];
	pipe(fd);
	int found[arraySize]; // keeps track of whether indexes were not found
	int counter = 0; // index incrementer for found

    if (fork() == 0)
		MySearch(0, arraySize-1, searchKey, array, fd, &counter);
	else{
		wait(NULL);
	}

	close(fd[1]);
    read(fd[0], &counter, sizeof(counter));  	
	if (counter == 0){
		printf("%d\n", -1 );
	}
   	
	return 0;
}
