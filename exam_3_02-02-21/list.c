#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/* actual node of the chain */
typedef struct
{
    void* data;
    struct list_node* next;
} list_node;

/* to use, point to the first node */
typedef struct
{
    list_node* begin;
    size_t count;
} list;


list* create_list(size_t _data_size)
{

}


/* test purpose */
int main(int ac, char** av)
{

    return 0;
}