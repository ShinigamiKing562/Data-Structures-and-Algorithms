#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// Course class
class Course {
public:
    string code;
    string name;
    Course() : code(""), name("") {}
    Course(const string& c, const string& n) : code(c), name(n) {}
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
    Student() : reg(""), name(""), age(0), course(), grade() {}
    Student(const string& r, const string& n, int a, const Course& c) : reg(r), name(n), age(a), course(c) {}
    bool operator==(const Student& other) const { return reg == other.reg; }

    void display() const {
        cout << "Reg: " << reg << ", Name: " << name << ", Age: " << age
            << ", Course: " << course.code << " (" << course.name << "), Grade: ";
        if (grade.locked)  cout << grade.letter << " (" << grade.mark << ")";
        else cout << "Not yet added";
        cout << endl;
    }
};

// Students class via an array-based list.
class StudentList {
private:
    int size;
    int capacity;
    Student* students;

    void resizeArray() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        Student* newStudents = (Student*)malloc(sizeof(Student) * capacity);
        for (int i = 0; i < size; ++i)  newStudents[i] = students[i];
        free(students);
        students = newStudents;
    }

public:
    StudentList() : size(0), capacity(0), students(nullptr) {}
    StudentList(const Student& initialStudent) : size(1), capacity(1), students((Student*)malloc(sizeof(Student))) {
        students[0] = initialStudent;
    }
    StudentList(const StudentList& other) : size(other.size), capacity(other.capacity), students((Student*)malloc(sizeof(Student) * other.capacity)) {
        for (int i = 0; i < size; ++i) students[i] = other.students[i];
    }
    ~StudentList() { free(students); }

    int getSize() const { return size; }

    void addStudent(const Student& student) {
        if (size == capacity) resizeArray();
        if (!students && capacity == 0) {
            capacity = 1;
            students = (Student*)malloc(sizeof(Student) * capacity);
        }
        students[size++] = student;
    }

    void addStudentAtPosition(const Student& student, int position) {
        if (size == capacity) resizeArray();
        if (!students && capacity == 0) {
            capacity = 1;
            students = (Student*)malloc(sizeof(Student) * capacity);
        }
        for (int i = size; i > position; --i)  students[i] = students[i - 1];
        students[position] = student;
        ++size;
    }

    void removeStudent(const Student& student) {
        for (int i = 0; i < size; ++i) {
            if (students[i] == student) { removeStudentAtPosition(i); return; }
        }
        cout << "Student not found.\n";
    }

    void removeStudentAtPosition(int position) {
        for (int i = position; i < size - 1; ++i) students[i] = students[i + 1];
        --size;
    }

    void displayAllStudents() const {
        cout << "\n--- Student List ---\n";
        if (size == 0)  cout << "No students in the list.\n";
        else for (int i = 0; i < size; ++i)  students[i].display();
        cout << "--------------------\n";
    }

    Student& getStudent(int index) {
        return students[index];
    }
};

int main() {
    StudentList studentList;
    int choice;

    do {
        cout << "\nStudent Profile Management System\n"
            << "1. Add New Student\n"
            << "2. Display All Students\n"
            << "3. Add Student \n"
            << "4. Remove Student\n"
            << "5. Exit\n"
            << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string reg, name, courseCode, courseName;
                int age;
                cout << "Enter registration number: "; cin >> reg;
                cout << "Enter name: "; cin.ignore(); getline(cin, name);
                cout << "Enter age: "; cin >> age;
                cout << "Enter course code: "; cin >> courseCode;
                cout << "Enter course name: "; cin.ignore(); getline(cin, courseName);
                studentList.addStudent(Student(reg, name, age, Course(courseCode, courseName)));
                cout << "Student added.\n";
                break;
            }
            case 2:
                studentList.displayAllStudents();
                break;
            case 3: {
                string reg, name, courseCode, courseName;
                int age, position;
                cout << "Enter registration number: "; cin >> reg;
                cout << "Enter name: "; cin.ignore(); getline(cin, name);
                cout << "Enter age: "; cin >> age;
                cout << "Enter course code: "; cin >> courseCode;
                cout << "Enter course name: "; cin.ignore(); getline(cin, courseName);
                cout << "Enter position to add student: "; cin >> position;
                studentList.addStudentAtPosition(Student(reg, name, age, Course(courseCode, courseName)), position);
                break;
            }
            case 4: {
                string regToRemove;
                cout << "Enter registration number of student to remove: "; cin >> regToRemove;
                studentList.removeStudent(Student(regToRemove, "", 0, Course()));
                break;
            }
            case 5:
                cout << "Exiting system.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}