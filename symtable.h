#ifndef __SYMTABLE_H
#define __SYMTABLE_H

#include "hash.h"
#include <stdbool.h>

enum type {INT_TYPE, REAL_TYPE, CHAR_TYPE, BOOL_TYPE, ARRAY_INT_TYPE, ARRAY_REAL_TYPE, ARRAY_CHAR_TYPE, ARRAY_BOOL_TYPE, INPUT_TYPE, OUTPUT_TYPE, NO_TYPE};

#define MAX_TABLE_SIZE 100

/* Entry in function table. */
typedef struct func_entry
{
  struct hash_elem func_table_elem; /* Element in global function table. */

  char* name;                       /* KEY - Name of the function/procedure. */
  int num_args;                     /* Number of arguments. */
  enum type* arg_types;             /* Array containing types of the arguments. */
  enum type return_type;            /* Return type. */
  int scope;                        /* Nesting depth of the function (global scope = 0). */
  struct hash* symbol_table;        /* Pointer to symbol table of this function/procedure. */
  struct func_entry* parent_scope;  /* Pointer to the record of the parent scope. */
  struct func_entry** child_scopes; /* Pointer to the records of the children scopes. */
  int num_childscopes;              /* Number of child funcs/procs created within this scope. */
}func_entry_t;


/* Entry in each symbol table. */
typedef struct 
{
  struct hash_elem sym_table_elem;  /* Element in a symbol table. */
  int offset;
  char* id_name;                    /* KEY - Name of the identifier (ONLY VARIABLE NAMES). */
  char* scope_name;                 /* Name of the scope in which it is defined (key value of func_entry record). */
  enum type id_type;                /* Type of the identifier. This flags the union value below. */
  union
  {
    int* i;
    float* f;
    char* c;
    bool* b;

    /* For array type, we need a bit more details. */
    struct
    {
      union
      {
	int** iptr;
	float** fptr;
	char** cptr;
	bool** bptr;
      }ptr_val;
      int lower_bound;
      int upper_bound;
    }arr;
  }mem_loc;                        /* Location in memory of the value held by the identifier. */

}id_entry_t;


unsigned symtable_hashpjw (const struct hash_elem *e, void* aux);
bool symtable_less (const struct hash_elem* a_, const struct hash_elem* b_, void* aux);
unsigned functable_hashpjw (const struct hash_elem *e, void* aux);
bool functable_less (const struct hash_elem* a_, const struct hash_elem* b_, void* aux);

#endif
