#include<stdio.h>
#include<string.h>

#define SAVED 0
#define NAME_SIZE 20
#define NUMBER_SIZE 11
#define EMAIL_SIZE 32

typedef enum
{
	K_FAIL,
	K_ADDRESS_BOOK_NULL,
	K_FILE_NOT_AVAILABLE,
	K_FILE_COULD_NOT_BE_CREATED,
	K_FILENAME_NULL,
	K_MEMORY_ALLOCATION_FAILURE,
	K_SUCCESS,
	K_WRONG_FILE_FORMAT,
} return_t;


int validation(char *,int);
int menu(FILE *,char *);
return_t add(FILE *,char *);
return_t edit(FILE *,char *);
return_t search(FILE *,char *);
return_t del_t(FILE *,char *);
return_t print(FILE *);
return_t is_file_empty(FILE *);
