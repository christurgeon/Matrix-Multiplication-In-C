// Author: Chris Turgeon
// File: hw1.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int get_int_length(int num) {
	/* This function calculates the amount of digits in 
	   any integer. */
	int count = 0;
	while (num != 0) {
		num /= 10;
		++count;
	}
	return count;
}



void print_matrix(int* matrix[], int r, int c) {
	/* This function takes in a 2D array by reference and prints
	   it in the form of a matrix, while formatting nicely. */
	/* Loop through the matrix to find the greatest digit in each column
     for formatting purposes. */
      int i, j;
      int lengths[c];
      for (i = 0; i < c; i++) {
	     	int temp = 0;
	     	for (j = 0; j < r; j++) {
	     		if (matrix[j][i] > temp) {
	     			temp = matrix[j][i];
	     		}
	     	}
	     	// Find the amount of digits in the largest number in each column
	     	int length = get_int_length(temp);
	     	lengths[i] = length;
      }
      // Print out the matrix
      for (i = 0; i < r; i++) {
      	printf("[");
      	for (j = 0; j < c; j++) {
      		int spc = lengths[j] - get_int_length(matrix[i][j]);
      		printf("%.*s", spc, "          ");
      		printf("%d", matrix[i][j]);
      		if (j+1 < c) { // Print a single space between numbers
      			printf(" ");
      		}
      	}
      	printf("]\n");
      }
}



void multiply(int* M1[], int r1, int c1, int* M2[], int r2, int c2) {
	/* This function takes in two matrices with their dimensions. 
	   It then creates a third matrix which is the product of the 
	   first two. It then calls the print_matrix function to print
	   the result to the console. */

	// Declare the needed variables
	int i, j, k; 
	int value = 0;

    // Product has same # of rows as matrix one and columns as matrix two.
    // Need to allocate memory for the product matrix. 
	int* productMatrix[r1]; 
	for (i = 0; i < r1; i++) {
		productMatrix[i] = (int*) malloc(c2 * sizeof(int));	
	}

	// Fill the productMatrix by multiplying matrix one and two
	for (i = 0; i < r1; i++) { 
		for (j = 0; j < c2; j++) {
			for (k = 0; k < c1; k++) { // k can be used as idx for both matrices
				value += M1[i][k] * M2[k][j];  
			}
			productMatrix[i][j] = value;
			value = 0;
		}
	}
	// Print product matrix
	print_matrix(productMatrix, r1, c2);

	// Free memory 
	for (i = 0; i < r1; i++)  
		free(productMatrix[i]);
}



int main(int argc, char* argv[]) {
	// Ensure that we have the correct number of command-line arguments
	if (argc != 5) {
		fprintf(stderr, "ERROR: Invalid inputs!\n");
		return EXIT_FAILURE;
	}

	// Read in dimensions for matrices, convert to type int
	int rowFirst = atoi(argv[1]);
	int colFirst = atoi(argv[2]);
	int rowSecond = atoi(argv[3]);
	int colSecond = atoi(argv[4]);

	// Error check to ensure that the two matrices can be multplied
	if (colFirst != rowSecond) {
		fprintf(stderr, "ERROR: Invalid inputs!\n");
		return EXIT_FAILURE;
	}

	// Read in user values for the first matrix and add to 2D array
	printf("Please enter the values for the first matrix (%dx%d):\n", rowFirst, colFirst);
	int* matrixOne[rowFirst]; 
	int i, j, value;
	for (i = 0; i < rowFirst; i++) {
		matrixOne[i] = (int*) malloc(colFirst * sizeof(int));
		for (j = 0; j < colFirst; j++) {
			scanf("%d", &value);
			matrixOne[i][j] = value;
		}
	}

	// Read in user values for the second matrix and add to 2D array
	printf("Please enter the values for the second matrix (%dx%d):\n", rowSecond, colSecond);
	int* matrixTwo[rowSecond]; 
	for (i = 0; i < rowSecond; i++) {
		matrixTwo[i] = (int*) malloc(colSecond * sizeof(int));
		for (j = 0; j < colSecond; j++) {
			scanf("%d", &value);
			matrixTwo[i][j] = value;
		}
	}

	printf("\n");
	print_matrix(matrixOne, rowFirst, colFirst);
	printf("multiplied by\n");
	print_matrix(matrixTwo, rowSecond, colSecond);
	printf("equals\n");
	multiply(matrixOne, rowFirst, colFirst, matrixTwo, rowSecond, colSecond);

	// Free memory matrixOne
	for (i = 0; i < rowFirst; i++)  
		free(matrixOne[i]);

	// Free memory matrixTwo
	for (i = 0; i < rowSecond; i++)  
		free(matrixTwo[i]);

	return EXIT_SUCCESS;
}