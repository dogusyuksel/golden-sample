include includeme.mk

CFILES = $(CURRENT_DIR)/main.c
  
OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
	gcc $(CFILES) -o $(NAME)

clean:
	rm -f $(OFILES) $(NAME)


.PHONY:  all clean
