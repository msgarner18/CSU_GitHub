#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Debug.h"
#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement the symbol.h interface
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file. The reference implementation added approximately
 *  110 lines of code to this file. This count includes lines containing
 *  only a single closing bracket (}).
 * <p>
 * @author <b>Your name</b> goes here
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16)

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** defines data structure used to store nodes in hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** defines the data structure for the hash table */
struct sym_table {
  int      capacity;    /**< length of hast_table array                  */
  int      size;        /**< number of symbols (may exceed capacity)     */
  node_t** hash_table;  /**< array of head of linked list for this index */
  char**   addr_table;  /**< look up symbols by addr (optional)          */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}

/** @todo implement this function */
//print vi reference card
sym_table_t* symbol_init (int capacity) {

  sym_table_t* ptr = calloc(1, sizeof(sym_table_t));
  //ptr-> same as (*ptr).
  ptr -> addr_table = (char**)calloc(LC3_MEMORY_SIZE, sizeof(char*));
  (*ptr).hash_table = (node_t**)calloc(capacity, sizeof(node_t*));
  (*ptr).capacity = capacity;
  ptr -> size = 0; 
  
  return ptr;
}

/** @todo implement this function */
void symbol_term (sym_table_t* symTab)//What is the difference between this and reset? How do I remove from symbol table? what does free do?
{
  symbol_reset(symTab);
  free(symTab->hash_table);
  free(symTab->addr_table);
  free(symTab);  
}

/** @todo implement this function */
void symbol_reset(sym_table_t* symTab)//Not getting rid of anything from my table when I type "list". Is that what this is supposed to do?
{
  int i;
  node_t* current;
  node_t* after;
  for(i = 0; i < (symTab->capacity); i++)
  {
    current = symTab->hash_table[i];
    after = current;
    while(current != NULL)
    {
      after = after->next;
      free(current->symbol.name);
      free(current);
      current = after;
    }
    symTab->hash_table[i] = NULL;
  } 
  symTab->size = 0; 
}

/** @todo implement this function */
int symbol_add (sym_table_t* symTab, const char* name, int addr)
{
  int hash;
  hash = symbol_hash(name);
  int index;
  index = hash%(symTab->capacity);

  if(symbol_search(symTab, name, &hash, &index) == NULL)
  {
    node_t* head = symTab->hash_table[index];
  
    node_t* newNode = calloc(1,sizeof(node_t));
    newNode->next = NULL;
    newNode->hash = hash;
    newNode->symbol.name = strdup(name);
    newNode->symbol.addr = addr;

    if(head != NULL)
    {
      newNode->next = head; 
    }   

    symTab->hash_table[index] = newNode;
    symTab->addr_table[addr] = newNode->symbol.name;

    symTab->size++;

    return 1;//DUPLICATE
  } 
  return 0;//OK
}

/** @todo implement this function */
struct node* symbol_search (sym_table_t* symTab, const char* name, int* hash, int* index)
{
  
  *hash = symbol_hash(name);
  *index = *hash%(symTab->capacity);
  node_t* current = symTab->hash_table[*index];

  if(current == NULL)
  {
    return NULL;//what you are searching for doesn't exist
  }  
  else
  {
    while(current != NULL && strcasecmp(current->symbol.name,name) != 0)
    {
      current = current->next;
    }
    return current;//information of name that is found
  }
}

/** @todo implement this function */
symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name)
{
  int hash;
  hash = symbol_hash(name);
  int index;
  index = hash%(symTab->capacity);
  if(symbol_search(symTab, name, &hash, &index) != NULL)
  {
    node_t* current = symTab->hash_table[index];
    return &(current->symbol);
  }
  return NULL;
}	

/** @todo implement this function */
char* symbol_find_by_addr (sym_table_t* symTab, int addr)//is my address my hash?
{
  
  return symTab->addr_table[addr];
}

/** @todo implement this function */
void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data)//how do I test to see if this is working?
{
  int i;
  for(i = 0; i < (symTab->capacity); i++)
  {
    node_t* current; 
    for(current = symTab->hash_table[i]; current != NULL; current = current->next)
    {
      (*fnc)(&(current->symbol), data);
    }
  } 
}

/** @todo implement this function */
int symbol_size (sym_table_t* symTab)
{
  return symTab->size;
}

/** @todo implement this function */
int compare_names (const void* vp1, const void* vp2)
{
  symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this
  symbol_t* sym2 = *((symbol_t**) vp2);

  return strcasecmp(sym1->name, sym2->name);
}

/** @todo implement this function */
int compare_addresses (const void* vp1, const void* vp2)
{
  symbol_t* sym1 = *((symbol_t**) vp1); // study qsort to understand this
  symbol_t* sym2 = *((symbol_t**) vp2); 
 
  if(sym1->addr < sym2->addr)
  {
   return -1;
  }
  else if(sym1->addr > sym2->addr)
  {
    return 1;
  }

  return 0;
}

/** @todo implement this function */
symbol_t** symbol_order (sym_table_t* symTab, int order)
{
  symbol_t** array = calloc(sizeof(symbol_t*), symTab->size);
  int i;
  int index = 0;
  for(i = 0; i < symTab->capacity;i++)
  {
    node_t* current;
    for(current = symTab->hash_table[i]; current!=NULL; current = current->next)
    {
      array[index] = &(current->symbol);
      index++;
    }
  }
  
  if(order != HASH)
  {
    qsort(array, symTab->size, sizeof(symbol_t*), order == NAME? compare_names: compare_addresses);//if statement for macros on symbol.h - if hash order, don't run qsort
  }
  
  // will call qsort with either compare_names or compare_addresses
  return array;
}

//dd cuts a line
//yy copy
//p pastes a line below cursor



