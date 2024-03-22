//Shreya Shukla
//CS211: Computer Architecture
//Monday, Nov 27, 2023
//Homework 2
// Created by AJ DiLeo
// For use in CS211 Fall 2023 ONLY

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#define MAX_BIT_POSITION 32

// Cache for storing FizzBuzz results for each bit position
char cache[MAX_BIT_POSITION][3]; //first bit is the bit in 2's comp, second bit is position, third bit is fizzBuzz

// Initialize the cache with FizzBuzz results
void preComputeResults() {
    // TODO: For every possible position, pre-compute its corresponding string output
	// Make sure to handle the case where you will not replace the bit with Z, R, or U
	// Your advancedBitwiseFizzBuzz() code should know when to use the replacement and when to use the bit
    // Use 'Z' for numbers divisible by 3 and 5, 'R' for divisible by 3, and 'U' for divisible by 5
    for (int i = MAX_BIT_POSITION - 1; i >= 0; i--){
        cache[i][1] = i; //position
        //printf("Position: %d ", i);
        if (i==MAX_BIT_POSITION-1){
            cache[i][2] = 'S';
        }
        if ((i%3 == 0) && (i%5 ==0)){
            cache[i][2]='Z';
        }
        else if (i%3 == 0){
            cache[i][2]='R';
        }
        else if (i%5 == 0){
            cache[i][2]='U';
        }
        //printf("Value: %c\n", cache[i][2]);
        /*
        else{
            cache[i][2]='\0'; //null character
        }
        */
        //If none of the conditions are met, cache will remain uninitialized
    }
}

// Retrieve the FizzBuzz result for a specific bit position
char* getFizzBuzzForBit(int position) {
    // TODO: Return the FizzBuzz result for the given position from the cache
    return cache[position];
}

// Perform the advanced Bitwise FizzBuzz logic on the given number
void advancedBitwiseFizzBuzz(int32_t N) {
    // TODO: Implement the advanced Bitwise FizzBuzz logic
    // - For each bit in the number, apply the FizzBuzz logic
    // - Replace the MSb with 'S' if it's set
    // - Print each bit or its FizzBuzz result
    // - Format the output with a space every four bits

	// Each bitstring should be outputted from Left -> Right, MSb -> LSb
	// Index 0 of the bitstring should be the LSb
	// E.g., 
	// 1  0  0 1 0 0 0 1 1 1 0 0   <=== bitstring
	// 11 10 9 8 7 6 5 4 3 2 1 0   <=== indices

    //convert long num to binary bit string
    long temp = N;
    int numBits = 32;
    char bitString[numBits +1];
    
    //get the Binary bit string
    for (int i = 0; i < numBits; i++){
        bitString[numBits -1 -i] = (temp & 1) + '0';
        temp = temp >> 1; //right shift operator divides by 2^1
    }
    bitString[numBits] = '\0';
    //printf ("Bitstring: %s\n",bitString);

    //now that we have twos complement bitString, we need to fill in the cache
    for (int i = 0; i<numBits; i++){
        cache[i][0]= bitString[numBits - i -1]; //bit
        if (cache[i][0] == '1'){
            if (cache[i][2] == '\0'){ //if cache is null
                cache[i][2] = '1';
            }
        }
        else cache[i][2] = '0'; //or if the bit is 0
    }
    for (int i = 0; i < numBits; i++){
        if(i%4 == 0 &&  i!=0){
            printf(" ");
        }
        printf("%c", cache[numBits - i -1][2]);
    }
}

// Main function to run the program
int main(int argc, char *argv[]) {

    // TODO: Parse the command line argument to get the input number
    char* input = strdup (argv[1]);

    // Use strtol to convert the string to a long integer
    long num = strtol (input, NULL, 10);

    // Check if the number is within the range of a 32-bit signed integer
	// If so, print "Number out of range for a 32-bit integer\n"
    int min = -2147483648;
    int max = 2147483647;
    if (!( (num>= min) && (num<= max) )){
        printf("Number out of range for a 32-bit integer\n");
        exit(0);
    }

    // TODO: Initialize the cache
    preComputeResults();
    // TODO: Call advancedBitwiseFizzBuzz with the parsed number
	// Make sure the number is an int32_t
    advancedBitwiseFizzBuzz((int32_t)num); //typecasting to type int32_t
    free(input);
    return 0;
}
