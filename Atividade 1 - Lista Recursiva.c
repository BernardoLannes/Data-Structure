#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int data;
    struct list *next;
} list;

list *create_node(int n)
{
    list *new_node = (list *)malloc(sizeof(list));
    if (new_node != NULL)
    {
        new_node->data = n;
        new_node->next = NULL;
    }

    return new_node;
}

void append_node(list **head, int n)
{
    if (*head == NULL)
    {
        *head = create_node(n);
    }
    else
    {
        if ((*head)->next == NULL)
        {
            (*head)->next = create_node(n);
        }
        else
        {
            append_node(&((*head)->next), n);
        }
    }
}

void print_list(list *head)
{
    if (head != NULL)
    {
        printf("%d -> ", head->data);
        print_list(head->next);
    }
    else
    {
        printf("NULL\n");
    }
}

void free_list(list *head)
{
    if (head != NULL)
    {
        free_list(head->next);
        free(head);
    }
}

int exists(list *head, int n)
{
    if (head == NULL)
    {
        return 0;
    }

    if (head->data == n)
    {
        return 1;
    }

    return exists(head->next, n);
}

// Exercício Proposto:

// Implementar função:
// 1. Soma todos os elementos da lista;
// 2. Contar número de ocorrências;
// 3. Remover elemento da lista.

// 1
int sum_list(list *head)
{
    if (head == NULL)
    {
        return 0;
    }

    return head->data + sum_list(head->next);
}

// 2
int element_occurrence(list *head, int n)
{
    if (head == NULL)
    {
        return 0;
    }

    if (head->data == n)
    {
        return 1 + element_occurrence(head->next, n);
    }

    return element_occurrence(head->next, n);
}

// 3
list *pop(list *head, int n)
{
    if (head == NULL)
    {
        return NULL;
    }

    head->next = pop(head->next, n);

    if (head->data == n)
    {
        list *temp = head->next;
        free(head);
        return temp;
    }

    return head;
}

int main()
{
    list *l = create_node(1);
    append_node(&l, 2);
    append_node(&l, 2);
    append_node(&l, 2);
    append_node(&l, 3);
    append_node(&l, 3);
    append_node(&l, 4);
    append_node(&l, 5);

    print_list(l);

    // Testando as funções dos exercícios propostos
    int r1 = sum_list(l);
    int r2 = element_occurrence(l, 2);
    int r3 = 3;

    l = pop(l, 3);

    print_list(l);

    printf("Resposta 1: %d\nResposta 2: %d\nResposta 3: Item removido %d\n", r1, r2, r3);

    return 0;
}