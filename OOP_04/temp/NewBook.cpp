#include "Book.h" 

Book::Book(string target_title) {
	title = target_title;
}

string Book::get_title() {
	return title;
};

string Book::get_author() {
	return author;
};
tm Book::get_published_date() {
	return published_date;
};

tm Book::get_date_lend() {
	return date_lend;
};

tm Book::get_date_return() {
	return date_return;
};
bool Book::get_isLend() {
	return isLend;
};

Student Book::get_borrower() {
	return borrower;
};

int Book::get_countLend() {
	return countLend;
};

void Book::print_bookinfo() {
	char buff[256];
	asctime_s(buff, sizeof(buff), &published_date);

	cout << title << ";" << author << ";" << buff << ";";
};

void Book::edit_title(string target_title) {
	title = target_title;
};

void Book::edit_author(string target_author) {
	author = target_author;
};

void Book::edit_date_lend(tm target_date) {
	date_lend = target_date;
};
void Book::edit_date_return(tm target_date) {
	date_return = target_date;
};
void Book::edit_countLend(int count) {
	countLend = count;
};

bool Book::canLend() {
	return !isLend;
};