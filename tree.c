#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#include "items.h"
#include "tree.h"


typedef struct treenode {
  item_t *item;
  struct treenode *left;
  struct treenode *right;
} treenode_t;

typedef struct tree{
  treenode_t *root;
} tree_t;


tree_t *tree_new(){
  tree_t *emptytree = NULL;
  emptytree = calloc(1, sizeof(tree_t));
  return emptytree;
}


int tree_size(treenode_t *tree)
  {
    int i = 1;
    if (tree == NULL)
      return 0;
    else {
      i += tree_size(tree->left);
      i += tree_size(tree->right);
      return i;
    }
  }     

treenode_t *minimum_Node(treenode_t *treenode){

  while (treenode->left != NULL){
    treenode = treenode->left;
  }
  return treenode;
}

int max_depth(treenode_t *tree){
  int leftDepth;
  int rightDepth;
  if (tree == NULL) return 0;
  else
    {
      leftDepth = max_depth(tree->left);
      rightDepth = max_depth(tree->right);

      if (leftDepth > rightDepth)
	return (leftDepth + 1);
      else return (rightDepth + 1);
    }
}

treenode_t* find_node(treenode_t *treenode, char *name){
  if(treenode == NULL){
    return NULL;
  }
  else if (strcmp(name, itemname(treenode->item)) == 0){
    return treenode;
  }
  else if(strcmp(name, itemname(treenode->item)) > 0){
    return find_node(treenode->right, name);
      }
  else{
    return find_node(treenode->left, name);
      }
}
  
treenode_t* inorder_successor(treenode_t *treenode, char *name){
  treenode_t *current  = find_node(treenode, name);
  if (current == NULL){
    return NULL;
      }
  
  //case 1: node has right subtree//
  if ((current->right) != NULL){
    return minimum_Node(current->right);
  }

// case 2: no right subtree //
     else {
      treenode_t *successor = NULL;
      treenode_t *ancestor = treenode;
     while(ancestor != current){
       if (strcmp ((itemname(current->item)), (itemname(ancestor->item))) < 0){
       successor = ancestor;
       ancestor = ancestor->left;
     }
       else ancestor = ancestor->right;
     }
   return successor;
     }
}


treenode_t* tree_remove(treenode_t **treenode, char *name){


   if (*treenode == NULL){ 
    return *treenode;
  }
  
  if(strcmp(name, itemname((*treenode)->item)) < 0){
      (*treenode)->left = tree_remove(&(*treenode)->left, name);

  }
  
  if (strcmp(name, itemname((*treenode)->item)) > 0){
    (*treenode)->right = tree_remove(&(*treenode)->right, name);
  }
  
  
  else if ((*treenode)->left == NULL && (*treenode)->right == NULL){
	free(treenode);
      }

  /// Node has 1 child (right)
  
      else if ((*treenode)->left == NULL) {
	treenode_t *temp = (*treenode)->right;
	free(*treenode);
	return temp;
    }
  /// Node has 1 child (left)
  
      else if ((*treenode)->right == NULL){
	treenode_t*temp = (*treenode) ->left;
	free(*treenode);
	return temp;	
      }
  // Find inorder successor
  treenode_t *temp = inorder_successor((*treenode)->right, name);
  //store inorder successor in node
  (*treenode)->item = temp->item;
  //delete the inorder successor
  (*treenode)->right = tree_remove(&(*treenode)->right, itemname(temp->item));
  
  return *treenode;
      }


treenode_t *create_treenode(item_t *item){
  treenode_t *temp;
  temp = calloc(1, sizeof(treenode_t));
  temp->item = item;
  temp->left = temp->right = NULL;
  return temp;
}


treenode_t* tree_insert(treenode_t **treenode, item_t *item){
  if (treenode == NULL){
    (*treenode) = create_treenode(item);
    return 0; // Not sure it should return 0..
             //(just so it compiles for now) 
  }
  else if(strcmp(itemname(item), itemname((*treenode)->item)) < 0)
    (*treenode)->left= tree_insert(&(*treenode)->left , item);

  else if(strcmp(itemname(item), itemname((*treenode)->item)) == 0)
    (*treenode)->left= tree_insert(&(*treenode)->left , item);

    
    else (*treenode)->right = tree_insert(&(*treenode)->right, item);
  
  return *treenode;
}

void ordered_print(treenode_t *treenode){
  if(treenode == NULL){
    puts("No more items to print");
    return;
  }
  ordered_print(treenode->left);
  printf("%s", itemname(treenode->item));
  ordered_print(treenode->right);
}
