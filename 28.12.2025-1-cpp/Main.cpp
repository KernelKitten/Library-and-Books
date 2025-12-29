#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <string>
extern "C" // To include SQLite C library
{
	#include "sqlite3.h"
}

using namespace std;


#pragma region Book and Library Classes

class Book
{
	public:
		string title, author, isbn, isAvailable;
		int year;
		void display()
		{
			cout << "Title: " << title << "\n";
			cout << "Author: " << author << "\n";
			cout << "Year: " << year << "\n";
			cout << "ISBN: " << isbn << "\n";
			cout << "Availability: " << isAvailable << "\n";
		}
};

class Library
{
	public:
		void displayBooks()
		{
			for (Book& book : books)
			{
				book.display();
				cout << "------------------------------------\n";
			}
		}

		void addBook(const Book& book)
		{
			books.push_back(book);
		}

		void removeBook(const string& isbn)
		{
			auto it = find_if(books.begin(), books.end(), [&](const Book& b)
				{
					return b.isbn == isbn;
				});
			if (it != books.end())
			{
				books.erase(it);
				cout << "\nBook removed successfully.\n";
			}
			else
			{
				cout << "\nBook not found.\n";
			}
		}

		void findBook(const string& title)
		{
			auto it = find_if(books.begin(), books.end(), [&](const Book& b)
			{
				return b.title == title;
			});

			if (it != books.end())
			{
				cout << "\nBook is found:\n";
				it->display();
			}
			else
			{
				cout << "\nBook not found.\n";
			}
		}

		void borrowBook(const string& isbn)
		{
			auto it = find_if(books.begin(), books.end(), [&](Book& b)
			{
				return b.isbn == isbn && b.isAvailable == "Yes";
			});

			if (it != books.end())
			{
				it->isAvailable = "No";
				cout << "\nBook borrowed successfully.\n";
			}
			else
			{
				cout << "\nBook not available for borrowing.\n";
			}
		}

		void returnBook(const string& isbn)
		{
			auto it = find_if(books.begin(), books.end(), [&](Book& b)
			{
				return b.isbn == isbn && b.isAvailable == "No";
			});

			if (it != books.end())
			{
				it->isAvailable = "Yes";
				cout << "Book borrowed successfully.\n";
			}
			else
			{
				cout << "Book not available for borrowing.\n";
			}
		}
	private:
		vector<Book> books;
};

istream& operator>>(istream& in, Book& book)
{
	//cout << "Enter title: ";
	getline(in, book.title);
	//cout << "Enter author: ";
	getline(in, book.author);
	//cout << "Enter year: ";
	in >> book.year;
	in.ignore(numeric_limits < streamsize>::max(), '\n');
	//cout << "Enter ISBN: ";
	getline(in, book.isbn);
	book.isAvailable = "Yes";
	return in;
}

ostream& operator<<(ostream& out, Book book)
{
	out << "Title: " << book.title << "\n";
	out << "Author: " << book.author << "\n";
	out << "Year: " << book.year << "\n";
	out << "ISBN: " << book.isbn << "\n";
	out << "Availability: " << book.isAvailable << "\n";
	return out;
}

#pragma endregion

void printMenu()
{
	cout << "Library Menu:\n";
	cout << "1. Add Book\n";
	cout << "2. Remove Book\n";
	cout << "3. Find Book\n";
	cout << "4. Borrow Book\n";
	cout << "5. Return Book\n";
	cout << "6. Display All Books\n";
	cout << "7. Exit\n";
	cout << "Choose an option: ";
}

void inputchoice(Library library)
{
	while (true)
	{
		cout << "\nLibrary Menu:\n";
		cout << "1. Add Book\n";
		cout << "2. Remove Book\n";
		cout << "3. Find Book\n";
		cout << "4. Borrow Book\n";
		cout << "5. Return Book\n";
		cout << "6. Display All Books\n";
		cout << "7. Exit\n";
		cout << "Choose an option: ";
		int choice;
		cin >> choice;
		cin.ignore(numeric_limits < streamsize>::max(), '\n');

		if (choice == 1)
		{
			Book newBook;
			cin >> newBook;
			library.addBook(newBook);
		}
		else if (choice == 2)
		{
			string isbn;
			cout << "\nEnter ISBN of the book to remove: ";
			getline(cin, isbn);
			library.removeBook(isbn);
		}
		else if (choice == 3)
		{
			string title;
			cout << "\nEnter title of the book to find: ";
			getline(cin, title);
			library.findBook(title);
		}
		else if (choice == 4)
		{
			string isbn;
			cout << "\nEnter ISBN of the book to borrow: ";
			getline(cin, isbn);
			library.borrowBook(isbn);
		}
		else if (choice == 5)
		{
			string isbn;
			cout << "\nEnter ISBN of the book to return: ";
			getline(cin, isbn);
			library.returnBook(isbn);
		}
		else if (choice == 6)
		{
			cout << "\nDisplaying all books in the library:\n";
			library.displayBooks();
		}
		else if (choice == 7)
		{
			cout << "\nExiting the program.\n";
			break;
		}
		else
		{
			cout << "\nInvalid choice. Please try again.\n";
		}
	}

}

int main()
{
	sqlite3* db;

	/*if (sqlite3_open("test.db", &db)) {
		std::cerr << "Ошибка открытия: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}*/

	//freopen("books.txt", "r", stdin);

	Book book;
	Library library;

	while (cin >> book)
	{
		library.addBook(book);
	}

	cin.clear();
	freopen("CON", "r", stdin);

	inputchoice(library);

	return 0;
}