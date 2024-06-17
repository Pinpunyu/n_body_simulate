#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "include/NBody.h"

int main(int argC,char* argV[])
{
	if(argC!=3){
		printf("Usage : %s <file name containing system configuration data>",argV[0]);
		return 0;
	}

	char* fileName = argV[1];
	int show_simulate = atoi(argV[2]);

	// Get Execution Time
	clock_t t1 = clock();
	n_body_simulate_cpu(fileName, show_simulate);
	clock_t t2 = clock();
	float CPU_elapsedTime = (t2 - t1) / (double)(CLOCKS_PER_SEC);

	printf("Excuetion Time on CPU : %10.10f ms\n", CPU_elapsedTime * 1000);
	// printf(" Excuetion Time on CPU: %3.20f s\n", CPU_elapsedTime);

	
	return 0;
}