#include "inverted_search.h"

/* to retrieve previously stored data from file */
void update_database(HASH_TABLE *hash, Slist **head)
{
    char filename[20];
    printf("Enter the file name <.txt> : ");
    scanf(" %s", filename);

    char *ptr = &filename[(strlen(filename) - 4)];

    if (strcmp(ptr, ".txt") != 0)
    {
        printf("%s is not <.txt> file\n", filename);
        return;
    }

    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("%s is not available\n", filename);
        return;
    }

    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) < 2)
    {
        printf("%s is Empty file\n", filename);
        return;
    }
    rewind(fptr);
    
    if(fgetc(fptr) == '#')
    {
        fseek(fptr, -2, SEEK_END);
        if(fgetc(fptr) != '#')
        {
            printf("ERROR: %s file is not valid data file\n", filename);
            return;
        }
    }
    else
    {
        printf("ERROR: %s file is not valid data file\n", filename);
        return;
    }
    rewind(fptr);

    char buf[512];
    char *token = NULL;

    MAIN_NODE *prev_main_node = NULL;
    while(fscanf(fptr, "%s\n", buf) > 0)        // reading data from file line by line
    {
        token = strtok(buf, "#;");      // index
        
        int index = atoi(token);
        
        token = strtok(NULL, "#;");    // word
        
        while(token != NULL)                       // creating mainnodes based on words availability
        {  
            MAIN_NODE *main_node = malloc(sizeof(MAIN_NODE));
            if(main_node == NULL)
            {
                printf("ERROR: Main node creation failed\n");
                return;
            }
            main_node->main_link = NULL;
            main_node->sub_link = NULL;

            if(hash[index].link == NULL)
            {
                hash[index].link = main_node;
            }
            else
            {
                prev_main_node->main_link = main_node;      // gives error on second time updating
            }
            
            strcpy(main_node->word, token);
            
            token = strtok(NULL, "#;");     // file count
            
            main_node->filecount = atoi(token);
            
            SUB_NODE *prev_sub_node = NULL;
            for(int i=0; i<main_node->filecount; i++)               // creating subnodes for one mainnode
            {
                SUB_NODE *sub_node = malloc(sizeof(SUB_NODE));
                if(sub_node == NULL)
                {
                    printf("ERROR: Sub node creation failed\n");
                    return;
                }
                sub_node->sub_link = NULL;
                
                token = strtok(NULL, "#;");     // file name
                
                delete_element(head, token);

                strcpy(sub_node->filename, token);
                
                token = strtok(NULL, "#;");     // word count
                
                sub_node->word_count = (atoi(token));
                
                if(main_node->sub_link == NULL)
                {
                    main_node->sub_link = sub_node;
                }
                else
                {
                    prev_sub_node->sub_link = sub_node;
                }
                
                prev_sub_node = sub_node;
            }   
            prev_main_node = main_node;
            token = strtok(NULL, "#;");    // word    
        }
    }
    fclose(fptr);
}


void delete_element(Slist **head, char *token)
{
    Slist *temp = *head;
    if(temp == NULL)
    {
        return;
    }

    Slist *prev=NULL;
    while(temp != NULL)
    {
        if( strcmp(temp->filename, token)!=0 )
        {
            prev = temp;
            temp=temp->filelink;
        }
        else
        {
            if(prev == NULL)
            {
                (*head) = temp->filelink;
            }
            else
            {
                prev->filelink = temp->filelink;
            }
            free(temp);
            return;
        }
    }
}