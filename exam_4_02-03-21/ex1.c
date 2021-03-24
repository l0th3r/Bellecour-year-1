#include "list_generic.h"
#include "check.h"


typedef struct {int a; float b; void* c; unsigned long d;} c_struct;
typedef enum {HELLO, WORLD} c_enum;

LIST_TYPE(float)
LIST_TYPE(c_struct)
LIST_TYPE(c_enum)

void stack_alloc_lists();

int main()
{
	list_float* lf;
	list_c_struct* lcs;
	list_c_enum* lce;

	CHECK_TRUE("Allocating list of floats", (lf = malloc(sizeof(list_float))) != NULL);
	CHECK_TRUE("Allocating list of custom struct", (lcs = malloc(sizeof(list_c_struct))) != NULL);
	CHECK_TRUE("Allocating list of custom enum", (lce = malloc(sizeof(list_c_enum))) != NULL);

	CHECK_EXEC("Allocating lists on the stack", stack_alloc_lists());

	CHECK_EXEC("Releasing lists", free(lf); free(lcs); free(lce));
	return 0;
}

void stack_alloc_lists()
{
	list_float lf;
	list_c_struct lcs;
	list_c_enum lce;

	/* The following prevents the unused variable warning */
	void * ptr;
	ptr = &lf;
	ptr = &lcs;
	ptr = &lce;
}
