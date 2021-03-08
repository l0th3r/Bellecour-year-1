#ifndef _LIST_GENERIC_
#define _LIST_GENERIC_

#include "list.h"

/* 1 */
#define LIST_TYPE(TYPE)\
    typedef struct {list* _list;} list_##TYPE;

/* 2 */
#define LIST_METHOD_DECL_CREATE(TYPE)\
    list_##TYPE* create_list_##TYPE();

#define LIST_METHOD_DECL_DESTROY(TYPE)\
    void destroy_list_##TYPE(list_##TYPE* _list);

/* 3 */
#define LIST_METHOD_DEFN_CREATE(TYPE)\
    list_##TYPE* create_list_##TYPE()\
    {\
        list_##TYPE* to_return = malloc(sizeof(list_##TYPE));\
        if(!to_return) {\
           fprintf(stderr, "\nERROR: memory allocation failed, list_%s* creation aborted.\n\n", #TYPE);\
           to_return = NULL;\
        } else {\
            to_return->_list = create_list();\
        }\
        return to_return;\
    }

#define LIST_METHOD_DEFN_DESTROY(TYPE)\
    void destroy_list_##TYPE(list_##TYPE* _list)\
    {\
        destroy_list(_list->_list);\
        free(_list);\
    }

/* 4 */
#define LIST_METHOD_DECL_COUNT(TYPE)\
    size_t list_##TYPE##_count(const list_##TYPE * _list);

#define LIST_METHOD_DECL_ADD(TYPE)\
    size_t list_##TYPE##_add(list_##TYPE * _list, TYPE* _data);

#define LIST_METHOD_DECL_GET(TYPE)\
    TYPE* list_##TYPE##_get(list_##TYPE * _list, size_t _index);

#define LIST_METHOD_DECL_SET(TYPE)\
    bool list_##TYPE##_set(list_##TYPE * _list, size_t _index, TYPE* _data);

#define LIST_METHOD_DECL_INSERT(TYPE)\
    bool list_##TYPE##_insert(list_##TYPE * _list, size_t _index, TYPE* _data);

#define LIST_METHOD_DECL_REMOVE(TYPE)\
    bool list_##TYPE##_remove(list_##TYPE * _list, size_t _index);


/* 5 */
#define LIST_METHOD_DEFN_COUNT(TYPE)\
    size_t list_##TYPE##_count(const list_##TYPE * _list)\
    {\
        return list_count(_list->_list);\
    }

#define LIST_METHOD_DEFN_ADD(TYPE)\
    size_t list_##TYPE##_add(list_##TYPE * _list, TYPE* _data)\
    {\
        _list->_list->count = list_add(_list->_list, _data);\
        return _list->_list->count;\
    }\

#define LIST_METHOD_DEFN_GET(TYPE)\
    TYPE* list_##TYPE##_get(list_##TYPE * _list, size_t _index)\
    {\
        return list_get(_list->_list, _index);\
    }\

#define LIST_METHOD_DEFN_SET(TYPE)\
    bool list_##TYPE##_set(list_##TYPE * _list, size_t _index, TYPE* _data)\
    {\
        return list_set(_list->_list, _index, _data);\
    }\

#define LIST_METHOD_DEFN_INSERT(TYPE)\
    bool list_##TYPE##_insert(list_##TYPE * _list, size_t _index, TYPE* _data)\
    {\
        return list_insert(_list->_list, _index, _data);\
    }\

#define LIST_METHOD_DEFN_REMOVE(TYPE)\
    bool list_##TYPE##_remove(list_##TYPE * _list, size_t _index)\
    {\
        return list_remove(_list->_list, _index);\
    }\

/* 6 */
#define LIST_METHOD_DECL_VAL_ADD(TYPE)\
    size_t list_##TYPE##_add(list_##TYPE * _list, TYPE _value);

#define LIST_METHOD_DECL_VAL_GET(TYPE)\
    TYPE list_##TYPE##_get(list_##TYPE * _list, size_t _index);

#define LIST_METHOD_DECL_VAL_SET(TYPE)\
    bool list_##TYPE##_set(list_##TYPE * _list, size_t _index, TYPE _value);

#define LIST_METHOD_DECL_VAL_INSERT(TYPE)\
    bool list_##TYPE##_insert (list_##TYPE * _list, size_t _index, TYPE _value);

#define LIST_METHOD_DECL_VAL_REMOVE(TYPE)\
    bool list_##TYPE##_remove (list_##TYPE * _list, size_t _index);

/* 8 */
#define LIST_METHOD_DECL_VAL_DESTROY(TYPE)\
    void destroy_list_##TYPE(list_##TYPE* _list);\
/* 8 */

#define LIST_METHOD_DEFN_VAL_ADD(TYPE)\
    size_t list_##TYPE##_add(list_##TYPE * _list, TYPE _value)\
    {\
        TYPE* temp = malloc(sizeof(TYPE));\
        *temp = _value;\
        return list_add(_list->_list, temp);\
    }\

#define LIST_METHOD_DEFN_VAL_GET(TYPE)\
    TYPE list_##TYPE##_get(list_##TYPE * _list, size_t _index)\
    {\
        TYPE* temp = list_get(_list->_list, _index);\
        return *temp;\
    }\

#define LIST_METHOD_DEFN_VAL_SET(TYPE)\
    bool list_##TYPE##_set(list_##TYPE * _list, size_t _index, TYPE _value)\
    {\
        list_node* node = list_get_node(_list->_list, _index);\
        if(node) {\
            *(TYPE *)node->data = _value;\
            return true; }\
        else\
            return false;\
    }\

#define LIST_METHOD_DEFN_VAL_INSERT(TYPE)\
    bool list_##TYPE##_insert (list_##TYPE * _list, size_t _index, TYPE _value)\
    {\
        TYPE* temp = malloc(sizeof(TYPE));\
        *temp = _value;\
        return list_insert(_list->_list, _index, temp);\
    }\

#define LIST_METHOD_DEFN_VAL_REMOVE(TYPE)\
    bool list_##TYPE##_remove (list_##TYPE * _list, size_t _index)\
    {\
        list_node* temp = list_get_node(_list->_list, _index);\
        free(temp->data);\
        return list_remove(_list->_list, _index);\
    }\

/* 8 */
#define LIST_METHOD_DEFN_VAL_DESTROY(TYPE)\
    void destroy_list_##TYPE(list_##TYPE* _list)\
    {\
        list_node* temp = _list->_list->begin;\
        while(temp)\
        {\
            free(temp->data);\
            temp = temp->next;\
        }\
        destroy_list(_list->_list);\
        free(_list);\
    }
/* 8 */

/* 7 */
#define LIST_DECLARE(TYPE)\
    LIST_TYPE(TYPE) LIST_METHOD_DECL_CREATE(TYPE) LIST_METHOD_DECL_DESTROY(TYPE)\
    LIST_METHOD_DECL_COUNT(TYPE) LIST_METHOD_DECL_ADD(TYPE) LIST_METHOD_DECL_GET(TYPE)\
    LIST_METHOD_DECL_SET(TYPE) LIST_METHOD_DECL_INSERT(TYPE) LIST_METHOD_DECL_REMOVE(TYPE)\

#define LIST_DEFINE(TYPE)\
    LIST_METHOD_DEFN_CREATE(TYPE) LIST_METHOD_DEFN_DESTROY(TYPE) LIST_METHOD_DEFN_COUNT(TYPE)\
    LIST_METHOD_DEFN_ADD(TYPE) LIST_METHOD_DEFN_GET(TYPE) LIST_METHOD_DEFN_SET(TYPE)\
    LIST_METHOD_DEFN_INSERT(TYPE) LIST_METHOD_DEFN_REMOVE(TYPE)\

#define LIST_VAL_DECLARE(TYPE)\
    LIST_TYPE(TYPE) LIST_METHOD_DECL_CREATE(TYPE) LIST_METHOD_DECL_VAL_DESTROY(TYPE)\
    LIST_METHOD_DECL_VAL_ADD(TYPE) LIST_METHOD_DECL_VAL_GET(TYPE) LIST_METHOD_DECL_VAL_SET(TYPE)\
    LIST_METHOD_DECL_VAL_INSERT(TYPE) LIST_METHOD_DECL_VAL_REMOVE(TYPE) LIST_METHOD_DECL_COUNT(TYPE)

#define LIST_VAL_DEFINE(TYPE)\
    LIST_METHOD_DEFN_CREATE(TYPE) LIST_METHOD_DEFN_VAL_DESTROY(TYPE)\
    LIST_METHOD_DEFN_VAL_ADD(TYPE) LIST_METHOD_DEFN_VAL_GET(TYPE) LIST_METHOD_DEFN_VAL_SET(TYPE)\
    LIST_METHOD_DEFN_VAL_INSERT(TYPE) LIST_METHOD_DEFN_VAL_REMOVE(TYPE) LIST_METHOD_DEFN_COUNT(TYPE)

#endif

/* 8
    I've added, a custom destroy macro, LIST_METHOD_DEFN_VAL_DESTROY(TYPE) for LIST_VAL_DECLARE(TYPE) and LIST_VAL_DEFINE(TYPE).
    This macro allow to clean memory leaks when destroying the list.
*/