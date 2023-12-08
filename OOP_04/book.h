#ifndef __BOOK_H
#define __BOOK_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ctime>
#include "student.h"

using namespace std;
typedef string String;

class Book {
private:
    String title;
    String author;
    tm pub_date;
    tm borrowed_date;
    tm returned_date;
	bool is_borrowed;
	Student borrow_student;
	int borrowed_count;

public:
    Book(String title, String author, tm pub_date);
    ~Book();

    bool operator==(const Book& other);
	
    String get_title() const;
    String get_author() const;
    tm get_pub_date() const;
    tm get_borrowed_date() const;
    tm get_borrowed_date() const;
	int get_borrow_count() const;
	Student get_borrow_student() const;
	/*
    tm get_returned_date() const;

	bool get_is_borrowed() const;
	*/
	void print_book_info();
	/*
	void set_title(string target_title);
	void set_author(string target_author);
	void set_borrowed_date(tm target_date);
	void set_returned_date(tm target_date);
	void set_borrow_count(int count);
	void set_is_borrowed(bool value);
	void add_borrow_count();
	*/
	void borrowed_by_student(const Student student);
	void returned_by_student();
	bool can_be_borrowed();
};

#endif