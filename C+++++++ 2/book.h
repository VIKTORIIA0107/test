#ifndef ITEM
#define ITEM

#include <string>
#include <list>

using namespace std;

class Book {
private:
    // private member variables
    string title;
    string ISBN;
    string Author;
    int status;

public:
    // default constructor
    Book();
    // parameterized constructor
    Book(string title, string author, string isbn, int status);

    // get title of the book
    string getTitle();
    // get author of the book
    string getAuthor();
    // get ISBN of the book
    string getISBN();
    // get status of the book
    int getStatus();
    // set status of the book
    void setStatus(int s);

    // compare two Book objects for equality
    bool operator==(const Book& other) const;
};
#endif
