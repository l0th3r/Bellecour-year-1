# COMPILER
CC=gcc

# FILES
CARD_FILES= card_lib/types/types.c card_lib/manipulate/manipulate.c card_lib/display/display.c
FILES= *.c

# FLAGS
NORME_FLAGS= -std=c89 -pedantic
DEBUG_FLAGS= -Wall -Werror -g
BEFORE_FLAGS= $(NORME_FLAGS) $(DEBUG_FLAGS)
LIBS= -lncurses

debug:$(FILES)
	$(CC) $(BEFORE_FLAGS) $(FILES) $(CARD_FILES) $(LIBS) -odebug