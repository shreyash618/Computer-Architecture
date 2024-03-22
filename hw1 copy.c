//Shreya Shukla
//CS211: Computer Architecture
//Monday, Oct 2nd, 2023
//Homework 1

// Created by AJ DiLeo
// For use in CS211 Fall 2023 ONLY

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

// ******STEP 0: SKIP TO MAIN FUNCTION*********

// TODO: Nested Reverse
// Input: 2d array, number of rows, number of cols
// For each array, reverse its position
// For each element in the array, reverse its position
// e.g, input: 
// [
// 	[1, 2, 3, 4, 5],
// 	[6, 7, 8, 9, 10],
// 	[1, 3, 6, 8, 9]
// ]
// first reverse the order of the arrays
// [
// 	[1, 3, 6, 8, 9],
// 	[6, 7, 8, 9, 10],
// 	[1, 2, 3, 4, 5]
// ]
// now reverse the order of each of the elements
// [
// 	[9, 8, 6, 3, 1],
// 	[10, 9, 8, 7, 6],
// 	[5, 4, 3, 2, 1]
// ]
// DONE!
// NOTE: You will notice the code for the two steps will be fairly similar

//helper function for nestedReverse
//gives us the index of the middle row or column
int middleIndex (int n){ 
	if ((n % 2) == 1){ //if n is odd
		return (int) ((n/2.0) - 0.5);
	}
	else return (int) ((n/2.0)); //if n is even
}

void nestedReverse(int** arr, int rows, int cols){
	/*
	// testing the helper function
	printf("Rows: %d\n", rows);
	printf("Middle row index: %d\n", middleIndex(rows));

	printf("Columns: %d\n", cols);
	printf("Middle column index: %d\n", middleIndex(cols));
	*/

	int midRow = middleIndex(rows);
	int midCol = middleIndex (cols);

	int i, j, temp = 0;
	
	//first, reverse the order of the rows:
	for (i = 0; i < midRow; i++){
		for (j = 0; j < cols; j++){
			/*
			printf ("Swtich row %d col %d with row %d col %d\n",
			i, j, (rows-i-1), j);
			*/
			
			temp = arr[i][j];
			arr[i][j] = arr[rows-i-1][j];
			arr[rows-i-1][j] = temp;
		}
	}
	

	//then, reverse the order of the elements in each row:
	for (i = 0; i < rows; i++){
		for (j = 0; j < midCol; j++){
			
			/*
			printf ("Swtich row %d col %d with row %d col %d\n",
			i, j, i, (cols-j-1));
			*/
			
			temp = arr[i][j];
			arr[i][j] = arr[i][cols-j-1];
			arr[i][cols-j-1] = temp;
		}
	}
	return;
}

typedef struct Student {
	int id;
	char* name;
	float gpa;
} student_t;
// It is a common naming convention to append
// a _t to a struct to denote that its a struct

// TODO: Deep Compare
// Input array of students, total number of students
// For every combination (numStudents C 2) of students, see if they all match
// e.g., students = [0,1,2,3]:
// combos are : 0,1  0,2  0,3  1,2  1,3  2,3

int deepCompare(student_t* students, int numStudents) {
	// RETURN 1 when all equal
	// ELSE 0

	for (int i = 1; i < numStudents; i++) 
	{		//compare all students to the first student in the array, student[0]
        	if (students[0].id == students[i].id   && (strcmp(students[0].name,students[i].name)==0)     && students[0].gpa == students[i].gpa) 
	   		//if the students are the same, continue
			{
                continue;
            }
			// else, if even one student is different, exit the loop and return 0
            else 
	   		{
				return 0; //at least one student is different
            }
	}
		return 1; //all student entries are identical and have same name, id, and gpa
}

// TODO: Replace random
// Input: int array, number of elements to replace
// ASSUME: numToReplace <= length of arr
// Replace the first numToReplace elements with a random number
// e.g., arr = [1,2,3,4,5], numToReplace=2
// Output: arr = []
// ONLY USE rand() function. `man 3 rand`

void replaceNRandom(int* arr, int numToReplace) {
	// Do not touch this line
	srand(time(0));
	// use rand() to generate a random number
	for(int i = 0; i < numToReplace ; i++)
	{
         	arr[i] = rand();
	}
	return;
}

int main(int argc, char* argv[]) {
	// argc - number of cmd line args
	// argv - array of cmd line args

	// Step 1: Ensure at least two command line args were given
	// e.g., ./hw1 {pointers|structs|malloc}
	//E`xit the program in failure if there are less than 2 command line arguments
	if (argc < 2) {
		// NOTE: Notice how we must include a new line char (\n)
		// NOTE: What is stderr? What is the difference between stdout & stderr?
		// Answer:
		// Stderr is the file where the program writes diagnostic output
		// Stdout is the file where the programs write conventional output
		fprintf(stderr, "Usage: ./hw1 {pointers|structs|malloc}\n");
		// NOTE: EXIT_FAILURE is a macro. This makes our code cleaner.
		return EXIT_FAILURE;
	}

	// Step 2: Now that we know what exercise to run, let's setup conditionals
	// to enforce this
	// NOTE: In your terminal, run `man strcmp`: This will give us the documentation
	// strcmp(char*, char*) -> 0 if the two strings are identical
	// strcmp will return <0 if string 1 comes after string 2 in a dictionary in alphabetical orer
	// strcmp will return >0 if string 1 comes before string 2 in a dictionary in alphabetical orer

	// NOTE: Why is it argv[1]? What is argv[0]?
	//argv[0] is the class name we gave (./hw1)
	//argv[1] is the function we're running, which can be either pointers, structs or malloc

	//Basically if the argument given is "pointers"
	if (strcmp(argv[1], "pointers") == 0) {
		// At this point, the user has entered ./hw1 pointers
		// The following code will setup our 2d array.
		// It is not necessary to understand this code yet, but take a stab at it.

		// ./hw1 pointers {rows} {cols} {elements}
		// atoi converts a char* (aka string) to an int
		int rows = atoi(argv[2]);
		int cols = atoi(argv[3]);

		// We are taking a 2D array as input
		// Thus, rows*cols is the number of elements in the array
		// We need to add 4 to skip the first four arguments: 
		// program name, exercise name, num rows, num cols
		
		//If the number of elements plus 4 is not the number of arguments given in command line,
		//exit the program in failure.
		if ((rows * cols) + 4 != argc) {
			fprintf(stderr, "Usage: ./hw1 pointers {rows} {cols} {rows*cols elements}\n");
			return EXIT_FAILURE;
		}
		
		// We are now ready to load the 2d array into memory
		// THIS IS OUR INPUT 2D ARRAY
		// first, we need to allocate enough room for num rows arrays

		//Right side: initialize 2D array arr.
		//Left side: allocate enough memory to arr so that there are given number of rows
		// type conversion to a 2d array(int **). 
		// each row is allocated memory: rows * sizeof(int*)
		int** arr = (int**)malloc(rows * sizeof(int*));

		//Loop through each row
		for (int i = 0; i < rows; i++) {
			// now, lets allocate enough room for num cols elements in each array

			//Give each row memory equivalent to the number of columns in each row
			// type conversion of each row to int array (int*)
			// each row is allocated memory: cols per row * sizeo (int)
			arr[i] = (int*)malloc(cols * sizeof(int));
			for (int j = 0; j < cols; j++) {
				// now lets load the elements
				// atoi parses char* (aka String) to int
				
				//this formula works for some reason?
				arr[i][j] = atoi(argv[4 + i * cols + j]);
			}
		}

		// Now arr is a 2d array loaded with elements from command line args
		// Step 3: Call your nestedReverse function
		// This function will reverse the order of the arrays, and each of their elements.
		// Thus, no need for a return value.
		nestedReverse(arr, rows, cols);

		// Now our arr is reversed. 

		// DO NOT TOUCH THE FOLLOWING CODE
		// FORMAT IS REQUIRED FOR AUTO-GRADER
		// ANY CHANGES WILL RESULT IN INVALID SCORE
		// Print the reversed 2D array
		for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					printf("%d ", arr[i][j]);
				}
				printf("\n");
			free(arr[i]); //free each row of it's memory after printing out it's contents row-by-row
		}
	} else if (strcmp(argv[1], "structs") == 0) {
		// At this point, the user has entered ./hw1 structs
		// each struct requires 3 elements: id, name, gpa

		// ./hw1 structs {numStudents} {data}
		// ./hw1 structs 2 1 aj 3.5 2 zoe 4.0
		int numStudents = atoi(argv[2]); //the numbers of student we're comparing

		//if the user didn't pass the correct number of arguments to specify each student struct,
		//exit the program in failure
		if (argc != (numStudents*3) + 3) { //add 3 for class name ./hw1, "structs" numStudents
			fprintf(stderr, "Usage: ./hw1 structs {numStudents} {data}\n");
			return EXIT_FAILURE;
		}

		// allocate enough space for an array of numStudents student_t structs.

		// Left side: make a array of class type student_t and name it "students"
		// Right side: allocate memory numStudents * sizeof(student_t)
		// Type conversion to array student_t*
		student_t* students = (student_t*)malloc(numStudents * sizeof(student_t));

		// load the data
		for (int i = 0; i < numStudents; i++) {
			// atoi converts char* (aka String) to int
			students[i].id = atoi(argv[3 + i * 3]); //input the student's id from cmd-line args
			// strdup returns a pointer to a string (basically it copies a string)
			students[i].name = strdup(argv[4 + i * 3]); //input student's name from cmd-line args

			// STEP 4: Add the data for GPA. Use the examples above for assistance.
			// Remember, gpa is a float. What function should you use to convert
			// char* to float?

			// atof converts a char* (aka String) to a float
			students[i].gpa = atof(argv[5 + i *3]);
		}
		/*
		printf("Is the ID same?\n");
		if(students[0].id == students[1].id){
			printf("Yes.\n");
		}
		else {
			printf("No.\n");
		}
		printf("Is name the same?\n");
		if(strcmp(students[0].name, students[1].name)==0){
			printf("Yes.\n");
		}
		else {
			printf("No.\n");
		}
		printf("Is GPA the same?\n");
		if(students[0].gpa == students[1].gpa){
			printf("Yes.\n");
		}
		else {
			printf("No.\n");
		}
		*/  
		int result = deepCompare(students, numStudents);

		// DO NOT TOUCH THE FOLLOWING CODE
		// FORMAT IS REQUIRED FOR AUTO-GRADER
		// ANY CHANGES WILL RESULT IN INVALID SCORE
		// Print the result
		if (result == 1) {
			printf("Data is the same!\n");
		} else {
			printf("At least one student is different!\n");
		}

		// release allocated memory
		// Why do we need to free name first before the entire array?
		// a char* is a dynamically alloc string => We do not know how long the string is
		// until the user enters it.
		// We have to free the inside of the array, before the entire array
		// else, that memory will forever be allocated
		for (int i = 0; i < numStudents; i++) {
			free(students[i].name); //must free string "name" inside of array first
		}
		free(students); //free the array students of class type student_t

	} else if (strcmp(argv[1], "malloc") == 0) {
		// At this point user has entered ./hw1 malloc

		// STEP 5: Extract numToReplace and numElements

		int numToReplace = atoi(argv[2]);
		int numElements = atoi (argv[3]);

		// STEP 6: Add a check to ensure user has passed correct num of args
		// check "pointers" for an example
		// ./hw1 malloc {numToReplace} {numElements} {elements}
		// ./hw1 malloc 2 5 1 2 3 4 5
		// You can assume numToReplace <= numElements
		// You can assume all elements will be integers

		//If the number of elements plus 4 is not the number of arguments given in command line,
		//exit the program in failure.
		if (numElements + 4 != argc) {
			fprintf(stderr, "Usage: ./hw1 malloc {numToReplace} {numElements} {elements}\n");
			return EXIT_FAILURE;
		}

		// STEP 7: Now load the array into memory
		// allocate enough space for a variable named arr
		// iterate over all elements and load them into their respective slots
		int* arr= (int *) malloc (numElements * sizeof(int));

		for (int s = 0; s < numElements; s++){
			arr[s] = atoi(argv[4+s]);
		}

		// STEP 8: replace the first numToReplace elements in the array
		replaceNRandom(arr, numToReplace);

		// STEP 9: Modify numElements and arr variable name as needed. 
		//does that mean we add ampersand or pointer to step 8? ^^^

		// DO NOT touch print statement, this is used for auto-grader
		// output should be:
		// 1 2 3 4 5
		for (int i = 0; i < numElements; i++) {
			printf("%d ", arr[i]);
		}
		printf("\n");

		// STEP 10: Free the allocated memory
		free(arr);
		
	}

	return EXIT_SUCCESS;
}