#ifndef HASHNODE
#define HASHNODE

#include <vector>
#include <algorithm>
#include <unordered_map>
#include "book.h"
#include "user.h"
#include <string>
#include "list"
using namespace std;

class HashNode {
private:
    unordered_map<string, Book> BookMap;
    unordered_map<int, user> userMap;

public:

    list<Book> allBook();

    list<user> getAllUser();

    void addBook(Book newBook);

    void addUser(user user, int id);

    // search for a book by ISBN in the HashNode
    Book search(string isbn);

    //search for a book by ISBN in the HashNode and return a pointer
    Book* search2(string isbn);

    bool removeBook(string isbn);

    //set the status of a book in the HashNode
    void setStatus(string isbn, bool boo);

    bool removeUser(int ID);

    // search for a user by ID in the HashNode
    bool searchUser(int ID);

    //search for a user by ID in the HashNode and return a pointer
    user* searchUser2(int ID);
};

#endif
