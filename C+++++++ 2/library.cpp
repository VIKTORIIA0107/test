#include "library.h"
/*
    Name: Viktoriia Yevsiukova
    Matric number: 2528502
    Module code: AC21008
*/
Library::Library()
{
    HashNode Map;
    user u("Viktoriia", 777);
    use = u;
}

int Library::addDataToHashNode()
{
    // read from the inventory.txt file
    ifstream inputFile("inventory.txt");

    // checking if the file is successfully opened
    if (!inputFile.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line;

    // reading lines from the file and add book data to the HashNode
    while (getline(inputFile, line))
    {
        stringstream l(line);
        string ISBN, title, Author;
        int status;
        l >> ISBN >> quoted(title) >> quoted(Author) >> status;
        //l >> ISBN >> __quoted(title) >> __quoted(Author) >> status; //( I have a Mac I was using __quoted )

        Book Book(title, Author, ISBN, status);
        Map.addBook(Book);
    }

    inputFile.close();

    // open and read from the users.txt file
    ifstream inputFile2("users.txt");

    // checking if the file is successfully opened
    if (!inputFile2.is_open())
    {
        cerr << "Error opening file!" << endl;
        return 1; // return an error code
    }

    // reading each line from the file and add user data to the HashNode
    while (getline(inputFile2, line))
    {
        stringstream ll(line);
        string userName, borrow, reserve;
        int userID;
        list<int> reservationAvailable;
        ll >> userID >> userName >> quoted(borrow) >> quoted(reserve);
        //ll >> userID >> userName >> __quoted(borrow) >> __quoted(reserve);

        // creating lists to store borrowed books and reserved books
        list<Borrow> BORROW;
        list<string> RESERVATION;

        istringstream b(borrow);
        string Book;
        while (getline(b, Book, ','))
        {
            // ISBN, due date from each borrowed book
            size_t position = Book.find(':');
            string borrowBook = Book.substr(0, position);
            string dueDate = Book.substr(position + 1);
            BORROW.push_back(Borrow(borrowBook, dueDate));
        }

        istringstream bb(reserve);
        while (getline(bb, Book, ','))
        {
            // adding each reserved book to the RESERVATION list
            RESERVATION.push_back(Book);
        }

        user user(userName, userID, BORROW, RESERVATION);
        Map.addUser(user, userID);
    }

    inputFile2.close();

    return 0;
}


void Library::addToFile()
{
    //"users.txt" file for writing user data
    ofstream outputFile("users.txt");

    // checking file if it is opening correctly
    if (!outputFile.is_open())
    {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    // list of all user in HashNode
    list<user> allUser = Map.getAllUser();

    // writing their data into the file
    for (user currentUser : allUser)
    {
        int userID = currentUser.getUserID();
        outputFile << userID << " " << currentUser.getUserName() << " ";

        // borrowed books data
        list<Borrow> Borrowed = currentUser.getBorrowedBooks();
        int count = 0;
        for (Borrow borrowBook : Borrowed)
        {
            if (count != 0)
            {
                outputFile << ",";
            }
            outputFile << borrowBook.getISBN() << ":" << borrowBook.getDate();
            count++;
        }

        // reserved books data
        outputFile << " ";
        list<string> reservation = currentUser.getUnavailableBooks();
        count = 0;
        for (string reserve : reservation)
        {
            if (count != 0)
            {
                outputFile << reserve;
            }
            else
            {
                outputFile << "," << reserve;
            }
            count++;
        }

        outputFile << endl;
    }


    outputFile.close();

    // "inventory.txt" file to write a book data
    ofstream outputFile2("inventory.txt");

    // checking if the second file is opening correctly
    if (!outputFile2.is_open())
    {
        cerr << "Error: Unable to open file for writing." << endl;
        return;
    }

    //  list of all books
    list<Book> allBook = Map.allBook();

    for (Book currentBook : allBook)
    {
        outputFile2 << currentBook.getISBN() << " "
                    << "\"" << currentBook.getTitle() << "\""
                    << " " << "\"" << currentBook.getAuthor() << "\""
                    << " " << currentBook.getStatus() << " ";

        outputFile2 << endl;
    }

    outputFile2.close();
}


void Library::addNewBook()
{
    // variables
    string title;
    string author;
    string ISBN;

    // display a message to indicate the process of adding a new book
    cout << "--Adding Book--" << endl;

    // asking user to enter the book title
    cout << "Enter Book title: ";
    cin.ignore();
    getline(cin, title);

    // asking user to enter the book author
    cout << "Enter Book author: ";
    getline(cin, author);

    // asking user to enter the book ISBN
    cout << "Enter Book ISBN: ";
    getline(cin, ISBN);

    // creating a new book
    Book newBook(title, author, ISBN, 1);

    // add new book
    Map.addBook(newBook);

    cout << "Book has been added successfully!" << endl;
}


void Library::removeBook()
{
    int choice;
    string ISBN;

    string isbn;
    cout << "Enter Book ISBN: ";
    cin >> isbn;

    cout << "--Removing Book with ISBN-- " << isbn << "...\n";
    ISBN = isbn;

    if (Map.removeBook(ISBN))
    {
        cout << "Book has been successfully deleted!" << endl;
    }
    else
    {
        cout << "Incorrect ISBN" << endl;
    }
}

void Library::printBook(Book book)
{
    cout << "Name of the book: " << book.getTitle() << endl;

    cout << "Author Name: " << book.getAuthor() << endl;
    cout << "ISBN: " << book.getISBN() << endl;
    //checking the status of the book and displaying its availability
    if (book.getStatus() == 0)
    {
        cout << "Unavailable" << endl;
    }
    else
    {
        cout << "Available" << endl;
    }
}
int Library::addUser(bool isInteractive)
{
    string name;


        if (isInteractive)
        {
            cout << "Please enter your name: ";
        }
        else
        {
            cout << "Enter User Name: ";
        }

        getline(cin, name);

        // custom logic for name validation
        if (name.length() >= 3)
        {
            isInteractive = true;
        }
        else
        {
            cout << "Please enter a name with at least 3 characters." << endl;
        }
    srand(time(0));

    // random number between 100 and 999
    int randomNumber = rand() % 900 + 100;
    int ID = randomNumber;

    user newUser(name, ID);

    Map.addUser(newUser, ID);

    if (!isInteractive)
    {
        cout << newUser.getUserName() << " with UserID " << newUser.getUserID() << " has been added." << endl;
    }
    return ID;
}


void Library::removeUser()
{
    int userID;

    cout << "Enter ID of the user you want to remove: ";

    while (!(cin >> userID))
    {
        cout << " Please enter a valid user ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (Map.removeUser(userID))
    {
        cout << "User with ID " << userID << " successfully removed!" << endl;
    }
    else
    {
        cout << "User with ID " << userID << " not found!" << endl;
    }
}
// display user
void Library::displayAllUser()
{
    list<user> AllUsers = Map.getAllUser();
    for (user currentUser : AllUsers)
    {
        cout << "***************************" << endl;
        //display the name
        cout << "User Name: " << currentUser.getUserName() << endl;
        //display user ID
        cout << "User ID: " << currentUser.getUserID() << endl;
        list<Borrow> borrowedBooks = currentUser.getBorrowedBooks();
        if (!borrowedBooks.empty())
        {
            cout << "Borrowed Book: " << endl;
            for (Borrow borrow : borrowedBooks)
            {
                Book book = Map.search(borrow.getISBN());
                printBook(book);
                cout << "Due Date: " << borrow.getDate() << endl;
            }
        }
        list<string> reservedBook = currentUser.getUnavailableBooks();
        if (!reservedBook.empty())
        {
            cout << "Reserved Books: " << endl;
            for (string reserve : reservedBook)
            {
                Book book = Map.search(reserve);
                printBook(book);
            }
        }
        cout << "***************************" << endl;
    }
}

void Library::borrowBook(Book book1)
{

    Book *newBook = Map.search2(book1.getISBN());

    // variable to store the user response
    char response;

    // checking if the book is available for borrowing
    if (newBook->getStatus() == 1)
    {
        cout << "Do you want to borrow this book? (y/n): ";
    }
    else
    {
        cout << "Do you want to reserve this book? (y/n): ";
    }

    // user response
    cin >> response;

    // process of the user response
    if (response == 'y' || response == 'Y')
    {
        // main user information
        user *MainUser = Map.searchUser2(use.getUserID());

        // check the availability of the book
        if (newBook->getStatus() == 1)
        {
            // borrowing, set a fixed due date (e.g., "2023-07-01")
            string date = "2023-07-01";

            // add borrowed book to the list
            MainUser->addBorrowedBook(book1.getISBN(), date);

            cout << "You borrow a book." << endl;
        }
        else
        {
            // add the book to the user's reserved books list
            MainUser->addUnavailableBook(book1.getISBN());
            cout << "Book reserved for you." << endl;
        }

        // status of the book to indicate it is no longer available
        Map.setStatus(newBook->getISBN(), false);
    }
    else
    {

        return;
    }
}


void Library::returnBook()
{

    string bookISBN;



    cout << "Enter the book isbn you want to return: ";
    cin >> bookISBN;


    user *MainUser = Map.searchUser2(use.getUserID());


    time_t t = time(0);
    tm *now = localtime(&t);
    string date = to_string(now->tm_year + 1900) + '-' +
                  (now->tm_mon + 1 < 10 ? "0" : "") + to_string(now->tm_mon + 1) + '-' +(now->tm_mday < 10 ? "0" : "") + to_string(now->tm_mday);


    if (MainUser->returnBook(bookISBN, date))
    {

        Book *book = Map.search2(bookISBN);

        cout << "Book has been returned successfully" << endl;
        cout << "The book is now available in the library" << endl;


        Map.setStatus(bookISBN, true);
    }
    else
    {
        cout << "You don't have the returning book" << endl;
    }
}

void Library::displayAllBook()
{
    list<Book> Books = Map.allBook();
    for (Book currentBook : Books)
        printBook(currentBook);
}

void Library::search()
{
    string ISBN;
    cout << "Enter the code of the book: ";
    getline(cin, ISBN);
    Book book = Map.search(ISBN);
    if (!book.getTitle().empty())
    {
        printBook(book);
        user *mainUser = Map.searchUser2(use.getUserID());
        for (Borrow borrow : mainUser->getBorrowedBooks())
        {
            if (borrow.getISBN() == book.getISBN())
            {
                break;
            }
        }
        borrowBook(book);
    }
}


void Library::displayOption()
{
    int choice;

    while (true)
    {
        cout << "---Menu---" << endl;
        cout << "1.) Display all users in the library;" << endl;
        cout << "2.) Display all books in the library;" << endl;
        cout << "3.) Search for a book in the library and borrow;" << endl;
        cout << "4.) Add user;" << endl;
        cout << "5.) Add book;" << endl;
        cout << "6.) Remove user;" << endl;
        cout << "7.) Remove book;" << endl;
        cout << "8.) Return Book;" << endl;
        cout << "9.) Exit." << endl;

        cout << "Enter your choice from (1-9): ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 9)
        {
            cout << "Exiting the menu." << endl;
            break;
        }

        if (choice < 1 || choice > 9)
        {
            cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
            continue;
        }

        // Handle menu choices here
        switch (choice)
        {
            case 1:
                cout << "Displaying all users in the library" << endl;
                displayAllUser();
                break;
            case 2:
                cout << "Displaying all books in the library" << endl;
                displayAllBook();
                break;
            case 3:
                cout << "Search for a book in the library and borrow" << endl;
                search();
                break;
            case 4:
                cout << "Add a new user" << endl;
                addUser(false);
                break;
            case 5:
                cout << "Add a new book" << endl;
                addNewBook();
                break;
            case 6:
                cout << "Remove a user" << endl;
                removeUser();
                break;
            case 7:
                cout << "Remove a book" << endl;
                removeBook();
                break;
            case 8:
                cout << "Return a book" << endl;
                returnBook();
                break;
        }
    }
}

int main()
{
    Library lib;
    lib.addDataToHashNode();

    lib.displayOption();
    lib.addToFile();
    return 0;
}
