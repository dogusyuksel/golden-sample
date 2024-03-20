CFILES = main.c
  
OFILES = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

LIB_PATH = ./../lib
INC_PATH = ./../lib
LIB_NAME = mylibrary

NAME = executable

all:
	gcc $(CFILES) -L$(LIB_PATH) -l$(LIB_NAME) -I$(INC_PATH) -o $(NAME) -Wl,-rpath=$(LIB_PATH)

clean:
	rm -f $(OFILES) $(NAME)


.PHONY:  all clean
