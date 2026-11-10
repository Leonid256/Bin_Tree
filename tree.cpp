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

    delete(node);
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

//----------------------------------------------------------------------------
// size_t len_of_file(const char* name)
// {
//     struct stat file_info;
//     stat(name, &file_info);

//     return file_info.st_size;
// }

//----------------------------------------------------------------------------
tree_node_t* pre_new_node(FILE* file, tree_node_t* parent)
{
    tree_node_t* node = (tree_node_t*) calloc(1, sizeof(tree_node_t));
    if (node == NULL)
    {
        printf(RED "Error in new_node\n" CRESET);
        return NULL;
    }

    tree_elem_t data = 0;
    fscanf(file, " %d", &data);

    node -> data = data;
    node -> parent = parent;

    char bracket = '\0';
    fscanf(file, " %c", &bracket);
    if (bracket == ')')
    {
        node -> left = NULL;
        node -> right = NULL;
        return node;
    }
    else if (bracket == '(')
    {
        node -> left = pre_new_node(file, node);
        if (!node -> left)
        {
            delete_subtree(node);
            return NULL;
        }
    }
    else if (bracket == '.')
        node -> left = NULL;
    else
    {
        printf(RED "Error in new_node\n" CRESET);
        return NULL;
    }

    fscanf(file, " %c", &bracket);
    if (bracket == ')')
    {
        node -> right = NULL;
        return node;
    }
    else if (bracket == '(')
    {
        node -> right = pre_new_node(file, node);
        if (!node -> right)
        {
            delete_subtree(node);
            return NULL;
        }
    }
    else if (bracket == '.')
        node -> right = NULL;
    else
    {
        printf(RED "Error in new_node\n" CRESET);
        return NULL;
    }

    fscanf(file, " %c", &bracket);
    if (bracket != ')')
    {
        printf(RED "Error in new_node\n" CRESET);
        return NULL;
    }
    
    return node;
}

//----------------------------------------------------------------------------
tree_status preorder_read(const char* const pre_file, tree_t* tree)
{
    assert(pre_file);

    FILE* file = fopen(pre_file, "r");
    if (!file)
    {
        printf(RED "Error in preorder_read\n" CRESET);
        return TREE_ERROR;
    }

    char bracket = '\0';
    if (!fscanf(file, " %c", &bracket) || bracket != '(')
    {
        printf(RED "Error in preorder_read\n" CRESET);
        return TREE_ERROR;
    }
    tree_node_t* root = pre_new_node(file, NULL);
    if (root)
        tree -> root = root;
    else
    {
        printf(RED "Error in preorder_read\n" CRESET);
        return TREE_ERROR;
    }
    
    tree -> size = 1;

    fclose(file);
    return TREE_OK;
}