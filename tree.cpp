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
tree_status delete_node(tree_node_t* node)
{
    assert(node != NULL);

    node -> data = POIZON_VALUE;
    node -> parent = NULL;
    node -> left = NULL;
    node -> right = NULL;
    free(node);
    node = NULL;

    return TREE_OK;
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