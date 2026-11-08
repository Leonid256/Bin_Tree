#ifndef TREE_HPP
#define TREE_HPP

//----------------------------------------------------------------------------
typedef int tree_elem_t;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "colours.hpp"

//----------------------------------------------------------------------------
const char* const GRAPH_FILE = "tree.dot";
const tree_elem_t POIZON_VALUE = 676767;

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
tree_status delete_node(tree_node_t* node);
tree_status dump_node(tree_node_t* node, int line);

//dump
FILE* open_graph_file(const char* const graph_file_name);
void close_graph_file(FILE* file);
void graph_dump_node(FILE* file, tree_node_t* node, int depth, tree_node_t* current);
void dump_tree(FILE* file, tree_t* treem, tree_node_t* current);

//----------------------------------------------------------------------------
#define DUMP_NODE(node) dump_node(node, __LINE__)

#endif