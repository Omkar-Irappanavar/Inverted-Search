#include "inverted_search.h"

void insert_at_last(Slist **head, char *data)
{
    Slist *new = malloc(sizeof(Slist));
    if(new == NULL)
    {
        printf("ERROR: Node not created\n");
        return;
    }
    strcpy(new->filename, data);
    new->filelink = NULL;

    if(*head == NULL)
    {
        *head = new;
    }
    else
    {
        Slist *temp = *head;
        while(temp->filelink != NULL)
        {
            temp = temp->filelink;
        }
        temp->filelink = new;
    }
}

