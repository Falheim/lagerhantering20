#ifndef __lagerio_h
#define __lagerio_h

#include <stdlib.h>
#include <stdbool.h>

typedef bool (*v_f)(char *);   // validate_function
typedef void *(*m_f)(char *);  // modify_function

typedef struct shelf shelf_t;

char *read_string(void);
char *get_string_with_buffer(char *b, size_t l, bool s_n);
bool is_valid_int(char *s);
bool is_valid_shelf(char *s);
bool is_valid_char(char *s);
char *str_to_str(char *s);
int str_to_int(char *s);
shelf_t *str_to_shelf(char *s); 
void *ask_question(char *q, v_f v, m_f m, bool c);
char *ask_string_question(void);
int *ask_int_question(void);
shelf_t *ask_shelf_question(void);

#endif
