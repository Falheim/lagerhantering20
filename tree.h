#ifndef __tree_h__
#define __tree_h__

typedef struct treenode treenode_t;
typedef struct tree tree_t;



//Funktionen skapar ett nytt träd
//Använder Calloc i den så elementet blir nollställt
//returnerar ett tomt träd med ett nollställt element
tree_t *tree_new();

//Funktion för att få storleken (antal element) i trädet.
//Returnerar antalet noder i trädet
int tree_size(treenode_t *tree);

//Söker igenom det vänstra sub-treet för att hitta det minsta värdet under root-noden
//returnerar noden med minst värde
treenode_t *minimum_Node(treenode_t *treenode);

//Funktionen söker igenom trädet och räknar ut max-höjden på trädet
//Räknar hur många nodes från roten till det yttersta bladet
//Returnerar en int som är höjden på trädet
int max_depth(treenode_t *tree);

//Hjälp-funktion för att skicka tillbaka pointern till noden med en viss data lagrad.
treenode_t find_node(treenode_t *treenode, char *name);

//Funktionen söker igenom trädet efter inorder successor
// dvs. då en nod tagits bort antingen det största värdet i vänstra subtreet
// eller det minsta värdet i det högra subtreet
// returnerar noden som är inorder successor ifall det finns någon.
treenode_t* inorder_successor(treenode_t *treenode, char *name);

//Funktion för att ta bort en nod ur trädet
//och ersätta den noden med Inorder successorn
treenode_t* tree_remove(treenode_t **treenode, char *name);

//Funktionen skapar en ny nod i trädet
//Noden kommer vara nollställd
treenode_t *create_treenode(item_t *item);

//Funktion för att spara data i trädets noder
//returnerar noden som värdet är sparat i
treenode_t* tree_insert(treenode_t **treenode, item_t *item);

//Funktion för att printa data i "rätt" ordning
//printar data i ordningen minst -> först
void ordered_print(treenode_t *treenode);

#endif
