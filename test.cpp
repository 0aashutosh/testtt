#include <iostream>
#include <vector>
#include <string>
#include<windows.h>
#include<conio.h>
#include <fstream>
#include<regex> //for pattern matching
#include <cstdlib> // For rand and srand
#include<sstream>
#include<algorithm>  //for transform
#include<cctype>    //for lowercase
#include<iomanip>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isAvailable;
};

// Admin and User credentials
const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";
const string USER_USERNAME = "user";
const string USER_PASSWORD = "user123";

// Helper functions for validation
bool isValidPassword(const string& password) {
    regex pattern(R"(^[a-zA-Z0-9]{3}[^a-zA-Z0-9]{1}\d{2}$)");
    return regex_match(password, pattern);
}

bool isValidEmail(const string& email) {
    regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, pattern);
}

// SignUp Class
class SignUp {
private:
    string fullName;
    string username;
    string password;
    string email;
    string securityQuestion;

public:
    SignUp() = default;

    void collectUserInfo() {
        cout << "\n--- Sign Up ---\n";
        cin.ignore();
        cout << "Enter full name: ";
        getline(cin, fullName);
        cout << "Enter username: ";
        getline(cin, username);

        while (true) {
            cout << "Enter password (3 alphanumeric + 1 special character + 2 digits): ";
            getline(cin, password);
            if (isValidPassword(password)) break;
            cout << "Invalid password format. Try again.\n";
        }

        while (true) {
            cout << "Enter email: ";
            getline(cin, email);
            if (isValidEmail(email)) break;
            cout << "Invalid email format. Try again.\n";
        }

        cout << "What is your favorite game? (for account recovery): ";
        getline(cin, securityQuestion);
    }

    void saveToFile() const {
        ofstream file("accounts.txt", ios::app);
        if (file.is_open()) {
            file << "Full Name: " << fullName << "\n"
                 << "Username: " << username << "\n"
                 << "Password: " << password << "\n"
                 << "Email: " << email << "\n"
                 << "Security Question: " << securityQuestion << "\n\n";
            file.close();
            cout << "Account created successfully!\n";
        } else {
            cout << "Error: Unable to open file for saving.\n";
        }
    }
};

// Login Class
class Login {
private:
    string username;
    string password;

public:
    Login(string uname, string pass) : username(uname), password(pass) {}

    bool authenticate() {
        ifstream file("accounts.txt");
        if (!file.is_open()) {
            cout << "Error: Unable to open file.\n";
            return false;
        }

        string line;
        string storedUsername, storedPassword;
        while (getline(file, line)) {
            if (line.find("Username:") != string::npos) {
                storedUsername = line.substr(line.find(":") + 2);
            } else if (line.find("Password:") != string::npos) {
                storedPassword = line.substr(line.find(":") + 2);
                if (storedUsername == username && storedPassword == password) {
                    file.close();
                    return true;
                }
            }
        }
        file.close();
        return false;
    }
};


// Functions for book management



void addBook(vector<Book>& books) {
    Book newBook;
    system("cls");

    cout << "Enter Book ID: ";
    while (!(cin >> newBook.id)) { // Validate input for Book ID
        cout << "Invalid input. Please enter a valid integer for Book ID: ";
        cin.clear(); // Clear the error flag
        cin.ignore(1000, '\n'); // Ignore invalid input
    }
    cin.ignore(); // Clear the newline character from input buffer

    cout << "Enter Book Title: ";
    getline(cin, newBook.title);

    cout << "Enter Book Author: ";
    getline(cin, newBook.author);

    newBook.isAvailable = true;
    books.push_back(newBook);

    // Append book details to the file
    ofstream outFile("books.txt", ios::app);
    if (outFile.is_open()) {
        outFile << newBook.id << "\n"
                << newBook.title << "\n"
                << newBook.author << "\n"
                << newBook.isAvailable << "\n"; // true is stored as 1
        outFile.close();
        cout << "Book added successfully and saved to file!\n";
        
    } else {
        cout << "Error: Unable to open file for writing.\n";
    }

    system("cls");
}



void searchBook(const vector<Book>& books) {
    string keyword;
    system("cls");
    cout << "Enter title or author to search: ";
//    cin.ignore();
    getline(cin, keyword);
	fflush(stdin);
    bool found = false;

    // Search directly in the file
    ifstream inFile("books.txt");
    if (inFile.is_open()) {
        while (!inFile.eof()) {
            Book book;
            string isAvailableStr;
            inFile >> book.id; 
            inFile.ignore();
            getline(inFile, book.title);
            getline(inFile, book.author);
            getline(inFile, isAvailableStr);
            if (!inFile.fail()) {
                book.isAvailable = (isAvailableStr == "1");
                if (book.title.find(keyword) != string::npos || book.author.find(keyword) != string::npos) {
                    cout << "ID: " << book.id << ", Title: " << book.title
                         << ", Author: " << book.author
                         << ", Available: " << (book.isAvailable ? "Yes" : "No") << endl;
                    found = true;
                }
            }
        }
        inFile.close();
    } else {
        cout << "Error: Unable to open file for reading.\n";
    }

    if (!found) {
        cout << "No books found.\n";
    }
    cout << "Press any key to continue: ";
    getch();
}

void displayBooks() {
    ifstream inFile("books.txt");
    system("cls");
    
    if (inFile.is_open()) {
        cout << "\nAvailable Books:\n";
        int id;
        string title, author, isAvailableStr;

        while (inFile >> id) { // Read book ID
            inFile.ignore();   // Ignore the newline character
            getline(inFile, title);       // Read title
            getline(inFile, author);      // Read author
            getline(inFile, isAvailableStr); // Read availability

            // Display book details
            cout << "ID: " << id 
                 << ", Title: " << title 
                 << ", Author: " << author 
                 << ", Available: " << (isAvailableStr == "1" ? "Yes" : "No") 
                 << endl;
        }
        inFile.close();
    } else {
        cout << "Error: Unable to open file for reading.\n";
    }

    cout << "Press any key to continue: ";
    getch();
}


void borrowBook(vector<Book>& books) {
    int id;
    system("cls");
    cout << "Enter Book ID to borrow: ";
    cin >> id;
    fflush(stdin);
    fstream file("books.txt", ios::in | ios::out);
    if (file.is_open()) {
        string line;
        streampos prevPos;
        while (!file.eof()) {
            prevPos = file.tellg();
            Book book;
            string isAvailableStr;
            file >> book.id;
            file.ignore();
            getline(file, book.title);
            getline(file, book.author);
            getline(file, isAvailableStr);
            if (book.id == id) {
                if (isAvailableStr == "1") {
                    book.isAvailable = false;
                    file.seekp(prevPos);
                    file << book.id << "\n"
                         << book.title << "\n"
                         << book.author << "\n0\n"; // Update availability to 0
                    cout << "You borrowed \"" << book.title << "\" successfully.\n";
                } else {
                    cout << "Book is already borrowed.\n";
                }
                file.close();
                cout << "Press any key to continue: ";
                getch();
                return;
            }
        }
        file.close();
    }
    cout << "Book ID not found.\n";
    cout << "Press any key to continue: ";
    getch();
}

void returnBook(vector<Book>& books) {
    int id;
    system("cls");
    cout << "Enter Book ID to return: ";
    cin >> id;
    fflush(stdin);
    fstream file("books.txt", ios::in | ios::out);
    if (file.is_open()) {
        string line;
        streampos prevPos;
        while (!file.eof()) {
            prevPos = file.tellg();
            Book book;
            string isAvailableStr;
            file >> book.id;
            file.ignore();
            getline(file, book.title);
            getline(file, book.author);
            getline(file, isAvailableStr);
            if (book.id == id) {
                if (isAvailableStr == "0") {
                    book.isAvailable = true;
                    file.seekp(prevPos);
                    file << book.id << "\n"
                         << book.title << "\n"
                         << book.author << "\n1\n"; // Update availability to 1
                    cout << "You returned \"" << book.title << "\" successfully.\n";
                } else {
                    cout << "Book was not borrowed.\n";
                }
                file.close();
                cout << "Press any key to continue: ";
                getch();
                return;
            }
        }
        file.close();
    }
    cout << "Book ID not found.\n";
    cout << "Press any key to continue: ";
    getch();
}
// Menu Functions
void adminMenu(vector<Book>& books) {
    int choice;
    do {
        system("cls");
        cout << "\nAdmin Menu\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Display All Books\n";
        cout << "4. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        fflush(stdin);
        switch(choice)
        {
        	case 1:
        		addBook(books);
				break;
			
			case 2:
				searchBook(books); 
				break;
        		
        	case 3:
        		displayBooks();
        		break;
        		
        	case 4:
        		return;
        	
        	  default: 
                    cout << "Invalid choice. Try again.\n"; 
                    getch(); 
                    break;
        	
		}
        
        
    }while (choice != 4);
}


void userMenu(vector<Book>& books) {
    int choice;
    do {
    	system("cls");
        cout << "\nUser Menu\n";
        cout << "1. Search Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Borrow Book\n";
        cout << "4. Return Book\n";
        cout << "5. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
		fflush(stdin);
        switch (choice) {
            case 1: searchBook(books); break;
            case 2: displayBooks(); break;
            case 3: borrowBook(books); break;
            case 4: returnBook(books); break;
            case 5: return;
            default: cout << "Invalid choice. Try again.\n";
            getch(); break;
        }
    } while (choice != 5);
}

void mainMenu(vector<Book>& books) {
    int option;
    do {
    	mainmenu:
    	system("cls");
        cout << "\nMain Menu\n";
        cout << "1. Login\n";
        cout << "2. Create Account\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 1) {
            int loginOption;
            system("cls");
            cout << "\nLogin Menu\n";
            cout << "1. Admin\n";
            cout << "2. Customer\n";
            cout << "3. Return to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> loginOption;
			fflush(stdin);
            if (loginOption == 1) {
            	system("cls");
            	cout<<"============admin login============"<<endl<<endl;
                string username, password;
                cout << "Enter Admin Username: ";
                getline(cin, username);
                fflush(stdin);
                cout << "Enter Admin Password: ";
                getline(cin, password);
				 if (username == ADMIN_USERNAME && password == ADMIN_PASSWORD) {
                	system("cls");
                    cout << "Welcome, Admin!\n";
                    cout<<endl<<"press any key to continue: ";
            		getch();
                    adminMenu(books);
                } else {
                	
                    cout << "Invalid Admin credentials.\n";
                    cout<<endl<<"press any key to continue: ";
					getch();
                }            
            } 
			else if (loginOption == 2) 
			{
                string username, password;
                system("cls");
                cout << "Enter Customer Username: ";
                getline(cin, username);
                
                fflush(stdin);
                cout << "Enter Customer Password: ";
                getline(cin, password);
                fflush(stdin);
				Login userLogin(username, password);
				if (userLogin.authenticate()) {
                	cout << "Login successful!\n";
                	getch();
                	userMenu(books);
            	} 
				else {
                	cout << "Invalid username or password. Try again.\n";
            	}   
            }
        } 
		else if (option == 2) {
            int createOption;
            system("cls");
            cout << "\nCreate Account Menu\n";
            cout << "1. Customer\n";
            cout << "2. Return to Main Menu\n";
            cout << "Enter your choice: ";
            cin >> createOption;
            fflush(stdin);
            
            if (createOption == 1)
			{
				SignUp newUser;
            	newUser.collectUserInfo();
            	newUser.saveToFile();
            }
            
            
        }
		
		 
		else if (option == 3) {
            cout << "Exiting the program. Goodbye!\n";
            cout<<endl<<"press any key to continue: ";
            getch();
        } else {
            cout << "Invalid option. Try again.\n";
        }
    } while (option != 3);
}

int main() {
    vector<Book> books;
    mainMenu(books);
    return 0;
}

