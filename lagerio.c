/*
Code pretty much taken from:
https://github.com/IOOPM-UU/ioopm15/blob/master/forelasningar/L10/f10.pdf
Author: Tobias Wrigstad
Editor: Eric Falheim
*/
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "lagerio.h"

#define Ask_int(q)  ask_question(q, is_valid_int, str_to_int, true)
#define Ask_str(q)  ask_question(q, NULL, str_to_str, true)
#define Ask_char(q) ask_question("Enter a character: ", is_valid_char, str_to_str, true)

#define Ask_name(q) Ask_str("Name:")
#define Ask_description(q) Ask_str("Description:")
#define Ask_price(q) Ask_int("Price:")
#define Ask_shelf(q) ask_question("Shelf - enter character followed by integer 0-99: ", is_valid_shelf, str_to_shelf, true)

#define STRIP_NEWLINE true

struct shelf
{
  char row;
  int column;
};

char *read_string()
{
  return get_string_with_buffer(NULL, 0, STRIP_NEWLINE);
}

char *get_string_with_buffer(char *buf, size_t len, bool strip_newline)
{
  ssize_t read = getline(&buf,&len,stdin);
  if(read > 0 && strip_newline)
    {
      buf[read-1] = '\0';
    }
  return buf;
}

bool is_valid_shelf(char *str)
{
  if (isalpha(str[0]) && strlen(str) == 3 && is_valid_int(str+1))
    return true; 
  return false;
}

bool is_valid_int(char *str)
{
  bool valid_int = true;
  if (strlen(str) == 0)
    valid_int = false;
  
  for(char *c = str; *c && valid_int; ++c)
    {
      valid_int = isdigit(*c);
    }
  return valid_int;
}

bool is_valid_char(char* str)
{
  if (strlen(str) == 1 && isalpha(str[0]))
    return true;
  return false;
}

char *str_to_str(char *str)
{
  return str;
}

int str_to_int(char *str)
{
  return atol(str);
}

shelf_t *str_to_shelf(char *str)
{
  shelf_t *shelf = malloc(sizeof(shelf_t));
  shelf->row = str[0];
  shelf->column = atol(str+1);
  return shelf;
}


void *ask_question(char *q, v_f validate, m_f convert, bool cleanup)
{
  char *input = NULL;
  
  do{
    puts(q);
    if(input) free(input);
    input = read_string();
  } while(validate && validate(input) == false);

  void *result = convert ? convert(input) : input;

  if(cleanup) free(input);
  return result;
}

char *ask_string_question()
{
  return ask_question("Enter a string:",
		       NULL,
		       NULL,
		       true);
}

shelf_t *ask_shelf_question()
{
  return ask_question("Enter a character followed by an integer between 0-99: ",
		      is_valid_shelf,
		      str_to_shelf,
		      true);
}

int *ask_int_question()
{
  return ask_question("Enter an integer: ",
		      is_valid_int,
		      str_to_int,
		      true);
}

int main(){
  return 0;
}
