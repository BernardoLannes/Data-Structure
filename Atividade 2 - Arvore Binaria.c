#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

typedef struct tree_node
{
    int data;
    struct tree_node *left;
    struct tree_node *right;

} tree_node;

tree_node *create_tree_node(int data)
{
    tree_node *new_root = (tree_node *)malloc(sizeof(tree_node));
    new_root->data = data;
    new_root->left = NULL;
    new_root->right = NULL;

    return new_root;
}

tree_node *insert_tree_node(tree_node *root, int data)
{
    if (root == NULL)
    {
        return create_tree_node(data);
    }

    if (data > root->data)
    {
        root->right = insert_tree_node(root->right, data);
    }
    else
    {
        root->left = insert_tree_node(root->left, data);
    }

    return root;
}

void free_tree(tree_node *root)
{
    if (root == NULL)
    {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void print_tree(tree_node *root, int mode)
{
    if (root == NULL)
    {
        return;
    }

    switch (mode)
    {
    case 1: // Pre-Order
        printf("%d ", root->data);
        print_tree(root->left, mode);
        print_tree(root->right, mode);
        break;
    case 2: // In-Order
        print_tree(root->left, mode);
        printf("%d ", root->data);
        print_tree(root->right, mode);
        break;
    case 3: // Post-Order
        print_tree(root->left, mode);
        print_tree(root->right, mode);
        printf("%d ", root->data);
        break;

    default:
        printf("Invalid print mode.");
        break;
    }
}

int is_in_tree(tree_node *root, int value)
{
    if (root == NULL)
    {
        return 0;
    }

    if (root->data == value)
    {
        return 1;
    }

    int result = is_in_tree(root->left, value);
    if (result == 1)
    {
        return 1;
    }
    return is_in_tree(root->right, value);
}

tree_node *read_tree(FILE *file)
{
    char c;
    int num;

    fscanf(file, "%c", &c);
    fscanf(file, "%d", &num);

    if (num == -1)
    {
        fscanf(file, "%c", &c);
        return NULL;
    }

    tree_node *new_root = (tree_node *)malloc(sizeof(tree_node));
    new_root->data = num;
    new_root->left = read_tree(file);
    new_root->right = read_tree(file);
    fscanf(file, "%c", &c);
    return new_root;
}

int count_elements(tree_node *root, int element)
{
    if (root == NULL)
    {
        return 0;
    }

    return (root->data == element) + count_elements(root->left, element) + count_elements(root->right, element);
}

void print_leaf_nodes(tree_node *root)
{
    if (root == NULL)
    {
        return;
    }

    if (root->left == NULL && root->right == NULL)
    {
        printf("%d ", root->data);
        return;
    }

    print_leaf_nodes(root->left);
    print_leaf_nodes(root->right);
}

int menu(tree_node **root)
{
    int temp;
    char aux[50];

    system("cls");
    printf("Opcoes:\n\n");
    printf("\t1. Ler arvore de arquivo\n");
    printf("\t2. Imprimir arvore\n");
    printf("\t3. Verificar se um dado esta na arvore\n");
    printf("\t4. Contar numero de elementos da arvore\n");
    printf("\t5. Imprimir os nos folhas\n");
    printf("\t6. Sair\n");

    printf("\nSelecione a opcao: ");
    scanf("%d", &temp);

    system("cls");

    switch (temp)
    {
    case 1:
        printf("Digite o nome do arquivo (sem extensao): ");
        char file_name[50] = "../";
        fflush(stdin);
        gets(aux);
        strcat(file_name, aux);
        strcat(file_name, ".txt");
        printf("\n\n%s\n", file_name);

        FILE *file = fopen(file_name, "rt");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo.\n");
            Sleep(500);
            break;
        }
        *root = read_tree(file);
        fclose(file);
        printf("Arquivo lido.");
        Sleep(500);
        break;
    case 2:
        printf("Escolha a opcao:\n\n");
        printf("\t1. Pre-ordem\n");
        printf("\t2. Em ordem\n");
        printf("\t3. Pos-ordem\n");

        printf("\nSelecione a opcao: ");
        scanf("%d", &temp);

        Sleep(200);
        system("cls");
        printf("Arvore:\n");
        print_tree(*root, temp);
        printf("\nAperte enter...");
        fflush(stdin);
        gets(aux);
        break;
    case 3:
        printf("Dado procurado: ");
        scanf("%d", &temp);
        if (is_in_tree(*root, temp))
        {
            printf("\nO dado esta na arvore.");
        }
        else
        {
            printf("\nO dado nao esta na arvore.");
        }
        printf("\nAperte enter...");
        fflush(stdin);
        gets(aux);
        break;
    case 4:
        printf("Dado procurado: ");
        scanf("%d", &temp);

        system("cls");
        printf("O dado aparece %d vezes na arvore", count_elements(*root, temp));
        printf("\nAperte enter...");
        fflush(stdin);
        gets(aux);

        break;
    case 5:
        printf("Nos folhas: ");
        print_leaf_nodes(*root);
        printf("\nAperte enter...");
        fflush(stdin);
        gets(aux);
        break;
    case 6:
        printf("Fechando o programa...");
        free_tree(*root);
        Sleep(1000);
        return 0;
        break;
    }
    return 1;
}

int main()
{
    tree_node *root = NULL;

    while (TRUE)
    {
        if (!menu(&root))
        {
            break;
        }
    }

    return 0;
}
