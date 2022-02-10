// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
node *cursor;


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //printf("Starting load();\n");
    // Open dictionary file
    FILE *dict_ptr = fopen(dictionary, "r");
    if (dict_ptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return 1;
    }

    // initialize table
    table[N - 1] = NULL;

    char dict_word[LENGTH];
    unsigned int index = 0;
    int len;

    while (fgets(dict_word, LENGTH + 1, dict_ptr) != NULL)
    {
        //printf("dict_word read from file: %s\n", dict_word);
        // remove \n from dict_word
        len = strlen(dict_word);
        if (dict_word[len - 1] == '\n')
        {
            dict_word[len - 1] = '\0';
        }

        if (strcmp(dict_word, "\n") != 0 && strcmp(dict_word, "\0") != 0)
        {
            // get hash value of word
            index = hash(dict_word);

            //create new node
            node *n = NULL;
            n = calloc(1, sizeof(node));
            if (n == NULL)
            {
                fprintf(stderr, "Could not create memory in load()\n");
                unload();
                return false;
            }

            strcpy(n->word, dict_word);
            n->next = table[index];

            table[index] = n;
            //printf("Added %s to the dictionary\n", table[index]->word);

            // increment size of dictionary
            //size();
        }
    }

    //printf("Closing dictionary file\n");
    fclose(dict_ptr);

    return true;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //printf("Starting check()\n");

    // get word hash
    unsigned int index = hash(word);

    cursor = table[index];

    //printf("Beginning traversal in check()\n");
    while (cursor != NULL)
    {
        //printf("Word = %s, Dictionary word = %s\n", word, cursor->word);
        if (strcasecmp(cursor->word, word) == 0)
        {
            //printf("found match\n");
            return true;
        }
        else
        {
            // word not found yet
            //printf("no match\n");
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int i = 0;
    //printf("Starting hash()\n");
    //printf("word = %s\n", word);
    if (islower(word[0]))
    {
        i = word[0] - 97;
    }
    else if (isupper(word[0]))
    {
        i = word[0] - 65;
    }

    //printf("index = %i\n", i);
    return i;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //printf("Starting size()\n");
    // static unsigned int count = -1;
    // count++;

    node *tmp;
    unsigned int count = 0;

    for (int i = 0; i < N; i++)
    {
        tmp = table[i];
        while (tmp != NULL)
        {
            count++;
            tmp = tmp->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //printf("Starting unload()\n");
    node *tmp;
    int count = 0;

    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            tmp = table[i]->next;
            //printf("Freeing %s\n", table[i]->word);
            free(table[i]);
            table[i] = tmp;
            count++;
        }
    }

    //printf("Unloaded %i nodes\n", count);
    return true;
}
