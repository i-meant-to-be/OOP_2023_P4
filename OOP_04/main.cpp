#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <format>

using namespace std;
typedef string String;

class Book {
private:
    // Variables
    String title;
    String author;
    String pubDate;
    int id;
    bool isBorrowed;
    int borrowedCount;
    int studentId;

public:
    // Constructor
    Book() {}
    Book(const String& t, const String& a, const String& p, int id)
        : title(t), author(a), pubDate(p), id(id), isBorrowed(false), borrowedCount(0), studentId(-1) {}
    Book(const String& t, const String& a, const String& p, int id, bool b, int c, int sId)
        : title(t), author(a), pubDate(p), id(id), isBorrowed(b), borrowedCount(c), studentId(sId) {}

    // Getter
    String getTitle() const { return title; }
    String getAuthor() const { return author; }
    String getPubDate() const { return pubDate; }
    int getId() const { return id; }
    bool getIsBorrowed() const { return isBorrowed; }
    bool canBeBorrowed() const { return !isBorrowed; }
    int getBorrowedCount() const { return borrowedCount; }
    int getStudentId() const { return studentId; }

    // Setter
    void setIsBorrowed(bool value) {
        isBorrowed = value;
    }
    void setStudentId(int value) {
        studentId = value;
    }

    // Methods
    void increaseBorrowedCount() {
        borrowedCount++;
    }
    String getFormattedString() {
        return format(
            "{}/{}/{}/{}/{}/{}/{}\n",
            title, author, pubDate, id, isBorrowed, borrowedCount, studentId
        );
    }
};

class Student {
private:
    // Variables
    String name;
    int id;
    vector<int> bookList;
    bool isOverdue;
    int overdueCount;

public:
    // Constructor
    Student() {}
    Student(const String& n, int id)
        : name(n), id(id), isOverdue(false), overdueCount(0) {}
    Student(const String& n, int id, bool o, int c)
        : name(n), id(id), isOverdue(o), overdueCount(c) {}

    // Getter
    String getName() const { return name; }
    int getId() const { return id; }
    bool getIsOverdue() const { return isOverdue; }
    bool canBorrow() const { return !isOverdue; }

    // Setter
    void setIsOverdue(bool value) {
        isOverdue = value;
    }

    // Methods
    void increaseOverdueCount() {
        overdueCount++;
    }
    void addToBookList(int bookId) {
        bookList.push_back(bookId);
    }
    void removeFromBookList(int bookId) {
        bookList.erase(remove(bookList.begin(), bookList.end(), bookId), bookList.end());
    }
    int getSizeOfBookList() {
        return bookList.size();
    }
    String getFormattedString() {
        return format(
            "{}/{}/{}/{}\n",
            name, id, isOverdue, overdueCount
        );
    }
};

class Library {
public:
    vector<Book> books;
    vector<Student> students;
    int currBookId = 0;
    int currStudentId = 0;

    void addBook(const String& title, const String& author, const String& pubDate) {
        books.emplace_back(title, author, pubDate, currBookId++);
    }

    void addStudent(const String& name) {
        students.emplace_back(name, currStudentId++);
    }

    void borrowBook(int bookId, int studentId) {
        if (bookId < 0 || bookId >= books.size() || studentId < 0 || studentId >= students.size()) {
            cout << "Invalid book or student index." << endl;
            return;
        }

        /*
        vector<Book>::iterator itBook = find(books.begin(), books.end(), [_bookId = bookId] (const Book& book) {
            return book.getId() == _bookId;
            });
        vector<Student>::iterator itStudent = find(students.begin(), students.end(), [_studentId = studentId] (const Student& student) {
            return student.getId() == _studentId;
            });


        
        if (itBook != books.end() && itStudent != students.end()) {
            int idxBook = find(books.begin(), books.end(), [_bookId = bookId](const Book& book) {
                return book.getId() == _bookId;
                }) - books.begin();
            int idxStudent = find(students.begin(), students.end(), [_studentId = studentId](const Student& student) {
                return student.getId() == _studentId;
                }) - students.begin();

            if (books[idxBook].canBeBorrowed() && students[idxStudent].getSizeOfBookList() && students[idxStudent].canBorrow()) {
                books[idxBook].setIsBorrowed(true);
                books[idxBook].increaseBorrowedCount();
                books[idxBook].setStudentId(students[idxStudent].getId());
                students[idxStudent].addToBookList(bookId);
                cout << "Book borrowed successfully." << endl;
            }
            /*
            if (book.canBeBorrowed() && student.getSizeOfBookList() < 5 && student.canBorrow()) {
                book.setIsBorrowed(true);
                book.increaseBorrowedCount();
                book.setStudentId(student.getId());
                student.addToBookList(bookId);
                cout << "Book borrowed successfully." << endl;
            }
        }
        else {
            cout << "Unable to borrow the book." << endl;
        }
            */
    }

    void returnBook(int bookIndex) {
        if (bookIndex < 0 || bookIndex >= books.size()) {
            cout << "Invalid book index." << endl;
            return;
        }

        Book& book = books[bookIndex];

        if (book.canBeBorrowed()) {
            book.setIsBorrowed(true);
            book.setStudentId(-1);
            cout << "Book returned successfully." << endl;
        }
        else {
            cout << "Book is not currently borrowed." << endl;
        }
    }

    void sortBooksByTitle() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.getTitle() < b.getTitle();
            });
    }

    void sortBooksByAuthor() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.getAuthor() < b.getAuthor();
            });
    }

    void sortBooksByPublishedDate() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.getPubDate() < b.getPubDate();
            });
    }

    void sortBooksByBorrowedCount() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.getBorrowedCount() > b.getBorrowedCount();
            });
    }

    /*
    # Class Book
    String title;
    String author;
    String pubDate;
    int id;
    bool isBorrowed;
    int borrowedCount;
    int studentId;

    # Class Student
    String name;
    int id;
    vector<int> bookList;
    bool isOverdue;
    int overdueCount;
    */

    bool readData() {
        fstream bookFile;
        fstream studentFile;
        int curr_index = 0, arr_index = 0;
        int string_index;

        bookFile.open("books.txt", ios::in | ios::app);
        studentFile.open("students.txt", ios::in | ios::app);

        
        if (bookFile.is_open() && studentFile.is_open()) {
            String buffer;
            String result[7];

            // Read books from the file
            while (getline(bookFile, buffer)) {
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
                while ((string_index = buffer.find("/", curr_index)) != String::npos) {
                    int len = string_index - curr_index;
                    result[arr_index++] = buffer.substr(curr_index, len);
                    curr_index = string_index + 1;
                }

                string_index = buffer.find("/", curr_index);
                result[arr_index] = buffer.substr(curr_index);
                students.emplace_back(
                    result[0],
                    atoi(result[1].c_str()),
                    (result[2] == "true" ? true : false),
                    atoi(result[3].c_str())
                );
                currStudentId++;
            }
            studentFile.close();
        }
        else return false;
    }

    bool writeData() {
        fstream bookFile;
        fstream studentFile;

        bookFile.open("books.txt", ios::out | ios::trunc);
        studentFile.open("students.txt", ios::out | ios::trunc);

        if (bookFile.is_open() && studentFile.is_open()) {
            String buffer;

            // Write books to the file
            for (int i = 0; i < currBookId; i++) {
                buffer = books[i].getFormattedString();
                bookFile << buffer;
            }

            // Write students to the fiel
            for (int i = 0; i < currStudentId; i++) {
                buffer = students[i].getFormattedString();
                studentFile << buffer;
            }

            bookFile.close();
            studentFile.close();
            return true;
        }
        else {
            bookFile.close();
            studentFile.close();
            return false;
        }
    }
};

int main() {
    // Example usage
    Library library;

    library.addBook("Book1", "Author1", "2022-01-01");
    library.addBook("Book2", "Author2", "2022-02-01");
    library.addBook("Book3", "Author3", "2022-03-01");
    library.addStudent("Jason");
    library.addStudent("Jack");
    library.addStudent("Katrina");

    library.sortBooksByTitle();
    // Display sorted books
    cout << "Sorted by title:" << endl;
    for (const auto& book : library.books) {
        cout << book.getTitle() << endl;
    }

    return 0;
}