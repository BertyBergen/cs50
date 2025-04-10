#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} node;

typedef struct hash_set {
    int *table;
    int size;
} hash_set;

node *add_to_list(node **head, int value);
void remove_similar(node *head);
void print_list(node *head);
void free_list(node *head);
hash_set *create_hash_set(int size);
void insert_hash_set(hash_set *set, int value);
int contains(hash_set *set, int value);

int main()
{
    node *head = NULL;
    int value;

    printf("Enter only numbers \n:");
    
    while (scanf("%i", &value) == 1)
    {
        add_to_list(&head, value);
    }

    printf("Your linked list before removing duplicates: \n");
    print_list(head);

    remove_similar(head);

    printf("Your linked list after removing duplicates: \n");
    print_list(head);

    free_list(head);
    return 0;
}

node *add_to_list(node **head, int value)
{
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        printf("Memory allocation error\n");
        return NULL;
    }

    new_node->value = value;
    new_node->next = *head;
    *head = new_node;

    return new_node;
}

void remove_similar(node *head)
{
    hash_set *set = create_hash_set(1000);  // Assuming 1000 unique values max
    node *current = head;
    node *prev = NULL;

    while (current != NULL)
    {
        if (contains(set, current->value))
        {
            prev->next = current->next;
            free(current);
            current = prev->next;
        }
        else
        {
            insert_hash_set(set, current->value);
            prev = current;
            current = current->next;
        }
    }

    free(set->table);
    free(set);
}

hash_set *create_hash_set(int size)
{
    hash_set *set = malloc(sizeof(hash_set));
    set->size = size;
    set->table = calloc(size, sizeof(int));
    return set;
}

void insert_hash_set(hash_set *set, int value)
{
    int index = value % set->size;
    set->table[index] = 1;
}

int contains(hash_set *set, int value)
{
    int index = value % set->size;
    return set->table[index] == 1;
}

void print_list(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("[%i] -> ", current->value);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(node *head)
{
    node *current = head;
    node *next_node;
    while (current != NULL)
    {
        next_node = current->next;
        free(current);
        current = next_node;
    }
}
