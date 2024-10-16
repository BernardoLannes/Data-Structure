#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#else
#endif

void clearScreen()
{
#ifdef __linux__
    system("clear");
#elif _Win32
    system("cls");
#else
#endif
}

void mySleep(int tempoMs)
{
#ifdef __linux__
    usleep(tempoMs * 1000);
#elif _WIN32
    Sleep(tempoMs);
#else
#endif
}

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

    clearScreen();
    printf("Opcoes:\n\n");
    printf("\t1. Ler arvore de arquivo\n");
    printf("\t2. Imprimir arvore\n");
    printf("\t3. Verificar se um dado esta na arvore\n");
    printf("\t4. Contar numero de elementos da arvore\n");
    printf("\t5. Imprimir os nos folhas\n");
    printf("\t6. Sair\n");

    printf("\nSelecione a opcao: ");
    scanf("%d", &temp);
    fflush(stdin);

    clearScreen();

    switch (temp)
    {
    case 1:
        printf("Digite o nome do arquivo (sem extensao): ");
        char file_name[50] = "../";
        scanf("%s", aux);
        fflush(stdin);
        strcat(file_name, aux);
        strcat(file_name, ".txt");
        printf("\n\n%s\n", file_name);

        FILE *file = fopen(file_name, "rt");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo.\n");
            mySleep(500);
            break;
        }
        *root = read_tree(file);
        fclose(file);
        printf("Arquivo lido.\n");
        mySleep(500);
        break;
    case 2:
        printf("Escolha a opcao:\n\n");
        printf("\t1. Pre-ordem\n");
        printf("\t2. Em ordem\n");
        printf("\t3. Pos-ordem\n");

        printf("\nSelecione a opcao: ");
        scanf("%d", &temp);
        fflush(stdin);

        mySleep(200);
        clearScreen();
        printf("Arvore:\n");
        print_tree(*root, temp);
        printf("\nAperte enter...");
        scanf("%s", aux);
        fflush(stdin);
        break;
    case 3:
        printf("Dado procurado: ");
        scanf("%d", &temp);
        fflush(stdin);
        if (is_in_tree(*root, temp))
        {
            printf("\nO dado esta na arvore.");
        }
        else
        {
            printf("\nO dado nao esta na arvore.");
        }
        printf("\nAperte enter...");
        scanf("%s", aux);
        fflush(stdin);
        break;
    case 4:
        printf("Dado procurado: ");
        scanf("%d", &temp);
        fflush(stdin);

        clearScreen();
        printf("O dado aparece %d vezes na arvore", count_elements(*root, temp));
        printf("\nAperte enter...");
        scanf("%s", aux);
        fflush(stdin);
        break;
    case 5:
        printf("Nos folhas: ");
        print_leaf_nodes(*root);
        printf("\nAperte enter...");
        scanf("%s", aux);
        fflush(stdin);
        break;
    case 6:
        printf("Fechando o programa...");
        free_tree(*root);
        mySleep(1000);
        return 0;
        break;
    }
    return 1;
}

int main()
{
    tree_node *root = NULL;

    while (1)
    {
        if (!menu(&root))
        {
            break;
        }
    }

    return 0;
}
