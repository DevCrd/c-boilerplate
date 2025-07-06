<!-- # Contact Manager CLI

A robust command-line contact management application written in C that demonstrates proper memory management, CSV file handling, and secure programming practices.

## Features

- **CSV File Support**: Load and save contacts from/to CSV files
- **Dynamic Memory Management**: Automatically resizes contact array as needed
- **Buffer Overflow Protection**: All string operations use bounds checking
- **Command-Line Interface**: Full argc/argv argument parsing
- **Memory Reporting**: Uses sizeof to report memory usage and entry counts
- **Search Functionality**: Search contacts by name, phone, or email
- **Proper Cleanup**: All allocated memory is properly freed

## Compilation

\`\`\`bash
make all
\`\`\`

Or compile manually:
\`\`\`bash
gcc -Wall -Wextra -std=c99 -g main.c contact.c -o contact_manager
\`\`\`

## Usage

\`\`\`bash
# Load contacts from CSV and list all
./contact_manager -f contacts.csv -l

# Add a new contact
./contact_manager -f contacts.csv -a "John Doe" "555-1234" "john@email.com"

# Search for contacts
./contact_manager -f contacts.csv -s "John"

# Remove a contact and save
./contact_manager -f contacts.csv -r "John Doe" -save contacts.csv

# Show help
./contact_manager -h
\`\`\`

## Command-Line Options

- `-f <file>`: Load contacts from CSV file
- `-l`: List all contacts with memory usage information
- `-a <name> <phone> <email>`: Add a new contact
- `-r <name>`: Remove contact by name
- `-s <query>`: Search contacts (searches name, phone, and email fields)
- `-save <file>`: Save current contacts to CSV file
- `-h`: Show help message

## CSV Format

The CSV file should have the format:
\`\`\`
Name,Phone,Email
John Doe,555-1234,john@email.com
Jane Smith,555-5678,jane@email.com
\`\`\`

## Security Features

1. **Buffer Overflow Prevention**: All string operations use `strncpy()` with proper bounds checking
2. **Input Validation**: Validates all input parameters and file operations
3. **Memory Safety**: Proper allocation, reallocation, and deallocation of memory
4. **Bounds Checking**: Array access is always bounds-checked
5. **Safe String Handling**: All strings are null-terminated and length-checked

## Memory Management

- Dynamic array that starts with 10 contacts and doubles in size when needed
- Proper cleanup of all allocated memory using `free()`
- Memory usage reporting shows both allocated and used memory
- Uses `sizeof()` to calculate and report memory usage accurately

## Testing

Run the included test suite:
\`\`\`bash
make test
\`\`\`

This will:
1. Create a sample CSV file
2. Test loading and listing contacts
3. Test search functionality
4. Test adding contacts and saving

## Project Structure

- `contact.h`: Header file with structure definitions and function prototypes
- `contact.c`: Core functionality implementation
- `main.c`: Command-line interface and argument parsing
- `Makefile`: Build configuration
- `sample_contacts.csv`: Sample data for testing

## Capstone Requirements Met

✅ **CSV Reading**: Reads CSV files into array of Contact structures  
✅ **Command-Line Arguments**: Full argc/argv parsing with multiple options  
✅ **Add/Remove/Search**: Complete CRUD operations via command line  
✅ **Buffer Overflow Protection**: All string operations use bounds checking  
✅ **sizeof Usage**: Reports memory usage and entry counts using sizeof  
✅ **Memory Cleanup**: Proper free() of all allocated memory  
✅ **Dynamic Arrays**: Automatically resizes contact array as needed  
✅ **Error Handling**: Comprehensive error checking and reporting  

## Example Session

\`\`\`bash
$ ./contact_manager -f sample_contacts.csv -l
Loaded 5 contacts from 'sample_contacts.csv'
Memory usage: 1100 bytes for contact data
All contacts (5 total):
Name                 Phone           Email                         
----                 -----           -----                         
John Doe             555-1234        john.doe@email.com           
Jane Smith           555-5678        jane.smith@email.com         
Bob Johnson          555-9012        bob.johnson@email.com        
Alice Brown          555-3456        alice.brown@email.com        
Charlie Wilson       555-7890        charlie.wilson@email.com     

Total entries: 5
Memory allocated: 10 contacts (2200 bytes)
Memory used: 5 contacts (1100 bytes) -->
