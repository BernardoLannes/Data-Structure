# Data Structures

This repository contains exercises and projects developed during the **Data Structures** course at the Federal Fluminense University (UFF). The main objective is to apply and solidify fundamental data structure concepts, developing efficient and scalable solutions to various problems.

# Contents

## **Linked Lists**
  #### `list *create_node(int n)`
  - **Creates** a new list node with value `n` and initializes `next` to `NULL`.
  - **Returns:** Pointer to the new node.

  #### `void append_node(list **head, int n)`
  - **Adds** a new node with value `n` to the end of the list. If the list is empty, it creates the first node.
  - **Parameters:** Pointer to the list head.

  #### `void print_list(list *head)`
  - **Prints** all elements of the list followed by `NULL`. Uses recursion to traverse the list.
  - **Parameters:** Pointer to the list head.

  #### `void free_list(list *head)`
  - **Frees** memory for all nodes in the list using recursion.
  - **Parameters:** Pointer to the list head.

  #### `int exists(list *head, int n)`
  - **Checks** if the value `n` exists in the list. Returns 1 if found, 0 otherwise.
  - **Parameters:** Pointer to the list head.

  #### `int sum_list(list *head)`
  - **Sum** all data in the list.
  - **Parameters:** Pointer to the list head.
  - **Returns:** An int with the sum.

  #### `element_occurrence(list *head, int n)`
  - **Count** all the occurrences of an element 'n' in the list.
  - **Parameters:** Pointer to the list head,the element 'n'.
  - **Returns:** An int with the number of occurrences.


  #### `list *pop(list *head, int n)`
  - **remove** all nodes that contains a data 'n' in the list.
  - **Parameters:** Pointer to the list head.
  - **Returns:** An int with the sum.


## Technologies

- Language: **C/C++**.

## How to Use

1. Clone the repository:
   ```bash
   git clone https://github.com/BernardoLannes/Data-Structure.git
