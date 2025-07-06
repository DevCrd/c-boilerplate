#include <string.h>
#include <stdio.h>

void print_initials(int count, char *names[]) {
    printf("Initials: ");
    for (int i = 0; i < count; i++) {
        if (names[i][0] != '\0') {  // Check for non-empty string
            char initial = names[i][0];
            printf("%c", initial);
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <name1> [name2] [name3] ...\n", argv[0]);
        return 1;
    }

    // Skip argv[0] (program name), pass the rest to the function
    print_initials(argc - 1, &argv[1]);

    return 0;
}