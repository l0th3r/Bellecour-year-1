#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {void* data; size_t count; size_t capacity; size_t type_size;} dynamic_array;

size_t dynamic_array_set(dynamic_array* darray, size_t index, const void* value);

/* EX 01 */
dynamic_array* create_dynamic_array(size_t type_size)
{
	dynamic_array* to_return = malloc(sizeof(dynamic_array));

	if(!to_return)
	{
		fprintf(stderr, "\nERROR: memoty allocation failed, pointer creation aborted.\n\n");
		to_return = NULL;
	}
	else
	{
		to_return->data = NULL;
		to_return->count = 0;
		to_return->capacity = 0;
		to_return->type_size = type_size;
	}

	return to_return;
}

/* EX 02 */
size_t dynamic_array_count(const dynamic_array* darray)
{
	return darray->count;
}

/* EX 03 */
size_t dynamic_array_reserve(dynamic_array* darray, size_t capacity)
{
	void* temp = darray->data;
	
	if(capacity > darray->capacity)
	{
		darray->data = realloc(darray->data, capacity * darray->type_size);

		if(darray->data)
			darray->capacity = capacity;
		else
		{
			darray->data = temp;
			fprintf(stderr, "\nERROR: memory allocation failed, reservation aborted.\n\n");	
		}
	}

	return darray->capacity;
}

/* EX 04 */
size_t dynamic_array_resize(dynamic_array* darray, size_t size)
{
	size_t catemp = darray->capacity;
	size_t cotemp = darray->count;
	void* temp = NULL;

	if(cotemp < size)
	{
		temp = calloc(size - cotemp, darray->type_size);
		if(!temp)
			fprintf(stderr, "\nERROR: memory allocation failed, resize aborted.\n\n");	
	}

	if(size > darray->capacity)
	{
		if(temp)
		{
			if(dynamic_array_reserve(darray, size) != catemp)
				darray->count = size;
		}
	}
	else
		darray->count = size;

	if(temp)
		memcpy(((char*)darray->data + (cotemp * darray->type_size)), temp, (size - cotemp) * darray->type_size);

	free(temp);

	return darray->count;
}

/* EX 05 */
size_t dynamic_array_shrink(dynamic_array* darray)
{
	void* temp = darray->data;

	if(darray->capacity > darray->count)
	{
		darray->data = realloc(darray->data, (darray->count + 1) * (darray->type_size));

		if(darray->data)
			darray->capacity = darray->count;
		else
		{
			darray->data = temp;
			fprintf(stderr, "\nERROR: memory allocation failed, shrink aborted.\n\n");	
		}
	}

	return darray->capacity;
}


/* EX 06 */
void* dynamic_array_get(dynamic_array* darray, size_t index)
{
	if(index < darray->count)
		return ((char*) darray->data + (index * darray->type_size));
	else
	{
		return NULL;
		fprintf(stderr, "\nERROR: attempt cause a segmentation fault, get aborted.\n\n");	
	}
}

/* EX 07 */
size_t dynamic_array_set(dynamic_array* darray, size_t index, const void* value)
{
	size_t to_return;

	if(index < darray->count)
	{
		memcpy(((char*) darray->data + (index * darray->type_size)), value, darray->type_size);
		to_return = 1;
	}
	else
	{
		fprintf(stderr, "\nERROR: attempt cause a segmentation fault, set aborted.\n\n");	
		to_return = 0;
	}

	return to_return;
}

/* EX 08 */
size_t dynamic_array_add(dynamic_array* darray, const void* value)
{
	if(value == NULL)
		return 0;

	if (darray->count == darray->capacity)
	{
		if (darray->capacity == 0)
			dynamic_array_reserve(darray, 1);
		else
			dynamic_array_reserve(darray, darray->capacity * 2);
	}

	darray->count += 1;

	return dynamic_array_set(darray, darray->count - 1, value);
}

/* EX 09 */
size_t dynamic_array_append(dynamic_array* darray, const dynamic_array* darray_to_append)
{
	int i = 0;
	size_t temp;
	size_t to_return = 1;	

	if(darray->type_size == darray_to_append->type_size)
	{
		while(i < darray_to_append->count)
		{
			temp = dynamic_array_add(darray, ((char*) darray_to_append->data + (i++ * darray->type_size)));
			if(temp != 1)
				to_return = 0;
		}
	}
	else
	{
		fprintf(stderr, "\nERROR: the two provided arrays have different types, append aborted.\n\n");	
		to_return = 0;
	}

	return to_return;
}

/* EX 10 */
void destroy_dynamic_array(dynamic_array* darray)
{
	free(darray->data);
	darray->data = NULL;
	darray->count = 0;
	darray->capacity = 0;
	free(darray);
}

/* EX 11 */

typedef struct {dynamic_array* darray;} dynamic_char_array;

typedef struct {dynamic_array* darray;} dynamic_int_array;

typedef struct {dynamic_array* darray;} dynamic_float_array;

/* CHAR */
dynamic_char_array* create_dynamic_char_array()
{
	dynamic_char_array* char_darray = (dynamic_char_array*)malloc(sizeof(dynamic_array));

	char_darray->darray = create_dynamic_array(sizeof(char));

	return char_darray;
}

size_t dynamic_char_array_count(const dynamic_char_array* darray)
{
	return darray->darray->count;
}

size_t dynamic_char_array_reserve(dynamic_char_array* darray, size_t capacity)
{
	return dynamic_array_reserve(darray->darray, capacity);
}

size_t dynamic_char_array_resize(dynamic_char_array* darray, size_t size)
{
	return dynamic_array_resize(darray->darray, size);
}

size_t dynamic_char_array_shrink(dynamic_char_array* darray)
{
	return dynamic_array_shrink(darray->darray);
}

char dynamic_char_array_get(dynamic_char_array* darray, size_t index)
{
	return *(char*)dynamic_array_get(darray->darray, index);
}

size_t dynamic_char_array_set(dynamic_char_array* darray, size_t index, char value)
{
	return dynamic_array_set(darray->darray, index, &value);
}

size_t dynamic_char_array_add(dynamic_char_array* darray, char value)
{
	return dynamic_array_add(darray->darray, &value);
}

size_t dynamic_char_array_append(dynamic_char_array* darray, dynamic_char_array* darray_to_append)
{
	return dynamic_array_append(darray->darray, darray_to_append->darray);
}

void destroy_dynamic_char_array(dynamic_char_array* darray)
{
	destroy_dynamic_array(darray->darray);
	free(darray);
}

/* INT */
dynamic_int_array* create_dynamic_int_array()
{
	dynamic_int_array* int_darray = (dynamic_int_array*)malloc(sizeof(dynamic_array));

	int_darray->darray = create_dynamic_array(sizeof(int));

	return int_darray;
}

size_t dynamic_int_array_count(const dynamic_int_array* darray)
{
	return darray->darray->count;
}

size_t dynamic_int_array_reserve(dynamic_int_array* darray, size_t capacity)
{
	return dynamic_array_reserve(darray->darray, capacity);
}

size_t dynamic_int_array_resize(dynamic_int_array* darray, size_t size)
{
	return dynamic_array_resize(darray->darray, size);
}

size_t dynamic_int_array_shrink(dynamic_int_array* darray)
{
	return dynamic_array_shrink(darray->darray);
}

int dynamic_int_array_get(dynamic_int_array* darray, size_t index)
{
	return *(int*)dynamic_array_get(darray->darray, index);
}

size_t dynamic_int_array_set(dynamic_int_array* darray, size_t index, int value)
{
	return dynamic_array_set(darray->darray, index, &value);
}

size_t dynamic_int_array_add(dynamic_int_array* darray, int value)
{
	return dynamic_array_add(darray->darray, &value);
}

size_t dynamic_int_array_append(dynamic_int_array* darray, dynamic_int_array* darray_to_append)
{
	return dynamic_array_append(darray->darray, darray_to_append->darray);
}

void destroy_dynamic_int_array(dynamic_int_array* darray)
{
	destroy_dynamic_array(darray->darray);
	free(darray);
}

/* FLOAT */
dynamic_float_array* create_dynamic_float_array()
{
	dynamic_float_array* float_darray = (dynamic_float_array*)malloc(sizeof(dynamic_array));
	
	float_darray->darray = create_dynamic_array(sizeof(float));

	return float_darray;
}

size_t dynamic_float_array_count(const dynamic_float_array* darray)
{
	return darray->darray->count;
}

size_t dynamic_float_array_reserve(dynamic_float_array* darray, size_t capacity)
{
	return dynamic_array_reserve(darray->darray, capacity);
}

size_t dynamic_float_array_resize(dynamic_float_array* darray, size_t size)
{
	return dynamic_array_resize(darray->darray, size);
}

size_t dynamic_float_array_shrink(dynamic_float_array* darray)
{
	return dynamic_array_shrink(darray->darray);
}

float dynamic_float_array_get(dynamic_float_array* darray, size_t index)
{
	return *(float*)dynamic_array_get(darray->darray, index);
}

size_t dynamic_float_array_set(dynamic_float_array* darray, size_t index, float value)
{
	return dynamic_array_set(darray->darray, index, &value);
}

size_t dynamic_float_array_add(dynamic_float_array* darray, float value)
{
	return dynamic_array_add(darray->darray, &value);
}

size_t dynamic_float_array_append(dynamic_float_array* darray, dynamic_float_array* darray_to_append)
{
	return dynamic_array_append(darray->darray, darray_to_append->darray);
}

void destroy_dynamic_float_array(dynamic_float_array* darray)
{
	destroy_dynamic_array(darray->darray);
	free(darray);
}

/* EX 12 */

typedef struct {dynamic_array* darray; size_t max_size;} stack, char_stack, int_stack, float_stack;

stack* create_stack(size_t _max_size, size_t _type_size)
{
	stack* _stack = (stack*)malloc(sizeof(dynamic_array));

	if(_stack != NULL)
	{
		_stack->darray = create_dynamic_array(_type_size);
		if(_max_size == 0)
			_stack->max_size = 999999999;
		else
			_stack->max_size = _max_size;
	}
	else
	{
		fprintf(stderr, "\nERROR: allocation failed, stack creation aborted.\n\n");	
	}

	return _stack;
}

void destroy_stack(stack* _stack)
{
	destroy_dynamic_array(_stack->darray);
	free(_stack);
}

/* EX 13 */
size_t stack_count(const stack* _stack)
{
	return dynamic_array_count(_stack->darray);
}

/* EX 14 */
const void* stack_get_top(const stack* _stack)
{
	return dynamic_array_get(_stack->darray, _stack->darray->count - 1);
}

/* EX 15 */
size_t stack_add_top(stack* _stack, void* _value_ptr) {

	if (_stack->darray->count + 1 > _stack->max_size)
	{
		fprintf(stderr, "\nERROR: stack maximum size exeeded\n");
		return 0;
	}
	else
		return dynamic_array_add(_stack->darray, _value_ptr);
}

/* EX 16 */
void stack_remove_top(stack* _stack)
{
	dynamic_array_resize(_stack->darray, _stack->darray->count - 1);
}

/* EX 17 */

/* CHAR */
stack* create_char_stack(size_t _max_size)
{
	return create_stack(_max_size, sizeof(char));
}

void destroy_char_stack(stack* _stack)
{
	destroy_stack(_stack);
}

size_t stack_char_count(const stack* _stack)
{
	return dynamic_array_count(_stack->darray);
}

char stack_char_get_top(const stack* _stack)
{
	return *(char*)dynamic_array_get(_stack->darray, _stack->darray->count - 1);
}

size_t stack_char_add_top(stack* _stack, char value) 
{
	return stack_add_top(_stack, &value);
}

void stack_char_remove_top(stack* _stack)
{
	dynamic_array_resize(_stack->darray, _stack->darray->count - 1);
}

/* INT */
stack* create_int_stack(size_t _max_size)
{
	return create_stack(_max_size, sizeof(int));
}

void destroy_int_stack(stack* _stack)
{
	destroy_stack(_stack);
}

size_t stack_int_count(const stack* _stack)
{
	return dynamic_array_count(_stack->darray);
}

int stack_int_get_top(const stack* _stack)
{
	return *(int*)dynamic_array_get(_stack->darray, _stack->darray->count - 1);
}

size_t stack_int_add_top(stack* _stack, int value) 
{
	return stack_add_top(_stack, &value);
}

void stack_int_remove_top(stack* _stack)
{
	dynamic_array_resize(_stack->darray, _stack->darray->count - 1);
}

/* FLOAT */
stack* create_float_stack(size_t _max_size)
{
	return create_stack(_max_size, sizeof(float));
}

void destroy_float_stack(stack* _stack)
{
	destroy_stack(_stack);
}

size_t stack_float_count(const stack* _stack)
{
	return dynamic_array_count(_stack->darray);
}

float stack_float_get_top(const stack* _stack)
{
	return *(float*)dynamic_array_get(_stack->darray, _stack->darray->count - 1);
}

size_t stack_float_add_top(stack* _stack, float value) 
{
	return stack_add_top(_stack, &value);
}

void stack_float_remove_top(stack* _stack)
{
	dynamic_array_resize(_stack->darray, _stack->darray->count - 1);
}
