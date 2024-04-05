CFILES = $(wildcard *.c)
  
OFILES = $(patsubst %.c,%.o,$(wildcard *.c))

CFLAGS = -Wall -Wextra -Werror

NAME = executable

CC = gcc

ifeq ($(COMPILER),GPP)
  CC = g++
endif

all:
	$(CC) $(CFILES) -o $(NAME)

clean:
	rm -f $(OFILES) $(NAME)


.PHONY:  all clean
