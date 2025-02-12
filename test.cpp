#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <windows.h>
#include <limits>
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


void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

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
    setColor(7);
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "\t\t\t\t\t\t\t\tMain Menu" << endl << endl;
    cout << "\t\t\t\t\t\t\t\t1. Login" << endl;
    cout << "\t\t\t\t\t\t\t\t2. Create Account" << endl;
    cout << "\t\t\t\t\t\t\t\t3. Exit" << endl;
	cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    fflush(stdin);
    cout << "\t\t\t\t\t\t\t\tEnter your choice: ";
    fflush(stdin);
    cin>>choice;
    switch (choice) {
    case 1:{
        int loginchoice,log;
    	login:
        system("cls");
        setColor(7);
        cout << "\t\t\t\t\t\t\t\tLogin Menu" << endl << endl;
        cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout << "\t\t\t\t\t\t\t\t1. Admin" << endl;
        cout << "\t\t\t\t\t\t\t\t2. Customer" << endl;
        cout << "\t\t\t\t\t\t\t\t3. Back to main menu" << endl;
        cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout << "\t\t\t\t\t\t\t\tEnter your choice: ";
        cin >> loginchoice;
        switch (loginchoice) {
        case 1: {
            char ckusername[50];
            char ckpass[50];
            int flag = 0;
            system("cls");
        	adminlogin:
            fflush(stdin);
            cout<<  "\t\t\t\t\t\t\t\tAdmin Login\n";
            cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout << "\t\t\t\t\t\t\t\tEnter Username: ";
            gets(ckusername);
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter Password: ";
            gets(ckpass);
            ifstream ptr("owner.txt", ios::binary);
            if (!ptr) {
            	setColor(12);
                cerr << "\t\t\t\t\t\t\t\tError opening file!" << endl;
                getch();
                goto main;
            }
            while (ptr.read(reinterpret_cast<char*>(&owner), sizeof(signup))) {
                if (strcmp(owner.username, ckusername) == 0 && strcmp(owner.password, ckpass) == 0) {
                    flag = 1;
                    setColor(10);
                    cout << "\t\t\t\t\t\t\t\tLogin successful" << endl;
                    getch();
                    ptr.close();
                    log=adminMenu();
                    if(log==1)
                    {
                    	setColor(10);
                    	cout<<"\n\t\t\t\t\t\t\t\tYou have been logged out\n";
                    	getch();
                    	goto main;
					}
                    break;
                }
            }
            if (!flag) {
            	setColor(12);
                cout << "\t\t\t\t\t\t\t\tInvalid credentials. Try again." << endl;
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
        	setColor(7);
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tCustomer Login\n";
            cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout << "\t\t\t\t\t\t\t\tEnter Username: ";
            gets(ckusername);
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter Password: ";
            gets(ckpass);
            ifstream ptr("user.txt", ios::binary);
            if (!ptr) {
            	setColor(12);
                cerr << "\t\t\t\t\t\t\t\tError opening file!" << endl;
                getch();
                goto main;
            }
            while (ptr.read(reinterpret_cast<char*>(&user), sizeof(signup))) {
                if (strcmp(user.username, ckusername) == 0 && strcmp(user.password, ckpass) == 0) {
                    flag = 1;
					setColor(10);
                    cout << "\t\t\t\t\t\t\t\tLogin successful" << endl;
                    getch();
                    ptr.close();
                    log = userMenu();
                    if(log==1)
                    {
                    	setColor(10);
                    	cout<<"\n\t\t\t\t\t\t\t\tYou have been logged out\n";
                    	getch();
                    	goto main;
					}
                    break;
                }
            }
            if (!flag) {
            	setColor(12);
                cout << "\t\t\t\t\t\t\t\tInvalid credentials. Try again." << endl;
                getch();
                goto userlogin;
            }
            break;
        }

        case 3:
            goto main;

        default:
        	setColor(12);
            cout << "\t\t\t\t\t\t\t\tEnter valid Choice!!";
            getch();
                // Clear error flags and ignore invalid input
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto login;
    
	    }
	}

    case 2:
        int createaccchoice;
    createacc:
        system("cls");
        setColor(7);
        cout << "\t\t\t\t\t\t\t\tCreate Account Menu" << endl << endl;
        cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout << "\t\t\t\t\t\t\t\t1. Admin" << endl;
        cout << "\t\t\t\t\t\t\t\t2. Customer" << endl;
        cout << "\t\t\t\t\t\t\t\t3. Back to main menu" << endl;
        cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout << "\t\t\t\t\t\t\t\tEnter your choice: ";
        cin >> createaccchoice;
        switch (createaccchoice) {
        case 1: {
            char ckpass[50];
            fstream inFile("owner.txt");
            if (inFile.read(reinterpret_cast<char*>(&owner), sizeof(signup))) {
            	setColor(12);
                cout << "\t\t\t\t\t\t\t\tAdmin already exists!!";
                getch();
                goto main;
            }
            inFile.close();
        signupmenu1:
            system("cls");
            setColor(7);
            cout << "\n\n\t\t\t\t\t\t\t\tSIGNUP FORM FOR ADMIN\n\n" << endl;
            cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter Your Full Name: ";
            gets(owner.fullname);
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter Your Username: ";
            gets(owner.username);
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter Your Password: ";
            gets(owner.password);
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter Confirmation Password: ";
            gets(ckpass);
            fflush(stdin);
            if (strcmp(ckpass, owner.password) != 0) {
            	setColor(12);
                cout << "\t\t\t\t\t\t\t\tBoth passwords should match!";
                getch();
                goto signupmenu1;
            }
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter Your Phone number: ";
            cin >> owner.contactnumber;
            fflush(stdin);
            if (owner.contactnumber < 9700000000 || owner.contactnumber > 9899999999) {
            	setColor(12);
                cout << "\t\t\t\t\t\t\t\tContact length is not correct!";
                getch();
                goto signupmenu1;
            }
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter your passkey (NOTE : REMEMBER TO KEEP THIS SAFE): ";
            cin >> owner.passkey;

            ofstream outFile("owner.txt", ios::app | ios::binary);
            if (!outFile) {
            	setColor(12);
                cout << "\t\t\t\t\t\t\t\tError: Unable to open file for writing!\n";
                return 1;
            }
            outFile.write(reinterpret_cast<char*>(&owner), sizeof(signup));
            setColor(10);
            cout << endl << "\t\t\t\t\t\t\t\tSignup Successful";
            setColor(7);
            getch();
            outFile.close();
            goto main;
            break;
        }

        case 2: {
            char ckpass[50];
        signupmenu:
            system("cls");
            setColor(7);
            fflush(stdin);
            cout << "\n\n\t\t\t\t\t\t\t\tSIGNUP FORM FOR CUSTOMER\n\n" << endl;
            cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout << "\t\t\t\t\t\t\t\tEnter Your Full Name: ";
            gets(user.fullname);
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter Your Username: ";
            gets(user.username);
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter Your Password: ";
            gets(user.password);
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter Confirmation Password: ";
            gets(ckpass);
            fflush(stdin);
            if (strcmp(ckpass, user.password) != 0) {
            	setColor(12);
                cout << "\t\t\t\t\t\t\t\tBoth passwords should match!";
                getch();
                goto signupmenu;
            }
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter Your Phone number: ";
            cin >> user.contactnumber;
            if (user.contactnumber < 9700000000 || user.contactnumber > 9899999999) {
            	setColor(12);
                cout << "\t\t\t\t\t\t\t\tContact length is not correct!";
                getch();
                goto signupmenu;
            }
            fflush(stdin);
            cout << "\t\t\t\t\t\t\t\tEnter your passkey (NOTE : REMEMBER TO KEEP THIS SAFE): ";
            cin >> user.passkey;

            ofstream outFile("user.txt", ios::app | ios::binary);
            if (!outFile) {
            	setColor(12);
                cout << "\t\t\t\t\t\t\t\tError: Unable to open file for writing!\n";
                return 1;
            }
            outFile.write(reinterpret_cast<char*>(&user), sizeof(signup));
            setColor(10);
            cout << endl << "\t\t\t\t\t\t\t\tSignup Successful";
            getch();
            outFile.close();
            goto main;
            break;
        }

        case 3:
            goto main;

        default:
        	setColor(12);
            cout << "\t\t\t\t\t\t\t\tEnter valid Choice!!";
            getch();
                // Clear error flags and ignore invalid input
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
            goto createacc;
        }

    case 3:
    	setColor(10);
        cout << "\t\t\t\t\t\t\t\tThank you for using this program!";
        getch();
        setColor(7);
        exit(0);

    default:{
    	setColor(12);
    	cout << "\t\t\t\t\t\t\t\tEnter valid Choice!!";
        getch();
                // Clear error flags and ignore invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    setColor(7);
    cout << "\n\t\t\t\t\t\t\t\tAdmin Menu\n";
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "\t\t\t\t\t\t\t\t1. Add Book\n";
    cout << "\t\t\t\t\t\t\t\t2. Search Book\n";
    cout << "\t\t\t\t\t\t\t\t3. Display All Books\n";
    cout << "\t\t\t\t\t\t\t\t4. Log Out\n";
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "\t\t\t\t\t\t\t\tEnter your choice: ";
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
    	setColor(12);
        cout << "\t\t\t\t\t\t\t\tInvalid Option! Please enter a valid option.";
        getch();
            // Clear error flags and ignore invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto adminmenu;
    }
    return 0;
}

int userMenu() {
    int choice;
usermenu:
    system("cls");
    fflush(stdin);
    setColor(7);
    cout << "\n\t\t\t\t\t\t\t\tUser Menu\n";
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "\t\t\t\t\t\t\t\t1. Search Book\n";
    cout << "\t\t\t\t\t\t\t\t2. Display All Books\n";
    cout << "\t\t\t\t\t\t\t\t3. Borrow Book\n";
    cout << "\t\t\t\t\t\t\t\t4. Return Book\n";
    cout << "\t\t\t\t\t\t\t\t5. Log Out\n";
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "\t\t\t\t\t\t\t\tEnter your choice: ";
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
        setColor(10);
        cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout << "\t\t\t\t\t\t\t\tYou have been logged out\n";
        cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        getch();
        return 1;
    default:
    	setColor(12);
        cout << endl << "\t\t\t\t\t\t\t\tInvalid Option! Please enter a valid option.";
        setColor(7);
        cout << endl << "\t\t\t\t\t\t\t\tPress any key to continue";
        getch();
            // Clear error flags and ignore invalid input
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto usermenu;
    }
    return 0;
}


void addBook() {
    book newBook;
    addbook:
    system("cls");
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "\t\t\t\t\t\t\t\tEnter Book ID: ";
    string idInput;
    getline(cin, idInput); // Read the entire line as a string

    // Check if the input is a valid integer
    istringstream iss(idInput);
    int parsedId;
    if (!(iss >> parsedId) || !iss.eof()) {
        cout << "\t\t\t\t\t\t\t\tError: Book ID must be a number. Press any key to try again.\n";
        getch();
        goto addbook;
    }
    newBook.id = parsedId;

    if (!isIDUnique(newBook.id)) {
        cout << "\t\t\t\t\t\t\t\tError: Book ID is not unique! Try again.\n";
        getch();
        goto addbook;
    }

    cout << "\t\t\t\t\t\t\t\tEnter Book Title: ";
    cin.getline(newBook.title, 100);
    cout << "\t\t\t\t\t\t\t\tEnter Book Author: ";
    cin.getline(newBook.author, 100);
    newBook.isAvailable = true;

    ofstream outFile("books.txt", ios::app | ios::binary);
    if (!outFile) {
        cout << "\t\t\t\t\t\t\t\tError: Unable to open file for writing!\n";
        return;
    }
    outFile.write(reinterpret_cast<char*>(&newBook), sizeof(book));
    outFile.close();
    setColor(10);
    cout << "\t\t\t\t\t\t\t\tBook added successfully!\n";
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    setColor(7);
	getch();
}
void searchBook() {
    int searchId;
    system("cls");
    setColor(7);
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "\t\t\t\t\t\t\t\tEnter Book ID to search: ";
    cin >> searchId;

    ifstream inFile("books.txt", ios::binary);
    if (!inFile) {
    	setColor(12);
        cout << "\t\t\t\t\t\t\t\tError: Unable to open file for reading!\n";
        getch();
    }

    book tempBook;
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&tempBook), sizeof(book))) {
        if (tempBook.id == searchId) {
        	setColor(1);
        	cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            cout <<endl<<endl<<endl<<"\t\t\t\t\t\t\t\tBook ID: " << tempBook.id << endl;
            cout << "\t\t\t\t\t\t\t\tBook Title: " << tempBook.title << endl;
            cout << "\t\t\t\t\t\t\t\tBook Author: " << tempBook.author << endl;
            cout << "\t\t\t\t\t\t\t\tAvailability: " << (tempBook.isAvailable ? "Available" : "Not Available") << endl;
            cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) {
    	setColor(12);
        cout << "\t\t\t\t\t\t\t\tBook not found!";
    }
    getch();
}

void displayAllBooks() {
	system("cls");
    ifstream inFile("books.txt", ios::binary);
    if (!inFile) {
    	setColor(12);
        cout << "\t\t\t\t\t\t\t\tError: Unable to open file for reading!\n";
        getch();
        return;
    }

    book tempBook;
    setColor(1);
    cout<<"\n-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    while (inFile.read(reinterpret_cast<char*>(&tempBook), sizeof(book))) {
        cout << "\t\t\t\t\t\t\t\tBook ID: " << tempBook.id << endl;
        cout << "\t\t\t\t\t\t\t\tBook Title: " << tempBook.title << endl;
        cout << "\t\t\t\t\t\t\t\tBook Author: " << tempBook.author << endl;
        cout << "\t\t\t\t\t\t\t\tAvailability: " << (tempBook.isAvailable ? "Available" : "Not Available") << endl;
        cout << "\t\t\t\t\t\t\t\t-----------------------------" << endl;
    }
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    inFile.close();
    getch();
}

void borrowBook() {
    int borrowId;
    setColor(7);
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "\t\t\t\t\t\t\t\tEnter Book ID to borrow: ";
    cin >> borrowId;

    fstream file("books.txt", ios::in | ios::out | ios::binary);
    if (!file) {
    	setColor(12);
        cout << "\t\t\t\t\t\t\t\tError: Unable to open file!\n";
        getch();
        setColor(7);
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
            setColor(10);
            cout << "\t\t\t\t\t\t\t\tBook borrowed successfully!";
            getch();
            found = true;
            break;
        }
    }
    file.close();
    if (!found) {
    	setColor(12);
        cout << "\t\t\t\t\t\t\t\tBook not available for borrowing!";
    }
    getch();
}

void returnBook() {
    int returnId;
    setColor(7);
    cout<<"-----------------------------------------------------------------------------------------------------------------------------------------------"<<endl;
    cout << "\t\t\t\t\t\t\t\tEnter Book ID to return: ";
    cin >> returnId;

    fstream file("books.txt", ios::in | ios::out | ios::binary);
    if (!file) {
    	setColor(12);
        cout << "\t\t\t\t\t\t\t\tError: Unable to open file!\n";
        getch();
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
            setColor(10);
			cout << "\t\t\t\t\t\t\t\tBook returned successfully!";
			getch();
            found = true;
            break;
        }
    }
    file.close();
    if (!found) {
    	setColor(12);
        cout << "\t\t\t\t\t\t\t\tBook not found or already returned!";
    }
    getch();
}
