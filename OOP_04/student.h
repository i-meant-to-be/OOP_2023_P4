#ifndef __STUDENT_H
#define __STUDENT_H

#include <string>
#include <format>
#include <vector>

using namespace std;
typedef string String;

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
    Student();
    Student(const String& n, int id);
    Student(const String& n, int id, bool o, int c);
    Student(const String& n, int id, vector<int> bl, bool o, int c);

    // Getter
    String getName() const;
    int getId() const;
    bool getIsOverdue() const;
    bool canBorrow() const;

    // Setter
    void setIsOverdue(bool value);

    // Methods
    void increaseOverdueCount();
    void addToBookList(int bookId);
    void removeFromBookList(int bookId);
    int getSizeOfBookList();
    String getFormattedString();
};

#endif