#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

/* 01 */
list* create_list()
{
    list* to_return = malloc(sizeof(list));

    if(!to_return)
	{
		fprintf(stderr, "\nERROR: memory allocation failed, list* creation aborted.\n\n");
		to_return = NULL;
	}
    else
    {
        to_return->begin = NULL;
        to_return->count = 0;
    }

    return to_return;
}


/* 02 */
size_t list_count(const list* _list)
{
    return _list->count;
}


/* 03 */
list_node* list_get_node(list* _list, size_t _index)
{
    int i = 0;
    list_node* to_return = _list->begin;

    /* loop until the node value is null or at the index */
    while(to_return != NULL && i < _index)
    {
        to_return = to_return->next;
        i++;
    }

    return to_return;
}


/* 04 */
size_t list_add(list* _list, void* _data)
{
    list_node* to_add = NULL;
    list_node* temp = NULL;

    /* allocate node */
    to_add = malloc(sizeof(list_node));

    /* handle errors */
    if(!to_add)
		fprintf(stderr, "\nERROR: memory allocation failed, list_node* creation aborted.\n\n");
    else
    {
        /* load data */
        to_add->data = _data;
        to_add->next = NULL;

        /* reach last list node */
        if(_list->begin != NULL)
        {
            temp = _list->begin;
        
            while(temp->next != NULL)
            {
                temp = temp->next;
            }
            /* add the allocated node to list */
            temp->next = to_add;
        }
        else
            _list->begin = to_add;

        /* increase list's count */
        _list->count += 1;
    }
    return list_count(_list);
}


/* 05 */
void* list_get(list* _list, size_t _index)
{
    list_node* temp = list_get_node(_list, _index);

    if(temp != NULL)
        return temp->data;
    else
        return NULL;
}


/* 06 */
bool list_set(list* _list, size_t _index, void* data)
{
    bool to_return = false;
    list_node* temp = list_get_node(_list, _index);

    if(temp)
    {
        temp->data = data;
        to_return = !to_return;
    }

    return to_return;
}


/* 07 */
bool list_insert(list* _list, size_t _index, void* _data)
{
    bool to_return = false;
    list_node* last_node = NULL;
    list_node* temp = NULL;

    if(_index < _list->count)
    {
        /* store last of the list */
        last_node = list_get_node(_list, _list->count - 1);

        /* add the new one */
        list_add(_list, _data);

        /* store the new one */
        temp = list_get_node(_list, _list->count - 1);

        /* remove link to list */
        last_node->next = NULL;

        /* link to following of the list */
        temp->next = list_get_node(_list, _index);

        /* link to previous elements  */
        if(_index == 0)
            _list->begin = temp;
        else
            list_get_node(_list, _index - 1)->next = temp;
        
        to_return = true;
    }
    /* in this case its just add -_- */
    else if(_index == _list->count)
    {
        list_add(_list, _data);
        to_return = true;
    }

    return to_return;
}

/* 08 */
bool list_remove(list* _list, size_t _index)
{
    bool to_return = false;
    list_node* temp = NULL;

    if(_index < _list->count)
    {
        /* store the one to remove */
        temp = list_get_node(_list, _index);

        /* assign previous node to the next node */
        if(_index == 0)
            _list->begin = temp->next;
        else
            list_get_node(_list, _index - 1)->next = temp->next;

        /* decrease list count */
        _list->count -= 1;

        /* free the one to delete */
        free(temp);

        to_return = true;
    }
    return to_return;
}

/* 09 */
void destroy_list(list* _list)
{
    int i = 0;
    while(i < _list->count)
    {
        list_remove(_list, 0);
        i++;
    }
    free(_list);
}