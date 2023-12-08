#ifndef __STUDENT_H
#define __STUDENT_H

#include <string>
#include <vector>
#include "book.h"

using namespace std;
typedef string String;

class Student {
private:
    String name;
    String student_id;
    bool is_overdue;
    vector<Book> borrowed_books;                              // vector<Book>으로 만들기
    int number_of_borrowed_books;
    int number_of_overdue;

public:
    Student();
    Student(String target_name, String target_student_id);
    ~Student();

    // void set_name(String target);
    // void set_id(String target);
    String get_name();
    void borrow_book(const Book book);
    void return_book(const Book book);
    void display_borrowed_books();
    // void set_overdue();
    // void reset_overdue();
    bool can_borrow();
};

#endif 