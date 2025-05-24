#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 40

typedef struct {
    char course_code[20];
    char course_name[50];
} Course;

typedef struct {
    int mark;
    char the_grade;
    int grade_assigned; 
} Grade;

typedef struct {
    char reg_number[21];
    char name[51];
    int age;
    Course course;
    Grade grade;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

// Function to calculate grade from mark
char calculate_grade(int mark) {
    if (mark > 69) return 'A';
    else if (mark > 59) return 'B';
    else if (mark > 49) return 'C';
    else if (mark > 39) return 'D';
    else return 'E';
}

// Add a new student
void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    Student s;

    printf("Enter registration number: ");
    scanf(" %20s", s.reg_number);

    printf("Enter name: ");
    scanf(" %50[^\n]", s.name);

    printf("Enter age: ");
    scanf("%d", &s.age);

    printf("Enter course code: ");
    scanf(" %19s", s.course.course_code);

    printf("Enter course name: ");
    scanf(" %49[^\n]", s.course.course_name);

    s.grade.grade_assigned = 0;

    students[student_count++] = s;

    printf("Student added successfully.\n");
}

// Edit existing student
void edit_student() {
    char reg[21];
    printf("Enter registration number of student to edit: ");
    scanf(" %20s", reg);

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].reg_number, reg) == 0) {
            printf("Editing student: %s\n", students[i].name);

            printf("Enter new name: ");
            scanf(" %50[^\n]", students[i].name);

            printf("Enter new age: ");
            scanf("%d", &students[i].age);

            printf("Enter new course code: ");
            scanf(" %19s", students[i].course.course_code);

            printf("Enter new course name: ");
            scanf(" %49[^\n]", students[i].course.course_name);

            printf("Student details updated.\n");
            return;
        }
    }
    printf("Student not found.\n");
}

// Add marks and calculate grade
void add_marks() {
    char reg[21];
    printf("Enter registration number to add marks: ");
    scanf(" %20s", reg);

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].reg_number, reg) == 0) {
            if (students[i].grade.grade_assigned) {
                printf("Grade already assigned. Cannot be changed.\n");
                return;
            }

            int mark;
            printf("Enter mark (0-100): ");
            scanf("%d", &mark);

            if (mark < 0 || mark > 100) {
                printf("Invalid mark.\n");
                return;
            }

            students[i].grade.mark = mark;
            students[i].grade.the_grade = calculate_grade(mark);
            students[i].grade.grade_assigned = 1;

            printf("Mark and grade assigned successfully. Grade: %c\n", students[i].grade.the_grade);
            return;
        }
    }

    printf("Student not found.\n");
}

// Display all students
void display_students() {
    for (int i = 0; i < student_count; i++) {
        Student s = students[i];
        printf("\n--- Student %d ---\n", i + 1);
        printf("Reg No: %s\n", s.reg_number);
        printf("Name: %s\n", s.name);
        printf("Age: %d\n", s.age);
        printf("Course Code: %s\n", s.course.course_code);
        printf("Course Name: %s\n", s.course.course_name);
        if (s.grade.grade_assigned) {
            printf("Mark: %d\n", s.grade.mark);
            printf("Grade: %c\n", s.grade.the_grade);
        } else {
            printf("Grade: Not assigned\n");
        }
    }
}

// Menu
void menu() {
    int choice;
    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Edit Student\n");
        printf("3. Add Marks & Calculate Grade\n");
        printf("4. Display All Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: add_student(); break;
            case 2: edit_student(); break;
            case 3: add_marks(); break;
            case 4: display_students(); break;
            case 5: printf("Exiting...\n"); break;
            default: printf("Invalid option. Try again.\n");
        }

    } while (choice != 5);
}

int main() {
    menu();
    return 0;
}
