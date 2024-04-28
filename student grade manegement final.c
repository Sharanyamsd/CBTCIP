#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 10
#define MAX_SUBJECTS 8
#define MAX_NAME_LENGTH 100

const char *subject_names[MAX_SUBJECTS] = {"Physics", "Chemistry", "Biology", "Geography", "Civics", "Bengali", "English", "Mathematics"};

typedef struct {
    char name[MAX_NAME_LENGTH];
    int scores[MAX_SUBJECTS];
    double average_score;
    char grade;
    double cgpa;
} Student;

void input_student_info(Student students[], int *num_students);
void identify_highest_lowest_scores(Student students[], int num_students);
void display_student_data(Student students[], int num_students);
void display_summary(Student students[], int num_students);
void display_average_scores(Student students[], int num_students);

int main() {
    Student students[MAX_STUDENTS];
    int num_students = 0;

    printf("Welcome to the Student Grade Management System\n");

    while (1) {
        printf("\n1. Input student information\n2. Identify highest and lowest scores\n3. Display student data\n4. Display summary\n5. Display average scores\n6. Exit\n\nEnter choice: ");
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                input_student_info(students, &num_students);
                break;
            case 2:
                identify_highest_lowest_scores(students, num_students);
                break;
            case 3:
                display_student_data(students, num_students);
                break;
            case 4:
                display_summary(students, num_students);
                break;
            case 5:
                display_average_scores(students, num_students);
                break;
            case 6:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

void input_student_info(Student students[], int *num_students) {
	int i;
    if (*num_students == MAX_STUDENTS) {
        printf("Maximum number of students reached\n");
        return;
    }

    Student new_student;

    printf("Enter student name: ");
    scanf("%s", new_student.name);

    printf("Enter scores for each subject (out of 100):\n");

    // Iterate through each subject to prompt for scores
    for ( i = 0; i < MAX_SUBJECTS; i++) {
        printf("%s: ", subject_names[i]);
        scanf("%d", &new_student.scores[i]);
    }

    students[*num_students] = new_student;
    (*num_students)++;

    printf("Student information recorded successfully\n");
}

void identify_highest_lowest_scores(Student students[], int num_students) {
	int i,j;
    for ( i = 0; i < num_students; i++) {
        int highest_score = 0, lowest_score = 100;
        char highest_subject[MAX_NAME_LENGTH], lowest_subject[MAX_NAME_LENGTH];

        for ( j = 0; j < MAX_SUBJECTS; j++) {
            if (students[i].scores[j] > highest_score) {
                highest_score = students[i].scores[j];
                strcpy(highest_subject, subject_names[j]);
            }
            if (students[i].scores[j] < lowest_score) {
                lowest_score = students[i].scores[j];
                strcpy(lowest_subject, subject_names[j]);
            }
        }

        printf("Highest score for %s: %s - %d\n", students[i].name, highest_subject, highest_score);
        printf("Lowest score for %s: %s - %d\n", students[i].name, lowest_subject, lowest_score);
    }
}

void display_student_data(Student students[], int num_students) {
	int i;
    printf("Student List:\n");
    for (i = 0; i < num_students; i++) {
        printf("%d. %s\n", i + 1, students[i].name);
    }

    int choice;
    printf("\nEnter the number corresponding to the student: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > num_students) {
        printf("Invalid choice\n");
        return;
    }

    printf("Student: %s\n", students[choice - 1].name);
    printf("Subject Scores:\n");

    // Calculate and display individual subject scores
    for (i = 0; i < MAX_SUBJECTS; i++) {
        printf("%s: %d\n", subject_names[i], students[choice - 1].scores[i]);
    }
}

void display_summary(Student students[], int num_students) {
	int i,j;
    printf("Summary of student performance:\n");

    for ( i = 0; i < num_students; i++) {
        double total_score = 0.0;
        for ( j = 0; j < MAX_SUBJECTS; j++) {
            total_score += students[i].scores[j];
        }
        students[i].average_score = total_score / MAX_SUBJECTS;

        // Calculate grade
        if (students[i].average_score >= 90) {
            students[i].grade = 'O';
        } else if (students[i].average_score >= 80) {
            students[i].grade = 'E';
        } else if (students[i].average_score >= 70) {
            students[i].grade = 'A';
        } else if (students[i].average_score >= 60) {
            students[i].grade = 'B';
        } else if (students[i].average_score >= 50) {
            students[i].grade = 'C';
        } else if (students[i].average_score >= 40) {
            students[i].grade = 'D';
        } else {
            students[i].grade = 'F';
        }

        // Calculate CGPA
        double grade_points = 0;
        for (j = 0; j < MAX_SUBJECTS; j++) {
            if (students[i].scores[j] >= 90) {
                grade_points += 10;
            } else if (students[i].scores[j] >= 80) {
                grade_points += 9;
            } else if (students[i].scores[j] >= 70) {
                grade_points += 8;
            } else if (students[i].scores[j] >= 60) {
                grade_points += 7;
            } else if (students[i].scores[j] >= 50) {
                grade_points += 6;
            } else if (students[i].scores[j] >= 40) {
                grade_points += 5;
            } else {
                grade_points += 2;
            }
        }
        students[i].cgpa = grade_points / MAX_SUBJECTS;

        printf("Student: %s\n", students[i].name);
        printf("Average Score: %.2lf\n", students[i].average_score);
        printf("Grade: %c\n", students[i].grade);
        printf("CGPA: %.2lf\n\n", students[i].cgpa);
    }
}

void display_average_scores(Student students[], int num_students) {
	int i,j;
    printf("Average scores of each student:\n");
    for ( i = 0; i < num_students; i++) {
        double total_score = 0.0;
        for (j = 0; j < MAX_SUBJECTS; j++) {
            total_score += students[i].scores[j];
        }
        students[i].average_score = total_score / MAX_SUBJECTS;
        printf("Student: %s, Average Score: %.2lf\n", students[i].name, students[i].average_score);
    }
}
