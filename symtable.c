#include "symtable.h"
#include <string.h>

/* Hash function for hashing into the symbol table.
   'e' is the hash table element, the member of the structure to go into the table. */
unsigned symtable_hashpjw (const struct hash_elem *e, void* aux)
{
  const id_entry_t* p = hash_entry (e, id_entry_t, sym_table_elem); /* Now 'p' is a record of id_entry_t type (symbol table). */
  char* str = p->id_name; /* This is the KEY of this table. */
  unsigned h = 0, g;
  int i;

  for(i = 0; str[i] != '\0'; i++)
   {
     h = (h << 4) + str[i];
     
     if(g = h & 0xf0000000)
      {
         h ^= (g >> 24);
         h ^= g;
      }
   }

  return h;
}

bool symtable_less (const struct hash_elem* a_, const struct hash_elem* b_, void* aux)
{
  const id_entry_t* a = hash_entry (a_, id_entry_t, sym_table_elem);
  const id_entry_t* b = hash_entry (b_, id_entry_t, sym_table_elem);

  short ret = strcmp (a->id_name, b->id_name);

  if (ret == -1)
    return 1;

  else
    return 0;
}





/* Hash function for hashing into function table. */
unsigned functable_hashpjw (const struct hash_elem *e, void* aux)
{
  const func_entry_t* p = hash_entry (e, func_entry_t, func_table_elem); /* Now 'p' is a record of id_entry_t type (symbol table). */
  char* str = p->name; /* This is the KEY of this table. */
  unsigned h = 0, g;
  int i;

  for(i = 0; str[i] != '\0'; i++)
   {
     h = (h << 4) + str[i];
     
     if(g = h & 0xf0000000)
      {
         h ^= (g >> 24);
         h ^= g;
      }
   }

  return h;
}

bool functable_less (const struct hash_elem* a_, const struct hash_elem* b_, void* aux)
{
  func_entry_t* a = hash_entry (a_, func_entry_t, func_table_elem);
  func_entry_t* b = hash_entry (b_, func_entry_t, func_table_elem);

  short ret = strcmp (a->name, b->name);

  if (ret == -1)
    return 1;

  else
    return 0;
}
