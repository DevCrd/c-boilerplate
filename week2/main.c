#include "contact.h"

int main(int argc, char *argv[]) {
    ContactManager *manager = create_contact_manager();
    if (!manager) {
        return 1;
    }
    
    if (argc < 2) {
        print_usage(argv[0]);
        destroy_contact_manager(manager);
        return 1;
    }
    
    int i = 1;
    while (i < argc) {
        
        if (strcmp(argv[i], "-l") == 0) {
            // List all contacts
            list_all_contacts(manager);
            i++;
        }
        else if (strcmp(argv[i], "-a") == 0) {
            // Add contact
            if (i + 3 >= argc) {
                fprintf(stderr, "Error: -a requires name, phone, and email\n");
                destroy_contact_manager(manager);
                return 1;
            }
            if (!add_contact(manager, argv[i + 1], argv[i + 2], argv[i + 3])) {
                destroy_contact_manager(manager);
                return 1;
            }
            i += 4;
        }
        else if (strcmp(argv[i], "-r") == 0) {
            // Remove contact
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: -r requires a name\n");
                destroy_contact_manager(manager);
                return 1;
            }
            remove_contact(manager, argv[i + 1]);
            i += 2;
        }
        else if (strcmp(argv[i], "-s") == 0) {
            // Search contacts
            if (i + 1 >= argc) {
                fprintf(stderr, "Error: -s requires a search query\n");
                destroy_contact_manager(manager);
                return 1;
            }
            search_contacts(manager, argv[i + 1]);
            i += 2;
        }
        else if (strcmp(argv[i], "-i") == 0) {
            // Interactive mode: read contacts from user input
            interactive_add_contacts(manager);
            i++;
        }
        
        else if (strcmp(argv[i], "-h") == 0) {
            // Help
            print_usage(argv[0]);
            i++;
        }
        else {
            fprintf(stderr, "Error: Unknown option '%s'\n", argv[i]);
            print_usage(argv[0]);
            destroy_contact_manager(manager);
            return 1;
        }
    }
    
    // Clean up memory
    destroy_contact_manager(manager);
    return 0;
}
