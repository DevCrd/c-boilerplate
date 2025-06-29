#include <stdio.h>
#include "include/input_utils.h"

int main(void)
{
    int students = get_int("How many students? ");
    int subjects = get_int("How many subjects? ");

    string names[students];
    int scores[students][subjects];

    // got  error: too many arguments to function ‘get_string’ and now i have to catch the formatted characters

    char prompt[100];


    for (int i = 0; i < students; i++)
    {
        snprintf(prompt, sizeof(prompt), "Enter name of student %i: ", i + 1);
        names[i] = get_string(prompt);
        
        // names[i] = get_string("Enter name of student %i: ", i + 1);
        for (int j = 0; j < subjects; j++)
        {

            snprintf(prompt, sizeof(prompt), "Enter score for subject %i: ", j + 1);
            scores[i][j] = get_int(prompt);

            // this part works with cs50 
            // scores[i][j] = get_int("Enter score for subject %i: ", j + 1);
        }
    }

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

        if (average >= 70) grade = 'A';
        else if (average >= 60) grade = 'B';
        else if (average >= 50) grade = 'C';
        else if (average >= 45) grade = 'D';
        else grade = 'F';

        printf("%-8s %5i  %7.2f    %c\n", names[i], total, average, grade);
    }
}
