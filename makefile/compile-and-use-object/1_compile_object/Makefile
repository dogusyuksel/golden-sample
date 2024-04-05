CFILES = $(wildcard *.c)
  
OFILES = $(patsubst %.c,%.o,$(wildcard *.c))

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
	gcc -c $(CFILES)

clean:
	rm -f $(OFILES) $(NAME)


.PHONY:  all clean
