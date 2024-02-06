#ifndef LIBRARY
#define LIBRARY
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include "user.h"
#include "book.h"
#include "HashNode.h"
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <regex>
#include <ctime>
#include <algorithm>
using namespace std;


class Library
{
private:
    HashNode Map;
    user use;

public:
    Library();

    // add data to the HashMap
    int addDataToHashNode();

    // add data to the file from HashMap
    void addToFile();

    // add a new item to the library
    void addNewBook();

    // remove an item from the library
    void removeBook();

    //  print information about an item
    void printBook(Book book);

    // display information about all items in the library
    void displayAllBook();

    // add a new user to the library
    int addUser(bool boo);

    // remove a user from the library
    void removeUser();

    // display information about all users in the library
    void displayAllUser();

    // handle the process of borrowing an item
    void borrowBook(Book book);

    // handle the process of returning an item
    void returnBook();

    // perform all searches in the library
    void search();

    // display the available library options
    void displayOption();

    // run the library management system
    int main();
};

#endif
 