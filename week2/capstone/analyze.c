#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define MAX_LEN 1024
#define ALPHA 26

// Function prototypes
long parse_and_validate_key(char *key_str);
int get_user_input(char *text, int max_len);
void encrypt_caesar_cipher(char *text, int key);
void count_letters_and_vowels(char *text, int *total_letters, int *vowel_count);
void display_results(char *ciphertext, int vowel_count, int total_letters);
void demonstrate_concepts(int key, int vowel_count, int total_letters);
void print_usage(char *program_name);
void print_header();
int is_vowel(char c);
void clear_input_buffer();

int main(int argc, char* argv[])
{
    print_header();
    
    // Step 1: Validate command-line arguments
    if (argc != 2) {
        print_usage(argv[0]);
        return 1;
    }
    
    // Step 2: Parse and validate key
    long key = parse_and_validate_key(argv[1]);
    if (key < 0 || key > INT_MAX) {
        printf("Error: Key must be a non-negative integer not exceeding %d\n", INT_MAX);
        printf("You entered: %s\n", argv[1]);
        return 1;
    }
    
    // Step 3: Get user input
    char text[MAX_LEN];
    if (get_user_input(text, MAX_LEN) != 0) {
        printf("Error: Failed to read input or input is empty\n");
        return 1;
    }
    
    // Step 4: Encrypt the text
    encrypt_caesar_cipher(text, (int)key);
    
    // Step 5: Analyze the encrypted text
    int total_letters = 0;
    int vowel_count = 0;
    count_letters_and_vowels(text, &total_letters, &vowel_count);
    
    // Step 6: Display results
    display_results(text, vowel_count, total_letters);
    
    // Step 7: Demonstrate programming concepts
    demonstrate_concepts((int)key, vowel_count, total_letters);
    
    printf("\nThank you for using the Caesar Cipher Analyzer!\n");
    return 0;
}

void print_header()
{
    printf("==========================================\n");
    printf("     Caesar Cipher + Vowel Analyzer      \n");
    printf("==========================================\n\n");
}

void print_usage(char *program_name)
{
    printf("Usage: %s <key>\n", program_name);
    printf("Where <key> is a non-negative integer\n\n");
    printf("Examples:\n");
    printf("  %s 5           # Shift letters by 5 positions\n", program_name);
    printf("  %s 13          # ROT13 cipher\n", program_name);
    printf("  %s 3000000000  # Demonstrate integer overflow\n", program_name);
    printf("\nNote: Keys larger than %d will be rejected\n", INT_MAX);
}

long parse_and_validate_key(char *key_str)
{
    char *endptr;
    errno = 0; // Reset errno before conversion
    long key = strtol(key_str, &endptr, 10);
    
    // Check if the entire string was consumed and valid
    if (endptr == key_str || *endptr != '\0') {
        return -1; // Invalid input (non-numeric or partial numeric)
    }
    
    // Check for negative numbers or overflow
    if (key < 0 || errno == ERANGE) {
        return -1;
    }
    
    return key;
}

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Clear remaining characters in input buffer
    }
}

int get_user_input(char *text, int max_len)
{
    printf("Enter your plaintext message:\n");
    printf("plaintext: ");
    
    if (fgets(text, max_len, stdin) == NULL) {
        return -1; // Error reading input
    }
    
    // Remove trailing newline if present
    int len = strlen(text);
    if (len > 0 && text[len-1] == '\n') {
        text[len-1] = '\0';
        len--;
    } else if (len == max_len - 1) {
        // Input was truncated; clear the buffer
        clear_input_buffer();
        printf("Warning: Input truncated to %d characters\n", max_len - 1);
    }
    
    // Check for empty input
    if (len == 0) {
        return -1;
    }
    
    return 0; // Success
}

void encrypt_caesar_cipher(char *text, int key)
{
    // Optimize key by reducing modulo 26 once
    key = key % ALPHA;
    if (key < 0) {
        key += ALPHA; // Handle negative keys (defensive programming)
    }
    
    printf("\nEncrypting with Caesar cipher (effective key = %d)...\n", key);
    
    for (int i = 0; text[i]; i++) {
        char c = text[i];
        
        if (isupper(c)) {
            c = 'A' + (c - 'A' + key) % ALPHA;
        }
        else if (islower(c)) {
            c = 'a' + (c - 'a' + key) % ALPHA;
        }
        // Non-alphabetic characters remain unchanged
        
        text[i] = c;
    }
}

int is_vowel(char c)
{
    // Direct comparison for efficiency - covers both cases
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
}

void count_letters_and_vowels(char *text, int *total_letters, int *vowel_count)
{
    *total_letters = 0;
    *vowel_count = 0;
    
    for (int i = 0; text[i]; i++) {
        char c = text[i];
        
        if (isalpha(c)) {
            (*total_letters)++;
            
            if (is_vowel(c)) {
                (*vowel_count)++;
            }
        }
    }
}

void display_results(char *ciphertext, int vowel_count, int total_letters)
{
    printf("\n==========================================\n");
    printf("                RESULTS                   \n");
    printf("==========================================\n");
    
    printf("ciphertext: %s\n\n", ciphertext);
    
    if (total_letters > 0) {
        // Use double for better precision demonstration
        double ratio = 100.0 * vowel_count / total_letters;
        printf("Letter Analysis:\n");
        printf("  Total letters: %d\n", total_letters);
        printf("  Vowels found:  %d\n", vowel_count);
        printf("  Vowel ratio:   %.2f%%\n", ratio);
        printf("  Summary: %d/%d\t(%.2f%%)\n", vowel_count, total_letters, ratio);
    } else {
        printf("No alphabetic characters found in the text.\n");
        printf("Vowels: 0/0\t(0.00%%)\n");
    }
}

void demonstrate_concepts(int key, int vowel_count, int total_letters)
{
    printf("\n==========================================\n");
    printf("         PROGRAMMING CONCEPTS             \n");
    printf("==========================================\n");
    
    printf("Key Information:\n");
    printf("  Original key: %d\n", key);
    printf("  Effective rotation: %d positions (key %% %d)\n", key % ALPHA, ALPHA);
    
    // Demonstrate integer overflow behavior
    if (key > 2000000000) {
        printf("\n🔍 INTEGER OVERFLOW DEMONSTRATION:\n");
        printf("  Large key (%d) demonstrates modular arithmetic\n", key);
        printf("  Despite the huge number, only %d positions are used\n", key % ALPHA);
        printf("  This shows how C handles large integers with modulo\n");
        printf("  Note: We used strtol() for safer parsing than atoi()\n");
    }
    
    // Demonstrate floating-point precision
    if (total_letters > 0) {
        printf("\n🔍 FLOATING-POINT PRECISION DEMONSTRATION:\n");
        printf("  Exact fraction: %d/%d\n", vowel_count, total_letters);
        
        // Show different precision levels
        float ratio_float = 100.0f * vowel_count / total_letters;
        double ratio_double = 100.0 * vowel_count / total_letters;
        
        printf("  As float (32-bit):  %.10f%%\n", ratio_float);
        printf("  As double (64-bit): %.10f%%\n", ratio_double);
        printf("  Rounded display:    %.2f%%\n", ratio_double);
        printf("  This demonstrates floating-point representation limits\n");
    }
    
    printf("\n📚 Week 1 & 2 Concepts Demonstrated:\n");
    printf("  ✓ Command-line arguments (argc/argv)\n");
    printf("  ✓ String manipulation and character arrays\n");
    printf("  ✓ Character classification functions\n");
    printf("  ✓ Modular arithmetic and Caesar cipher\n");
    printf("  ✓ Floating-point vs double precision\n");
    printf("  ✓ Integer overflow and safe parsing\n");
    printf("  ✓ Loops, conditionals, and functions\n");
    printf("  ✓ Input validation and error handling\n");
    printf("  ✓ Escape sequences (\\n, \\t, %%%%)\n");
}


/*
 * Caesar + Vowel Analyzer CLI
 * 
 * PSEUDOCODE:
 * 1. Check command-line arguments (exactly 1 key)
 * 2. Parse key as non-negative integer with robust validation
 * 3. Prompt user for plaintext input with error handling
 * 4. Read plaintext using fgets (max 1024 chars)
 * 5. Encrypt text using Caesar cipher:
 *    - Rotate A-Z and a-z by key % 26
 *    - Leave other characters unchanged
 * 6. Count total alphabetic characters
 * 7. Count vowels (A,E,I,O,U case-insensitive)
 * 8. Calculate vowel-to-letter ratio as percentage
 * 9. Print ciphertext and statistics with formatting
 * 10. Demonstrate integer overflow and floating-point precision
 */
