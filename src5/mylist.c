#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node
{
    char word[80];
    struct node *next;
}
node;

int add_value(node **list, char *input);
int print_values(node *list);
int unload(node *list);

int main(void)
{
    node *list = NULL;

    add_value(&list, "Hello, ");
    add_value(&list, "World!");

    print_values(list);

    unload(list);

    return 0;
}

int add_value(node **list, char *input)
{
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    strcpy(n->word, input);
    n->next = *list;
    *list = n;

    return 0;
}

int print_values(node *list)
{
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        printf("Value = %s\n", tmp->word);
    }

    return 0;
}

int unload(node *list)
{
    node *tmp;

    while (list != NULL)
    {
        tmp = list->next;
        free(list);
        list = tmp;
    }

    return 0;
}