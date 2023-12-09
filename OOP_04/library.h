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

class Library {
private:
    vector<Book> books;
    vector<Student> students;
    int currBookId = 0;
    int currStudentId = 0;

public:
    void addBook(const String& title, const String& author, const String& pubDate);
    void addStudent(const String& name);

    void borrowBook(int bookId, int studentId);
    void returnBook(int bookId);

    void sortBooksByTitle();
    void sortBooksByAuthor();
    void sortBooksByPublishedDate();
    void sortBooksByBorrowedCount();

    bool readData();
    bool writeData();
};


#endif