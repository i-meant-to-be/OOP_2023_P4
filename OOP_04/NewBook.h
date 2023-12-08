#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Book {
private:
	string title;
	string author;
	tm published_date;
	tm date_lend;
	tm date_return;
	bool isLend;
	Student borrower;
	int countLend;

public:
	Book(string target_title) {};

	string get_title() {};
	string get_author() {};
	tm get_published_date() {};
	tm get_date_lend() {};
	tm get_date_return() {};
	bool get_isLend() {};
	Student get_borrower() {};
	int get_countLend() {};

	void print_bookinfo() {};
	void edit_title(string target_title) {};
	void edit_author(string target_author) {};
	void edit_date_lend(tm target_date) {};
	void edit_date_return(tm target_date) {};
	void edit_countLend(int count) {};
	bool canLend() {};
};