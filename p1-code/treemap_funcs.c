#include "treemap.h"

void treemap_init(treemap_t *tree){
    tree->root = NULL;                          //  set root to null
}

int treemap_add(treemap_t *tree, char key[], char val[]){
    node_t *head = NULL;                        //  set head to null
    node_t *ptr = tree->root;                   //  ptr traverses tree
    while(ptr!=NULL){
        if(strcmp(key, ptr->key)<0){            //  compare parameter key to ptr key
            head = ptr;
            ptr = ptr->left;                    //  traversing left
        }
        else if(strcmp(key, ptr->key)>0){
            head = ptr;
            ptr = ptr->right;                   //  traversing right
        }
        else{
            strcpy(ptr->val, val);              //  modify value for identical key
            return 0;                           //  don't create new node
        }
    }
    node_t *add = malloc(sizeof(node_t));       //  initialize new tree node
    strcpy(add->key, key);
    strcpy(add->val, val);
    add->left = NULL;
    add->right = NULL;
    if(head==NULL){                             //  check for empty tree
        tree->root = add;                       //  new node becomes root of tree
    }
    else if(strcmp(key, head->key)<0){
        head->left = add;                       //  pointer to new node on left
    }
    else{
        head->right = add;                      //  pointer to new node on right
    }
    return 1;                                   //  return 1 to indicate node created
}

char *treemap_get(treemap_t *tree, char key[]){
    node_t *ptr = tree->root;                   //  ptr traverses tree
    while(ptr!=NULL){
        if(strcmp(key, ptr->key)<0){            //  compare parameter key to ptr key
            ptr = ptr->left;                    //  traversing left
        }
        else if(strcmp(key, ptr->key)>0){
            ptr = ptr->right;                   //  traversing right
        }
        else{
            return ptr->val;                    //  key found, return matching value
        }
    }
    return NULL;                                //  return null when key not found
}

void treemap_clear(treemap_t *tree){
    node_remove_all(tree->root);                //  call to helper remove function
    tree->root = NULL;                          //  root set to null
}

void node_remove_all(node_t *cur){
    if(cur==NULL) return;                       //  recursive base case
    node_remove_all(cur->left);                 //  remove all nodes in left subtree
    node_remove_all(cur->right);                //  remove all nodes in right subtree
    free(cur);                                  //  free memory in root of subtree
}

int treemap_size(treemap_t *tree){
    return node_count_all(tree->root);          //  call to helper count function
}

int node_count_all(node_t *cur){
    if(cur==NULL){                              //  recursive base case
        return 0;
    }
    else{                                       //  root plus left and right subtree nodes
        return 1 + node_count_all(cur->left) + node_count_all(cur->right);
    }
}

void treemap_print_revorder(treemap_t *tree){
    if(tree->root==NULL){                       //  check for empty tree
        printf("\n");                           //  print empty tree
    }
    else{
        node_print_revorder(tree->root, 0);     //  call to helper print function
    }
}

void node_print_revorder(node_t *cur, int indent){
    if(cur->right!=NULL){                       //  traversing to farthest right node
        node_print_revorder(cur->right, indent+1);
    }
    if(cur!=NULL){                              //  farthest right node reached, print
        for(int i = 0; i<indent; i++){ printf("  "); }
        printf("%s -> %s\n", cur->key, cur->val);
    }
    if(cur->left!=NULL){                        //  traverse down left subtree
        node_print_revorder(cur->left, indent+1);
    }
}

void treemap_print_preorder(treemap_t *tree){
    if(tree->root==NULL){                       //  check for empty tree
        printf("\n");                           //  print empty tree
    }
    else{                                       //  call to helper print function
        node_write_preorder(tree->root, stdout, 0);
    }
}

void treemap_save(treemap_t *tree, char *fname){
    FILE *file = fopen(fname,"w");              //  open file
    node_write_preorder(tree->root, file, 0);   //  call to helper write function
    fclose(file);                               //  close file
}

void node_write_preorder(node_t *cur, FILE *out, int depth){
    if(cur!=NULL){                              //  print highest node in tree
        for(int i = 0; i<depth; i++){ fprintf(out, "  "); }
        fprintf(out, "%s %s\n", cur->key, cur->val);
    }
    if(cur->left!=NULL){                        //  traverse left subtree
        node_write_preorder(cur->left, out, depth+1);
    }
    if(cur->right!=NULL){                       //  traverse right subtree
        node_write_preorder(cur->right, out, depth+1);
    }
}

int treemap_load(treemap_t *tree, char *fname ){
    FILE *file = fopen(fname,"r");              //  open file
    if(file==NULL){                             //  check if file exists
        printf("ERROR: could not open file '%s'\n", fname);
        return 0;                               //  error message, return 0 if file DNE
    }
    treemap_clear(tree);                        //  clear tree
    char key[64]; char val[64];                 //  temporary string variables
    while(fscanf(file,"%s %s", key, val)!=EOF){
        treemap_add(tree, key, val);            //  read and add new key nodes with values
    }
    fclose(file);                               //  close file
    return 1;                                   //  return 1 when file opens successfully
}