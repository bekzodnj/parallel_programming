#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#define TRUE 1
#define FALSE 0 

void printToConsole(){
	printf("Radix sorting serial method: \n");
	printf("Example: ./radix_serial sizeOfArray<int> flagMode<int>"); 
}

void printArray(unsigned long int *list, unsigned long int size)
{
	int i; 
	for(i = 0; i < size; i++)
		printf("%lu%c", list[i], (i==size-1) ? '\n': ' '); 
}

int getMaxFromList(unsigned long int *list, int n){
	int max = list[0]; 
	int i; 
	for(i = 1; i < n; i++)
		if(list[i] > max)
			max = list[i];
	return max; 
}
void countSort(unsigned long int *list, int n, int exp)
{
	unsigned long int *result = malloc(n*sizeof(unsigned long int)); 
	int i, count[10] = {0}; 

	for(i = 0; i < n; i++)
		count[ (list[i]/exp)%10 ]++; 

	for(i = 1; i < 10; i++)
		count[i] += count[i - 1]; 

	for(i = n - 1; i >= 0; i--)
	{
		result[count[ (list[i]/exp)%10 ] - 1] = list[i]; 
		count[ (list[i]/exp)%10 ]--; 
	} 
	
	for(i = 0; i < n; i++)
		list[i] = result[i];
}

void radixSort(unsigned long int *list, int n)
{
	int exp; 
	int m = getMaxFromList(list,n); 
	for(exp = 1; m / exp > 0; exp *= 10)
		countSort(list,n,exp); 
}

int main(int argc, char *argv[]){
	if(argc != 3){
		printToConsole(); 
		exit(EXIT_FAILURE); 
	}
	// declarations
	unsigned long int n = atoi(argv[1]); 
	int flag = atoi(argv[2]); 
	int i;

	unsigned long int len = n; 
	unsigned long int *list = malloc(n*sizeof(unsigned long int)); 
	clock_t start; 
	for(i = 0; i < n; i++){
		list[i] = rand()%100000; 
	}

	if(flag == TRUE){
		printf("Initial List: \n"); 
		printArray(list, len);
	}
	else if (flag == 2){
		start = clock(); 
	}
	radixSort(list, n); 
	
	if(flag == TRUE) {
		printf("After sorting: \n"); 
		printArray(list, len);
	}
	else if(flag == 2) {
		printf("%10.10f\n", (double)(clock() - start) / CLOCKS_PER_SEC); 
	}
	free(list);
	return 0;
}
