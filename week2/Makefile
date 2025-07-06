CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = contact_manager
SOURCES = main.c contact.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c contact.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

test: $(TARGET)
	@echo "Creating sample CSV file..."
	@echo "John Doe,555-1234,john@email.com" > sample_contacts.csv
	@echo "Jane Smith,555-5678,jane@email.com" >> sample_contacts.csv
	@echo "Bob Johnson,555-9012,bob@email.com" >> sample_contacts.csv
	@echo ""
	@echo "Testing load and list:"
	./$(TARGET) -f sample_contacts.csv -l
	@echo ""
	@echo "Testing search:"
	./$(TARGET) -f sample_contacts.csv -s "John"
	@echo ""
	@echo "Testing add and save:"
	./$(TARGET) -f sample_contacts.csv -a "Alice Brown" "555-3456" "alice@email.com" -save updated_contacts.csv -l

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

help:
	@echo "Available targets:"
	@echo "  all     - Build the contact manager"
	@echo "  clean   - Remove object files and executable"
	@echo "  test    - Run basic functionality tests"
	@echo "  install - Install to /usr/local/bin"
	@echo "  help    - Show this help message"
