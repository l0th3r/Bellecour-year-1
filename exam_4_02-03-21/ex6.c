#include "list_generic.h"
#include "check.h"


typedef struct {int a; float b; void* c; unsigned long d;} c_struct;
typedef enum {HELLO, NICE, WORLD} c_enum;
typedef unsigned long long ullong;

LIST_TYPE(float)
LIST_TYPE(ullong)
LIST_TYPE(c_enum)

LIST_METHOD_DECL_CREATE(float)
LIST_METHOD_DECL_CREATE(ullong)
LIST_METHOD_DECL_CREATE(c_enum)

LIST_METHOD_DECL_DESTROY(float)
LIST_METHOD_DECL_DESTROY(ullong)
LIST_METHOD_DECL_DESTROY(c_enum)

LIST_METHOD_DECL_COUNT(float)
LIST_METHOD_DECL_COUNT(ullong)
LIST_METHOD_DECL_COUNT(c_enum)

LIST_METHOD_DECL_VAL_ADD(float)
LIST_METHOD_DECL_VAL_ADD(ullong)
LIST_METHOD_DECL_VAL_ADD(c_enum)

LIST_METHOD_DECL_VAL_GET(float)
LIST_METHOD_DECL_VAL_GET(ullong)
LIST_METHOD_DECL_VAL_GET(c_enum)

LIST_METHOD_DECL_VAL_SET(float)
LIST_METHOD_DECL_VAL_SET(ullong)
LIST_METHOD_DECL_VAL_SET(c_enum)

LIST_METHOD_DECL_VAL_INSERT(float)
LIST_METHOD_DECL_VAL_INSERT(ullong)
LIST_METHOD_DECL_VAL_INSERT(c_enum)

LIST_METHOD_DECL_VAL_REMOVE(float)
LIST_METHOD_DECL_VAL_REMOVE(ullong)
LIST_METHOD_DECL_VAL_REMOVE(c_enum)

#define TEST_LIST(LTYPE, LIST, VAL_A, VAL_B, VAL_C) \
	CHECK_EXEC("Creating list of type" #LTYPE , LIST = create_##LTYPE()); \
	CHECK_TRUE("Checking count of empty list of type " #LTYPE, LTYPE##_count(LIST) == 0); \
	CHECK_TRUE("Adding elements to" #LTYPE, LTYPE##_add(LIST, VAL_A) == 1 && LTYPE##_add(LIST, VAL_B) == 2 && LTYPE##_count(LIST) == 2); \
	CHECK_TRUE("Getting elements of " #LTYPE, LTYPE##_get(LIST,0) == VAL_A && LTYPE##_get(LIST, 1) == VAL_B); \
	CHECK_TRUE("Setting and inserting elements on " #LTYPE, LTYPE##_set(LIST, 1, VAL_A) == true && LTYPE##_insert(LIST, 0, VAL_C) == true && LTYPE##_count(LIST) == 3 && LTYPE##_get(LIST, 0) == VAL_C && LTYPE##_get(LIST, 1) == VAL_A && LTYPE##_get(LIST, 2) == VAL_A) \
	CHECK_TRUE("Removing elements on " #LTYPE, LTYPE##_remove(LIST, 0) == true && LTYPE##_remove(LIST, 1) == true && LTYPE##_count(LIST) == 1 && LTYPE##_get(LIST, 0) == VAL_A) \
	CHECK_EXEC("Destroying list" #LTYPE, destroy_##LTYPE(LIST))

int main()
{
	list_float* lf;
	list_ullong* lull;
	list_c_enum* lce;
	float fa = .1f, fb = 10.f, fc = -3.1f;
	ullong ulla = 100, ullb = 1000, ullc = 123456789;
	c_enum cea = NICE, ceb = HELLO, cec = WORLD;

	TEST_LIST(list_float, lf, fa, fb, fc);
	TEST_LIST(list_ullong, lull, ulla, ullb, ullc);
	TEST_LIST(list_c_enum, lce, cea, ceb, cec);


	return 0;
}


LIST_METHOD_DEFN_CREATE(float)
LIST_METHOD_DEFN_CREATE(ullong)
LIST_METHOD_DEFN_CREATE(c_enum)
LIST_METHOD_DEFN_DESTROY(float)
LIST_METHOD_DEFN_DESTROY(ullong)
LIST_METHOD_DEFN_DESTROY(c_enum)

LIST_METHOD_DEFN_COUNT(float)
LIST_METHOD_DEFN_COUNT(ullong)
LIST_METHOD_DEFN_COUNT(c_enum)
LIST_METHOD_DEFN_VAL_ADD(float)
LIST_METHOD_DEFN_VAL_ADD(ullong)
LIST_METHOD_DEFN_VAL_ADD(c_enum)
LIST_METHOD_DEFN_VAL_GET(float)
LIST_METHOD_DEFN_VAL_GET(ullong)
LIST_METHOD_DEFN_VAL_GET(c_enum)
LIST_METHOD_DEFN_VAL_SET(float)
LIST_METHOD_DEFN_VAL_SET(ullong)
LIST_METHOD_DEFN_VAL_SET(c_enum)
LIST_METHOD_DEFN_VAL_INSERT(float)
LIST_METHOD_DEFN_VAL_INSERT(ullong)
LIST_METHOD_DEFN_VAL_INSERT(c_enum)
LIST_METHOD_DEFN_VAL_REMOVE(float)
LIST_METHOD_DEFN_VAL_REMOVE(ullong)
LIST_METHOD_DEFN_VAL_REMOVE(c_enum)
