#include<stdio.h>
#include<string.h>
#include"main.h"
FILE *fptr;
int main(int argc,char *argv[])
{
	if(validation(argv[1],argc))
	{                                 //validation complete
		printf("success\n");
		fptr = fopen(argv[1],"rw");
		menu(fptr,argv[1]);
	}
	else 
		printf("ERROR: failed\n");
}
int validation(char *argv,int argc)
{
	if(argc==2)
	{
		if(strstr(argv,".csv"))
			return 1;
		printf("ERROR: please enter a .csv file\n");
	}
	else 
		printf("ERROR: please enter one .csv file\n");

	return 0;
}
