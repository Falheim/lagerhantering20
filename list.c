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
	printf("%c%d}", current->shelf.row, current->shelf.col);
	return;
      }
    }
  printf("NULL}");
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
  while(current != NULL)
    {
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

/*
bool list_insert(list_t *list, int index, int elem)
{
  return true;
}



bool list_remove(list_t *list, int index, int *elem)
{
  return true;
}

int *list_get(list_t *list, int index)
{
  return -1;
}

*/

int main()
{
  shelf_t a = {.row = 'A', .col = 1};
  shelf_t b = {.row = 'B', .col = 2};
  shelf_t c = {.row = 'C', .col = 3};
  shelf_t d = {.row = 'D', .col = 4};
  shelf_t e = {.row = 'E', .col = 5};
  list_t *l = make_list();
  list_append(l,a);
  list_prepend(l,b);
  list_append(l,c);
  list_prepend(l,d);
  list_append(l,e);
   
  print_list(l);
  shelf_t *f = list_first(l);
  shelf_t *la = list_last(l);
  printf("\nLength of list: %d\n", list_length(l) );
  printf("First: %c%d\tLast: %c%d", f->row,f->col, la->row, la->col);
  return 0;
}


  
