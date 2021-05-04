#include <omp.h>
#include <stdio.h>
#include <stdlib.h>



// show hint if number of console args is less than 3
void printToConsole(){
	printf("Bubble sorting serial method: \n");
	printf("Example: ./bubble_serial sizeOfArray<int> debugMode<int>"); 
}

void printList(unsigned long int *list, unsigned long int size)
{
	int i; 
	for(i = 0; i < size; i++)
		printf("%lu%c", list[i], (i==size-1) ? '\n': ' '); 
}

void swap(unsigned long int *xp, unsigned long int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
int main (int argc, char *argv[]) {
	int SIZE =1<<8;
	int A[SIZE];
	for(int i=0;i<SIZE;i++)
	{
	    A[i]=rand()%SIZE;
	}
	//int A[5] = {6,9,1,3,7};

	//
    if(argc != 3){
		printToConsole(); 
		exit(EXIT_FAILURE); 
	}
	unsigned long int arraySize = atoi(argv[1]); 
	int flag = atoi(argv[2]); 

	// variable declarations
	int i;
	unsigned long int len = arraySize; 
	unsigned long int *list = malloc(arraySize*sizeof(unsigned long int)); 
	// if debugMode is true then timing will be calculated
	clock_t startTime, endTime; 

	// filling the array with random numbers
	for(i = 0; i < arraySize; i++){
		list[i] = rand()%100; 
	}

	// filling the array with random numbers
	for(i = 0; i < arraySize; i++){
		list[i] = rand()%100; 
	}

	if(flag == 1){
		printf("Initial List: \n"); 
		printList(list, len); 
	}

	// parallel sorting
	int N = arraySize;
	i=0;
	int j=0; 
	int first;
	double start,end;
	start=omp_get_wtime();
	for( i = 0; i < N-1; i++ )
	{
		first = i % 2; 
		#pragma omp parallel for default(none),shared(list,first,N)
		for( j = first; j < N-1; j += 1 )
		{
			if( list[ j ] > list[ j+1 ] )
			{
				swap( &list[ j ], &list[ j+1 ] );
			}
		}
	}
	end=omp_get_wtime();

	// if mode to set to true print the result
	if(flag == 1){
		printf("After sorting: \n"); 
		printList(list, len); 
	}

	printf("\n------------------------- Time Parallel= %f \n",(end-start));
}

