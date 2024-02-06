#ifndef UNTITLED8_USER_H
#define UNTITLED8_USER_H

#include <iostream>
#include <string>
#include <list>  // Include the necessary header for the list container


using namespace std;

// borrow class
class Borrow {
private:
    string ISBN;
    string date;

public:
    Borrow();
    Borrow(string ISBN, string Date);

    string getISBN();
    string getDate();

    // overloaded equality operator
    bool operator==(const Borrow& other) const;
};

// user class
class user {
private:
    int userID;
    string userName;
    list<Borrow> borrowedBooks;
    list<string> unavailableBooks;

public:
    user();
    user(string name, int ID, list<Borrow> borrow, list<string> unavailable);
    user(string name, int Id);

    string getUserName();
    int getUserID();

    // borrowing and returning books
    list<Borrow> getBorrowedBooks();
    void addBorrowedBook(string ISBN, string date);

    void addUnavailableBook(string ISBN);
    bool returnBook(string ISBN, string Data);

    // method for unavailable books
    list<string> getUnavailableBooks();
};

#endif
