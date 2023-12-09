#include "book.h"
#include "student.h"
#include "library.h"

using namespace std;
typedef string String;

int main() {
    Library library;

    /*
    library.addBook("And Then There Were None", "Agatha Christie", "1939-11-06");
    library.addBook("JUSTICE: What's the right thing to do?", "Michael Sandel", "2010-08-17");
    library.addBook("The Art of Loving", "Erich Fromm", "2019-09-01");
    library.addStudent("Jason");
    library.addStudent("Jack");
    library.addStudent("Katrina");

    library.sortBooksByTitle();
    cout << "# Sorted by title:" << endl;
    for (const auto& book : library.books) {
        cout << book.getTitle() << endl;
    }
    cout << endl;
    
    library.sortBooksByAuthor();
    cout << "# Sorted by author:" << endl;
    for (const auto& book : library.books) {
        cout << book.getTitle() << endl;
    }
    cout << endl;
    
    library.sortBooksByPublishedDate();
    cout << "# Sorted by published date:" << endl;
    for (const auto& book : library.books) {
        cout << book.getTitle() << endl;
    }
    cout << endl;
    
    library.sortBooksByBorrowedCount();
    cout << "# Sorted by borrowed count:" << endl;
    for (const auto& book : library.books) {
        cout << book.getTitle() << endl;
    }
    cout << endl;

    library.addBook("And Then There Were None", "Agatha Christie", "1939-11-06");
    library.addBook("JUSTICE: What's the right thing to do?", "Michael Sandel", "2010-08-17");
    library.addBook("The Art of Loving", "Erich Fromm", "2019-09-01");

    library.addStudent("Jason");
    library.addStudent("Jack");
    library.addStudent("Katrina");

    library.borrowBook(0, 0);
    */

    library.readData();

    library.writeData();

    return 0;
}