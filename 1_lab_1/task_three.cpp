#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Course class
class Course {
public:
    string code;
    string name;

    Course(string c, string n) : code(c), name(n) {}
};

// Grade class
class Grade {
public:
    int mark;
    char letter;
    bool locked;

    Grade() : mark(-1), letter(' '), locked(false) {}

    char getLetterGrade(int m) {
        if (m > 69) return 'A';
        if (m > 59) return 'B';
        if (m > 49) return 'C';
        if (m > 39) return 'D';
        return 'E';
    }

    void setGrade(int m) {
        mark = m;
        letter = getLetterGrade(m);
        locked = true;
    }
};

// Student class
class Student {
public:
    string reg;
    string name;
    int age;
    Course course;
    Grade grade;

    Student(string r, string n, int a, Course c) : reg(r), name(n), age(a), course(c) {}

    void display() const {
        cout << "Reg: " << reg << ", Name: " << name << ", Age: " << age
             << ", Course: " << course.code << " (" << course.name << ")";
        if (grade.locked) {
            cout << ", Grade: " << grade.letter << " (" << grade.mark << ")";
        } else {
            cout << ", Grade: Not yet added";
        }
        cout << endl;
    }
};

// StudentManagementSystem class
class StudentManagementSystem {
public:
    vector<Student> students;

    void addStudent() {
        if (students.size() < 40) {
            string reg, name;
            int age;
            string courseCode, courseName;
            cout << "Enter registration number: "; cin >> reg;
            cout << "Enter name: "; cin.ignore(); getline(cin, name);
            cout << "Enter age: "; cin >> age;
            cout << "Enter course code: "; cin >> courseCode;
            cout << "Enter course name: "; cin.ignore(); getline(cin, courseName);
            Course course(courseCode, courseName);
            Student newStudent(reg, name, age, course);
            students.push_back(newStudent);
            cout << "Student added.\n";
        } else {
            cout << "Maximum number of students reached.\n";
        }
    }

    void editStudent() {
        string regToEdit;
        cout << "Enter registration number of student to edit: "; cin >> regToEdit;
        for (auto& student : students) {
            if (student.reg == regToEdit) {
                cout << "Enter new name: "; cin.ignore(); getline(cin, student.name);
                cout << "Enter new age: "; cin >> student.age;
                cout << "Student details updated.\n";
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void addGrade() {
        string regToAddGrade;
        cout << "Enter registration number of student to add grade for: "; cin >> regToAddGrade;
        for (auto& student : students) {
            if (student.reg == regToAddGrade) {
                if (!student.grade.locked) {
                    int mark;
                    cout << "Enter mark (0-100): "; cin >> mark;
                    if (mark >= 0 && mark <= 100) {
                        student.grade.setGrade(mark);
                        cout << "Grade added: " << student.grade.letter << "\n";
                    } else {
                        cout << "Invalid mark.\n";
                    }
                } else {
                    cout << "Grade for this student is already locked.\n";
                }
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void showStudents() const {
        cout << "\n--- Student List ---\n";
        if (students.empty()) {
            cout << "No students in the system.\n";
        } else {
            for (const auto& student : students) {
                student.display();
            }
        }
        cout << "--------------------\n";
    }
};

int main() {
    StudentManagementSystem system;
    int choice;

    do {
        cout << "\n--- Student Management System ---\n";
        cout << "1. Add New Student\n";
        cout << "2. Edit Student Details\n";
        cout << "3. Add Marks and Calculate Grade\n";
        cout << "4. Display All Students\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.addStudent(); break;
            case 2: system.editStudent(); break;
            case 3: system.addGrade(); break;
            case 4: system.showStudents(); break;
            case 5: cout << "Exiting system.\n"; break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}