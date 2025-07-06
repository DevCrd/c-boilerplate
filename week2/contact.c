#include "contact.h"

ContactManager* create_contact_manager(void) {
    ContactManager *manager = malloc(sizeof(ContactManager));
    if (!manager) {
        fprintf(stderr, "Error: Failed to allocate memory for ContactManager\n");
        return NULL;
    }
    
    manager->contacts = malloc(INITIAL_CAPACITY * sizeof(Contact));
    if (!manager->contacts) {
        fprintf(stderr, "Error: Failed to allocate memory for contacts array\n");
        free(manager);
        return NULL;
    }
    
    manager->count = 0;
    manager->capacity = INITIAL_CAPACITY;
    return manager;
}

void destroy_contact_manager(ContactManager *manager) {
    if (manager) {
        if (manager->contacts) {
            free(manager->contacts);
        }
        free(manager);
    }
}

void trim_whitespace(char *str) {
    if (!str) return;
    
    // Trim leading whitespace
    char *start = str;
    while (*start == ' ' || *start == '\t' || *start == '\n' || *start == '\r') {
        start++;
    }
    
    // Trim trailing whitespace
    char *end = start + strlen(start) - 1;
    while (end > start && (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r')) {
        end--;
    }
    
    // Move trimmed string to beginning and null terminate
    int len = end - start + 1;
    memmove(str, start, len);
    str[len] = '\0';
}

int resize_contact_array(ContactManager *manager) {
    if (!manager) return 0;
    
    int new_capacity = manager->capacity * 2;
    Contact *new_contacts = realloc(manager->contacts, new_capacity * sizeof(Contact));
    
    if (!new_contacts) {
        fprintf(stderr, "Error: Failed to resize contacts array\n");
        return 0;
    }
    
    manager->contacts = new_contacts;
    manager->capacity = new_capacity;
    return 1;
}

int load_contacts_from_csv(ContactManager *manager, const char *filename) {
    if (!manager || !filename) return 0;
    
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s' for reading\n", filename);
        return 0;
    }
    
    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    
    while (fgets(line, sizeof(line), file)) {
        line_number++;
        
        // Skip empty lines
        trim_whitespace(line);
        if (strlen(line) == 0) continue;
        
        // Parse CSV line
        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        
        if (!name || !phone || !email) {
            fprintf(stderr, "Warning: Invalid format on line %d, skipping\n", line_number);
            continue;
        }
        
        // Trim whitespace from each field
        trim_whitespace(name);
        trim_whitespace(phone);
        trim_whitespace(email);
        
        // Check if we need to resize the array
        if (manager->count >= manager->capacity) {
            if (!resize_contact_array(manager)) {
                fclose(file);
                return 0;
            }
        }
        
        // Bounds checking and safe copying
        if (strlen(name) >= MAX_NAME_LENGTH || 
            strlen(phone) >= MAX_PHONE_LENGTH || 
            strlen(email) >= MAX_EMAIL_LENGTH) {
            fprintf(stderr, "Warning: Contact on line %d has fields that are too long, skipping\n", line_number);
            continue;
        }
        
        // Safe string copying with bounds checking
        strncpy(manager->contacts[manager->count].name, name, MAX_NAME_LENGTH - 1);
        manager->contacts[manager->count].name[MAX_NAME_LENGTH - 1] = '\0';
        
        strncpy(manager->contacts[manager->count].phone, phone, MAX_PHONE_LENGTH - 1);
        manager->contacts[manager->count].phone[MAX_PHONE_LENGTH - 1] = '\0';
        
        strncpy(manager->contacts[manager->count].email, email, MAX_EMAIL_LENGTH - 1);
        manager->contacts[manager->count].email[MAX_EMAIL_LENGTH - 1] = '\0';
        
        manager->count++;
    }
    
    fclose(file);
    printf("Loaded %d contacts from '%s'\n", manager->count, filename);
    printf("Memory usage: %zu bytes for contact data\n", 
           manager->count * sizeof(Contact));
    return 1;
}

int save_contacts_to_csv(ContactManager *manager, const char *filename) {
    if (!manager || !filename) return 0;
    
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file '%s' for writing\n", filename);
        return 0;
    }
    
    for (int i = 0; i < manager->count; i++) {
        fprintf(file, "%s,%s,%s\n", 
                manager->contacts[i].name,
                manager->contacts[i].phone,
                manager->contacts[i].email);
    }
    
    fclose(file);
    printf("Saved %d contacts to '%s'\n", manager->count, filename);
    return 1;
}

int add_contact(ContactManager *manager, const char *name, const char *phone, const char *email) {
    if (!manager || !name || !phone || !email) return 0;
    
    // Bounds checking
    if (strlen(name) >= MAX_NAME_LENGTH || 
        strlen(phone) >= MAX_PHONE_LENGTH || 
        strlen(email) >= MAX_EMAIL_LENGTH) {
        fprintf(stderr, "Error: One or more fields are too long\n");
        return 0;
    }
    
    // Check if we need to resize the array
    if (manager->count >= manager->capacity) {
        if (!resize_contact_array(manager)) {
            return 0;
        }
    }
    
    // Safe string copying with bounds checking
    strncpy(manager->contacts[manager->count].name, name, MAX_NAME_LENGTH - 1);
    manager->contacts[manager->count].name[MAX_NAME_LENGTH - 1] = '\0';
    
    strncpy(manager->contacts[manager->count].phone, phone, MAX_PHONE_LENGTH - 1);
    manager->contacts[manager->count].phone[MAX_PHONE_LENGTH - 1] = '\0';
    
    strncpy(manager->contacts[manager->count].email, email, MAX_EMAIL_LENGTH - 1);
    manager->contacts[manager->count].email[MAX_EMAIL_LENGTH - 1] = '\0';
    
    manager->count++;
    printf("Added contact: %s\n", name);
    return 1;
}

int remove_contact(ContactManager *manager, const char *name) {
    if (!manager || !name) return 0;
    
    for (int i = 0; i < manager->count; i++) {
        if (strcmp(manager->contacts[i].name, name) == 0) {
            // Shift remaining contacts down
            for (int j = i; j < manager->count - 1; j++) {
                manager->contacts[j] = manager->contacts[j + 1];
            }
            manager->count--;
            printf("Removed contact: %s\n", name);
            return 1;
        }
    }
    
    printf("Contact '%s' not found\n", name);
    return 0;
}

void search_contacts(ContactManager *manager, const char *query) {
    if (!manager || !query) return;
    
    int found = 0;
    printf("Search results for '%s':\n", query);
    printf("%-20s %-15s %-30s\n", "Name", "Phone", "Email");
    printf("%-20s %-15s %-30s\n", "----", "-----", "-----");
    
    for (int i = 0; i < manager->count; i++) {
        if (strstr(manager->contacts[i].name, query) ||
            strstr(manager->contacts[i].phone, query) ||
            strstr(manager->contacts[i].email, query)) {
            
            printf("%-20s %-15s %-30s\n",
                   manager->contacts[i].name,
                   manager->contacts[i].phone,
                   manager->contacts[i].email);
            found++;
        }
    }
    
    if (found == 0) {
        printf("No contacts found matching '%s'\n", query);
    } else {
        printf("\nFound %d contact(s)\n", found);
    }
}

void list_all_contacts(ContactManager *manager) {
    if (!manager) return;
    
    if (manager->count == 0) {
        printf("No contacts in the database\n");
        return;
    }
    
    printf("All contacts (%d total):\n", manager->count);
    printf("%-20s %-15s %-30s\n", "Name", "Phone", "Email");
    printf("%-20s %-15s %-30s\n", "----", "-----", "-----");
    
    for (int i = 0; i < manager->count; i++) {
        printf("%-20s %-15s %-30s\n",
               manager->contacts[i].name,
               manager->contacts[i].phone,
               manager->contacts[i].email);
    }
    
    printf("\nTotal entries: %d\n", manager->count);
    printf("Memory allocated: %d contacts (%zu bytes)\n", 
           manager->capacity, manager->capacity * sizeof(Contact));
    printf("Memory used: %d contacts (%zu bytes)\n", 
           manager->count, manager->count * sizeof(Contact));
}

void print_usage(const char *program_name) {
    printf("Contact Manager CLI\n");
    printf("Usage: %s [options]\n\n", program_name);
    printf("Options:\n");
    printf("  -f <file>              Load contacts from CSV file\n");
    printf("  -l                     List all contacts\n");
    printf("  -a <name> <phone> <email>  Add a new contact\n");
    printf("  -r <name>              Remove contact by name\n");
    printf("  -s <query>             Search contacts\n");
    printf("  -save <file>           Save contacts to CSV file\n");
    printf("  -h                     Show this help message\n\n");
    printf("Examples:\n");
    printf("  %s -f contacts.csv -l\n", program_name);
    printf("  %s -f contacts.csv -a \"John Doe\" \"555-1234\" \"john@email.com\"\n", program_name);
    printf("  %s -f contacts.csv -s \"John\"\n", program_name);
    printf("  %s -f contacts.csv -r \"John Doe\" -save contacts.csv\n", program_name);
}
