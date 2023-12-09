#include "book.h"

// ----------------------------------------
//
// Constructors
//
// ----------------------------------------

Book::Book()
	: title(""), author(""), pubDate(""), id(-1), isBorrowed(false), borrowedCount(0), studentId(-1) {
	// Nothing to do
}
Book::Book(const String& t, const String& a, const String& p, int id)
	: title(t), author(a), pubDate(p), id(id), isBorrowed(false), borrowedCount(0), studentId(-1) {
	// Nothing to do
}
Book::Book(const String & t, const String & a, const String & p, int id, bool b, int c, int sId)
	: title(t), author(a), pubDate(p), id(id), isBorrowed(b), borrowedCount(c), studentId(sId) {
	// Nothing to do
}



// ----------------------------------------
//
// Methods
//
// ----------------------------------------

// Getter
String Book::getTitle() const {
    return title;
}
String Book::getAuthor() const {
    return author;
}
String Book::getPubDate() const {
    return pubDate;
}
int Book::getId() const {
    return id;
}
bool Book::getIsBorrowed() const {
    return isBorrowed; 
}
bool Book::canBeBorrowed() const {
    return !isBorrowed;
}
int Book::getBorrowedCount() const {
    return borrowedCount;
}
int Book::getStudentId() const {
    return studentId;
}

// Setter
void Book::setIsBorrowed(bool value) {
    isBorrowed = value;
}
void Book::setStudentId(int value) {
    studentId = value;
}

// Methods
void Book::increaseBorrowedCount() {
    borrowedCount++;
}
String Book::getFormattedString() {
    return format(
        "{}/{}/{}/{}/{}/{}/{}\n",
        title, author, pubDate, id, isBorrowed, borrowedCount, studentId
    );
}