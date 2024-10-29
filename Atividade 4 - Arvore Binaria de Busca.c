#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#else
#endif

typedef struct tree_node
{
    int data;
    struct tree_node *left;
    struct tree_node *right;

} tree_node;

void clearScreen();
void mySleep(int tempoMs);

tree_node *create_tree_node(int data);
tree_node *insert_tree_node(tree_node *root, int data);
tree_node *read_tree(FILE *file);
void free_tree(tree_node *root);

int count_elements(tree_node *root, int element);
int height(tree_node *root);
int count_nodes(tree_node *root);
int find_height(tree_node *root, int value);

int is_in_tree(tree_node *root, int value);
int is_balanced(tree_node *root);
int is_full(tree_node *root);

void print_tree(tree_node *root, int mode);
void print_leaf_nodes(tree_node *root);
void print_level(tree_node *root, int level);
void traversal_print(tree_node *root);
void print_leafs_under(tree_node *root, int value);

int menu(tree_node **root);

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
    case 4: // Length
        traversal_print(root);
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

    if (value > root->data)
    {
        is_in_tree(root->right, value);
    }

    is_in_tree(root->left, value);
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

int height(tree_node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    int lHeight = height(root->left);
    int rHeight = height(root->right);

    return (lHeight > rHeight ? lHeight : rHeight) + 1;
}

int is_balanced(tree_node *root)
{
    if (root == NULL)
    {
        return 1;
    }

    if (abs(height(root->left) - height(root->right)) > 1)
    {
        return 0;
    }

    return (is_balanced(root->left) && is_balanced(root->right));
}

int count_nodes(tree_node *root)
{
    if (root == NULL)
    {
        return 0;
    }

    return 1 + count_nodes(root->left) + count_nodes(root->right);
}

int is_full(tree_node *root)
{
    if (root != NULL)
    {
        int nElements = count_nodes(root);
        int nHeight = height(root);

        if (nElements != (1 << nHeight) - 1)
        {
            return 0;
        }
    }

    return 1;
}

void print_level(tree_node *root, int level)
{
    if (root == NULL)
    {
        return;
    }

    if (level == 1)
    {
        printf("%d ", root->data);
    }
    else if (level > 1)
    {
        print_level(root->left, level - 1);
        print_level(root->right, level - 1);
    }
}

int find_height(tree_node *root, int value)
{
    if (root == NULL)
    {
        return -1;
    }
    if (root->data == value)
    {
        return 0;
    }

    int height = 0;

    if (value > root->data)
    {
        height = find_height(root->right, value);
    }

    height = find_height(root->right, value);

    return (height == -1) ? -1 : height + 1;
}

void traversal_print(tree_node *root)
{
    int temp = height(root);

    for (int i = 1; i <= temp; i++)
    {
        print_level(root, i);
        printf("\n");
    }
}

void print_leafs_under(tree_node *root, int value)
{
    if (root == NULL)
    {
        return;
    }

    if (root->data < value && root->left == NULL && root->right == NULL)
    {
        printf("%d ", root->data);
    }

    print_leafs_under(root->left, value);
    print_leafs_under(root->right, value);
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
    printf("\t4. Imprimir nivel de um no\n");
    printf("\t5. Imprimir folhas menores que um valor\n"); //
    printf("\t6. Inserir um no\n");                        //
    printf("\t7. Remover um no\n");                        //
    printf("\t8. Sair\n");

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
        printf("\t4. Em largura\n");

        printf("\nSelecione a opcao: ");
        scanf("%d", &temp);
        fflush(stdin);

        mySleep(200);
        clearScreen();
        printf("Arvore:\n");
        print_tree(*root, temp);
        printf("\nAperte enter...");
        getchar();
        getchar();
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
        getchar();
        getchar();
        break;
    case 4:
        printf("No procurado: ");
        scanf("%d", &temp);

        temp = find_height(*root, temp);

        if (temp != -1)
        {
            print_level(*root, temp - 1);
        }
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
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
