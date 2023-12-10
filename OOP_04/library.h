#ifndef __LIBRARY_H
#define __LIBRARY_H

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <map>
#include "student.h"
#include "book.h"

using namespace std;
typedef string String;

const String BOOKS_FILE_NAME = "books.txt";
const String STUDENTS_FILE_NAME = "students.txt";

enum SortOptions {
    SORT_BY_TITLE,
    SORT_BY_AUTHOR,
    SORT_BY_PUB_DATE,
    SORT_BY_BORROWED_COUNT
};

class Library {
private:
    map<int, Book> nBooks;
    map<int, Student> nStudents;
    vector<pair<int, Book>> sortedList;
    int currBookId = 0;
    int currStudentId = 0;
    SortOptions sortOptions = SORT_BY_TITLE;

public:
    // Map methods
    void nSetSortOptions(int value);

    void nPrintAllStudents();
    void nPrintAllBooks();

    void nAddBook(const String& title, const String& author, const String& pubDate);
    void nAddStudent(const String& name);
    void nAddBook(Book& book);
    void nAddStudent(Student& student);

    void nBorrowBook(int bookId, int studentId);
    void nReturnBook(int bookId);

    bool nReadData();
    bool nWriteData();

    void sortBooks();
};


#endif