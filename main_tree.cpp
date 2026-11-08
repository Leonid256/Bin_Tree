#include "tree.hpp"

int main()
{
    tree_t tree;
    tree_init(&tree);

    //left side
    tree_node_t* left_node;
    tree_node_t* left_left_node;
    tree_node_t* left_right_node;
    left_node = new_node();
    link_left(left_node, tree.root);
    left_left_node = new_node();
    link_left(left_left_node, left_node);
    left_right_node = new_node();
    link_right(left_right_node, left_node);

    //right side
    tree_node_t* right_node;
    tree_node_t* right_left_node;
    tree_node_t* right_right_node;
    right_node = new_node();
    link_right(right_node, tree.root);
    right_left_node = new_node();
    link_left(right_left_node, right_node);
    right_right_node = new_node();
    link_right(right_right_node, right_node);

    DUMP_NODE(right_right_node);

    tree_node_t* current = right_right_node;
    FILE* dump_file = open_graph_file(GRAPH_FILE);
    dump_tree(dump_file, &tree, current);
    close_graph_file(dump_file);
}