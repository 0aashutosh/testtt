#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <windows.h>
using namespace std;

struct book {
    int id;
    char title[100];
    char author[100];
    bool isAvailable;
};

struct signup {
    char fullname[50];
    char username[50];
    char password[50];
    long long int contactnumber;
    int passkey;
} user, owner;

int userMenu();
int adminMenu();
void addBook();
void searchBook();
void displayAllBooks();
void borrowBook();
void returnBook();

bool isIDUnique(int id)
{
	ifstream inFile("books.txt", ios::in | ios::binary);
    if (!inFile) {
        return true; // File doesn't exist yet, so ID is unique
    }
    book b;
    while (inFile.read(reinterpret_cast<char*>(&b), sizeof(book))) {
        if (b.id == id) {
            inFile.close();
            return false;
        }
    }
    inFile.close();
    return true;
}

int main() {
    int choice;
	main:
    system("cls");
    cout << "Main Menu" << endl << endl;
    cout << "1. Login" << endl;
    cout << "2. Create Account" << endl;
    cout << "3. Exit" << endl;
    fflush(stdin);
    cout << "Enter your choice: ";
    fflush(stdin);
    cin>>choice;
    switch (choice) {
    case 1:{
        int loginchoice;
    	login:
        system("cls");
        cout << "Login Menu" << endl << endl;
        cout << "1. Admin" << endl;
        cout << "2. Customer" << endl;
        cout << "3. Back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> loginchoice;
        switch (loginchoice) {
        case 1: {
            char ckusername[50];
            char ckpass[50];
            int flag = 0;
            system("cls");
        	adminlogin:
            fflush(stdin);
            cout << "Enter Username: ";
            gets(ckusername);
            fflush(stdin);
            cout << "Enter Password: ";
            gets(ckpass);
            ifstream ptr("owner.txt", ios::binary);
            if (!ptr) {
                cerr << "Error opening file!" << endl;
                return 1;
            }
            while (ptr.read(reinterpret_cast<char*>(&owner), sizeof(signup))) {
                if (strcmp(owner.username, ckusername) == 0 && strcmp(owner.password, ckpass) == 0) {
                    flag = 1;
                    cout << "Login successful" << endl;
                    getch();
                    ptr.close();
                    adminMenu();
                    break;
                }
            }
            if (!flag) {
                cout << "Invalid credentials. Try again." << endl;
                getch();
                goto adminlogin;
            }
            break;
        }

        case 2: {
            char ckusername[50];
            char ckpass[50];
            int flag = 0, log = 0;
            system("cls");
        userlogin:
            fflush(stdin);
            cout << "Enter Username: ";
            gets(ckusername);
            fflush(stdin);
            cout << "Enter Password: ";
            gets(ckpass);
            ifstream ptr("user.txt", ios::binary);
            if (!ptr) {
                cerr << "Error opening file!" << endl;
                return 1;
            }
            while (ptr.read(reinterpret_cast<char*>(&user), sizeof(signup))) {
                if (strcmp(user.username, ckusername) == 0 && strcmp(user.password, ckpass) == 0) {
                    flag = 1;
                    cout << "Login successful" << endl;
                    getch();
                    ptr.close();
                    log = userMenu();
                    if (log == 1) {
                        goto main;
                    }
                    break;
                }
            }
            if (!flag) {
                cout << "Invalid credentials. Try again." << endl;
                getch();
                goto userlogin;
            }
            break;
        }

        case 3:
            goto main;

        default:
            cout << "Enter valid Choice!!";
            getch();
            goto login;
    
	    }
	}

    case 2:
        int createaccchoice;
    createacc:
        system("cls");
        cout << "Create Account Menu" << endl << endl;
        cout << "1. Admin" << endl;
        cout << "2. Customer" << endl;
        cout << "3. Back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> createaccchoice;
        switch (createaccchoice) {
        case 1: {
            char ckpass[50];
            fstream inFile("owner.txt");
            if (inFile.read(reinterpret_cast<char*>(&owner), sizeof(signup))) {
                cout << "Admin already exists!!";
                getch();
                goto main;
            }
            inFile.close();
        signupmenu1:
            system("cls");
            cout << "\n\n\t\t\t\t\tSIGNUP FORM FOR ADMIN\n\n" << endl;
            fflush(stdin);
            cout << "Enter Your Full Name: ";
            gets(owner.fullname);
            fflush(stdin);
            cout << "Enter Your Username: ";
            gets(owner.username);
            fflush(stdin);
            cout << "Enter Your Password: ";
            gets(owner.password);
            fflush(stdin);
            cout << "Enter Confirmation Password: ";
            gets(ckpass);
            fflush(stdin);
            if (strcmp(ckpass, owner.password) != 0) {
                cout << "Both passwords should match!";
                getch();
                goto signupmenu1;
            }
            fflush(stdin);
            cout << "Enter Your Phone number: ";
            cin >> owner.contactnumber;
            fflush(stdin);
            if (owner.contactnumber < 9700000000 || owner.contactnumber > 9899999999) {
                cout << "Contact length is not correct!";
                getch();
                goto signupmenu1;
            }
            fflush(stdin);
            cout << "Enter your passkey (NOTE : REMEMBER TO KEEP THIS SAFE): ";
            cin >> owner.passkey;

            ofstream outFile("owner.txt", ios::app | ios::binary);
            if (!outFile) {
                cout << "Error: Unable to open file for writing!\n";
                return 1;
            }
            outFile.write(reinterpret_cast<char*>(&owner), sizeof(signup));
            cout << endl << "Signup Successful";
            getch();
            outFile.close();
            goto main;
            break;
        }

        case 2: {
            char ckpass[50];
        signupmenu:
            system("cls");
            fflush(stdin);
            cout << "\n\n\t\t\t\t\tSIGNUP FORM FOR CUSTOMER\n\n" << endl;
            cout << "Enter Your Full Name: ";
            gets(user.fullname);
            fflush(stdin);
            cout << "Enter Your Username: ";
            gets(user.username);
            fflush(stdin);
            cout << "Enter Your Password: ";
            gets(user.password);
            fflush(stdin);
            cout << "Enter Confirmation Password: ";
            gets(ckpass);
            fflush(stdin);
            if (strcmp(ckpass, user.password) != 0) {
                cout << "Both passwords should match!";
                getch();
                goto signupmenu;
            }
            fflush(stdin);
            cout << "Enter Your Phone number: ";
            cin >> user.contactnumber;
            if (user.contactnumber < 9700000000 || user.contactnumber > 9899999999) {
                cout << "Contact length is not correct!";
                getch();
                goto signupmenu;
            }
            fflush(stdin);
            cout << "Enter your passkey (NOTE : REMEMBER TO KEEP THIS SAFE): ";
            cin >> user.passkey;

            ofstream outFile("user.txt", ios::app | ios::binary);
            if (!outFile) {
                cout << "Error: Unable to open file for writing!\n";
                return 1;
            }
            outFile.write(reinterpret_cast<char*>(&user), sizeof(signup));
            cout << endl << "Signup Successful";
            getch();
            outFile.close();
            goto main;
            break;
        }

        case 3:
            goto main;

        default:
            cout << "Enter valid Choice!!";
            getch();
            goto createacc;
        }

    case 3:
        cout << "Thank you for using this program!";
        getch();
        exit(0);

    default:{
    	cout << "Enter valid Choice!!";
        getch();
        goto main;
		break;
	}
        
    }
    return 0;
}

int adminMenu() {
    int choice;
adminmenu:
    system("cls");
    fflush(stdin);
    cout << "\nAdmin Menu\n";
    cout << "1. Add Book\n";
    cout << "2. Search Book\n";
    cout << "3. Display All Books\n";
    cout << "4. Return to Main Menu\n";
    cout << "Enter your choice: ";
    cin >> choice;
    fflush(stdin);
    switch (choice) {
    case 1:
        addBook();
        goto adminmenu;
    case 2:
        searchBook();
        goto adminmenu;
    case 3:
        displayAllBooks();
        goto adminmenu;
    case 4:
        return 1;
    default:
        cout << "Invalid Option! Please enter a valid option.";
        getch();
        goto adminmenu;
    }
    return 0;
}

int userMenu() {
    int choice;
usermenu:
    system("cls");
    fflush(stdin);
    cout << "\nUser Menu\n";
    cout << "1. Search Book\n";
    cout << "2. Display All Books\n";
    cout << "3. Borrow Book\n";
    cout << "4. Return Book\n";
    cout << "5. Return to Main Menu\n";
    cout << "Enter your choice: ";
    fflush(stdin);
    cin >> choice;
    switch (choice) {
    case 1:
        searchBook();
        goto usermenu;
    case 2:
        displayAllBooks();
        goto usermenu;
    case 3:
        borrowBook();
        goto usermenu;
    case 4:
        returnBook();
        goto usermenu;
    case 5:
        system("cls");
        cout << "You have been logged out";
        getch();
        return 1;
    default:
        cout << endl << "Invalid Option! Please enter a valid option.";
        cout << endl << "Press any key to continue";
        getch();
        goto usermenu;
    }
    return 0;
}

void addBook() {
    book newBook;
    addbook:
    system("cls");
    fflush(stdin);
    cout << "Enter Book ID: ";
    cin >> newBook.id;
    if (!isIDUnique(newBook.id)) 
	{
        cout << "Error: Book ID is not unique! Try again.\n";
        getch();
        goto addbook;
    }
    fflush(stdin);
    cout << "Enter Book Title: ";
    cin.ignore();
    cin.getline(newBook.title, 100);
    cout << "Enter Book Author: ";
    cin.getline(newBook.author, 100);
    newBook.isAvailable = true;

    ofstream outFile("books.txt", ios::app | ios::binary);
    if (!outFile) {
        cout << "Error: Unable to open file for writing!\n";
        return;
    }
    outFile.write(reinterpret_cast<char*>(&newBook), sizeof(book));
    outFile.close();
    cout << "Book added successfully!";
    getch();
}

void searchBook() {
    int searchId;
    system("cls");
    cout << "Enter Book ID to search: ";
    cin >> searchId;

    ifstream inFile("books.txt", ios::binary);
    if (!inFile) {
        cout << "Error: Unable to open file for reading!\n";
        return;
    }

    book tempBook;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&tempBook), sizeof(book))) {
        if (tempBook.id == searchId) {
            cout << "Book ID: " << tempBook.id << endl;
            cout << "Book Title: " << tempBook.title << endl;
            cout << "Book Author: " << tempBook.author << endl;
            cout << "Availability: " << (tempBook.isAvailable ? "Available" : "Not Available") << endl;
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
        cout << "Book not found!";
    }
    getch();
}

void displayAllBooks() {
    ifstream inFile("books.txt", ios::binary);
    if (!inFile) {
        cout << "Error: Unable to open file for reading!\n";
        return;
    }

    book tempBook;
    while (inFile.read(reinterpret_cast<char*>(&tempBook), sizeof(book))) {
        cout << "Book ID: " << tempBook.id << endl;
        cout << "Book Title: " << tempBook.title << endl;
        cout << "Book Author: " << tempBook.author << endl;
        cout << "Availability: " << (tempBook.isAvailable ? "Available" : "Not Available") << endl;
        cout << "-----------------------------" << endl;
    }
    inFile.close();
    getch();
}

void borrowBook() {
    int borrowId;
    cout << "Enter Book ID to borrow: ";
    cin >> borrowId;

    fstream file("books.txt", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "Error: Unable to open file!\n";
        return;
    }

    book tempBook;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&tempBook), sizeof(book))) {
        if (tempBook.id == borrowId && tempBook.isAvailable) {
            tempBook.isAvailable = false;
            int pos = -1 * static_cast<int>(sizeof(book));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&tempBook), sizeof(book));
            cout << "Book borrowed successfully!";
            found = true;
            break;
        }
    }
    file.close();
    if (!found) {
        cout << "Book not available for borrowing!";
    }
    getch();
}

void returnBook() {
    int returnId;
    cout << "Enter Book ID to return: ";
    cin >> returnId;

    fstream file("books.txt", ios::in | ios::out | ios::binary);
    if (!file) {
        cout << "Error: Unable to open file!\n";
        return;
    }

    book tempBook;
    bool found = false;
    while (file.read(reinterpret_cast<char*>(&tempBook), sizeof(book))) {
        if (tempBook.id == returnId && !tempBook.isAvailable) {
            tempBook.isAvailable = true;
            int pos = -1 * static_cast<int>(sizeof(book));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&tempBook), sizeof(book));
            cout << "Book returned successfully!";
            found = true;
            break;
        }
    }
    file.close();
    if (!found) {
        cout << "Book not found or already returned!";
    }
    getch();
}
