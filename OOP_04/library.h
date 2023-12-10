#ifndef __LIBRARY_H
#define __LIBRARY_H

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
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
    SORT_BY_BORROWED_COUNT,
    DEFALUT
};

class Library {
private:
    vector<Book> books;
    vector<Student> students;
    int currBookId = 0;
    int currStudentId = 0;
    SortOptions sortOptions = DEFALUT;

public:
    // Print methods
    void printAllStudents();
    void printAllBooks();

    // Add elements
    void addBook(const String& title, const String& author, const String& pubDate);
    void addStudent(const String& name);
    void addBook(Book& book);
    void addStudent(Student& student);

    // Borrow and return books
    void borrowBook(int bookId, int studentId);
    void returnBook(int bookId);

    // Sorting methods
    void sortBooksByTitle();
    void sortBooksByAuthor();
    void sortBooksByPublishedDate();
    void sortBooksByBorrowedCount();

    // File I/O methods
    bool readData();
    bool writeData();
};


#endif