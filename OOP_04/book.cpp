#include "book.h" 

Book::Book(String title, String author, tm pub_date) {
	this->title = title;
	this->author = author;
	this->pub_date = pub_date;

	this->borrowed_count = 0;
	this->is_borrowed = false;
}

Book::~Book() {

}

bool Book::operator==(const Book& other) {
	return true;
}


String Book::get_title() const {
	return title;
};

String Book::get_author() const  {
	return author;
};
tm Book::get_pub_date() const {
	return pub_date;
};

tm Book::get_borrowed_date() const {
	return borrowed_date;
};

int Book::get_borrow_count() const {
	return borrowed_count;
};

Student Book::get_borrow_student() const {
	return borrow_student;
};

/*
tm Book::get_returned_date() const {
	return returned_date;
};

bool Book::get_is_borrowed() const {
	return get_is_borrowed;
};
*/

void Book::print_book_info() {
	//
};

void Book::borrowed_by_student(const Student student) {
	borrow_student = student;
	is_borrowed = true;
	borrowed_count++;
}

void Book::returned_by_student() {
	is_borrowed = false;
};

bool Book::can_be_borrowed() {
	return !is_borrowed;
};

/*
void Book::set_title(string target_title) {
	title = target_title;
};

void Book::set_author(string target_author) {
	author = target_author;
};

void Book::set_borrowed_date(tm target_date) {
	borrowed_date = target_date;
};

void Book::set_returned_date(tm target_date) {
	returned_date = target_date;
};

void Book::set_borrow_count(int count) {
	borrowed_count = count;
}

void Book::set_is_borrowed(bool value) {
	is_borrowed = value;
};

void Book::add_borrow_count() {
	borrowed_count++;
};
*/