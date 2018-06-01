#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// Prints the numbers from 1-100, according to the following rules:
// For multiples of 3: print Retail
// For multiples of 5: print Equation
// For multiples of BOTH 3 & 5: print RetailEquation
// For any other number: print the number
void applepie (){ 
	for (int i = 1; i < 101; i++){
		if (i % 3 == 0 && i % 5 == 0)
			printf("%s %d\n", "ApplePie", i);
		else if (i % 3 == 0)
			printf("%s %d\n", "Apple", i);
		else if (i % 5 == 0)
			printf("%s %d\n", "Pie", i );
		else
			printf("%d\n", i );
	}
}


void removeDuplicates ( char *originalList, char *listToCheckAgainst){
	size_t originalListSize = sizeof(originalList) / sizeof(originalList[0]);
	size_t listToCheckAgainstSize = sizeof(listToCheckAgainst) / sizeof(listToCheckAgainst[0]);

	//char newList[originalListSize];
	//printf("%lu\n", sizeof(originalList) / sizeof(originalList[0])  );
	//printf("%zu\n", originalListSize);

	char *newList = NULL;
	
	char *list1 = NULL;
	char *list2 = NULL;
	for (list1 = originalList; *list1 != '\0'; list1++) {
		for (list2 = listToCheckAgainst; *list2 != '\0'; list2++) {
			if (list1[0] == list2[0]){
				break;	
			}
			else if (list2 + 1 == '\0'){
				printf("%c\n", list1[0] );
				// newList++;
				// newList = &list1[0];	
				// // newList++;	
			}
		}
	}

	//newList[0] = 'z';
	//strcpy(originalList, newList);
	//printf("%s\n", originalList );
	printf("%s\n", newList);
}



int main(){


	applepie();
	char list1[] = {'a', 'b', 'c', 'd', 'e', 'f'};
	char list2[] = {'c', 'e', 'f'};
	//removeDuplicates(list1,list2);
	// printf("%lu\n", sizeof(list1) / sizeof(list1[0])  );
	//printf("%s\n", list2 );

	return 0;
}