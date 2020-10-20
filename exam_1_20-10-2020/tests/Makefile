CC = clang
CFLAGS = -std=c89 -pedantic -c -Wall -Werror

ex%.o: ex%.c
	$(CC) $(CFLAGS) -c $^

test_ex% : ex%.o exam_1.o check.o
	$(info Linking with exercise $* test...) \
	$(CC) $(C) $^ -o $@ \
	&& ./$@

test_ex4:
	$(info No functional check for exercise 4)
