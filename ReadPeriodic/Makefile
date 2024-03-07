RM = rm -rf
CFLAGS = -Werror -Wall -Wextra -g3 -O0
TARGET_EXECUTABLE_NAME=port_read_periodic

CFLAGS += -I../HWIO
CFLAGS += -I../TMR
CFLAGS += -Isrc

C_SRCS = \
../HWIO/hwio.c \
../TMR/tmr.c \
src/readperiodic.c \
src/main.c

OBJS += \
./../HWIO/hwio.o \
./../TMR/tmr.o \
./src/readperiodic.o \
./src/main.o

.PHONY: all clean

all:
	$(COMPILER) -o ./$(TARGET_EXECUTABLE_NAME) $(C_SRCS) $(CFLAGS) $(LIBS)
	@echo ' Finish all'

clean:
	$(RM) $(OBJS) ./$(TARGET_EXECUTABLE_NAME)
