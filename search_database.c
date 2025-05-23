#include "inverted_search.h"

/* to search a word from hashtable data */
void search_database(HASH_TABLE *hash)
{
	MAIN_NODE *temp_main;
	SUB_NODE *temp_sub;

	char word[30], search_found=0;
	printf("Enter the word: ");
	scanf(" %s", word);

	int index;
	if (word[0] >= 'A' && word[0] <= 'Z')
		index = word[0] - 'A';
	else if (word[0] >= 'a' && word[0] <= 'z')
		index = word[0] - 'a';
	else if (word[0] >= '0' && word[0] <= '9')
		index = 26;
	else
		index = 27;

	temp_main = hash[index].link;
	while(temp_main != NULL)
	{
		if( strcmp(temp_main->word, word)==0 )
		{
			search_found=1;
			temp_sub = temp_main->sub_link;
			printf("Word %s is present in %d files\n", temp_main->word, temp_main->filecount);
			while(temp_sub != NULL)
			{
				printf("In file %s %d times\n", temp_sub->filename, temp_sub->word_count);
				temp_sub = temp_sub->sub_link;
			}
		}
		if(search_found==1)
			return;

		temp_main = temp_main->main_link;
	}
	if(search_found!=1)
		printf("%s not Found\n", word);

}

/*  to check duplicate files present in list */
status check_duplicate(Slist *head, char *argv)
{
	if (head == NULL)
	{
		return SUCCESS;
	}

	while (head != NULL)
	{
		if (strcmp(head->filename, argv) != 0)
			head = head->filelink;
		else
			return FAILURE;		// duplicate file found
	}
	return SUCCESS;
}
