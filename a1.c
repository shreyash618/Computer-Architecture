//Shreya Shukla
//CS211: Computer Architecture
//Tuesday, Oct 17th, 2023
//Assignment 1

// Created by AJ DiLeo
// For use in CS211 Fall 2023 ONLY

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS_SIZE 100

typedef struct programmingLanguage {
	int id;
	char* language;
	int year;
	char* creator;
	char* paradigm;
	double popularityIndex;

	//1 if it is deleted, 0 otherwise
	int isDeleted; // internal field, not accessible to user
} lang_t; //typedef links lang_t with type programmingLanguage

// step 1: create structs for the other two tables: operatingSystems
// and databases
// include internal field

typedef struct operatingSystem {
	int id;
	char* name;
	int year;
	char* developer;
	char* kernelType;
	
	//1 if it is deleted, 0 otherwise
	int isDeleted; //internal field, not accesible to user

} os_t; //typedef links os_t with type operatingSystem

typedef struct database {
	int id;
	char* name;
	int year;
	char* type;
	char* developer;

	//1 if it is deleted, 0 otherwise
	int isDeleted; //internal field, not accesible to user
} db_t; //typedef links db_t with type database


// step 2: create typedef struct for storing metadata
struct metadata {
	int count; //number of data entries in table/array
	int nextIndex; //next index to insert data into in table/array
	int maxCount; //max number of rows in table/array
};

// step 3: declare the two other arrays of structs
// programmingLanguages has been defined for you already
// TODO: add operatingSystems and databases

lang_t* programmingLanguages;
os_t* operatingSystems;
db_t* databases;

// step 4: declare 3 metadata structs, one for each table

struct metadata lang_metadata; //metadata for the programming languages table
struct metadata os_metadata; //metadata for the operating systems table
struct metadata db_metadata; //metadata for the databases table

// step 5: jump to L167

// This function takes the user's input and splits it by spaces
// into an array of strings, ignoring spaces that are wrapped in quotes
// There is no need to modify this code.
// You do not need to understand this code
// but you are welcome to research its application
void splitInput(char* input, char** args, int* arg_count) {
    *arg_count = 0;
    int in_quotes = 0; // Flag to track whether we are inside quotes
    char* token_start = input;

    for (char* ptr = input; *ptr != '\0'; ptr++) {
        if (*ptr == '"') {
            in_quotes = !in_quotes; // Toggle the in_quotes flag when a quote is encountered
        }

        if ((*ptr == ' ' || *ptr == '\n') && !in_quotes) {
            // If not inside quotes and a space or newline is found, consider it as a separator
            *ptr = '\0'; // Replace space or newline with null terminator
            args[(*arg_count)++] = token_start;
            token_start = ptr + 1; // Start of the next token
        }
    }

    // Add the last token (if any) after the loop
    if (*token_start != '\0') {
        // Remove leading and trailing double quotes if they exist
        if (token_start[0] == '"' && token_start[strlen(token_start) - 1] == '"') {
            token_start[strlen(token_start) - 1] = '\0'; // Remove trailing quote
            args[(*arg_count)++] = token_start + 1; // Remove leading quote
        } else {
            args[(*arg_count)++] = token_start;
        }
    }
    args[*arg_count] = NULL;
}

// step 7: implement setup function
// this function is responsible for dynamically allocating the
// particular table. Use the tables declared on L27.

void setup(char* table, int numRows) {
	//string compare to see what kind of table we're setting up
	//set metadata attribute maxCount
	//also use malloc to allocate memory to the arrays!

	if (strcmp(table, "programmingLanguages") == 0){
		lang_metadata.maxCount = numRows;
		programmingLanguages = malloc (numRows * sizeof (lang_t));
	}

	else if (strcmp(table, "operatingSystems") == 0){
		os_metadata.maxCount = numRows;
		operatingSystems = malloc (numRows * sizeof (os_t));
	}

	else if (strcmp(table, "databases") == 0){
		db_metadata.maxCount = numRows;
		databases = malloc (numRows * sizeof (db_t));
	}

	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("setup complete\n");
}

// step 8: implement insert function
// this function is responsible for updating the corresponding
// fields of the struct located at the next available index
// make sure to use and update your metadata.

// autograder print for insufficient capacity:
// fprintf(stderr, "cannot insert due to insufficient capacity.\n");
void insert(char** args) {
	// in the string array args, the first string is the function name (insert), and the second is the table name (programmingLanguages, operatingSystems, or databases)
	//thus, we start inputting the row data from the third argument, at index 2
	char* table = args[1];

	if (strcmp(table, "programmingLanguages") == 0){
		//check if there is enough space in array to enter data
		if (lang_metadata.count >= lang_metadata.maxCount){
			fprintf(stderr, "cannot insert due to insufficient capacity.\n");
			return; //Or should I use return EXIT_FAILURE;
		}

		//printf("Inserted data at index %d\n", lang_metadata.nextIndex);

		//enter the user inputted data into the fields of the struct located at the next available index
		programmingLanguages[lang_metadata.nextIndex].id = atoi (args[2]);
		programmingLanguages[lang_metadata.nextIndex].language = strdup(args[3]);
		programmingLanguages[lang_metadata.nextIndex].year = atoi(args[4]);
		programmingLanguages[lang_metadata.nextIndex].creator = strdup(args[5]);
		programmingLanguages[lang_metadata.nextIndex].paradigm = strdup(args[6]);
		programmingLanguages[lang_metadata.nextIndex].popularityIndex = atof(args[7]);

		//set the isDeleted parameter to 0, which means it's not deleted
		programmingLanguages[lang_metadata.nextIndex].isDeleted = 0;

		//update nextIndex and count
		lang_metadata.nextIndex++;
		lang_metadata.count++;
	}
	else if (strcmp(table, "operatingSystems") == 0){
		//check if there is enough space in array to enter data
		if (os_metadata.count >= os_metadata.maxCount){
			fprintf(stderr, "cannot insert due to insufficient capacity.\n");
			return;
		}

		//enter the user inputted data into the fields of the struct located at the next available index
		operatingSystems[os_metadata.nextIndex].id = atoi (args[2]);
		operatingSystems[os_metadata.nextIndex].name = strdup(args[3]);
		operatingSystems[os_metadata.nextIndex].year = atoi(args[4]);
		operatingSystems[os_metadata.nextIndex].developer = strdup(args[5]);
		operatingSystems[os_metadata.nextIndex].kernelType = strdup(args[6]);

		//set the isDeleted parameter to 0, which means it's not deleted
		operatingSystems[os_metadata.nextIndex].isDeleted = 0;

		//update nextIndex and count
		os_metadata.nextIndex++;
		os_metadata.count++;
		
	}
	else if (strcmp(table, "databases") == 0){
		//check if there is enough space in array to enter data
		if (db_metadata.count >= db_metadata.maxCount){
			fprintf(stderr, "cannot insert due to insufficient capacity.\n");
			return;
		}

		//enter the user inputted data into the fields of the struct located at the next available index
		databases[db_metadata.nextIndex].id = atoi (args[2]);
		databases[db_metadata.nextIndex].name = strdup(args[3]);
		databases[db_metadata.nextIndex].year = atoi(args[4]);
		databases[db_metadata.nextIndex].type = strdup(args[5]);
		databases[db_metadata.nextIndex].developer = strdup(args[6]);

		//set the isDeleted parameter to 0, which means it's not deleted
		databases[db_metadata.nextIndex].isDeleted = 0;

		//update nextIndex and count
		db_metadata.nextIndex++;
		db_metadata.count++;

	}
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("insert complete\n");
}

// step 9: implement soft delete function
// this function is responsible for marking a record as deleted
// you should be updating an internal field flag so that get will
// not display this record. 
// You should not be attempting to free/overwrite this record - it remains alloc
// with a updated field
// make use of your metadata
void delete(char* table, int id) {
	if (strcmp(table, "programmingLanguages") == 0){
		for (int i = 0; i<lang_metadata.nextIndex; i++){
			//if you find a record matching the user-inputted id
			if (programmingLanguages[i].id == id){
				programmingLanguages[i].isDeleted = 1; //soft-delete
				--lang_metadata.count; //minus 1 from the count
			}
		}
	}
	else if (strcmp(table, "operatingSystems") == 0){
		for (int i = 0; i<os_metadata.nextIndex; i++){
			if (operatingSystems[i].id == id){
				operatingSystems[i].isDeleted = 1; //soft-delete
				--os_metadata.count; //minus 1 from the count
			}
		}
	}
	else if (strcmp(table, "databases") == 0){
		for (int i = 0; i<db_metadata.nextIndex; i++){
			//if you find a record matching the user-inputted id
			if (databases[i].id == id){
				databases[i].isDeleted = 1; //soft-delete
				--db_metadata.count; //minus 1 from the count
			}
		}
	}
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("delete complete\n");
}

// step 10: implement modify function
// this function is responsible for overwriting all of the contents of all
// records that match an ID.
// make use of your metadata
// !!!NOTE: The structs store pointers. Make sure to free any allocated
// memory before overwriting it!!!
void modify(char** args) {
	char* table = args[1];
	int mod_id = atoi(args[2]);
	if (strcmp(table, "programmingLanguages") == 0){
		for (int i = 0; i<lang_metadata.nextIndex; i++){
			//if you find a record matching the user-inputted id
			if (programmingLanguages[i].id == mod_id){
				//free the elements with type char*
				free (programmingLanguages[i].language);
				free (programmingLanguages[i].creator);
				free (programmingLanguages[i].paradigm);

				//update the elements
				programmingLanguages[i].language = strdup(args[3]);
				programmingLanguages[i].year = atoi(args[4]);
				programmingLanguages[i].creator = strdup(args[5]);
				programmingLanguages[i].paradigm = strdup(args[6]);
				programmingLanguages[i].popularityIndex = atof(args[7]);
			}
		}
	}
	else if (strcmp(table, "operatingSystems") == 0){
		for (int i = 0; i<os_metadata.nextIndex; i++){
			//if you find a record matching the user-inputted id
			if (operatingSystems[i].id == mod_id){
				//free the memory of type char*
				free(operatingSystems[i].name);
				free(operatingSystems[i].developer);
				free(operatingSystems[i].kernelType);

				//update the elements
				operatingSystems[i].name = strdup(args[3]);
				operatingSystems[i].year = atoi(args[4]);
				operatingSystems[i].developer = strdup(args[5]);
				operatingSystems[i].kernelType = strdup(args[6]);

			}
		}
	}
	else if (strcmp(table, "databases") == 0){
		for (int i = 0; i<db_metadata.nextIndex; i++){
			//if you find a record matching the user-inputted id
			if (databases[i].id == mod_id){
				//free the memory of type char*
				free(databases[i].name);
				free(databases[i].type);
				free(databases[i].developer);

				//update the elements
				databases[i].name = strdup(args[3]);
				databases[i].year = atoi(args[4]);
				databases[i].type = strdup(args[5]);
				databases[i].developer = strdup(args[6]);
			}
		}
	}

	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("modify complete\n");
}

// step 11: implement get function
// this function is responsible for fetching all non-deleted records
// make use of your metadata
// Make sure to follow guidelines for format in writeup
// see examples as well
// Use %lf for formatting double data type
void get(char* table) {
	if (strcmp(table, "programmingLanguages") == 0){
		printf("id,language,year,creator,paradigm,popularityIndex\n");
		for (int i = 0; i<lang_metadata.nextIndex; i++){
			if (programmingLanguages[i].isDeleted == 0){
				printf ("%d,%s,%d,%s,%s,%lf\n", programmingLanguages[i].id, programmingLanguages[i].language, 
				programmingLanguages[i].year, programmingLanguages[i].creator, programmingLanguages[i].paradigm,
				programmingLanguages[i].popularityIndex);
			}
		}
		
	}
	else if (strcmp(table, "operatingSystems") == 0){
		printf("id,name,year,developer,kernelType\n");
		for (int i = 0; i<os_metadata.nextIndex; i++){
			if (operatingSystems[i].isDeleted == 0){
				printf("%d,%s,%d,%s,%s\n", operatingSystems[i].id, operatingSystems[i].name, 
				operatingSystems[i].year, operatingSystems[i].developer, 
				operatingSystems[i].kernelType);

			}
		}

		
	}
	else if (strcmp(table, "databases") == 0){
		printf("id,name,year,type,developer\n");
		for (int i = 0; i<db_metadata.nextIndex; i++){
			if (databases[i].isDeleted == 0){
				printf("%d,%s,%d,%s,%s\n", databases[i].id, databases[i].name, 
				databases[i].year, databases[i].type, 
				databases[i].developer);
			}
		}
	}
}


// step 12: implement exit function
// this function should free all allocated memory
// Make sure to avoid memory leaks by freeing any allocated memory
// inside a struct (char*) before freeing the struct pointer
void exitProgram() {
	// Free allocated memory for programmingLanguage table
    for (int i = 0; i < lang_metadata.nextIndex; i++) {
        free(programmingLanguages[i].language);
        free(programmingLanguages[i].creator);
        free(programmingLanguages[i].paradigm);
    }
    free(programmingLanguages);

    // Free allocated memory for operatingSystems and databases tables
    for (int i = 0; i < os_metadata.nextIndex; i++) {
        free(operatingSystems[i].name);
        free(operatingSystems[i].developer);
        free(operatingSystems[i].kernelType);
        
    }
    free(operatingSystems);
   
    for (int i = 0; i < db_metadata.nextIndex; i++) {
        free(databases[i].name);
        free(databases[i].type);
        free(databases[i].developer);
        
    }
    free(databases);

	//only need to free the variables I malloced

    //printf("Exit program.\n");
    exit(EXIT_SUCCESS);
}

// this code is responsible for parsing the user's
// input, and determining based on the command
// which function to send it to.
// You do not have to modify this code, but you should
// understand it.
void execute_cmd(char** args, int arg_count) {
	char* cmd = args[0];
	if (strcmp(cmd, "setup") == 0) {
		setup(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "insert") == 0) {
		insert(args);
	} else if (strcmp(cmd, "delete") == 0) {
		delete(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "modify") == 0) {
		modify(args);
	} else if (strcmp(cmd, "get") == 0) {
		get(args[1]);
	} else if (strcmp(cmd, "exit") == 0) {
		exitProgram();
	} else {
		printf("\n");
	}
}

// step 6: initialize the default metadata values here
// jump to L76
void initializeMetadata() {
	//count and nextIndex should be initialized to 0, but you can leave maxCount alone 
	//(that will be initialized in setup)

	//also how do you access that specific metadata object's attributes?
	//use dot operator but we don't have any input for this function?
	//nvm, just use the metadata objects that we declared earlier in Step 4

	//initialize all of them
	lang_metadata.count = 0;
	lang_metadata.nextIndex = 0;

	os_metadata.count = 0;
	os_metadata.nextIndex = 0;

	db_metadata.count = 0;
	db_metadata.nextIndex = 0;

}

// this code creates the interactive shell
// you do not need to modify this
// You do not need to understand this code
// but you are welcome to research its application
void cmd_loop() {
	char input[MAX_INPUT_SIZE];
    ssize_t bytes_read;
	printf("Usage: \n");
	printf("setup {table} {numRows}\n");
	printf("insert {table} {data}\n");
	printf("delete {table} {id}\n");
	printf("modify {table} {id} {data}\n");
	printf("get {table}\n\n");
	initializeMetadata();
    while (1) {
        printf("CS211> ");
		fflush(stdout);
        
        // Read user input using the read() system call
        bytes_read = read(STDIN_FILENO, input, sizeof(input));
        
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        if (bytes_read == 0) {
			printf("\n");
            break;
        }
        
        // Null-terminate the input
        input[bytes_read] = '\0';

		char** args = (char**)malloc(MAX_ARGS_SIZE * sizeof(char*));
		int arg_count;

		splitInput(input, args, &arg_count);
        
        // Execute the user's command
        execute_cmd(args, arg_count);
		free(args);
    }
}


int main() {
	cmd_loop();
}