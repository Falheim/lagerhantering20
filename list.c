//list.c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

struct shelf{
  char row;
  int col;
};

struct link{
  struct shelf shelf;
  struct link *next;
};

struct list{
  struct link *first;
  struct link *last;
};

list_t *make_list()
{
  list_t *result = malloc(sizeof(struct list));
  if(result != NULL) {
    result->first = NULL;
    result->last = NULL;
    return result;
  }
  return NULL;
}

void print_list(list_t *list){
  struct link *current = list->first;
  printf("{");
  while(current != NULL)
    {
      if(current->next) {
	printf("%c%d,", current->shelf.row, current->shelf.col);
	current = current->next;
      } else{
	printf("%c%d}\n", current->shelf.row, current->shelf.col);
	return;
      }
    }
  printf("NULL}\n");
}

struct link *make_link(shelf_t shelf, struct link *next)
{
  struct link *result = malloc(sizeof(struct link));
  if (result != NULL){
    result->shelf = shelf;
    result->next = next;
    return result;
  }
  return NULL;
}

void list_prepend(list_t *list, shelf_t shelf)
{
  list->first = make_link(shelf, list->first);
  if (list->last == NULL){
    list->last = list->first;
  }
}

void list_append(list_t *list, shelf_t shelf)
{
  if (list->last == NULL) {
    list->last = list->first = make_link(shelf, NULL);
  } else {
    list->last = list->last->next = make_link(shelf, NULL);
  }
}

unsigned int list_length(list_t *list)
{
  unsigned int size = 0;
  struct link *current = list->first;
  while(current != NULL) {
    ++size;
    current = current->next;
  }
  return size;
}

bool is_list_empty(list_t *list)
{
  return list->first == NULL;
}

shelf_t *list_first(list_t *list)
{
  if (is_list_empty(list)){
    return NULL;
  } else {
    return &(list->first->shelf);
  }
}

shelf_t *list_last(list_t *list)
{
  if (is_list_empty(list)){
    return NULL;
  } else {
    return &(list->last->shelf);
  } 
}

shelf_t *list_get(list_t *list, int index)
{
  struct link *current = list->first;
  while (current != NULL && index >= 0)
    {
      if (index == 0) return &(current->shelf);
      current = current->next;
      index--;
    }
  return NULL;
}

bool list_insert(list_t *list, int index, shelf_t shelf)
{
  struct link *current = list->first;
  if(index == 0) {
    list_prepend(list, shelf);
    }
  while(current){
    if(index == 1){ //nod före där vi vill sätta in
      struct link *temp = current->next;
      current->next = make_link(shelf, temp);
      return true;
    }
    current=current->next;
    index--;
  }
  return false; 
}

bool list_remove(list_t *list, int index, shelf_t *store_shelf)
{
  struct link *current = list->first;
  size_t size_shelf = sizeof(shelf_t);
  
  if(index == 0){
    memcpy(store_shelf, &(current->shelf), size_shelf);
    list->first = current->next;
    return true;
  }
  while(current){
    if(index == 1){ //nod före index
      memcpy(store_shelf, &(current->next->shelf), size_shelf);
      current->next = current->next->next;
      return true;
    }
    current=current->next;
    index--;
  }
  return false;  
}

int main()
{
  shelf_t a = {.row = 'A', .col = 1};
  shelf_t b = {.row = 'B', .col = 2};
  shelf_t c = {.row = 'C', .col = 3};
  shelf_t d = {.row = 'D', .col = 4};
  shelf_t e = {.row = 'E', .col = 5};
  
  list_t *l = make_list();
  list_append(l,d);
  list_prepend(l,b);
  list_append(l,d);
  list_prepend(l,b);
  list_append(l,d);
  list_prepend(l,b);
  
  list_insert(l, 0, a); // insättning head
  list_insert(l, 4, c); // insättning index
  list_insert(l, 8, e); // insättning som sista element
  list_insert(l, -1, d); // ogiltig insättning före listan
  list_insert(l, 10, d); // insättning efter slutet av listan
  
  print_list(l);
  shelf_t *f = list_first(l);
  shelf_t *la = list_last(l);
  printf("\nLength of list: %d\n", list_length(l) );
  printf("First: %c%d\tLast: %c%d", f->row,f->col, la->row, la->col);
  
  shelf_t *g = list_get(l, 0);
  printf("\n%c%d\n", g->row, g->col);
  shelf_t *h = list_get(l, 2);
  printf("%c%d", h->row, h->col);
  shelf_t *i = list_get(l, 4);
  printf("\n%c%d\n", i->row, i->col);

  shelf_t *s_shelf = malloc(sizeof(shelf_t));
  list_remove(l, 0, s_shelf);
  print_list(l);
  printf("Storedshelf: %c%d\n", (*s_shelf).row, (*s_shelf).col);
  
  list_remove(l, 3, s_shelf);
  print_list(l);
  printf("Storedshelf: %c%d\n", (*s_shelf).row, (*s_shelf).col);

  free(s_shelf);
  return 0;
}
