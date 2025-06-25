/*

- Object-orianted programming => is a programming paradigm based on the concept "Objects".
- Object is a thing => collection of (data and methods()) that operate on that data.
- data => attributes - properties / methods() => operations - functions.

*/

#include <iostream>
#include <list>
#include <vector>
#include <limits>
using namespace std;


class book {
    int bookId;
    string bookTitle;
    string bookAuthor;
    bool isAvailable;

public:
    book(int BID ,string BT, string BA) {
        bookId = BID;
        bookTitle = BT;
        bookAuthor = BA;
        isAvailable = true;
    }

    virtual void display() {
        cout << "- Book ID: " << bookId << endl;
        cout << "- Book title: " << bookTitle << endl;
        cout << "- Book author: " << bookAuthor << endl;
    }

    int getId() { return bookId; }
    bool getIsAvailable() { return isAvailable; }
    string getTitle() { return bookTitle; }
    void borrowBook() { isAvailable = false; }
    void returnBook() { isAvailable = true; }
    virtual string getType(){ return "book"; }


};

class Ebook : public book {
    string downloadLink;

public:
    Ebook(int BID ,string BT, string BA, string DL) : book(BID,BT,BA), downloadLink(DL) {}

    void display() override {
        book::display();
        cout << "- Download Link: " << downloadLink << endl;
    }

    string getType() override { return "Ebook"; }
};

class audioBook : public book {
private:
    double duration;

public:
    audioBook(int BID, std::string BT, string BA, double D) : book(BID,BT,BA), duration(D) {}

    void display() override {
        book::display();
        cout << "- Duration: " << duration << endl;
    }


    string getType() override { return "Audiobook"; }

};




class library {
    vector<book*> books;

public:

    // for check books arr is empty or Not.
    bool libIsEmpty() {
        return books.empty();
    }


    void addBook(book* b) {
        books.push_back(b);
    };

    void removeBook(const int id) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i]->getId() == id) {
                books.erase(books.begin() + i);
                cout << "Book with ID: " << id << " Removed Successfully!" << endl;
                return;
            }
        }
        cout << "Book with ID: " << id << " Not Found!" << endl;
    }

    void displayAllBooks() {
        for (int i = 0; i < books.size(); i++) {
            cout << i + 1 << ". " << endl;
            books[i]->display();
            cout << "- Status: " << (books[i]->getIsAvailable() ? "Available" : "Borrowed") << endl;
            cout << "- Type: " << books[i]->getType() << endl;
            cout << "------------------------------------------------------------" << endl;
        }
    }


    void borrowBook(const int id) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i]->getId() == id && books[i]->getIsAvailable()) {
                books[i]->borrowBook();
                cout << "Book with ID: " << id << " Borrowed Successfully!" << endl;
                return;
            }
        }
        cout << "Book with ID: " << id << " Not Found!" << endl;
    }

    void returnBook(const int id) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i]->getId() == id && !books[i]->getIsAvailable()) {
                books[i]->returnBook();
                cout << "Book Returned Successfully!" << endl;
                return;
            }
        }
        cout << "Book not found or not borrowed!\n";
    }

    void searchByTitle(const string bookTitle) {
        for (int i = 0; i < books.size(); i++) {
            if (books[i]->getTitle() == bookTitle) {
                cout << "Your book is Exist: " << endl;
                books[i]->display();
                return;
            }
        }
        cout << "The Book with titel " << bookTitle << " Not Found!" << endl;
    }
};





int main(){

    library lib;

    book* b1 = new Ebook(1, "HTML", "Anas", "www.html.com");
    book* b2 = new book(2, "CSS", "Khaled");
    book* b3 = new Ebook(3, "JS", "Ahmed", "www.js.com");
    book* b4 = new audioBook(4, "C++", "Mahmoud",10.43);

    lib.addBook(b1);
    lib.addBook(b2);
    lib.addBook(b3);
    lib.addBook(b4);

    int choice;

    bool running = true;
    while(running){
        cout << "================== Welcome to the Library ==================" << endl;
        cout << "1. Show All Books" << endl;
        cout << "2. Borrow a Book" << endl;
        cout << "3. Return a Book" << endl;
        cout << "4. Remove a Book" << endl;
        cout << "5. Search on a Book" << endl;
        cout << "0. Exit" << endl;
        cout << "============================================================" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        if(lib.libIsEmpty()) {
            cout << "No books in the library yet!\n";
            break;
        }

        int bookId;
        string title;
        switch (choice) {
            case 1:
                lib.displayAllBooks();
                break;
            case 2:
                cout << "Enter Book ID to borrow: ";
                cin >> bookId;
                lib.borrowBook(bookId);
                break;

            case 3:
                cout << "Enter Book ID to return: ";
                cin >> bookId;
                lib.returnBook(bookId);
                break;

            case 4:
                cout << "Enter Book ID to remove: ";
                cin >> bookId;
                lib.removeBook(bookId);
                break;


            case 5:
                cout << "Please enter your Book Title: ";
                cin >> title;
                lib.searchByTitle(title);
                break;

            case 0: {
                char confirm;
                while (true) {
                    cout << "Are you sure you want to exit? (y / n): ";
                    cin >> confirm;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if(confirm == 'y' || confirm == 'Y') {
                        cout << "Thank you for visiting the library. Goodbye!\n";
                        cout << "Exiting...\n";
                        running = false;
                        break;
                    } else if (confirm == 'n' || confirm == 'N') {
                        cout << "Returning to main menu.\n";
                        break;
                    } else {
                        cout << "Please enter only 'y' or 'n'. Try again.\n";
                    }
                }
            }
            break;

            default:
                cout << "Invalid Choice! Please try again.\n";
        }

    }

    return 0;
}