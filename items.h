#ifndef __items_h__
#define __items_h__

typedef struct item item_t;

char *itemname(item_t *item);

char *itemdesc(item_t *item);

int itemprice(item_t *item);

int itemamount(item_t *item);



#endif
