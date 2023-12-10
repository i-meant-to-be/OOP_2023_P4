#include "library.h"

// ----------------------------------------
//
// Map methods
//
// ----------------------------------------

void Library::nSetSortOptions(int value) {
    if (value == 1) sortOptions = SORT_BY_AUTHOR;
    else if (value == 2) sortOptions = SORT_BY_PUB_DATE;
    else if (value == 3) sortOptions = SORT_BY_BORROWED_COUNT;
    else sortOptions = SORT_BY_TITLE;
}

void Library::nPrintAllStudents() {
    if (!nStudents.empty()) {
        for (int i = 0; i < nStudents.size(); i++) {
            cout << format(
                "# {}.\t {}\n",
                nStudents[i].getId(),
                nStudents[i].getName()
            );
            for (int bookId : nStudents[i].getBookList()) {
                cout << format("  - {} / {} \n", nBooks[bookId].getTitle(), nBooks[bookId].getAuthor());
            }
        }
        cout << format("\n# Total {} student{} are registered on the service. \n", nStudents.size(), (nStudents.size() == 1 ? "" : "s"));
    }
    else {
        cout << "# There isn't any students registered on the service. \n";
    }
}

void Library::nPrintAllBooks() {
    if (!nBooks.empty()) {
        sortBooks();

        for (auto pair : sortedList) {
            cout << format(
                "# {}.\t {} / {} / Published on {} / {} time{} borrowed / {}\n",
                pair.second.getId(),
                pair.second.getTitle(),
                pair.second.getAuthor(),
                pair.second.getPubDate(),
                pair.second.getBorrowedCount(),
                (pair.second.getBorrowedCount() > 1 ? "s" : ""),
                (pair.second.canBeBorrowed() ? "Available" : "Not available")
            );
        }
        cout << format("\n# Total {} book{} are registered on the service. \n", nBooks.size(), (nBooks.size() == 1 ? "" : "s"));
    }
    else {
        cout << "# There isn't any books registered on the service. \n";
    }
}

// Add elements
void Library::nAddBook(const String& title, const String& author, const String& pubDate) {
    //books.emplace_back(title, author, pubDate, currBookId++);
    nBooks.emplace(currBookId, Book(title, author, pubDate, currBookId++));
}

void Library::nAddStudent(const String& name) {
    //students.emplace_back(name, currStudentId++);
    nStudents.emplace(currStudentId, Student(name, currStudentId++));
}

void Library::nAddBook(Book& book) {
    //book.setId(currBookId++);
    //books.push_back(book);
    book.setId(currBookId);
    nBooks.insert(make_pair(currBookId++, book));
}

void Library::nAddStudent(Student& student) {
    //student.setId(currStudentId++);
    //students.push_back(student);
    student.setId(currStudentId);
    nStudents.insert(make_pair(currStudentId++, student));
}

void Library::nBorrowBook(int bookId, int studentId) {
    if (bookId < 0 || bookId > nBooks.size() || studentId < 0 || studentId > nStudents.size()) {
        cout << "# Invalid book or student id." << endl;
        return;
    }

    if (nBooks[bookId].canBeBorrowed() && nStudents[studentId].canBorrow()) {
        nBooks[bookId].increaseBorrowedCount();
        nBooks[bookId].setIsBorrowed(true);
        nBooks[bookId].setStudentId(studentId);
        nStudents[studentId].addToBookList(bookId);

        cout << format(
            "# Student '{}' borrowed the book '{}' successfully. \n",
            nStudents[studentId].getName(), nBooks[bookId].getTitle()
        ) << endl;
    }
    else {
        cout << "# Cannot borrow book." << endl;
        return;
    }
}

void Library::nReturnBook(int bookId) {
    if (bookId < 0 || bookId >= nBooks.size()) {
        cout << "# Invalid book id." << endl;
        return;
    }

    if (!nBooks[bookId].canBeBorrowed()) {
        int studentId = nBooks[bookId].getStudentId();

        nBooks[bookId].setIsBorrowed(false);
        nBooks[bookId].setStudentId(-1);

        nStudents[studentId].removeFromBookList(bookId);

        cout << format("# Book '{}' returned successfully.", nBooks[bookId].getTitle()) << endl;
    }
    else {
        cout << format("# Book '{}' returned successfully.", nBooks[bookId].getTitle()) << endl;
    }
}

bool Library::nReadData() {
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

            // Insert the book into vector<Book>
            nBooks.emplace(
                // Key
                atoi(result[3].c_str()),
                // Value
                Book(
                    result[0],
                    result[1],
                    result[2],
                    atoi(result[3].c_str()),
                    (result[4] == "true" ? true : false),
                    atoi(result[5].c_str()),
                    atoi(result[6].c_str())
                )
            );
            currBookId++;
        }
        bookFile.close();

        // Read students from the file
        while (getline(studentFile, buffer)) {
            curr_index = 0; arr_index = 0; string_index = 0;
            vector<int> bookParsingResult;
            String bookParsingBuffer = result[2];

            while ((string_index = buffer.find("/", curr_index)) != String::npos) {
                int len = string_index - curr_index;
                result[arr_index++] = buffer.substr(curr_index, len);
                curr_index = string_index + 1;
            }
            string_index = buffer.find("/", curr_index);
            result[arr_index] = buffer.substr(curr_index);

            // Parsing student's book lists
            if (!result[2].empty()) {
                curr_index = 0; arr_index = 0; string_index = 0;

                while ((string_index = bookParsingBuffer.find(",", curr_index)) != String::npos) {
                    int len = string_index - curr_index;
                    bookParsingResult.emplace_back(atoi(bookParsingBuffer.substr(curr_index, len).c_str()));
                    curr_index = string_index + 1;
                }
                string_index = bookParsingBuffer.find(",", curr_index);
                bookParsingResult.emplace_back(atoi(bookParsingBuffer.substr(curr_index).c_str()));
            }

            // Insert the student into vector<Student>
            nStudents.emplace(
                // Key
                atoi(result[1].c_str()),
                // Value
                Student(
                    result[0],
                    atoi(result[1].c_str()),
                    (!result[3].empty() ? bookParsingResult : vector<int>()),
                    (result[3] == "true" ? true : false),
                    atoi(result[4].c_str())
                )
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

bool Library::nWriteData() {
    fstream bookFile;
    fstream studentFile;

    bookFile.open(BOOKS_FILE_NAME, ios::out | ios::trunc);
    studentFile.open(STUDENTS_FILE_NAME, ios::out | ios::trunc);

    if (bookFile.is_open() && studentFile.is_open()) {
        String buffer;

        // Write books to the file
        for (int i = 0; i < currBookId; i++) {
            buffer = nBooks[i].getFormattedString();
            bookFile << buffer;
        }
        bookFile.close();

        // Write students to the file
        for (int i = 0; i < currStudentId; i++) {
            buffer = nStudents[i].getFormattedString();
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

class SortBooksByTitle {
public:
    bool operator()(const pair<int, Book>& a, const pair<int, Book>& b) {
        return a.second.getTitle() < b.second.getTitle();
    }
};

class SortBooksByAuthor {
public:
    bool operator()(const pair<int, Book>& a, const pair<int, Book>& b) {
        return a.second.getAuthor() < b.second.getAuthor();
    }
};

class SortBooksByPubDate {
public:
    bool operator()(const pair<int, Book>& a, const pair<int, Book>& b) {
        return a.second.getPubDate() < b.second.getPubDate();
    }
};

class SortBooksByBorrowedCount {
public:
    bool operator()(const pair<int, Book>& a, const pair<int, Book>& b) {
        return a.second.getBorrowedCount() < b.second.getBorrowedCount();
    }
};

void Library::sortBooks() {
    sortedList = vector<pair<int, Book>>(nBooks.begin(), nBooks.end());

    if (sortOptions == SORT_BY_TITLE) {
        sort(sortedList.begin(), sortedList.end(), SortBooksByTitle());
    }
    else if (sortOptions == SORT_BY_AUTHOR) {
        sort(sortedList.begin(), sortedList.end(), SortBooksByAuthor());
    }
    else if (sortOptions == SORT_BY_PUB_DATE) {
        sort(sortedList.begin(), sortedList.end(), SortBooksByPubDate());
    }
    else {
        sort(sortedList.begin(), sortedList.end(), SortBooksByBorrowedCount());
    }

    /*
    for (auto pair : sortedList) {
        cout << format(
            "# {}.\t {} / {} / Published on {} / {} time{} borrowed / {}\n",
            pair.second.getId(),
            pair.second.getTitle(),
            pair.second.getAuthor(),
            pair.second.getPubDate(),
            pair.second.getBorrowedCount(),
            (pair.second.getBorrowedCount() > 1 ? "s" : ""),
            (pair.second.canBeBorrowed() ? "Available" : "Not available")
        );
    }
    */
}