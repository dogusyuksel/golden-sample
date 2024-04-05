INCLUDE_DIR = ../thirdpartylib

CFILES = $(wildcard *.c)
CFILES += $(wildcard $(INCLUDE_DIR)/*.c)
  
OFILES = $(patsubst %.c,%.o,$(wildcard *.c))

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
	gcc $(CFILES) -o $(NAME) -I$(INCLUDE_DIR)

clean:
	rm -f $(OFILES) $(NAME)


.PHONY:  all clean
