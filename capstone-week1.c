#include <stdio.h>
#include "include/input_utils.h"

int main(void)
{
    // Ask user for number of students and subjects
    int students = get_int("How many students? ");
    int subjects = get_int("How many subjects? ");

    // Declare array to store student names
    string names[students];
    // Declare 2D array to store scores for each student and subject
    int scores[students][subjects];

    // Grade thresholds as named constants (magic numbers removed)
    const int GRADE_A = 70;
    const int GRADE_B = 60;
    const int GRADE_C = 50;
    const int GRADE_D = 45;

    // Buffer to hold formatted prompt strings
    char prompt[100];

    // Input loop: get names and scores for each student
    for (int i = 0; i < students; i++)
    {
        // Create formatted prompt: "Enter name of student 1: "
        snprintf(prompt, sizeof(prompt), "Enter name of student %i: ", i + 1);
        names[i] = get_string(prompt);

        for (int j = 0; j < subjects; j++)
        {
            // Create formatted prompt: "Enter score for subject 1: "
            snprintf(prompt, sizeof(prompt), "Enter score for subject %i: ", j + 1);
            scores[i][j] = get_int(prompt);
        }
    }

    // Print summary report header
    printf("\n--- Summary Report ---\n");
    printf("Name     Total  Average  Grade\n");

    // Process and print each student's total, average, and grade
    for (int i = 0; i < students; i++)
    {
        int total = 0;
        for (int j = 0; j < subjects; j++)
        {
            total += scores[i][j];
        }

        float average = (float) total / subjects;
        char grade;

        // Determine grade based on average using thresholds
        if (average >= GRADE_A)
            grade = 'A';
        else if (average >= GRADE_B)
            grade = 'B';
        else if (average >= GRADE_C)
            grade = 'C';
        else if (average >= GRADE_D)
            grade = 'D';
        else
            grade = 'F';

        // Print formatted summary line for each student
        printf("%-8s %5i  %7.2f    %c\n", names[i], total, average, grade);
    }
}
