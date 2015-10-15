#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#include "items.h"



//Trädets nodes / branches uppbyggnad //

typedef struct treenode {
  item_t *item;
  struct treenode *left;
  struct treenode *right;
} treenode_t;


//Trädets uppbygnad //

typedef struct tree{
  treenode_t *root;
} tree_t;


/// Creates a new tree
///
/// \returns: empty tree
tree_t *tree_new(){
  tree_t *emptytree = NULL;
  emptytree = calloc(1, sizeof(tree_t));
  return emptytree;
}


/// Get the size of the tree 
///
/// \returns: the number of nodes in the tree
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


/// Scans left path from node for smallest value (since smallest will always be on left side)
treenode_t *minimum_Node(treenode_t *treenode){

  while (treenode->left != NULL){
    treenode = treenode->left;
  }
  return treenode;
}



// Get the depth of the tree 
//
// \returns: the depth of the deepest subtree
/*int tree_depth(tree_t *tree){
  if (tree == NULL) return 0;
  else {


  }
}
*/
///Calculates the maxdepth of the tree
///i.e the number of nodes from the root to the farthest leaf

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

// return pointer to node with data //
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
  


/// Finds and returns the inorder successor in bst // 
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
  // Some repetition here, could probably easily be fixed.
    
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
						  


















int main(){
  printf("Hello world");
}























/// FUNCTIONS THAT NEED LOVE ///

 /// Deleting a node from the tree

//struct treenode_t* tree_remove(struct treenode_t *root, char *name)
//{
  /* (FUNGERAR EJ, behöver fixas stort)
  if (*treenode == NULL) return 0;

  else if(name < warename((*root->item))) root->left = tree_remove(root->left, item_t);
  else if(name > warename((*root->item))) root->right = tree_remove(root->right, item_t);
  else
    {
      /// Node has no children
      if (root->left == NULL && root->right == NULL){
	free(treenode);
      }
      /// Node has 1 left child
      else if (root->left == NULL){
	struct treenode *temp = root;
	root = root -> left;
	free(temp);

      }
      /// Node has 1 right child
      else if(root->right == NULL) {
	struct treenode *temp = root;
	root = root->right;
	free(temp);
      }
      else{
	struct treenode *temp = minNode(root->right);
	root->name = temp->name;
	root->right = tree_remove(root->right, temp->name);
      }
    }
}
return treenode;
	
  */
