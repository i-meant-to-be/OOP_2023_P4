#include "library.h"

// ----------------------------------------
//
// Methods
//
// ----------------------------------------

// Add elements
void Library::addBook(const String& title, const String& author, const String& pubDate) {
    books.emplace_back(title, author, pubDate, currBookId++);
}

void Library::addStudent(const String& name) {
    students.emplace_back(name, currStudentId++);
}

// Borrow and return books
void Library::borrowBook(int bookId, int studentId) {
    if (bookId < 0 || bookId >= books.size() || studentId < 0 || studentId >= students.size()) {
        cout << "Invalid book or student id." << endl;
        return;
    }

    if (books[bookId].canBeBorrowed() && students[studentId].canBorrow()) {
        books[bookId].increaseBorrowedCount();
        books[bookId].setIsBorrowed(true);
        books[bookId].setStudentId(studentId);

        students[studentId].addToBookList(bookId);
    }
    else {
        cout << "Cannot borrow book." << endl;
        return;
    }
}

void Library::returnBook(int bookId) {
    if (bookId < 0 || bookId >= books.size()) {
        cout << "Invalid book id." << endl;
        return;
    }

    if (!books[bookId].canBeBorrowed()) {
        int studentId = books[bookId].getStudentId();

        books[bookId].setIsBorrowed(true);
        books[bookId].setStudentId(-1);

        students[studentId].removeFromBookList(bookId);

        cout << "Book returned successfully." << endl;
    }
    else {
        cout << "Book is not currently borrowed." << endl;
    }
}

// Sorting methods
void Library::sortBooksByTitle() {
    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.getTitle() < b.getTitle();
        });
}

void Library::sortBooksByAuthor() {
    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.getAuthor() < b.getAuthor();
        });
}

void Library::sortBooksByPublishedDate() {
    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.getPubDate() < b.getPubDate();
        });
}

void Library::sortBooksByBorrowedCount() {
    sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
        return a.getBorrowedCount() > b.getBorrowedCount();
        });
}

// File I/O methods
bool Library::readData() {
    fstream bookFile;
    fstream studentFile;
    int curr_index, arr_index;
    int string_index;

    bookFile.open(BOOKS_FILE_NAME, ios::in | ios::app);
    studentFile.open(STUDENTS_FILE_NAME, ios::in | ios::app);


    if (bookFile.is_open() && studentFile.is_open()) {
        String buffer;
        String result[7];

        // Read books from the file
        while (getline(bookFile, buffer)) {
            curr_index = 0; arr_index = 0; string_index = 0;

            while ((string_index = buffer.find("/", curr_index)) != String::npos) {
                int len = string_index - curr_index;
                result[arr_index++] = buffer.substr(curr_index, len);
                curr_index = string_index + 1;
            }

            string_index = buffer.find("/", curr_index);
            result[arr_index] = buffer.substr(curr_index);
            books.emplace_back(
                result[0],
                result[1],
                result[2],
                atoi(result[3].c_str()),
                (result[4] == "true" ? true : false),
                atoi(result[5].c_str()),
                atoi(result[6].c_str())
            );

            currBookId++;
        }
        bookFile.close();

        // Read students from the file
        while (getline(studentFile, buffer)) {
            curr_index = 0; arr_index = 0; string_index = 0;

            while ((string_index = buffer.find("/", curr_index)) != String::npos) {
                int len = string_index - curr_index;
                result[arr_index++] = buffer.substr(curr_index, len);
                curr_index = string_index + 1;
            }
            string_index = buffer.find("/", curr_index);
            result[arr_index] = buffer.substr(curr_index);

            // Parsing student's book lists
            curr_index = 0; arr_index = 0; string_index = 0;
            vector<int> bookParsingResult;
            String bookParsingBuffer = result[2];

            while ((string_index = bookParsingBuffer.find(",", curr_index)) != String::npos) {
                int len = string_index - curr_index;
                bookParsingResult.emplace_back(atoi(bookParsingBuffer.substr(curr_index, len).c_str()));
                curr_index = string_index + 1;
            }
            string_index = bookParsingBuffer.find(",", curr_index);
            bookParsingResult.emplace_back(atoi(bookParsingBuffer.substr(curr_index).c_str()));

            students.emplace_back(
                result[0],
                atoi(result[1].c_str()),
                bookParsingResult,
                (result[3] == "true" ? true : false),
                atoi(result[4].c_str())
            );

            currStudentId++;
        }
        studentFile.close();
    }
    else {
        bookFile.close();
        studentFile.close();
        return false;
    }
}

bool Library::writeData() {
    fstream bookFile;
    fstream studentFile;

    bookFile.open(BOOKS_FILE_NAME, ios::out | ios::trunc);
    studentFile.open(STUDENTS_FILE_NAME, ios::out | ios::trunc);

    if (bookFile.is_open() && studentFile.is_open()) {
        String buffer;

        // Write books to the file
        for (int i = 0; i < currBookId; i++) {
            buffer = books[i].getFormattedString();
            bookFile << buffer;
        }
        bookFile.close();

        // Write students to the fiel
        for (int i = 0; i < currStudentId; i++) {
            buffer = students[i].getFormattedString();
            studentFile << buffer;
        }
        studentFile.close();

        return true;
    }
    else {
        bookFile.close();
        studentFile.close();
        return false;
    }
}