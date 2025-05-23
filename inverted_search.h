#ifndef INVERTED_SEARCH
#define INVERTED_SEARCH

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum
{
    FAILURE,
    SUCCESS
}status;

typedef struct node
{
    char filename[30];
    struct node *filelink;
}Slist;

typedef struct Subnode
{
    int word_count;
    char filename[20];
    struct Subnode *sub_link;
}SUB_NODE;

typedef struct Mainnode
{
    int filecount;
    char word[30];
    SUB_NODE *sub_link;
    struct Mainnode *main_link;
}MAIN_NODE;

typedef struct Hashtable
{
    int index;
    MAIN_NODE *link;
}HASH_TABLE;


void read_and_validate_args(int argc,char *argv[], Slist **head);
void insert_at_last(Slist **head, char *data);
status check_duplicate(Slist *head,char *argv);
void create_database(HASH_TABLE *hash_table, Slist *head);
void display_database(HASH_TABLE *hash_table);
void search_database(HASH_TABLE *hash_table);
void save_database(HASH_TABLE *hash);
void update_database(HASH_TABLE *hash, Slist **head);
void delete_element(Slist **head, char *token);
// void create_database(FILE *filelist);
// word* create_indexlist(FILE* index_file, Word* index_list);
// void display_output(File* output_list);
// char* input_from_user(void);
// word* read_datafile(FILE *file, word* wordlist, char *filename);
// file* search (char *word, word *indexlist, file* output_list);
// word* store_word(cahr *word, char *filename, word* wordlist);
// char* string_token (char* input_string);
// void write_databasefile(word* wordlist, FILE* databasefile);


#endif