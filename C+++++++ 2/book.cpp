#include "book.h"
/*
    Name: Viktoriia Yevsiukova
    Matric number: 2528502
    Module code: AC21008
*/
// default constructor
Book::Book() {
    // member variables
    title = "";
    ISBN = "";
    Author = "";
    status = 0;
}

// parameterized constructor
Book::Book(string title, string author, string isbn, int status) {
    // initialize member variables with provided values
    this->title = title;
    this->ISBN = isbn;
    this->Author = author;
    this->status = status;
}

// method for retrieving the title of the book
string Book::getTitle() {
    return title;
}

// method for retrieving the author of the book
string Book::getAuthor() {
    return Author;
}

// method for retrieving the ISBN of the book
string Book::getISBN() {
    return ISBN;
}

// method for retrieving the status of the book
int Book::getStatus() {
    return status;
}

// method for updating the status of the book
void Book::setStatus(int s) {
    status = s;
}

// compare two Book objects
bool Book::operator==(const Book& other) const {
    // return true if all are equal, otherwise return false
    return (ISBN == other.ISBN && title == other.title && Author == other.Author);
}
