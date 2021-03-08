#ifndef LIST_LIB
#define LIST_LIB

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* actual node of the chain */
typedef struct list_node list_node;
struct list_node
{
    void* data;
    list_node* next;
};

/* to use, point to the first node */
typedef struct
{
    list_node* begin;
    size_t count;
} list;


/* 01 */
list* create_list();

/* 02 */
size_t list_count(const list* _list);

/* 03 */
list_node* list_get_node(list* _list, size_t _index);

/* 04 */
size_t list_add(list* _list, void* _data);

/* 05 */
void* list_get(list* _list, size_t _index);

/* 06 */
bool list_set(list* _list, size_t _index, void* data);

/* 07 */
bool list_insert(list* _list, size_t _index, void* _data);

/* 08 */
bool list_remove(list* _list, size_t _index);

/* 09 */
void destroy_list(list* _list);

#endif