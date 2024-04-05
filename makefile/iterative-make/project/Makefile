SUBDIRS = ../compile_object

CFILES = $(wildcard *.c)
  
OFILES = $(patsubst %.c,%.o,$(wildcard *.c))
  
CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
	$(foreach subdir,$(SUBDIRS),make -C $(subdir) all;)
	gcc $(CFILES) -o $(NAME) $(wildcard $(SUBDIRS)/*.o) -I$(SUBDIRS)

clean:
	$(foreach subdir,$(SUBDIRS),make -C $(subdir) clean;)
	rm -f $(OFILES) $(NAME)


.PHONY:  all clean
