#include "student.h"

// ----------------------------------------
//
// Constructors
//
// ----------------------------------------

Student::Student()
	: name(""), id(-1), isOverdue(false), overdueCount(-1) {
	// Nothing to do
}
Student::Student(const String& n)
    : name(n), id(-1), isOverdue(false), overdueCount(0) {
	// Nothing to do
}
Student::Student(const String& n, int id)
    : name(n), id(id), isOverdue(false), overdueCount(0) {
	// Nothing to do
}
Student::Student(const String& n, int id, bool o, int c)
    : name(n), id(id), isOverdue(o), overdueCount(c) {
	// Nothing to do
}
Student::Student(const String& n, int id, vector<int> bl, bool o, int c)
    : name(n), id(id), isOverdue(o), bookList(bl), overdueCount(c) {
	// Nothing to do
}



// ----------------------------------------
//
// Methods
//
// ----------------------------------------

// Getter
String Student::getName() const {
    return name; 
}
int Student::getId() const { 
    return id;
}
bool Student::getIsOverdue() const { 
    return isOverdue;
}
bool Student::canBorrow() const {
    return !isOverdue;
}
const vector<int>& Student::getBookList() {
    return bookList;
}

// Setter
void Student::setIsOverdue(bool value) {
    isOverdue = value;
}
void Student::setId(int value) {
    id = value;
}

// Methods
void Student::increaseOverdueCount() {
    overdueCount++;
}
void Student::addToBookList(int bookId) {
    bookList.push_back(bookId);
}
void Student::removeFromBookList(int bookId) {
    bookList.erase(remove(bookList.begin(), bookList.end(), bookId), bookList.end());
}
int Student::getSizeOfBookList() {
    return bookList.size();
}
String Student::getFormattedString() {
    String bookListString = "";

    for (int i = 0; i < bookList.size(); i++) {
        if (i < bookList.size() - 1) {
            bookListString += format("{},", bookList[i]);
        }
        else {
            bookListString += format("{}", bookList[i]);
        }
    }

    return format(
        "{}/{}/{}/{}/{}\n",
        name, id, bookListString, isOverdue, overdueCount
    );
}