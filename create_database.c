#include "inverted_search.h"

extern int update_create_flag;

/* to insert data into hashtable */
void create_database(HASH_TABLE *hash_table, Slist *head)
{
	FILE *fptr = NULL;
	char buf[20];

	if(head == NULL)
	{
		printf("INFO: List is Empty\n");
		return;
	}
	while (head != NULL)
	{
		fptr = fopen(head->filename, "r");
		if (fptr == NULL)
		{
			printf("%s file not opened\n", head->filename);
			head = head->filelink;
			continue;
		}

		int temp_index;
		while (fscanf(fptr, "%s", buf) != -1)
		{
			if (buf[0] >= 'A' && buf[0] <= 'Z')
				temp_index = buf[0] - 'A';
			else if (buf[0] >= 'a' && buf[0] <= 'z')
				temp_index = buf[0] - 'a';
			else if (buf[0] >= '0' && buf[0] <= '9')
				temp_index = 26;
			else
				temp_index = 27;

			if (hash_table[temp_index].link == NULL)
			{
				MAIN_NODE *new_main = malloc(sizeof(MAIN_NODE));
				if (new_main == NULL)
				{
					printf("ERROR: Main node Creation failed\n");
					return;
				}
				new_main->filecount = 1;
				strcpy(new_main->word, buf);
				new_main->sub_link = NULL;
				new_main->main_link = NULL;

				hash_table[temp_index].link = new_main;

				SUB_NODE *new_sub = malloc(sizeof(SUB_NODE));
				if (new_sub == NULL)
				{
					printf("ERROR: Sub node creation failed\n");
					return;
				}
				new_sub->word_count = 1;
				strcpy(new_sub->filename, head->filename);
				new_sub->sub_link = NULL;

				new_main->sub_link = new_sub;
			}
			else
			{
				MAIN_NODE *main_temp = hash_table[temp_index].link, *prev_main = NULL;
				int main_match_flag = 0;
				while (main_temp != NULL)
				{
					int sub_match_flag = 0;
					if (strcmp(main_temp->word, buf) == 0)
					{
						main_match_flag = 1;
						SUB_NODE *sub_temp = main_temp->sub_link;
						while (sub_temp->sub_link != NULL)
						{
							if (strcmp(sub_temp->filename, head->filename) == 0)
							{
								sub_match_flag = 1;
								sub_temp->word_count++;
								break;
							}

							sub_temp = sub_temp->sub_link;
						}

						if (sub_match_flag == 1)
							break;
						else
						{
							if (strcmp(sub_temp->filename, head->filename) == 0)
							{
								sub_temp->word_count++;
								break;
							}
							else
							{
								SUB_NODE *sub_node = malloc(sizeof(SUB_NODE));
								if (sub_node == NULL)
								{
									printf("ERROR: Child sub node creation failed\n");
									return;
								}
								sub_node->word_count = 1;
								strcpy(sub_node->filename, head->filename);
								sub_node->sub_link = NULL;

								sub_temp->sub_link = sub_node;
								main_temp->filecount++;
								break;
							}
						}
					}
					prev_main = main_temp;
					main_temp = main_temp->main_link;
				}
				if (main_match_flag == 0)
				{
					MAIN_NODE *new_main = malloc(sizeof(MAIN_NODE));
					if (new_main == NULL)
					{
						printf("ERROR: Main node Creation failed\n");
						return;
					}
					new_main->filecount = 1;
					strcpy(new_main->word, buf);
					new_main->sub_link = NULL;
					new_main->main_link = NULL;
					prev_main->main_link = new_main;

					SUB_NODE *new_sub = malloc(sizeof(SUB_NODE));
					if (new_sub == NULL)
					{
						printf("ERROR: Sub node creation failed\n");
						return;
					}
					new_sub->word_count = 1;
					strcpy(new_sub->filename, head->filename);
					new_sub->sub_link = NULL;

					new_main->sub_link = new_sub;
				}
			}
		}
		fclose(fptr);
		head = head->filelink;
	}
}
