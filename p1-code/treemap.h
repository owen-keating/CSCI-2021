// Header for BST problem

#ifndef TREEMAP_H
#define TREEMAP_H 1

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>              // for FILE * declaration in I/O funcs

// Type of tree nodes
typedef struct node {
  char key[64];                 // key for the node
  char val[64];                 // value for the node
  struct node *left;            // left branch,  NULL if not present
  struct node *right;           // right branch, NULL if not present
} node_t;

// Type of tree itself
typedef struct {
  node_t *root;                 // root of tree, NULL if tree empty
} treemap_t;

// tree functions which will be tested in binary
void treemap_init(treemap_t *tree);
int treemap_add(treemap_t *tree, char key[], char val[]);
char *treemap_get(treemap_t *tree, char key[]);
void treemap_clear(treemap_t *tree);
int treemap_size(treemap_t *tree);
void treemap_print_revorder(treemap_t *tree);
void treemap_print_preorder(treemap_t *tree);
void treemap_save(treemap_t *tree, char *fname);
int treemap_load(treemap_t *tree, char *fname);

// node functions, not tested but useful as helpers
char *node_get(node_t *cur, char key[]);
void node_remove_all(node_t *cur);
int node_count_all(node_t *cur);
void node_print_revorder(node_t *cur, int indent);
void node_write_preorder(node_t *cur, FILE *out, int depth);

#endif
