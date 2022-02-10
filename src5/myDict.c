#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

typedef struct
{
    char letter;
    int count;
}
letter_count;

unsigned int size(void);

//char infile[] = "med.txt";
char infile[] = "large";
char outfile[] = "dict_counts.txt";

int main(void)
{
    letter_count dict_count[26];
    char word[LENGTH];

    for (int i = 0; i < 26; i++)
    {
        //printf("%c\n",'a' + i);
        dict_count[i].letter = 'a' + i;
        dict_count[i].count = 0;
    }

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // get word from dictionary file, check first letter, increment letter count in dict_count
    while (fgets(word, LENGTH, inptr) != NULL)
    {
        printf("%s", word);
        int index;

        if (islower(word[0]))
        {
            index = word[0] - 97;
            dict_count[index].count++;
        }
        else if (isupper(word[0]))
        {
            index = word[0] - 65;
            dict_count[index].count++;
        }
        size();
    }

    // Open output file
    FILE *outptr = fopen(outfile, "a");
    if (outptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    int total = 0;

    // output letter totals
    for (int i = 0; i < 26; i++)
    {
        total += dict_count[i].count;
        printf("%c: %i\n", dict_count[i].letter, dict_count[i].count);
        fprintf(outptr, "%c: %i\n", dict_count[i].letter, dict_count[i].count);
    }
    printf("Total Words: %i\n", total);
    printf("Total Words from size(): %i\n", size() - 1);
    fprintf(outptr, "Total Words: %i\n", total);

    fclose(inptr);
    fclose(outptr);

    return 0;
}

unsigned int size(void)
{
    static unsigned int count = 0;
    count++;

    return count;
}