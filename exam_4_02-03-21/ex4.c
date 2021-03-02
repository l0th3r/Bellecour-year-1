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



int main()
{
	list_float* lf;
	list_c_struct* lcs;
	list_c_enum* lce;
	float f;
	c_struct cs;
	c_enum ce;

	CHECK_EXEC("Creating list of floats", lf = create_list_float());
	CHECK_EXEC("Creating list of custom struct", lcs = create_list_c_struct());
	CHECK_EXEC("Creating list of custom enum", lce = create_list_c_enum());

	CHECK_EXEC("Using list methods on float list", 
		list_float_count(lf);
		list_float_add(lf, &f);
		list_float_get(lf, 0);
		list_float_set(lf, 0, &f);
		list_float_insert(lf, 0, &f);
		list_float_remove(lf, 0);
	);

	CHECK_EXEC("Using list methods on custom struct list", 
		list_c_struct_count(lcs);
		list_c_struct_add(lcs, &cs);
		list_c_struct_get(lcs, 0);
		list_c_struct_set(lcs, 0, &cs);
		list_c_struct_insert(lcs, 0, &cs);
		list_c_struct_remove(lcs, 0);
	);

	CHECK_EXEC("Using list methods on custom enum list", 
		list_c_enum_count(lce);
		list_c_enum_add(lce, &ce);
		list_c_enum_get(lce, 0);
		list_c_enum_set(lce, 0, &ce);
		list_c_enum_insert(lce, 0, &ce);
		list_c_enum_remove(lce, 0);
	);


	CHECK_EXEC("Destroying list of floats", destroy_list_float(lf));
	CHECK_EXEC("Destroying list of custom struct", destroy_list_c_struct(lcs));
	CHECK_EXEC("Destroying list of custom enum", destroy_list_c_enum(lce));

	return 0;
}


LIST_METHOD_DEFN_CREATE(float)
LIST_METHOD_DEFN_CREATE(c_struct)
LIST_METHOD_DEFN_CREATE(c_enum)
LIST_METHOD_DEFN_DESTROY(float)
LIST_METHOD_DEFN_DESTROY(c_struct)
LIST_METHOD_DEFN_DESTROY(c_enum)

size_t list_float_count (const list_float *_list) {return 0;}
size_t list_float_add (list_float *_list, float *_data) {return 0;}
float* list_float_get (list_float *_list, size_t _index) {return NULL;}
bool list_float_set (list_float* _list, size_t _index, float* data) {return NULL;}
bool list_float_insert (list_float *_list, size_t _index, float* _data) {return false;}
bool list_float_remove (list_float *_list, size_t _index) {return false;}

size_t list_c_struct_count (const list_c_struct *_list) {return 0;}
size_t list_c_struct_add (list_c_struct *_list, c_struct *_data) {return 0;}
c_struct* list_c_struct_get (list_c_struct *_list, size_t _index) {return NULL;}
bool list_c_struct_set (list_c_struct* _list, size_t _index, c_struct* data) {return NULL;}
bool list_c_struct_insert (list_c_struct *_list, size_t _index, c_struct* _data) {return false;}
bool list_c_struct_remove (list_c_struct *_list, size_t _index) {return false;}

size_t list_c_enum_count (const list_c_enum *_list) {return 0;}
size_t list_c_enum_add (list_c_enum *_list, c_enum *_data) {return 0;}
c_enum* list_c_enum_get (list_c_enum *_list, size_t _index) {return NULL;}
bool list_c_enum_set (list_c_enum* _list, size_t _index, c_enum* data) {return NULL;}
bool list_c_enum_insert (list_c_enum *_list, size_t _index, c_enum* _data) {return false;}
bool list_c_enum_remove (list_c_enum *_list, size_t _index) {return false;}

