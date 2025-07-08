# Compiler and flags
CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g
TARGET  = contact_manager

# Sources and objects
SOURCES = main.c contact.c
OBJECTS = $(SOURCES:.c=.o)

# Default target
.PHONY: all clean run test install help

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.c contact.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

# Quick run (example: list then add a contact, then list)
run: $(TARGET)
	./$(TARGET) -l -a "John Doe" "555-1234" "john@email.com" -l

# Basic test with multiple argv operations
test: $(TARGET)
	@echo ""
	@echo "Running tests with command-line arguments only:"
	@echo "-----------------------------------------------"
	./$(TARGET) -a "Alice" "555-0000" "alice@email.com" -a "Bob" "555-1111" "bob@email.com" -l
	@echo ""
	./$(TARGET) -s "Alice"
	@echo ""
	./$(TARGET) -r "Alice" -l



help:
	@echo "Available targets:"
	@echo "  all      - Build the contact manager"
	@echo "  clean    - Remove object files and executable"
	@echo "  run      - Build and run with sample argv commands"
	@echo "  test     - Run basic functionality tests (argv only)"
	@echo "  help     - Show this help message"
