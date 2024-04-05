CFILES = $(wildcard *.c)
  
OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
	gcc $(CFILES) -o $(NAME)

clean:
	rm -f $(OFILES) $(NAME)


.PHONY:  all clean
