#include "tree.hpp"

//----------------------------------------------------------------------------
tree_status tree_init(tree_t* tree)
{
    assert(tree != NULL);

    tree_node_t* root = new_node();
    if (root)
        tree -> root = root;
    else
    {
        printf(RED "Error in tree_init\n" CRESET);
        return TREE_ERROR;
    }
    
    tree -> size = 1;

    return TREE_OK;
}

//----------------------------------------------------------------------------
tree_node_t* new_node()
{
    tree_node_t* node = (tree_node_t*) calloc(1, sizeof(tree_node_t));
    if (node == NULL)
    {
        printf(RED "Error in new_node\n" CRESET);
        return NULL;
    }

    tree_elem_t data = 0;
    scanf(" %d", &data);

    node -> data = data;
    node -> left = NULL;
    node -> right = NULL;
    node -> parent = NULL;

    return node;
}

//----------------------------------------------------------------------------
tree_status link_left(tree_node_t* node_left, tree_node_t* node_parent)
{
    assert(node_left != NULL);
    assert(node_parent != NULL);

    node_parent -> left = node_left;
    node_left -> parent = node_parent;

    return TREE_OK;
}

//----------------------------------------------------------------------------
tree_status link_right(tree_node_t* node_right, tree_node_t* node_parent)
{
    assert(node_right != NULL);
    assert(node_parent != NULL);

    node_parent -> right = node_right;
    node_right -> parent = node_parent;

    return TREE_OK;
}

//----------------------------------------------------------------------------
void delete_node(tree_node_t* node)
{
    assert(node != NULL);

    node -> data = POIZON_VALUE;
    node -> parent = NULL;
    node -> left = NULL;
    node -> right = NULL;
    free(node);
    node = NULL;
}

//----------------------------------------------------------------------------
void delete_subtree(tree_node_t* node)
{
    if (!node) return;

    delete_subtree(node -> left);
    delete_subtree(node -> right);

    free(node);
}

//----------------------------------------------------------------------------
tree_status dump_node(tree_node_t* node, int line)
{
    assert(node != NULL);

    printf("_______________________________\n");
    printf("dump node in %d line\n", line);
    printf("node address = <%p>\n", node);
    printf("node value   = <%d>\n", node -> data);
    printf("node parent  = <%p>\n", node -> parent);
    printf("node left    = <%p>\n", node -> left);
    printf("node right   = <%p>\n", node -> right);
    printf("_______________________________\n");

    return TREE_OK;
}


//postorder         для %d
//----------------------------------------------------------------------------
tree_node_t* post_new_node(FILE* file, tree_node_t* parent, size_t* size)
{
    tree_node_t* node = (tree_node_t*) calloc(1, sizeof(tree_node_t));
    if (node == NULL)
    {
        printf(RED "Error in post_new_node\n" CRESET);
        return NULL;
    }

    node -> parent = parent;

    char bracket = '\0';
    fscanf(file, " %c", &bracket);
    if (bracket == '(')
    {
        node -> left = post_new_node(file, node, size);
        if (!node -> left)
        {
            delete_subtree(node);
            return NULL;
        }
    }
    else
    {
        ungetc(bracket, file);
    }

    fscanf(file, " %c", &bracket);
    if (bracket == '(')
    {
        node -> right = post_new_node(file, node, size);
        if (!node -> right)
        {
            delete_subtree(node);
            return NULL;
        }
    }
    else
    {
        ungetc(bracket, file);
    }

    tree_elem_t data = 0;
    fscanf(file, " %d", &data);
    node -> data = data;
    (*size)++;

    fscanf(file, " %c", &bracket);
    if (bracket != ')')
    {
        printf(RED "Error in post_new_node\n" CRESET);
        return NULL;
    }
    
    return node;
}

//----------------------------------------------------------------------------
tree_status postorder_read(const char* const post_file, tree_t* tree)
{
    assert(post_file);

    FILE* file = fopen(post_file, "r");
    if (!file)
    {
        printf(RED "Error in postorder_read\n" CRESET);
        return TREE_ERROR;
    }

    char bracket = '\0';
    if (fscanf(file, " %c", &bracket) != 1 || bracket != '(')
    {
        printf(RED "Error in postorder_read\n" CRESET);
        fclose(file);
        return TREE_ERROR;
    }
    size_t size = 0;
    tree_node_t* root = post_new_node(file, NULL, &size);
    if (root)
    {
        tree -> root = root;
        tree -> size = size;
    }
    else
    {
        printf(RED "Error in postorder_read\n" CRESET);
        return TREE_ERROR;
    }

    fclose(file);
    return TREE_OK;
}

//inorder       для %d
//----------------------------------------------------------------------------
tree_node_t* in_new_node(FILE* file, tree_node_t* parent, size_t* size)
{
    tree_node_t* node = (tree_node_t*) calloc(1, sizeof(tree_node_t));
    if (node == NULL)
    {
        printf(RED "Error in in_new_node\n" CRESET);
        return NULL;
    }

    node -> parent = parent;

    char bracket = '\0';
    fscanf(file, " %c", &bracket);
    if (bracket == '(')
    {
        node -> left = in_new_node(file, node, size);
        if (!node -> left)
        {
            delete_subtree(node);
            return NULL;
        }
    }
    else
    {
        ungetc(bracket, file);
    }

    tree_elem_t data = 0;
    fscanf(file, " %d", &data);
    node -> data = data;
    (*size)++;

    fscanf(file, " %c", &bracket);
    if (bracket == '(')
    {
        node -> right = in_new_node(file, node, size);
        if (!node -> right)
        {
            delete_subtree(node);
            return NULL;
        }
    }
    else
    {
        ungetc(bracket, file);
    }

    fscanf(file, " %c", &bracket);
    if (bracket != ')')
    {
        printf(RED "Error in in_new_node\n" CRESET);
        return NULL;
    }
    
    return node;
}

//----------------------------------------------------------------------------
tree_status inorder_read(const char* const post_file, tree_t* tree)
{
    assert(post_file);

    FILE* file = fopen(post_file, "r");
    if (!file)
    {
        printf(RED "Error in inorder_read\n" CRESET);
        return TREE_ERROR;
    }

    char bracket = '\0';
    if (fscanf(file, " %c", &bracket) != 1 || bracket != '(')
    {
        printf(RED "Error in inorder_read\n" CRESET);
        fclose(file);
        return TREE_ERROR;
    }
    size_t size = 0;
    tree_node_t* root = in_new_node(file, NULL, &size);
    if (root)
    {
        tree -> root = root;
        tree -> size = size;
    }
    else
    {
        printf(RED "Error in inorder_read\n" CRESET);
        return TREE_ERROR;
    }

    fclose(file);
    return TREE_OK;
}

//----------------------------------------------------------------------------
size_t len_of_file(const char* name)
{
    struct stat file_info;
    stat(name, &file_info);

    if (file_info.st_size <= 0) return 0;
    else return (size_t)file_info.st_size;
}

//preorder      для char
//----------------------------------------------------------------------------
tree_status preorder_read(const char* const pre_file, tree_t* tree)
{
    assert(pre_file);
    assert(tree);

    FILE* file = fopen(pre_file, "r");
    if (!file)
    {
        printf(RED "Error in preorder_read\n" CRESET);
        return TREE_ERROR;
    }

    size_t file_size = len_of_file(pre_file);
    char* buffer_file = (char*)calloc(file_size + 2, 1);
    fread(buffer_file, 1, file_size + 2, file);
    fclose(file);

    int i = 0;
    while (isspace((unsigned char)buffer_file[i])) i++;

    if (buffer_file[i++] != '(')
    {
        printf(RED "Error in preorder_read\n" CRESET);
        free(buffer_file);
        return TREE_ERROR;
    }
    
    size_t size = 0;
    tree_node_t* root = pre_new_node(buffer_file, NULL, &size, &i);
    if (root)
        tree -> root = root;
    else
    {
        printf(RED "Error in preorder_read\n" CRESET);
        free(buffer_file);
        return TREE_ERROR;
    }
    
    tree -> size = size;

    free(buffer_file);
    return TREE_OK;
}

//----------------------------------------------------------------------------
tree_node_t* pre_new_node(char* buffer_file, tree_node_t* parent, size_t* size, int* i)
{
    tree_node_t* node = (tree_node_t*) calloc(1, sizeof(tree_node_t));
    if (node == NULL)
    {
        printf(RED "Error in pre_new_node\n" CRESET);
        return NULL;
    }

    char* buffer_data = (char*)calloc(BUFFER_SIZE, 1);

    int buf_i = 0;
    while(buffer_file[*i] != '\0' && buffer_file[*i] != '(' && buffer_file[*i] != ')')
    {
        buffer_data[buf_i++] = buffer_file[*i];
        (*i)++;
    }
    buffer_data[buf_i] = '\0';

    //node -> data = buffer_data;
    node -> parent = parent;
    (*size)++;

    while(buffer_file[*i] != '\0' && buffer_file[*i] != '(' && buffer_file[*i] != ')') (*i)++;
    if (buffer_file[*i] == ')')
    {
        node -> left = NULL;
        node -> right = NULL;
        (*i)++;
        return node;
    }
    else if (buffer_file[*i] == '(')
    {
        (*i)++;
        node -> left = pre_new_node(buffer_file, node, size, i);
        if (!node -> left)
        {
            delete_subtree(node);
            return NULL;
        }
    }
    else
    {
        printf(RED "Error in pre_new_node\n" CRESET);
        return NULL;
    }

    while(buffer_file[*i] != '\0' && buffer_file[*i] != '(' && buffer_file[*i] != ')') (*i)++;
    if (buffer_file[*i] == ')')
    {
        node -> right = NULL;
        (*i)++;
        return node;
    }
    else if (buffer_file[*i] == '(')
    {
        (*i)++;
        node -> right = pre_new_node(buffer_file, node, size, i);
        if (!node -> right)
        {
            delete_subtree(node);
            return NULL;
        }
    }
    else
    {
        printf(RED "Error in pre_new_node\n" CRESET);
        return NULL;
    }

    if (buffer_file[*i] != ')')
    {
        printf(RED "Error in pre_new_node\n" CRESET);
        return NULL;
    }
    
    (*i)++;
    return node;
}

//----------------------------------------------------------------------------
void preorder_print(const tree_node_t* node, FILE* file)    //для строк
{
    assert(node);
    assert(file);


    fprintf(file, "(");
    fprintf(file, "%s", node -> data);
    if (node -> left) preorder_print(node -> left, file);
    if (node -> right) preorder_print(node -> right, file);
    fprintf(file, ")");
}

//----------------------------------------------------------------------------
void inorder_print(const tree_node_t* node, FILE* file)     //для %d
{
    assert(node);
    assert(file);


    fprintf(file, "(");
    if (node -> left) inorder_print(node -> left, file);
    fprintf(file, "%d", node -> data);
    if (node -> right) inorder_print(node -> right, file);
    fprintf(file, ")");
}

//----------------------------------------------------------------------------
void postorder_print(const tree_node_t* node, FILE* file)   //для %d
{
    assert(node);
    assert(file);


    fprintf(file, "(");
    if (node -> left) postorder_print(node -> left, file);
    if (node -> right) postorder_print(node -> right, file);
    fprintf(file, "%d", node -> data);
    fprintf(file, ")");
}