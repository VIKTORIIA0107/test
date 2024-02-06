#include <iostream>
#include "user.h"
/*
    Name: Viktoriia Yevsiukova
    Matric number: 2528502
    Module code: AC21008
*/

Borrow::Borrow()
{

    this->ISBN = "";
    this->date = "";
}

Borrow::Borrow(string ISBN, string dueDate)
{
    this->ISBN = ISBN;
    this->date = dueDate;
}
//getter for ISBN
string Borrow::getISBN()
{

    return ISBN;
}
//getter for date
string Borrow::getDate()
{
    return date;
}

bool Borrow::operator==(const Borrow &other) const
{
    // overload based on ISBN and date
    return (ISBN == other.ISBN) && (date == other.date);
}

//implementation of the user class
user::user()
{
    this->userName = "";
    this->userID = 0;
}

user::user(string name, int Id, list<Borrow> borrow, list<string> reserved)
{

    this->userName = name;
    this->userID = Id;
    borrowedBooks = borrow;
    unavailableBooks = reserved;
}

user::user(string name, int Id)
{

    this->userName = name;
    this->userID = Id;
}
//userName
string user::getUserName()
{

    return userName;
}
//userID
int user::getUserID()
{
    return userID;
}
//borrowed books
list<Borrow> user::getBorrowedBooks()
{
    return borrowedBooks;
}
//unavailable books
list<string> user::getUnavailableBooks()
{
    return unavailableBooks;
}

void user::addBorrowedBook(string ISBN, string Date)
{
    // add a borrowed book to the list
    Borrow boo(ISBN, Date);
    borrowedBooks.push_back(boo);
}

void user::addUnavailableBook(string ISBN)
{
    // add an unavailable book to the list
    unavailableBooks.push_back(ISBN);
}

bool user::returnBook(string ISBN, string currentDate)
{

    for (Borrow borrowBook : borrowedBooks)
    {
        // check if the current borrowed book matches the ISBN
        if (borrowBook.getISBN() == ISBN)
        {
            // if the book is overdue
            if (borrowBook.getDate() < currentDate)
            {
                cout << "Book with ISBN " << ISBN << " is overdue. A penalty of 10 pounds is applied." << endl;
                borrowedBooks.remove(borrowBook);
                return true;
            }
            else
            {
                // book is not overdue
                cout << "Returned successfully." << endl;
                cout << "Book is not overdue, so NO penalty :-)" << endl;
                // remove book from the borrow list
                borrowedBooks.remove(borrowBook);
                return true;
            }
        }
    }

    return false;
}
