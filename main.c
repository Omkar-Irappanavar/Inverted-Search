/***************************************************************************************************************************************************
 *Author	: Omkar Irappanavar
 *File		:main.c
 *Title		:Driver function
 *Description	:This function acts like the driver function for the project inverted search
 ****************************************************************************************************************************************************/
#include "inverted_search.h"

int update_create_flag;

/* Function to crdeate hashtable */
void create_hashtable(HASH_TABLE *hash, int size)
{
	for(int i=0; i<size; i++)
	{
		hash[i].index = i;
		hash[i].link = NULL;
	}
}

/* main function */
int main(int argc, char *argv[])
{
	Slist *head = NULL;

	if (argc < 2)
	{
		printf("USAGE: ./a.out <.txt>\n");
		return FAILURE;
	}

	read_and_validate_args(argc, argv, &head);

	if (head == NULL)
	{
		printf("DATABASE is Empty\n");
		return FAILURE;
	}

	HASH_TABLE hash_table[28];
	
	create_hashtable(hash_table, 28);
	char repeat='y', choice=0;

	while(repeat=='Y' || repeat=='y')
	{
		printf("\n1. Create database\n2. Display database\n3. Search database\n4. Save databse\n5. Update databse\n");
		printf("Enter your choice: ");
		scanf("%hhd", &choice);

		switch(choice)
		{
			case 1:
				/* to insert data into hashtable */
				if(update_create_flag==0 || update_create_flag==1)
				{
					create_database(hash_table, head);
					update_create_flag=2;					
				}
				break;
			case 2:
				/* to display hashtable data */
				display_database(hash_table);
				break;
			case 3:
				/* to search a word from hashtable data */
				search_database(hash_table);
				break;
			case 4:
				/* to save the data into file */
				save_database(hash_table);
				break;
			case 5:
				/* to retrieve previously stored data from file */
				if(update_create_flag==0)
				{
					update_database(hash_table, &head);
					update_create_flag=1;
				}
				break;
			default:
				printf("Invalid Choice\n");
				
		}
		printf("Do you want continue(Y/y)? : ");
		scanf(" %c", &repeat);
	}
	
}

/* Function to validate the arguments */
void read_and_validate_args(int argc, char *argv[], Slist **head)
{
	for (int i = 1; i < argc; i++)
	{

		char *ptr = &argv[i][(strlen(argv[i]) - 4)];

		if (strcmp(ptr, ".txt") == 0)
		{
			FILE *fptr = fopen(argv[i], "r");
			if (fptr == NULL)
				printf("%s is not available\n", argv[i]);
			else
			{
				fseek(fptr, 0, SEEK_END);
				if (ftell(fptr) < 2)
					printf("%s is Empty file\n", argv[i]);
				else
				{
					if (check_duplicate(*head, argv[i]) == FAILURE)
						printf("%s is already available in list\n", argv[i]);
					else
					{
						insert_at_last(head, argv[i]);
						printf("%s is successfully added to the list\n", argv[i]);
					}
				}
				fclose(fptr);
			}
		}
		else
			printf("%s is not .txt file\n", argv[i]);
	}
}
