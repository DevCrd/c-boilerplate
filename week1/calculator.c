#include <stdio.h>

int main() {
    double num1, num2;
    char operator;

    // Prompt the user for input
    printf("Enter an operation in the format: number operator number (e.g. 5 + 3): ");
    scanf("%lf %c %lf", &num1, &operator, &num2);

    // Perform the chosen operation
    switch (operator) {
        case '+':
            printf("%.2lf + %.2lf = %.2lf\n", num1, num2, num1 + num2);
            break;
        case '-':
            printf("%.2lf - %.2lf = %.2lf\n", num1, num2, num1 - num2);
            break;
        case '*':
            printf("%.2lf * %.2lf = %.2lf\n", num1, num2, num1 * num2);
            break;
        case '/':
            if (num2 != 0) {
                printf("%.2lf / %.2lf = %.2lf\n", num1, num2, num1 / num2);
            } else {
                printf("Error: Division by zero is not allowed.\n");
            }
            break;
        default:
            printf("Error: Unsupported operator '%c'\n", operator);
    }

    return 0;
}
