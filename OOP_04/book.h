#ifndef __BOOK_H
#define __BOOK_H

#include <string>
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
    Book();
    Book(const String& t, const String& a, const String& p);
    Book(const String& t, const String& a, const String& p, int id);
    Book(const String& t, const String& a, const String& p, int id, bool b, int c, int sId);

    // Getter
    String getTitle() const;
    String getAuthor() const;
    String getPubDate() const;
    int getId() const;
    bool getIsBorrowed() const;
    bool canBeBorrowed() const;
    int getBorrowedCount() const;
    int getStudentId() const;

    // Setter
    void setIsBorrowed(bool value);
    void setStudentId(int value);
    void setId(int value);

    // Methods
    void increaseBorrowedCount();
    String getFormattedString();
};

#endif