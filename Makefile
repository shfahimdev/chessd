CC = gcc
CFLAGS = -Wall -Wextra -g -Isrc
TARGET = chessd
SRCS = $(shell find src/ -name "*.c")
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	find src/ -name "*.o" -delete
