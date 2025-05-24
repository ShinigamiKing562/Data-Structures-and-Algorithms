class Course:
    def __init__(self, code, name):
        self.course_code = code
        self.course_name = name

    def __str__(self):
        return f"{self.course_code} - {self.course_name}"


class Grade:
    def __init__(self):
        self.marks = 0
        self.grade = 'E'

    def set_marks(self, marks):
        self.marks = marks
        self.calculate_grade()

    def calculate_grade(self):
        if self.marks >= 69:
            self.grade = 'A'
        elif self.marks >= 59:
            self.grade = 'B'
        elif self.marks >= 49:
            self.grade = 'C'
        elif self.marks >= 39:
            self.grade = 'D'
        else:
            self.grade = 'E'

    def __str__(self):
        return f"Marks: {self.marks} | Grade: {self.grade}"


class Student:
    def __init__(self, reg_number, name, age, course):
        self.reg_number = reg_number
        self.name = name
        self.age = age
        self.course = course
        self.grade = Grade()
        self.next_student = None

    def set_marks(self, marks):
        self.grade.set_marks(marks)

    def __str__(self):
        return (f"Reg Number: {self.reg_number}\n"
                f"Name: {self.name}\n"
                f"Age: {self.age}\n"
                f"Course: {self.course}\n"
                f"{self.grade}")


class StudentList:
    def __init__(self):
        self.head = None

    def add_student(self, student):
        if not self.head:
            self.head = student
        else:
            current = self.head
            while current.next_student:
                current = current.next_student
            current.next_student = student

    def remove_student(self, reg_number):
        current = self.head
        prev = None
        while current and current.reg_number != reg_number:
            prev = current
            current = current.next_student

        if current is None:
            print(f"Student with registration number {reg_number} not found.")
            return

        if prev is None:
            self.head = current.next_student
        else:
            prev.next_student = current.next_student

    def display_all(self):
        current = self.head
        while current:
            print(current)
            print("\n" + "-"*40)
            current = current.next_student


def main():
    course1 = Course("ICS2301", "Data Structures")
    course2 = Course("ICS2302", "Algorithms")
    course3 = Course("ICS2303", "Databases")
    course4 = Course("ICS2304", "Networking")
    course5 = Course("ICS2305", "Operating Systems")

    student_list = StudentList()

    student_list.add_student(Student("SCT212-101", "Mark Otieno", 21, course1))
    student_list.add_student(Student("SCT212-102", "John Wanjala", 22, course2))
    student_list.add_student(Student("SCT212-103", "Cathy Naliaka", 20, course3))
    student_list.add_student(Student("SCT212-104", "Dan Musyoka", 23, course4))
    student_list.add_student(Student("SCT212-105", "Eva Wambui", 21, course5))

    student_list.head.set_marks(78)
    student_list.head.next_student.set_marks(67)
    student_list.head.next_student.next_student.set_marks(58)
    student_list.head.next_student.next_student.next_student.set_marks(49)
    student_list.head.next_student.next_student.next_student.next_student.set_marks(35)

    print("All Students:")
    student_list.display_all()

    print("\nRemoving student with reg number SCT212-103 (Cathy Naliaka)...")
    student_list.remove_student("SCT212-103")

    print("\nUpdated Students List:")
    student_list.display_all()


if __name__ == "__main__":
    main()