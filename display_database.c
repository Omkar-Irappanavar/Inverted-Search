#include "inverted_search.h"

/* to display hashtable data */
void display_database(HASH_TABLE *hash_table)
{
    int empty_flag=0;
    for(int i=0; i<28; i++)
    {
        if(hash_table[i].link != NULL)
        {
            empty_flag=1;
            break;
        }
    }
    if(empty_flag==0)
    {
        printf("INFO: Hash table is empty\n");
        return;
    }
   
    printf("----------------------------------------------------------\n");
    printf("Index\tword\tfilecount\tfilename\twordcount\n");
    HASH_TABLE *temp_hash=hash_table;
    MAIN_NODE *temp_main=NULL;
    SUB_NODE *temp_subnode=NULL;
    
    for(int i=0; i<28; i++)
    {
        if(temp_hash[i].link != NULL)
        {
            
            temp_main = temp_hash[i].link;
            while(temp_main != NULL)
            {
                temp_subnode = temp_main->sub_link;
                printf("----------------------------------------------------------\n");
                printf("%d\t%s\t%d\t\t%s\t\t%d\n", temp_hash[i].index, temp_main->word, temp_main->filecount, temp_subnode->filename, temp_subnode->word_count);
                temp_subnode = temp_subnode->sub_link;
                while(temp_subnode != NULL)
                {
                    printf("\t\t\t\t%s\t\t%d\n", temp_subnode->filename, temp_subnode->word_count);
                    temp_subnode = temp_subnode->sub_link;
                }
                temp_main = temp_main->main_link;
            }
        }
    }
    printf("----------------------------------------------------------\n");
}