#include "tree.hpp"

int main()
{
    tree_t tree;
    tree.root = NULL;
    tree.size = 0;
    // tree_init(&tree);

    //preorder_read(PREORDER_FILE, &tree);
    //inorder_read(INORDER_FILE, &tree);
    postorder_read(POSTORDER_FILE, &tree);


    // //left side
    // tree_node_t* left_node;
    // tree_node_t* left_left_node;
    // tree_node_t* left_right_node;
    // left_node = new_node();
    // link_left(left_node, tree.root);
    // left_left_node = new_node();
    // link_left(left_left_node, left_node);
    // left_right_node = new_node();
    // link_right(left_right_node, left_node);

    //right side
    // tree_node_t* right_node;
    // tree_node_t* right_left_node;
    // tree_node_t* right_right_node;
    // right_node = new_node();
    // link_right(right_node, tree.root);
    // right_left_node = new_node();
    // link_left(right_left_node, right_node);
    // right_right_node = new_node();
    // link_right(right_right_node, right_node);

    // DUMP_NODE(right_right_node);

    // FILE* preorder_file = fopen(PREORDER_FILE, "w");
    // preorder_print(tree.root, preorder_file);
    // fclose(preorder_file);

    // FILE* inorder_file = fopen(INORDER_FILE, "w");
    // inorder_print(tree.root, inorder_file);
    // fclose(inorder_file);

    FILE* postorder_file = fopen(POSTORDER_FILE, "w");
    postorder_print(tree.root, postorder_file);
    fclose(postorder_file);

    tree_node_t* current = NULL;
    FILE* dump_file = open_graph_file(GRAPH_FILE);
    if (dump_file) dump_tree(dump_file, &tree, current);
    close_graph_file(dump_file);
}