OBJS = mylibrary.o

CFLAGS = -Wall -Wextra -Werror
CFLAG += -fPIC
NAME = libmylibrary.so

all: $(NAME)

$(OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@


$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)


.PHONY:  all clean
