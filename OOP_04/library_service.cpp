#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include "book.h"
#include "student.h"

using namespace std;
typedef string String;

/*
	검색
	정렬
	베스트셀러 출력
	신작 출력
	도서의 연체 여부 확인
	학생의 연체 비용 계산
	대출
		최대 5권
		일정 연체 횟수 넘어가면 아예 금지
		연체 중인 사람은 추가 대출 금지
	반납
*/

class BookTitleCmp {
public:
	bool operator() (Book* a, Book* b) {
		return a->get_title() < b->get_title();
	}
};

class BookAuthorCmp {
public:
	bool operator() (Book* a, Book* b) {
		return a->get_author() < b->get_author();
	}
};

class BookPubDateCmp {
public:
	bool operator() (Book* a, Book* b) {
		return mktime(&a->get_pub_date()) < mktime(&b->get_pub_date());
		// return (a->get_pub_date() < b->get_pub_date());
	}
};

class BookBorrowedDateCmp {
public:
	bool operator() (Book* a, Book* b) {
		return mktime(&a->get_borrowed_date()) < mktime(&b->get_borrowed_date());
	}
};

class BookBorrowedCountCmp {
public:
	bool operator() (Book* a, Book* b) {
		return a->get_borrow_count() < b->get_borrow_count();
	}
};

enum SortCriteria {
	TITLE,
	WRITER,
	PUB_DATE,
	BORROWED_DATE,
	BORROWED_COUNT
};

void search_books(const vector<Book> books, vector<Book>& result, const String value) {
	result.clear();

	for (Book book : books) {
		if (book.get_title().find(value)) {
			result.push_back(book);
		}
	}
}

void sort_books(vector<Book>& books, SortCriteria sortCriteria) {
	if (sortCriteria == TITLE) {
		BookTitleCmp bookTitleCmp;
		sort(books.begin(), books.end(), bookTitleCmp);
	}
	else if (sortCriteria == WRITER) {
		BookAuthorCmp bookAuthorCmp;
		sort(books.begin(), books.end(), bookAuthorCmp);
	}
	else if (sortCriteria == PUB_DATE) {
		BookPubDateCmp bookPubDateCmp;
		sort(books.begin(), books.end(), bookPubDateCmp);
	}
	else if (sortCriteria == BORROWED_DATE) {
		BookBorrowedDateCmp bookBorrowedDateCmp;
		sort(books.begin(), books.end(), bookBorrowedDateCmp);
	}
	else {
		BookBorrowedCountCmp bookBorrowedCountCmp;
		sort(books.begin(), books.end(), bookBorrowedCountCmp);
	}
}

bool borrow_book(Student& student, Book& book) {
	if (student.can_borrow() && book.can_be_borrowed()) {
		student.borrow_book(book);
		book.borrowed_by_student(student);
		return true;
	}
	else {
		return false;
	}
}

void return_book(Book& book) {
	book.returned_by_student();
	book.get_borrow_student().return_book(book);
}