//                                              ======Library Management System======

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Book{
    int book_id;
    string book_title, book_author;
    bool is_Issued;

public:
    Book(int id , string title , string author , bool issued = false){
        book_id = id;
        book_title = title;
        book_author = author;
        is_Issued = issued;
    }

    void display(){
        cout<<"ID: "<<book_id <<", Title: "<<book_title<<", Author: "<<book_author<< ", Issued: "<<(is_Issued?"yes":"no")<<endl;
    }

    int getid(){
        return book_id;
    }
    string gettitle(){
        return book_title;
    }
    bool getissued(){
        return is_Issued;
    }
    void setissued(bool a){
        is_Issued = a;
    }

    string stringconvert(){                         
        return to_string(book_id) + "," + book_title + "," + book_author + "," + (is_Issued ? "1" : "0");
    }

    static Book fromstring(string l){                   
        int i;
        string t , a;
        bool is;

        size_t p1 = l.find(',');
        size_t p2 = l.find(',', p1 + 1);            
        size_t p3 = l.find(',', p2 + 1);

        i = stoi(l.substr(0, p1));                    
        t = l.substr(p1 + 1, p2 - p1 - 1);        
        a = l.substr(p2 + 1, p3 - p2 - 1);
        is = l.substr(p3 + 1) == "1";

        return Book(i, t, a, is);          

    }

};

class library{
    vector<Book> b;
public:
    void loadbooks(){
        ifstream f ("C:\\Users\\HP\\Documents\\DSA C++\\LIBRARY.TXT");
        string s;
        while(getline(f,s)){
            b.push_back(Book::fromstring(s));
        } 
        f.close();                    
    }

    
    void savebook(){
        ofstream f ("C:\\Users\\HP\\Documents\\DSA C++\\LIBRARY.TXT");
        for(Book bo : b){
            f<<bo.stringconvert()<<endl;
        }                                                   
        f.close();
                                        
    }           
    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore(); 

        cout << "Enter Title: ";
        getline(cin, title);

        cout << "Enter Author: ";
        getline(cin, author);

        b.push_back(Book(id, title, author));
        cout << "Book Added Successfully!!!" << endl;
    }

    void viewBook() {
        for (Book bo : b) {
            bo.display();
        }                           
    }                           

    void issueBook() {
        int id;
        cout << "Enter ID of the Book to Issue: ";
        cin >> id;

        for (Book &bo : b) {            
            if (bo.getid() == id && !bo.getissued()) {
                bo.setissued(true);
                cout << "Book Issued Successfully!!." << endl;
                
            }       
            cout << "!Book not available or already issued!" << endl;                    
        }                                                                       
        
    }

    void returnBook() {
        int id;
        cout << "Enter ID of the Book to Return: ";
        cin >> id;

        for (Book &bo : b) {
            if (bo.getid() == id && bo.getissued()) {                   
                bo.setissued(false);
                cout << "Book Returned Successfully!!." << endl;
                
            }
            cout << "Invalid Book ID or book not issued." << endl;
        }
        
    }

    void menu() {
        loadbooks();
        int choice;

        do {
            cout << "\n-------- LIBRARY MENU---------\n";
            cout << "1. Add Book\n";
            cout << "2. View Books\n";
            cout << "3. Issue Book\n";
            cout << "4. Return Book\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addBook();
                    break;
                case 2:
                    viewBook();
                    break;
                case 3:
                    issueBook();
                    break;
                case 4:
                    returnBook();
                    break;
                case 5:
                    savebook();
                    cout << "Exiting... Data saved!!!.\n";
                    break;
                default:
                    cout << "Invalid choice. Try again....\n";
            }
        } while (choice != 5);
    }
    
};

int main(){
    library lib;
    lib.menu();
}