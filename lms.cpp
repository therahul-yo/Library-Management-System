#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Book {
public:
    int isbn;
    string title;
    string author;

    Book() : isbn(0), title(""), author("") {}

    Book(int bookIsbn, string bookTitle, string bookAuthor)
        : isbn(bookIsbn), title(bookTitle), author(bookAuthor) {}
};

class Student {
public:
    int id;
    string name;
    vector<int> borrowedBooks;

    Student() : id(0), name("") {}

    Student(int studentId, string studentName)
        : id(studentId), name(studentName) {}

    void borrowBook(int bookIsbn) {
        borrowedBooks.push_back(bookIsbn);
        cout << "Book with ISBN " << bookIsbn << " borrowed by student " << name << "." << endl;
    }

    void returnBook(int bookIsbn) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookIsbn);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
            cout << "Book with ISBN " << bookIsbn << " returned by student " << name << "." << endl;
        } else {
            cout << "Book with ISBN " << bookIsbn << " not found in borrowed list for student " << name << "." << endl;
        }
    }
};

class Library {
private:
    unordered_map<int, Book> books;
    unordered_map<int, Student> students;

public:
    void addBook(int isbn, string title, string author) {
        books[isbn] = Book(isbn, title, author);
        cout << "Book added: " << title << " by " << author << " (ISBN: " << isbn << ")" << endl;
    }

    void addStudent(int id, string name) {
        students[id] = Student(id, name);
        cout << "Student added: " << name << " (ID: " << id << ")" << endl;
    }

    void borrowBook(int studentId, int bookIsbn) {
        if (students.find(studentId) == students.end()) {
            cout << "Student with ID " << studentId << " not found." << endl;
            return;
        }
        if (books.find(bookIsbn) == books.end()) {
            cout << "Book with ISBN " << bookIsbn << " not found." << endl;
            return;
        }
        students[studentId].borrowBook(bookIsbn);
    }

    void returnBook(int studentId, int bookIsbn) {
        if (students.find(studentId) == students.end()) {
            cout << "Student with ID " << studentId << " not found." << endl;
            return;
        }
        students[studentId].returnBook(bookIsbn);
    }

    void displayBooks() {
        cout << "\nAvailable Books:" << endl;
        for (const auto &pair : books) {
            cout << "ISBN: " << pair.second.isbn
                 << ", Title: " << pair.second.title
                 << ", Author: " << pair.second.author << endl;
        }
    }

    void displayStudents() {
        cout << "\nRegistered Students:" << endl;
        for (const auto &pair : students) {
            cout << "ID: " << pair.second.id
                 << ", Name: " << pair.second.name << endl;
        }
    }
};

int main() {
    Library library;
    int choice;

    while (true) {
        cout << "\nLibrary Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. Add Student\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Display Books\n";
        cout << "6. Display Students\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int isbn;
            string title, author;
            cout << "Enter ISBN: ";
            cin >> isbn;
            cin.ignore();  // To clear the newline character from the buffer
            cout << "Enter Book Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            library.addBook(isbn, title, author);
        } 
        else if (choice == 2) {
            int id;
            string name;
            cout << "Enter Student ID: ";
            cin >> id;
            cin.ignore();  // To clear the newline character from the buffer
            cout << "Enter Student Name: ";
            getline(cin, name);
            library.addStudent(id, name);
        } 
        else if (choice == 3) {
            int studentId, bookIsbn;
            cout << "Enter Student ID: ";
            cin >> studentId;
            cout << "Enter Book ISBN: ";
            cin >> bookIsbn;
            library.borrowBook(studentId, bookIsbn);
        } 
        else if (choice == 4) {
            int studentId, bookIsbn;
            cout << "Enter Student ID: ";
            cin >> studentId;
            cout << "Enter Book ISBN: ";
            cin >> bookIsbn;
            library.returnBook(studentId, bookIsbn);
        } 
        else if (choice == 5) {
            library.displayBooks();
        } 
        else if (choice == 6) {
            library.displayStudents();
        } 
        else if (choice == 7) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        } 
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
