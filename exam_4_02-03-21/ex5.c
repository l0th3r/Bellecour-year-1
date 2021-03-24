#include "list_generic.h"
#include "check.h"


typedef struct {int a; float b; void* c; unsigned long d;} c_struct;
typedef enum {HELLO, WORLD} c_enum;

LIST_TYPE(float)
LIST_TYPE(c_struct)
LIST_TYPE(c_enum)

LIST_METHOD_DECL_CREATE(float)
LIST_METHOD_DECL_CREATE(c_struct)
LIST_METHOD_DECL_CREATE(c_enum)

LIST_METHOD_DECL_DESTROY(float)
LIST_METHOD_DECL_DESTROY(c_struct)
LIST_METHOD_DECL_DESTROY(c_enum)

LIST_METHOD_DECL_COUNT(float)
LIST_METHOD_DECL_COUNT(c_struct)
LIST_METHOD_DECL_COUNT(c_enum)

LIST_METHOD_DECL_ADD(float)
LIST_METHOD_DECL_ADD(c_struct)
LIST_METHOD_DECL_ADD(c_enum)

LIST_METHOD_DECL_GET(float)
LIST_METHOD_DECL_GET(c_struct)
LIST_METHOD_DECL_GET(c_enum)

LIST_METHOD_DECL_SET(float)
LIST_METHOD_DECL_SET(c_struct)
LIST_METHOD_DECL_SET(c_enum)

LIST_METHOD_DECL_INSERT(float)
LIST_METHOD_DECL_INSERT(c_struct)
LIST_METHOD_DECL_INSERT(c_enum)

LIST_METHOD_DECL_REMOVE(float)
LIST_METHOD_DECL_REMOVE(c_struct)
LIST_METHOD_DECL_REMOVE(c_enum)

#define TEST_LIST(LTYPE, LIST, VAL_A, VAL_B, VAL_C) \
	CHECK_EXEC("Creating list of type" #LTYPE , LIST = create_##LTYPE()); \
	CHECK_TRUE("Checking count of empty list of type " #LTYPE, LTYPE##_count(LIST) == 0); \
	CHECK_TRUE("Checking get on empty " #LTYPE, LTYPE##_get(LIST, 0) == NULL && LTYPE##_get(LIST, 1)  == NULL); \
	CHECK_TRUE("Adding elements to" #LTYPE, LTYPE##_add(LIST, VAL_A) == 1 && LTYPE##_add(LIST, VAL_B) == 2 && LTYPE##_count(LIST) == 2); \
	CHECK_TRUE("Getting elements of " #LTYPE, LTYPE##_get(LIST,0) == VAL_A && LTYPE##_get(LIST, 1) == VAL_B && LTYPE##_get(LIST, 2) == NULL); \
	CHECK_TRUE("Checking setting and inserting elements at invalid indexes on " #LTYPE, LTYPE##_set(LIST, 2, VAL_C) == false && LTYPE##_set(LIST, 3, VAL_C) ==  false && LTYPE##_insert(LIST, 3, VAL_C) == false && LTYPE##_insert(LIST, 4, VAL_C) == false && LTYPE##_count(LIST) == 2 && LTYPE##_get(LIST, 0) == VAL_A && LTYPE##_get(LIST, 1) == VAL_B); \
	CHECK_TRUE("Setting and inserting elements on " #LTYPE, LTYPE##_set(LIST, 1, VAL_A) == true && LTYPE##_insert(LIST, 0, VAL_C) == true && LTYPE##_count(LIST) == 3 && LTYPE##_get(LIST, 0) == VAL_C && LTYPE##_get(LIST, 1) == VAL_A && LTYPE##_get(LIST, 2) == VAL_A) \
       CHECK_TRUE("Trying to remove elements at invalid indices on " #LTYPE, LTYPE##_remove(LIST, 3) == false && LTYPE##_remove(LIST, 4) == false && LTYPE##_count(LIST) == 3 && LTYPE##_get(LIST, 0) == VAL_C && LTYPE##_get(LIST, 1) == VAL_A && LTYPE##_get(LIST, 2) == VAL_A) \
	CHECK_TRUE("Removing elements on " #LTYPE, LTYPE##_remove(LIST, 0) == true && LTYPE##_remove(LIST, 1) == true && LTYPE##_count(LIST) == 1 && LTYPE##_get(LIST, 0) == VAL_A) \
	CHECK_EXEC("Destroying list" #LTYPE, destroy_##LTYPE(LIST))

int main()
{
	list_float* lf;
	list_c_struct* lcs;
	list_c_enum* lce;
	float fa, fb, fc;
	c_struct csa, csb, csc;
	c_enum cea, ceb, cec;

	TEST_LIST(list_float, lf, &fa, &fb, &fc);
	TEST_LIST(list_c_struct, lcs, &csa, &csb, &csc);
	TEST_LIST(list_c_enum, lce, &cea, &ceb, &cec);


	return 0;
}


LIST_METHOD_DEFN_CREATE(float)
LIST_METHOD_DEFN_CREATE(c_struct)
LIST_METHOD_DEFN_CREATE(c_enum)
LIST_METHOD_DEFN_DESTROY(float)
LIST_METHOD_DEFN_DESTROY(c_struct)
LIST_METHOD_DEFN_DESTROY(c_enum)

LIST_METHOD_DEFN_COUNT(float)
LIST_METHOD_DEFN_COUNT(c_struct)
LIST_METHOD_DEFN_COUNT(c_enum)
LIST_METHOD_DEFN_ADD(float)
LIST_METHOD_DEFN_ADD(c_struct)
LIST_METHOD_DEFN_ADD(c_enum)
LIST_METHOD_DEFN_GET(float)
LIST_METHOD_DEFN_GET(c_struct)
LIST_METHOD_DEFN_GET(c_enum)
LIST_METHOD_DEFN_SET(float)
LIST_METHOD_DEFN_SET(c_struct)
LIST_METHOD_DEFN_SET(c_enum)
LIST_METHOD_DEFN_INSERT(float)
LIST_METHOD_DEFN_INSERT(c_struct)
LIST_METHOD_DEFN_INSERT(c_enum)
LIST_METHOD_DEFN_REMOVE(float)
LIST_METHOD_DEFN_REMOVE(c_struct)
LIST_METHOD_DEFN_REMOVE(c_enum)
