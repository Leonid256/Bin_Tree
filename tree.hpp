#ifndef TREE_HPP
#define TREE_HPP

//----------------------------------------------------------------------------
typedef const char* tree_elem_t;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>

#include "colours.hpp"

//----------------------------------------------------------------------------
const char* const GRAPH_FILE     = "tree.dot";
const char* const PREORDER_FILE  = "preorder.txt";
const char* const POSTORDER_FILE = "postorder.txt";
const char* const INORDER_FILE   = "inorder.txt";
const tree_elem_t POIZON_VALUE = "676767";
const size_t BUFFER_SIZE = 20;

//----------------------------------------------------------------------------
enum tree_status
{
    TREE_OK     = 0,
    TREE_ERROR  = 1,
};

struct tree_node_t
{
    tree_elem_t data;
    tree_node_t* left;
    tree_node_t* right;
    tree_node_t* parent;
};

struct tree_t
{
    tree_node_t* root;
    size_t size;
};

//----------------------------------------------------------------------------
tree_status tree_init(tree_t* tree);
tree_node_t* new_node();
tree_status link_left(tree_node_t* node_left, tree_node_t* node_parent);
tree_status link_right(tree_node_t* node_right, tree_node_t* node_parent);
void delete_node(tree_node_t* node);
void delete_subtree(tree_node_t* node);
tree_status dump_node(tree_node_t* node, int line);
void preorder_print(const tree_node_t* node, FILE* file);

tree_node_t* pre_new_node(char* buffer_file, tree_node_t* parent, size_t* size, int* i);
tree_status preorder_read(const char* const pre_file, tree_t* tree);

tree_node_t* post_new_node(FILE* file, tree_node_t* parent, size_t* size);
tree_status postorder_read(const char* const post_file, tree_t* tree);

tree_node_t* in_new_node(FILE* file, tree_node_t* parent, size_t* size);
tree_status inorder_read(const char* const post_file, tree_t* tree);

//dump
FILE* open_graph_file(const char* const graph_file_name);
void close_graph_file(FILE* file);
void graph_dump_node(FILE* file, tree_node_t* node, int depth, tree_node_t* current);
void dump_tree(FILE* file, tree_t* treem, tree_node_t* current);

//----------------------------------------------------------------------------
#define DUMP_NODE(node) dump_node(node, __LINE__)

#endif