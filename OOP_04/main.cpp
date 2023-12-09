#include <iostream>
#include "book.h"
#include "student.h"
#include "library.h"

using namespace std;
typedef string String;

// ----------------------------------------
//
// Console UI functions declaration
//
// ----------------------------------------
enum Screen {
    SCREEN_MAIN_MENU,
    SCREEN_SHOW,
    SCREEN_NEW,
    SCREEN_SEARCH,
    SCREEN_SORT_BOOKS,
    SCREEN_DEFAULT,
    SCREEN_BORROW,
    SCREEN_RETURN,
    SCREEN_EXIT
};

void navigate(Screen& screen, int& args);
void printMainMenu();
void printShow(const int args);
void printNew(const int args);
void printSortBooks(int& args);
void printBorrow1();
void printBorrow2(int& args);
void printReturn1();
void printReturn2(int& args);
void printBorrow3(int& args);



// ----------------------------------------
//
// Main function
//
// ----------------------------------------
int main() {
    Library library;
    Screen screen = SCREEN_DEFAULT;
    int args;

    if (library.readData()) {
        while (screen != SCREEN_EXIT) {
            printMainMenu();
            navigate(screen, args);

            switch (screen) {
            case SCREEN_SHOW:
                printShow(args);
                if (args == 0) library.printAllStudents();
                else library.printAllBooks();
                break;
            case SCREEN_NEW:
                printNew(args);
                break;
            case SCREEN_SEARCH:
                printNew(args);
                break;
            case SCREEN_SORT_BOOKS:
                printSortBooks(args);
                if (args == 2) library.sortBooksByAuthor();
                else if (args == 3) library.sortBooksByPublishedDate();
                else if (args == 3) library.sortBooksByBorrowedCount();
                else library.sortBooksByTitle();
                break;
            case SCREEN_BORROW:
                int bookId, studentId;
                printBorrow1();
                library.printAllBooks();
                printBorrow2(args);
                bookId = args;
                library.printAllStudents();
                printBorrow3(args);
                studentId = args;
                library.borrowBook(bookId, studentId);
                break;
            case SCREEN_RETURN:
                printReturn1();
                library.printAllBooks();
                printReturn2(args);
                library.returnBook(args);
                break;
            case SCREEN_EXIT:
                break;
            default:
                break;
            }

            cout << "\n\n\n";
        }

        library.writeData();
    }
    else {

    }

    return 0;
}



// ----------------------------------------
//
// Console UI functions implementation
//
// ----------------------------------------
void navigate(Screen& screen, int& args) {
    String input;
    getline(cin, input);

    if (input[0] == '0') {
        screen = SCREEN_EXIT;
    }
    else if (input[0] == '1') {
        screen = SCREEN_SHOW;
        args = 0;
    }
    else if (input[0] == '2') {
        screen = SCREEN_SHOW;
        args = 1;
    }
    else if (input[0] == '3') {
        screen = SCREEN_NEW;
        args = 0;
    }
    else if (input[0] == '4') {
        screen = SCREEN_NEW;
        args = 1;
    }
    else if (input[0] == '5') {
        screen = SCREEN_SEARCH;
        args = 0;
    }
    else if (input[0] == '6') {
        screen = SCREEN_SEARCH;
        args = 1;
    }
    else if (input[0] == '7') {
        screen = SCREEN_SORT_BOOKS;
    }

    else if (input[0] == '8') {
        screen = SCREEN_BORROW;
    }

    else if (input[0] == '9') {
        screen = SCREEN_RETURN;
    }

    cout << "\n\n\n";
}

void printMainMenu() {
    cout << "----------------------------------------\n";
    cout << "### Main menu - Library service\n";
    cout << "----------------------------------------\n\n";

    cout << "# Select actions from below. \n";
    cout << "  - 1. Show all students \n";
    cout << "  - 2. Show all books \n";
    cout << "  - 3. Add new student \n";
    cout << "  - 4. Add new book \n";
    cout << "  - 5. Search students \n";
    cout << "  - 6. Search books \n";
    cout << "  - 7. Sort books \n";
    cout << "  - 8. Borrow book \n";
    cout << "  - 9. Return book \n";
    cout << "  - 0. Save changes and exit \n\n";

    cout << "# Enter number: ";
}

void printShow(const int args) {
    cout << "----------------------------------------\n";
    cout << format("### Show all {}\n", (args == 0 ? "students" : "books"));
    cout << "----------------------------------------\n\n";
}

void printNew(const int args) {
    cout << "----------------------------------------\n";
    cout << format("### Add new {}\n", (args == 0 ? "student" : "book"));
    cout << "----------------------------------------\n\n";
}

void printSearch(const int args) {
    cout << "----------------------------------------\n";
    cout << format("### Search {}\n", (args == 0 ? "students" : "books"));
    cout << "----------------------------------------\n\n";
}

void printSortBooks(int& args) {
    cout << "----------------------------------------\n";
    cout << "### Select book sort option\n";
    cout << "----------------------------------------\n\n";

    cout << "# Select sort option from below. \n";
    cout << "  - 1. Sort by title \n";
    cout << "  - 2. Sort by author \n";
    cout << "  - 3. Sort by published date \n";
    cout << "  - 4. Sort by borrowed count \n\n";

    cout << "# Enter number: ";

    String input;
    getline(cin, input);
    
    if (input[0] == '1') {
        cout << "# From now on, books will sorted by title. \n";
        args = 1;
    }
    else if (input[0] == '2') {
        cout << "# From now on, books will sorted by author. \n";
        args = 2;
    }
    else if (input[0] == '3') {
        cout << "# From now on, books will sorted by published date. \n";
        args = 3;
    }
    else if (input[0] == '4') {
        cout << "# From now on, books will sorted by borrowed count. \n";
        args = 4;
    }
    else {
        cout << "# Wrong input, automatically sorted by title. \n";
        args = 1;
    }
}

void printBorrow1() {
    cout << "----------------------------------------\n";
    cout << "### Borrow book from the student\n";
    cout << "----------------------------------------\n\n";
}

void printBorrow2(int& args) {
    cout << "# Enter the id of the book that will be borrowed: ";

    String input;
    getline(cin, input);
    args = atoi(input.c_str());

    cout << "\n\n\n";
}

void printBorrow3(int& args) {
    cout << "# Enter the id of the student that will borrow book: ";

    String input;
    getline(cin, input);
    args = atoi(input.c_str());

    cout << "\n\n\n";
}

void printReturn1() {
    cout << "----------------------------------------\n";
    cout << "### Return book from the student\n";
    cout << "----------------------------------------\n\n";
}

void printReturn2(int& args) {
    cout << "# Enter the id of the book that will be returned: ";

    String input;
    getline(cin, input);
    args = atoi(input.c_str());
}
