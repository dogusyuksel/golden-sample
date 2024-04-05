CFILES = $(wildcard *.c)
  
OFILES = $(patsubst %.c,%.o,$(CFILES))

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
	gcc $(CFILES) -o $(NAME)

clean:
	rm -f $(OFILES) $(NAME)


.PHONY:  all clean
