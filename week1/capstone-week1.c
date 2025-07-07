#include <stdio.h>
#include "include/input_utils.h"

// Grade cutoffs defined as constants so they’re easy to adjust
const int GRADE_A = 70;
const int GRADE_B = 60;
const int GRADE_C = 50;
const int GRADE_D = 45;

// Collect names and scores from the user
void collect_student_data(int students, int subjects, string names[], int scores[][subjects])
{
    char prompt[100];

    for (int i = 0; i < students; i++)
    {
        snprintf(prompt, sizeof(prompt), "Enter name of student %i: ", i + 1);
        names[i] = get_string(prompt);

        for (int j = 0; j < subjects; j++)
        {
            snprintf(prompt, sizeof(prompt), "Enter score for subject %i: ", j + 1);
            scores[i][j] = get_int(prompt);
        }
    }
}

// Calculate and display the final summary report
void print_summary_report(int students, int subjects, string names[], int scores[][subjects])
{
    printf("\n--- Summary Report ---\n");
    printf("Name     Total  Average  Grade\n");

    for (int i = 0; i < students; i++)
    {
        int total = 0;

        for (int j = 0; j < subjects; j++)
        {
            total += scores[i][j];
        }

        float average = (float) total / subjects;
        char grade;

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

        printf("%-8s %5i  %7.2f    %c\n", names[i], total, average, grade);
    }
}

int main(void)
{
    // Ask how many students and subjects we’re working with
    int students = get_int("How many students? ");
    int subjects = get_int("How many subjects? ");

    // Allocate space for student names and their scores
    string names[students];
    int scores[students][subjects];

    // Get all input data from the user
    collect_student_data(students, subjects, names, scores);

    // Show the final report
    print_summary_report(students, subjects, names, scores);

    return 0;
}
