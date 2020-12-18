#include <stdio.h>
#include <string.h>
#include <libc.h>

//Size of the Map
#define HASH_TABLE_SIZE 5000

struct hash_node{
    int key;
    char *value;
};

struct hash_node *hash_table[HASH_TABLE_SIZE];
//char *key;

int store();
int retrieve();
int del();
int hash_code(char *);

void clr();

int main(int argc, char **argv) {
    char input[10];
    while (1){
        scanf("%s",input);
        if (strcmp(input,"STOP") == 0){
            break;
        }
        else if(strcmp(input,"STR") == 0){
            store();
        }
        else if(strcmp(input,"GET")== 0){
            retrieve();
        }
        else if(strcmp(input,"DEL")== 0){
            del();
        }
        else if(strcmp(input,"CLR")== 0){
            clr();
        }
        else{
            printf("\nEnter a valid command");
        }
    }
    return 0;
}

void clr() {
    for(int i = 0 ; i < HASH_TABLE_SIZE ; i++)
    {
        if(hash_table[i] != NULL)
        {
            if(hash_table[i]->value != NULL);
            {
                free(hash_table[i]->value);
            }
            free(hash_table[i]);
        }
        hash_table[i] = NULL;
    }
}

int del() {
    char key_delete[10];
    printf("\nEnter your key:");
    scanf("%s",key_delete);

    int key_hash = hash_code(key_delete);

    if(hash_table[key_hash] == NULL){
        printf("\nNode does not exist\n");
        return -1;
    }
    else{
        if(hash_table[key_hash]->value != NULL)
        {
            free(hash_table[key_hash]->value);
        }
        free(hash_table[key_hash]);
        hash_table[key_hash] = NULL;
        printf("\nNode Deleted\n");
    }
    return 0;
}

int retrieve() {
    char key[10];
    printf("\nEnter the key to be retrieved:");
    scanf("%s",key);

    int key_hash = hash_code(key);
    struct hash_node *node = hash_table[key_hash];

    if(node == NULL){
        printf("\nNode does not exist\n");
    }
    else
        {
        printf("\n%s",hash_table[key_hash]->value);
    }

    return 0;
}

int hash_code(char *s)
{
    int hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31*hashval;
    return hashval % HASH_TABLE_SIZE;
}

//int hash_code(char *key,int len){
//    char *temp = key;
//    int sum = 0;
//    for(int i = 0; i <len; i++){
//        sum = sum + temp;
//        temp++;
//    }
//    return sum % HASH_TABLE_SIZE;
//}

int store() {
    int size;
    char key[10];
    printf("\nEnter the size of the item: ");
    scanf("%d",&size);

    printf("\nEnter the key: ");
    scanf("%s",key);

    //Checking the size of the item
    if(size<1){
        return -1;
    }

    char *string = (char *)malloc(size);
    //Checking if a Malloc Call is successful
    if(string == NULL){
        return -1;
    }

    printf("\nEnter the String: ");
    scanf("%s",string);

    int key_hash = hash_code(key);
    struct hash_node *node = hash_table[key_hash];

    if(node == NULL)
    {
        hash_table[key_hash] = (struct hash_node *)malloc(sizeof(struct hash_node));
        if(hash_table[key_hash] == NULL ){
            return -1;
        }
        hash_table[key_hash]->key = key;
        hash_table[key_hash]->value = string;
        //node = hash_table[key_hash];
        printf("\nNew Node is Created\n");
    } else{
        free(hash_table[key_hash]->value);
        hash_table[key_hash]->value = string;
        printf("\nOld Node is replaced\n");
    }

    return 0;
}
