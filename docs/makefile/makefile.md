# General Usage

```

MAKEFILE
	> -C <dir>		--> changing directory
	> -d			--> print debug logs
	> -I <dir>		--> include header files
	> -j <number>	--> simultaneous jobs
	> -o <name>		--> executable name
	> -Werror		--> shows error
	> -Wall			--> treat warnings as error
	> -g<number>	--> used for development
	> -O<number>	--> optimization
	> -L <dir>		--> library directory
	> -l<name>		--> library name
	> -c			--> creating object file
	> .PHONY: all clean
	> .EXPORT_ALL_VARIABLES
	> .ONESHELL
	> -fPIC -shared		--> create shared library
	> -WL, -rpath=<dir>	--> load and use shared library in runtime
```

# Examples

## include-mk example

Just type "make all"

### structure
```
├── includeme.mk
├── main.c
└── Makefile
```

### Makefile
```
include includeme.mk

CFILES = $(CURRENT_DIR)/main.c
  
OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
        gcc $(CFILES) -o $(NAME)

clean:
        rm -f $(OFILES) $(NAME)


.PHONY:  all clean
```

### include.mk
```
CURRENT_DIR ?= $(shell pwd)
```

## condition (and different directory) example

Just execute "runmake.sh"

```
├── project
│   ├── main.c
│   └── Makefile
└── runmake.sh
```

### runmake.sh

```
#!/bin/bash

make -C project COMPILER=GPP all
```

### makefile

```
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
```

## iterative makefile example

in the makefile under "compile_object" folder just creating object files from the sorce and the other one uses these object.
so just executing make under the "project" will be enough

```
├── compile_object
│   ├── afile.c
│   ├── afile.h
│   └── Makefile
└── project
    ├── main.c
    └── Makefile
```

### makefile in compile_object folder

```
CFILES = $(wildcard *.c)
  
OFILES = $(patsubst %.c,%.o,$(wildcard *.c))

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
        gcc -c $(CFILES)

clean:
        rm -f $(OFILES) $(NAME)


.PHONY:  all clean
```

### makefile in "project" folder

```
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
```

## include third party lib example

```
├── project
│   ├── main.c
│   └── Makefile
└── thirdpartylib
    ├── afile.c
    └── afile.h
```

### makefile

```
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
```

## static lib example

Makefile under "lib" will create a static library, so it should be executed first
the other makefile in the project folder will use this library, so it should be executed later on

```
├── lib
│   ├── Makefile
│   ├── mylibrary.c
│   └── mylibrary.h
└── project
    ├── main.c
    └── Makefile
```

### makefile under lib folder

```
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
```

### makefile under project folder

```
CFILES = main.c
  
OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

LIB_PATH = ./../lib
INC_PATH = ./../lib
LIB_NAME = mylibrary

NAME = executable

all:
        gcc $(CFILES) -L$(LIB_PATH) -l$(LIB_NAME) -I$(INC_PATH) -o $(NAME)

clean:
        rm -f $(OFILES) $(NAME)


.PHONY:  all clean
```

## dynamic lib example

Makefile under "lib" will create a static library, so it should be executed first
the other makefile in the project folder will use this library, so it should be executed later on

```
├── lib
│   ├── Makefile
│   ├── mylibrary.c
│   └── mylibrary.h
└── project
    ├── main.c
    └── Makefile
```

### makefile under lib folder

```
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
```

### makefile under project folder

```
CFILES = main.c
  
OFILES = $(CFILES:.c=.o)

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
```

## functions examples

### filter function

```
├── main.c
└── Makefile
```

```
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
```

### findstring function

```
└── Makefile
```

```
MYSTRING = asdasd
MYSUBSTRING = asp

ifneq ($(findstring $(MYSUBSTRING),$(MYSTRING)),$(MYSUBSTRING))
        RESULT = "does not contain"
else
        RESULT = "contain"
endif

all:
        @echo 'RESULT $(RESULT)'

.PHONY:  all
```

### pathsubst function

```
├── main.c
└── Makefile
```

```
CFILES = $(wildcard *.c)
  
OFILES = $(patsubst %.c,%.o,$(CFILES))

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
        gcc $(CFILES) -o $(NAME)

clean:
        rm -f $(OFILES) $(NAME)


.PHONY:  all clean
```

### sort function

```
└── Makefile
```

```
MYSTRING = aaa  bsd asd asd asd asd bsd
SORTED = $(sort $(MYSTRING))

all:
        @echo 'RESULT $(SORTED)'

.PHONY:  all
```

### strip function

```
└── Makefile
```

```
MYSTRING = "this is dummy       string"
  
AFTER_STRIP = $(strip  $(MYSTRING))

all:
        @echo 'AFTER_STRIP $(AFTER_STRIP)'

.PHONY:  all
```

### subst function

```
├── main.c
└── Makefile
```

```
CFILES = main.c
  
OFILES = $(subst .c,.o,$(CFILES))

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
        gcc $(CFILES) -o $(NAME)

clean:
        rm -f $(OFILES) $(NAME)


.PHONY:  all clean
```

### word function

```
└── Makefile
```

```
MYSTRING = aaa  bsd asd asd asd asd bsd
Nth = $(word 2, $(MYSTRING))
# $(wordlist 2, 3, $(MYSTRING)) where 2 si starting and 3 is ending index
# $(words text) -> Returns the number of words in text. Thus, the last word of text is $(word $(words text),text).

all:
        @echo 'RESULT $(Nth)'

.PHONY:  all
```

### wildcard function

```
├── main.c
└── Makefile
```

```
CFILES = $(wildcard *.c)
  
OFILES = $(CFILES:.c=.o)

CFLAGS = -Wall -Wextra -Werror

NAME = executable

all:
        gcc $(CFILES) -o $(NAME)

clean:
        rm -f $(OFILES) $(NAME)


.PHONY:  all clean
```

