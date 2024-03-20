OBJS = mylibrary.o

CFLAGS = -Wall -Wextra -Werror
NAME = libmylibrary.a

all: $(NAME)

$(OBJS): %.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@


$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS) 

clean:
	rm -f $(OBJS)


.PHONY:  all clean
