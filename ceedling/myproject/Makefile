RM = rm -rf
CFLAGS = -Werror -Wall -Wextra -g3 -O0
TARGET_EXECUTABLE_NAME=myproject.exe

CFLAGS += -I../hwdependentcode
CFLAGS += -I../thirdpartycode
CFLAGS += -Isrc

C_SRCS = \
	../hwdependentcode/randombytegenerator.c \
	../thirdpartycode/customprint.c \
	src/customprintrandom.c \
	src/main.c

OBJS += $(C_SRCS:.c=.o)

.PHONY: all clean

all:
	$(CC) -o ./$(TARGET_EXECUTABLE_NAME) $(C_SRCS) $(CFLAGS)
	@echo ' Finish all'

clean:
	$(RM) $(OBJS) ./$(TARGET_EXECUTABLE_NAME)
