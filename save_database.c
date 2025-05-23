#include "inverted_search.h"

/* to save the data into file */
void save_database(HASH_TABLE *hash)
{
    char filename[30];
    printf("Enter the file name<.txt> : ");
    scanf(" %s", filename);

    char *ptr = &filename[(strlen(filename) - 4)];

	if (strcmp(ptr, ".txt") != 0)
    {
        printf("ERROR: %s is not <.txt> file\n", filename);
        return;
    }
    
    FILE *fptr = fopen(filename, "w");
    if(fptr == NULL)
    {
        printf("ERROR: %s is not opened\n", filename);
        return;
    }

    MAIN_NODE *temp_main;
    SUB_NODE *temp_sub;

    for(int i=0; i<28; i++)
    {
        if(hash[i].link != NULL)
        {
            fprintf(fptr, "#%d;", i);
            temp_main = hash[i].link;
            while(temp_main != NULL)
            {
                fprintf(fptr, "%s;%d;", temp_main->word, temp_main->filecount);
                temp_sub = temp_main->sub_link;
                while(temp_sub != NULL)
                {
                    fprintf(fptr, "%s;%d;", temp_sub->filename, temp_sub->word_count);
                    temp_sub = temp_sub->sub_link;
                }
                temp_main = temp_main->main_link;
            }
            fprintf(fptr, "%s\n", "#");
        }
    }
    fclose(fptr);
    system("clear");
}