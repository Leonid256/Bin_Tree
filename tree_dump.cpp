#include "tree.hpp"

//----------------------------------------------------------------------------
FILE* open_graph_file(const char* const graph_file_name)
{
    return fopen(graph_file_name, "w");
}

//----------------------------------------------------------------------------
void close_graph_file(FILE* file)
{
    assert(file != NULL);

    fclose(file);
}

//----------------------------------------------------------------------------
void graph_dump_node(FILE* file, tree_node_t* node, int depth, tree_node_t* current)
{
    if (!node) return;

    const char* colour = "lightgrey";
    if (node -> left == NULL || node -> right == NULL) colour = "green";
    if (node -> left == NULL && node -> right == NULL) colour = "lightgreen";
    if (node -> parent == NULL) colour = "lightblue";
    if ((node -> left  && node -> left -> parent  != node) || (node -> right && node -> right -> parent != node))
        colour = "red";
    if (node == current) colour = "yellow";

    fprintf(file, "\tn_%p [style = filled, fillcolor = %s, label = \"{ %p | DATA = %d | PARENT = %p | { <l> LEFT = %p | <r> RIGHT = %p}}\"];\n",
                (void*)node, colour, (void*)node, node -> data, (void*)node -> parent, (void*)node -> left, (void*)node -> right);

    if (node -> left)
    {
        fprintf(file, "\tn_%p:l -> n_%p;\n", (void*)node, (void*)node -> left);
        graph_dump_node(file, node -> left, depth + 1, current);
    }
    else
    {
        fprintf(file, "\tnl_%p [style = invis, label = \"\", width = 0];\n", (void*)node);
        fprintf(file, "\tn_%p:l -> nl_%p [style = invis];\n", (void*)node, (void*)node);
    }

    if (node -> right)
    {
        fprintf(file, "\tn_%p:r -> n_%p;\n", (void*)node, (void*)node -> right);
        graph_dump_node(file, node -> right, depth + 1, current);
    }
    else
    {
        fprintf(file, "\tnr_%p [style = invis, label = \"\", width = 0];\n", (void*)node);
        fprintf(file, "\tn_%p:r -> nr_%p [style = invis];\n", (void*)node, (void*)node);
    }
}

//----------------------------------------------------------------------------
void dump_tree(FILE* file, tree_t* tree, tree_node_t* current)
{
    assert(file && tree);

    fprintf(file, "digraph Tree\n{\n");
    fprintf(file, "\tordering = out;\n");
    fprintf(file, "\tnode [shape = record];\n");

    graph_dump_node(file, tree -> root, 0, current);

    fprintf(file, "}\n");
}

