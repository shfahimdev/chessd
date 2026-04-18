# The compiler we're using
CC = gcc

# Compiler flags:
# -Wall = show all warnings
# -Wextra = show extra warnings
# -g = include debug info (so gdb works)
CFLAGS = -Wall -Wextra -g

# The final binary name
TARGET = chessd

# All .c files in src/ are our sources
SRCS = src/main.c

# For each .c file, there will be a .o (object) file
# This replaces the src/ prefix and .c suffix with .o
OBJS = $(SRCS:.c=.o)

# Default target — what runs when you just type `make`
all: $(TARGET)

# Link all object files into the final binary
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each .c file into a .o file
# $< = the .c file, $@ = the .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove all compiled files
clean:
	rm -f $(OBJS) $(TARGET)
