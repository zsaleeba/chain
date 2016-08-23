/***********************************************************************/
/***                                                                 ***/
/***                     "chain" data structure.                     ***/
/***                                                                 ***/
/***                           - by Zik Saleeba zik@zikzak.net       ***/
/***                                       2016-08-20                ***/
/***                                                                 ***/
/***********************************************************************/

/*
 * Licensed under the "unlicense".
 * See: http://unlicense.org/
 */

#include "stddef.h"


/* Chain structure. */
typedef struct
{
    void  *data;
    size_t items;
    size_t left_items;
    size_t right_items;
} chain_node;

typedef struct
{
    size_t     items;
    size_t     item_size;
    chain_node root;
} chain;

/* Macros. */
#define chain_size(ch) ((ch)->items)
#define chain_get(ch)  XXX

/* Prototypes. */
void   chain_init(chain *ch, size_t item_size);
void   chain_free(chain *ch);
void  *chain_get_fn(chain *ch, size_t pos);
void   chain_resize(chain *ch, size_t new_size);
void   chain_insert_item(chain *ch, size_t pos, void *item);
void   chain_insert_multi(chain *ch, size_t pos, void *items, size_t n_items);
void   chain_insert_chain(chain *ch, size_t pos, chain *items);
void   chain_delete(chain *ch, size_t pos, size_t n_items);
chain *chain_remove(chain *ch, size_t pos, size_t n_items);
void   chain_flatten(chain *ch);

/* Helpers. These just call chain_insert_XXX(). */
void   chain_append_item(chain *ch, size_t pos, void *item);
void   chain_append_multi(chain *ch, size_t pos, void *items, size_t n_items);
void   chain_append_chain(chain *ch, size_t pos, chain *items);
void   chain_prepend_item(chain *ch, size_t pos, void *item);
void   chain_prepend_multi(chain *ch, size_t pos, void *items, size_t n_items);
void   chain_prepend_chain(chain *ch, size_t pos, chain *items);
