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

int main()
{
	list_float* lf;
	list_c_struct* lcs;
	list_c_enum* lce;

	CHECK_EXEC("Creating list of floats", lf = create_list_float());
	CHECK_EXEC("Creating list of custom struct", lcs = create_list_c_struct());
	CHECK_EXEC("Creating list of custom enum", lce = create_list_c_enum());

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

