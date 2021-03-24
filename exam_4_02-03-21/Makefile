CC = clang
CFLAGS = -g -O0 -Wall -Werror
VALGRINDFLAGS = --log-file=memcheck.log --leak-check=full -q 

ex%.o: ex%.c list_generic.h list.h
	$(info Compiling with exercise $i test...) $(CC) $(CFLAGS) -c $<

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

ex%: ex%.o list.o
	$(info Linking with list code...) $(CC) $^ -o $@

exec_test_ex% : ex%
	@valgrind $(VALGRINDFLAGS) ./$^ 

test_ex% : exec_test_ex%
	@sh memcheck.sh
	

