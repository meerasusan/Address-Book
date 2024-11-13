#include<stdio.h>
#include<stdlib.h>
#include"main.h"
int menu(FILE *fptr,char *fname)
{
	char ch, name[20];
	while(1)
	{
		printf("\nEnter the operation to be performed\n Add contact (a)\n Edit contact (e)\n Search contact (s)\n Delete contact (d)\n Print (p)\n Exit (x)\n");
		scanf("%c",&ch);
		getchar();
		switch(ch)
		{
			case 'a':
				{
					add(fptr,fname);
					fptr = fopen(fname,"r+");
					break;
				}
			case 'e':
				{
					edit(fptr,fname);
					fptr = fopen(fname,"r+");
					break;
				}
			case 's':
				{
					printf("Enter the name/phone no/location to be searched\n");
					scanf("%[^\n]",name);
					getchar();
					search(fptr,name);
					break;
				}
			case 'd':
				{
					del_t(fptr,fname);
					fptr = fopen(fname,"r+");
					break;
				}
			case 'p':
				{
					print(fptr);
					break;
				}
			case 'x':
				{
					return 0;
				}
			default:
				printf("Please enter valid option\n");
		}

	}
}
return_t edit(FILE *fptr,char *fname)
{

	char name[20],phone[12],email[30],address[30],line[60],ch;
	printf("Enter the phone no to be searched\n");
	scanf("%[^\n]",phone);
	getchar();
	printf("Are you sure you want to make changes in this contact (y/n)\n");//double checking
	scanf("%c",&ch);
	getchar();

	FILE *temp = fopen("temp.csv","w");
	if(!temp)//temp==NULL->file cannot be opened
	{
		printf("ERROR: Delete Operation failed\n");
		return 0;
	}

	if(ch == 'y' || ch == 'Y')  //edit
	{
		if(search(fptr,phone))//if contact present 
		{
			rewind(fptr);//resetting the curser
			while(fscanf(fptr,"%[^\n]",line)!=EOF)
			{
				if(strstr(line,phone)==0)
				{
					fputs(line,temp);
					putc('\n',temp);
				}
				else if(strstr(line,phone))
				{
					printf("Re-enter the details with required modifications\nName\n");
					scanf("%[^\n]",name); //name
					getchar();
					fputs(name,temp);
					putc(',',temp);
					while(1)  //phone
					{
						printf("Phone Number\n");
						scanf("%[^\n]",phone);
						getchar();
						if(strlen(phone)==10)
							break;
						else
							printf("ERROR: Please enter 10 digit phone number\n");
					}
					fputs(phone,temp);
					putc(',',temp);
					while(1)          //Email
					{
						printf("Email ID\n");
						scanf("%[^\n]",email);
						getchar();
						if(strstr(email,".com"))
						{
							if(strchr(email,'@'))
							{
								fputs(email,temp);
								putc(',',temp);
								break;
							}
							else
								printf("ERROR: Please enter valid email id\n");
						}
						else if(strlen(email)==0)
						{
							putc(',',temp);
							break;
						}
						else
							printf("ERROR: Please enter valid email id\n");
					}
					printf("Location\n"); //location
					scanf("%[^\n]",address);
					getchar();
					fputs(address,temp);
					putc('\n',temp);
				}
				fseek(fptr,1,SEEK_CUR);//move to the next line
			}

			fclose(fptr);
			fclose(temp);
			rename("temp.csv",fname);
		}
	}
}

return_t add(FILE *fptr,char *fname)
{
	char name[20],phone[12],email[30],address[30],line[60],x[7];

	rewind(fptr);//resetting the curser
	fscanf(fptr,"%[^\n]",line); //reading 1st line
	for(int i=1;i<strlen(line)-1;i++)//reading only the int chars
		x[i-1]=line[i];
	x[strlen(line)-2] = '\0';
	int a = atoi(x);
	a++; 	//incrementing the int
	printf("%d",a);
	sprintf(x,"%d",a);
	printf("%s",x);


	FILE *temp = fopen("temp.csv","w");
	if(!temp)//temp==NULL->file cannot be opened
	{
		printf("ERROR: Delete Operation failed\n");
		return 0;
	}

	putc('#',temp); 
	for(int i=0;x[i];i++)
		putc(x[i],temp);
	putc('#',temp);
	putc('\n',temp);
	fseek(fptr,1,SEEK_CUR);//move to the next line

	while(fscanf(fptr,"%[^\n]",line)!=EOF)
	{
		fputs(line,temp);
		putc('\n',temp);
		fseek(fptr,1,SEEK_CUR);//move to the next line
	}

	printf("Enter the following details\nName\n");  //name
	scanf("%[^\n]",name);
	getchar();
	fputs(name,temp);
	putc(',',temp);
	while(1)  //phone
	{
		printf("Phone Number\n");
		scanf("%[^\n]",phone);
		getchar();
		if(strlen(phone)==10)
			break;
		else
			printf("ERROR: Please enter 10 digit phone number\n");
	}
	fputs(phone,temp);
	putc(',',temp);
	while(1)          //Email
	{
		printf("Email ID\n");
		scanf("%[^\n]",email);
		getchar();
		if(strstr(email,".com"))
		{
			if(strchr(email,'@'))
			{
				fputs(email,temp);
				putc(',',temp);
				break;
			}
			else
				printf("ERROR: Please enter valid email id\n");
		}
		else if(strlen(email)==0)
		{
			putc(',',temp);
			break;
		}
		else
			printf("ERROR: Please enter valid email id\n");
	}
	printf("Location\n"); //location
	scanf("%[^\n]",address);
	getchar();
	fputs(address,temp);
	putc('\n',temp);

	fclose(fptr);
	fclose(temp);
	rename("temp.csv",fname);
}

return_t search(FILE *fptr,char *name)
{
	if(is_file_empty(fptr))// check if file empty -> abort
		return 0; 

	//"not empty"
	int flag=1; //if data present / not
	char line[60];  //show all possible matches

	//searching
	while(fscanf(fptr,"%[^\n]",line)!=EOF)
	{
		if(strstr(line,name))//if the data matches with the line
		{
			if(flag)//print only once
			{
				printf("\n...All possible matches...\n");
				flag=0;
			}
			printf("%s\n",line);
		}
		fseek(fptr,1,SEEK_CUR);//move to the next line
	}
	if(flag)  //when data not found
	{
		printf("...Sorry, not such contact found...\n");
		return 0;
	}
	return 1;
}

return_t del_t(FILE *fptr,char *fname)
{
	//deleting line
	char name[20],phone[12],line[60],x[8],ch;  //search by name && phone no //show all possible matches
	printf("Enter the name and phone no to be searched\n");
	scanf("%[^\n]",name);
	getchar();
	scanf("%[^\n]",phone);
	getchar();
	printf("Are you sure you want to delete this contact (y/n)\n");//double checking
	scanf("%c",&ch);
	getchar();

	if(ch == 'y' || ch == 'Y')  //deletr
	{
		if(search(fptr,name) && search(fptr,phone))//if contact present 
		{
			//decrementing the int in the 1st line
			rewind(fptr);//resetting the curser
			fscanf(fptr,"%[^\n]",line); //reading 1st line
			for(int i=1;i<strlen(line)-1;i++)//reading only the int chars
				x[i-1]=line[i];
			x[strlen(line)-2] = '\0';
			int a = atoi(x);
			a--;
			sprintf(x,"%d",a);
			FILE *temp = fopen("temp.csv","w");
			if(!temp)//temp==NULL->file cannot be opened
			{
				printf("ERROR: Delete Operation failed\n");
				return 0;
			}
			putc('#',temp); 
			for(int i=0;x[i];i++)
				putc(x[i],temp);
			putc('#',temp);
			putc('\n',temp);
			fseek(fptr,1,SEEK_CUR);//move to the next line

			while(fscanf(fptr,"%[^\n]",line)!=EOF)
			{
				if(strstr(line,phone)==0 && strstr(line,name)==0)
				{
					fputs(line,temp);
					putc('\n',temp);
				}
				else if(strstr(line,phone)==0 && strstr(line,name))
				{
					fputs(line,temp);
					putc('\n',temp);
				}
				fseek(fptr,1,SEEK_CUR);//move to the next line
			}
			fclose(fptr);
			fclose(temp);
			rename("temp.csv",fname);

		}
	}
	else         //don't want to delete
		return K_FAIL;
}

return_t print(FILE *fptr)
{
	if(is_file_empty(fptr))// check if file empty -> abort
		return K_FAIL;       
	char line[60];
	while(fscanf(fptr,"%[^\n]",line)!=EOF)
	{
		printf("%s\n",line);
		fseek(fptr,1,SEEK_CUR);
	}
}

return_t is_file_empty(FILE *fptr)
{
	fseek(fptr,0,SEEK_SET);//repositioning the cursser
	char line1[4];
	if(fscanf(fptr,"%[^\n]",line1)==EOF || line1[1]=='0' || line1[1]=='\0')//checking if empty
	{
		printf("ERROR: File is eimpty\n");
		return 1;
	}
	return 0;// when file not empty
}
