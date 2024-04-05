FILES = main.c dummy.a dummy.k
CFILES = $(filter %.c,$(FILES))

# or use filter-out like below
# GARBAGE_FILES = dummy.a dummy.k
# CFILES = $(filter $(GARBAGE_FILES),$(FILES))
  
OFILES = $(patsubst %.c,%.o,$(CFILES))

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
	gcc $(CFILES) -o $(NAME)

clean:
	rm -f $(OFILES) $(NAME)


.PHONY:  all clean
