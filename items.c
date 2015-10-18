#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "items.h"
#include "list.h"
#inlude "tree.h"

struct item{  
  char *name;
  char *desc;
  int price;
  int amount;
  list_t;
};

char *itemname(item_t *item){
  return item->name;
}

char *itemdesc(item_t *item){
  return item->desc;
}

int itemprice(item_t *item){
  return item->price;
}

int itemamount(item_t *item){
  return item->amount;
}

item_t print_item(item_t *item){
  while(item != NULL){
    printf("Name: %s\n", item->name);
    printf("Description: %s\n", item->desc);
    printf("Price: %d\n", item->price);
    printf("amount: %d\n", item->amount);
    printf("Shelf: %s\n", item->list_t);
    return item;
  }
  puts("Try adding a ware to the warehouse first!");
  return item;
}

item_t *add_item(char *name, char *desc, int price, int amount, list_t){
  item_t *add_temp;
  add_temp = calloc(1, sizeof(item_t));

  add_temp->name = name;
  add_temp->desc = desc;
  add_temp->price = price;
  add_temp->amount = amount;
  add_temp->list_t = list_t;

  return add_temp;
}

