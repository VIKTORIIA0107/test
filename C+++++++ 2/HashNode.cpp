#include <iostream>
#include "HashNode.h"
#include "book.h"
/*
    Name: Viktoriia Yevsiukova
    Matric number: 2528502
    Module code: AC21008
*/
// list of all books in the HashNode
list<Book> HashNode::allBook()
{
    list<Book> allBook;
    for (const auto &BookPair : BookMap)
    {
        allBook.push_back(BookPair.second);
    }
    return allBook;
}

// list of all users in the HashNode
list<user> HashNode::getAllUser()
{
    list<user> allUsers;
    for (const auto &userPair : userMap)
    {
        allUsers.push_back(userPair.second);
    }
    return allUsers;
}

// adding a new book to the HashNode
void HashNode::addBook(Book newBook)
{
    BookMap[newBook.getISBN()] = newBook;
}

// adding a new user to the HashNode
void HashNode::addUser(user user, int id)
{
    userMap[id] = user;
}

// searching for a book by ISBN in the HashNode
Book HashNode::search(string isbn)
{
    auto it = BookMap.find(isbn);

    if (it != BookMap.end())
    {
        return it->second;
    }
    else
    {
        cerr << "Book with ISBN " << isbn << " not found." << endl;
        return Book();
    }
}

// searching for a book by ISBN in the HashNode and return a pointer
Book *HashNode::search2(string isbn)
{
    auto it = BookMap.find(isbn);

    if (it != BookMap.end())
    {
        return &(it->second);
    }
    else
    {
        cerr << "Item with ISBN " << isbn << " not found." << endl;
        return nullptr;
    }
}

// removing a book from the HashNode
bool HashNode::removeBook(string isbn)
{
    Book mainBook;
    auto it = BookMap.find(isbn);
    if (it != BookMap.end())
    {
        mainBook = it->second;
        BookMap.erase(it);
    }
    else
    {
        return false;
    }
    return true;
}

// setting the status of a book in the HashNode
void HashNode::setStatus(string isbn, bool boo)
{
    auto it = BookMap.find(isbn);
    if (it != BookMap.end())
    {
        it->second.setStatus(boo);
    }
}

// removing a user from the HashNode
bool HashNode::removeUser(int ID)
{
    auto it = userMap.find(ID);
    if (it != userMap.end())
    {
        userMap.erase(it);
        return true;
    }
    else
    {
        return false;
    }
}

// searching for a user by ID in the HashNode
bool HashNode::searchUser(int ID)
{
    auto it = userMap.find(ID);
    return it != userMap.end();
}

// searching for a user by ID in the HashNode and returning a pointer
user *HashNode::searchUser2(int ID)
{
    auto it = userMap.find(ID);
    if (it != userMap.end())
    {
        return &(it->second);
    }
    else
    {
        return nullptr;
    }
}
