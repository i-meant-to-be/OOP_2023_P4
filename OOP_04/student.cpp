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
    if (book.return_day < today) {            //연체 여부 업데이트입니다. tm을 활용해주시고 이부분 살짝만 수정부탁드립니다.
        is_overdue = true;
        number_of_overdue++;
    }
}
void Student::reset_overdue() {
    if (payment) {                            //연체 여부 리셋입니다. 연체료 납부 후 is_overdue를 false로 초기화하는 작업입니다.
        is_overdue = false;
    }
}
*/

bool Student::can_borrow() {
    return !is_overdue;
}