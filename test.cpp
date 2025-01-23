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

bool valid_password(const string& pass_wrd)
{
	regex pass(R"(^[a-zA-Z0-9]{3}[^a-zA-Z0-9]{1}\d{2}$)");
	return regex_match(pass_wrd,pass);
}
bool valid_email(const string& eml)
{
	regex email(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
	return regex_match(eml,email);
}

class sign_up{
	protected:
		string full_name; // full_name of sign_up person 
		char user_name[100]; //user_name of sign_up person
		char password[100]; //user password 
		string email_address;//email address of sign_up person 
		string s_question;
		int earn;
	public:
		sign_up()
		 {
		 	full_name="";
			strcpy(user_name,"");
			strcpy(password,""); 
			email_address="";
			s_question="";
		 }
		sign_up(string f_name, const char* u_name, const char* pass, string eml_add ,string s_quest)
		 {
		    full_name=f_name;
			strcpy(user_name, u_name);
            strcpy(password, pass);
			email_address=eml_add;
			s_question=s_quest;
		 }
		 void saveToFile()
		 {
		 	fstream signup_file;
			signup_file.open("account.txt",ios::out|ios::app);
			if(signup_file.is_open())
			{
				signup_file<<"\t\t\t\t\tInformation of Home_owner"<<endl;
			   	signup_file<<full_name<<endl;
			 	signup_file<<user_name<<endl;
			 	signup_file<<password<<endl;
			 	signup_file<<email_address<<endl;
			 	signup_file<<s_question<<endl<<endl;
			 	system("cls");
			 	cout<<"\t\t\t\t\tSIGNUP sucessflly!!!";
			 	Sleep(2000);
			 	system("cls");
				signup_file.close();
			}
			else
			{
				cout<<"\t\t\t\t\tfile not created !!";
			}	
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
                string username, password;
                cout << "Enter Admin Username: ";
                cin >> username;
                fflush(stdin);
                cout << "Enter Admin Password: ";
                cin >> password;
                fflush(stdin);

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
            } else if (loginOption == 2) {
                string username, password;
                system("cls");
                cout << "Enter Customer Username: ";
                cin >> username;
                fflush(stdin);
                cout << "Enter Customer Password: ";
                cin >> password;
                fflush(stdin);

                if (username == USER_USERNAME && password == USER_PASSWORD) {
                    system("cls");
					cout << "Welcome, User!\n";
					cout<<endl<<"press any key to continue: ";
            		getch();
                    userMenu(books);
                } else {
                    cout << "Invalid Customer credentials.\n";
                    cout<<endl<<"press any key to continue: ";
            getch();
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
				signup:
				system("cls");
                // Add logic for creating a customer account
                string fullName,email,recover_qn; 
	 			char username[100],password[100];
				cout<<"\n\n\t\t\t\t\tCreate account"<<endl;
				cin.ignore();
				cout<<"\t\t\t\t\tFull name:";
				getline(cin,fullName);
				cout<<"\t\t\t\t\tUser name:";
				cin.getline(username,100);
        	    getch();
        	    while(true)
        	    {
        	    	cout<<"\t\t\t\t\tPassword:";
		 	    	cin.getline(password,100);
		 	    	if(valid_password(password))
		 	        {
		 	         	break;
					}
					else
					{
					 	cout<<"\t\t\t\t\tpassword format not match!!\n";
					 	getch();
					 	goto signup;
					}
				}
				
				while(true)
				{
					cout<<"\t\t\t\t\tEmail address:";
		 	    	getline(cin,email);
		 	    	if(valid_email(email))
		 	     	{
		 	     		break;
				  	}
					else
					{
				 		cout<<"\t\t\t\t\tInvalid email address!!\n";
					}	
		    	}
		    	cout<<"\t\t\t\t\tWhat is your favourite game?";
		 		getline(cin,recover_qn);
		 		sign_up obj_1(fullName, username, password, email,recover_qn);
		 		obj_1.saveToFile();
		 		
				goto mainmenu;
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

