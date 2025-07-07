#include "include/input_utils.h"
#include <stdio.h>

int main() {
    char name[50];
    int age = get_int("Enter your age: ");
    get_string("Enter your name: ");
    printf("Hello, %s! You are %d years old.\n", name, age);
    return 0;
}