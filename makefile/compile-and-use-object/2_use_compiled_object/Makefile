INCLUDE_DIR = ../1_compile_object

CFILES = $(wildcard *.c)
  
OFILES = $(patsubst %.c,%.o,$(wildcard *.c))
  
LINKED_OFILES = $(wildcard $(INCLUDE_DIR)/*.o)

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
	gcc $(CFILES) -o $(NAME) $(LINKED_OFILES) -I$(INCLUDE_DIR)

clean:
	rm -f $(OFILES) $(NAME)


.PHONY:  all clean
