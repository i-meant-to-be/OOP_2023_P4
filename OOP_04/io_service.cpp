#include <vector>
#include <ctime>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>

using namespace std;
typedef string String;

void load_file(String student, String book);
void save_student(String student);
void save_book(String book);

/*
int main() {
	//ifstream fp_student, fp_book;
	String path_book = "./book.txt";				// name / author / borrow date1 / return date2 / booltype / std id / date3 / count
	String path_student = "./student.txt";			// name / std id / bool / vector<book> -> bookname:bookname:bookname... / count
	// delimeter = ';', in book vector = ':' 
	// Assume that date data will be I/O in String type. (YYYYMMDD)
	//fp_student.open(path_student);
	//fp_book.open(path_book);

	String student_example = "Seonu;20202437;0;Book1:Book2:Book3;3;0";
	String book_example = "OOP2023BongBong;BongsuSon;20231101;20231201;1;20202437;20010320;4";

	load_file(path_student, path_book);

	// ���� SAVE �κ��� student, book ��ü�� getStr �޼ҵ带 �����Ѵٴ� ���� �Ͽ� ���۵�.
	// ����� Save, Load�� ����ϴ� ������ �и��Ǿ�������, ���� ���� �ÿ��� �ϳ��� ���� (�л�, å�� ���� �� 2��)�� �̿��ϰ� �� ��.

	save_student(student_example);
	save_book(book_example);

	cout << "Program End" << endl;


	return 0;
}
*/

void load_file(String student, String book) {
	/*
	BOOK FORMAT
		Name(String) ; Author(String) ; Data_Lend(YYYYMMDD) ; DATE_RETURN(YYYYMMDD) ; isLend ? 1 : 0 (-> bool) ; StdID(String) ; Date_Release(YYYYMMDD) ; Count_Lend(int)

	STUDENT FORMAT
		Name(String) ; StdID(String) ; Overdue(now) ? 1 : 0 (-> bool) ; book_name:book_name:book_name:book_name(String -> vector<book>) ; Count_Lend(int) ; Count_Overdue(int)

	----> No white space allowed except 'book_name'
	*/

	ifstream books, students;		 				// Open files
	students.open(student);
	books.open(book);
	String strbuf;
	String line;

	// for book.txt
	String name_book, author, date_lend, date_return, book_stdid, date_release;
	int isLend = 0, count_lended = 0;

	//for student.txt
	String name_std, stdid;
	vector<String> lend_books;
	int isOverdue = 0, count_lend = 0, count_overdue = 0;

	int count = 0;
	while (getline(books, line)) {
		if (line[0] == '/') continue;
		vector<String> bookbuf;
		cout << "Book number: " << count++ << endl;
		iStringstream ss(line);
		while (getline(ss, strbuf, ';')) {
			bookbuf.push_back(strbuf);
		}

		// Change here to store data
		cout << "	Name: " << bookbuf[0] << endl;
		cout << "	Author: " << bookbuf[1] << endl;
		cout << "	Lend: " << bookbuf[2] << endl;
		cout << "	Return: " << bookbuf[3] << endl;
		cout << "	isLend: " << ((bookbuf[4] == "1") ? "true" : "false") << endl;
		cout << "	Std ID: " << bookbuf[5] << endl;
		cout << "	Release: " << bookbuf[6] << endl;
		cout << "	Lended: " << bookbuf[7] << endl;

		cout << endl;
	}

	cout << "\n\n";
	count = 0;
	while (getline(students, line)) {
		if (line[0] == '/') continue;
		vector<String> stdbuf;
		cout << "Student number: " << count++ << endl;
		iStringstream ss(line);
		while (getline(ss, strbuf, ';')) {
			stdbuf.push_back(strbuf);
		}

		// Change here to store data
		cout << "	Name: " << stdbuf[0] << endl;
		cout << "	Std ID: " << stdbuf[1] << endl;
		cout << "	isOverdue: " << ((stdbuf[2] == "1") ? "true" : "false") << endl;

		cout << "	Books: " << "\n		 ";
		iStringstream ss_book(stdbuf[3]);
		int bookcount = 0;
		while (getline(ss_book, strbuf, ':')) {
			cout << bookcount++ << " - " << strbuf << " // ";
		}
		cout << endl;

		cout << "	Count_Lend: " << stdbuf[4] << endl;
		cout << "	Count_Overdue: " << stdbuf[5] << endl;

		cout << endl;
	}

	students.close();
	books.close();
}

void save_student(String student) {
	ofstream outfile("./student_example.txt");	// �ӽ÷� ���� ����. ���� ���� Vector<student>���� ���˿� �´� String�� �ϳ��� �о�� ������ �ʿ� ����. ������ Library���� ����	

	outfile << student << endl;					// ���� ���� Loop�� �̿��� Vector�� ��� �����͸� �ѹ��� ����.
}

void save_book(String book) {
	ofstream outfile("./book_example.txt");

	outfile << book << endl;
}

