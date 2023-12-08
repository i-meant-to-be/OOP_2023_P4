#include "student.h"

Student::Student() {

}

Student::Student(String target_name, String target_student_id) {
    name = target_name;
    student_id = target_student_id;
    is_overdue = false;
    number_of_borrowed_books = 0;
    number_of_overdue = 0;
}

Student::~Student() {

}

/*
void Student::set_name(String target) {
    name = target;
}

void Student::set_id(String target) {
    student_id = target;
}
*/

String Student::get_name() {
    return name;
}

void Student::borrow_book(const Book book) {
    borrowed_books.push_back(book);
    number_of_borrowed_books++;
}

void Student::return_book(const Book book) {
    vector<Book>::iterator it = borrowed_books.begin();
    for (it; it != borrowed_books.end(); it++) {
        if (book.get_title() == (*it).get_title()) {
            borrowed_books.erase(it);
            number_of_borrowed_books = borrowed_books.size();
            return;
        }
    }
    cout << "He(She) didn't borrowed that book\n";
}

void Student::display_borrowed_books() {
    //cout.setf(ios::left);
    cout << "Student name: " << setw(10) << name << "  Student id: " << setw(10) << student_id << "\n";
    vector<Book>::iterator it = borrowed_books.begin();
    for (it; it != borrowed_books.end(); it++) {
        cout << (*it).get_title() << "   ";
    }
    if (it == borrowed_books.begin()) {
        cout << "No books are borrowed";
    }
    cout << "\n---------------------------------------------------------\n";
}

/*
void Student::set_overdue() {
    if (book.return_day < today) {            //��ü ���� ������Ʈ�Դϴ�. tm�� Ȱ�����ֽð� �̺κ� ��¦�� ������Ź�帳�ϴ�.
        is_overdue = true;
        number_of_overdue++;
    }
}
void Student::reset_overdue() {
    if (payment) {                            //��ü ���� �����Դϴ�. ��ü�� ���� �� is_overdue�� false�� �ʱ�ȭ�ϴ� �۾��Դϴ�.
        is_overdue = false;
    }
}
*/

bool Student::can_borrow() {
    return !is_overdue;
}