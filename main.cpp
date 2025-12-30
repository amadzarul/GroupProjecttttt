#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Book {
    int id = 0;
    string title;
    string author;
    bool isLoaned = false;
};

const int MAX_BOOKS = 100;
Book library[MAX_BOOKS];
int bookCount = 0;

double calculateFee(int days) {
    if (days <= 0)
        return 0.0;
    if (days == 1)
        return 5.0;
    if (days == 2)
        return 6.0;
    if (days == 3)
        return 7.0;
    return 10.0 * days;
}

void addBook() {
    if (bookCount >= MAX_BOOKS) {
        cout << "Library full!" << endl;
        return;
    }
    cout << "Enter Book ID (Number): ";
    cin >> library[bookCount].id;
    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, library[bookCount].title);

    cout << "Enter Author Name: ";
    getline(cin, library[bookCount].author);

    library[bookCount].isLoaned = false;
    bookCount++;
    cout << "Book added successfully!" << endl;
}

void loanBook() {
    int searchID;
    cout << "Enter Book ID to loan: ";
    cin >> searchID;
    cin.ignore();

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == searchID) {
            if (library[i].isLoaned) {
                cout << "Error: Book is already out." << endl;
            }
            else {
                library[i].isLoaned = true;
                cout << "Success! You borrowed " << library[i].title << endl;
            }
            return;
        }
    }
    cout << "Book ID not found." << endl;
}

void searchBook() {
    if (bookCount == 0) {
        cout << "Catalogue is empty." << endl;
        return;
    }
    cout << "Enter title to search for: ";
    string query;
    getline(cin, query);

    bool found = false;
    for (int i = 0; i < bookCount; i++) {
        if (library[i].title.find(query) != string::npos) {
            cout << "Found -> ID: " << library[i].id << " | Title: " << library[i].title << endl;
            found = true;
        }
    }
    if (!found) cout << "No book found with that title." << endl;
}

void returnBook() {
    int searchID, days;
    cout << "Enter Book ID to return: ";
    cin >> searchID;

    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == searchID) {
            if (!library[i].isLoaned) {
                cout << "This book is not currently loaned." << endl;
            }
            else {
                cout << "How many days late is it? ";
                cin >> days;
                double fee = calculateFee(days);
                if (fee > 0) {
                    cout << fixed << setprecision(2);
                    cout << "Overdue Fee: RM" << fee << endl;
                }
                library[i].isLoaned = false;
                cout << "Success! Returned: " << library[i].title << endl;
            }
            cin.ignore();
            return;
        }
    }
    cout << "ID not found." << endl;
    cin.ignore();
}

void displayCatalogue() {
    if (bookCount == 0) {
        cout << "\nCatalogue is empty." << endl;
        return;
    }
    cout << "\n" << left << setw(10) << "ID" << setw(25) << "Title" << setw(20) << "Author" << "Status" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    for (int i = 0; i < bookCount; i++) {
        cout << left << setw(10) << library[i].id
            << setw(25) << library[i].title
            << setw(20) << library[i].author
            << (library[i].isLoaned ? "LOANED" : "AVAILABLE") << endl;
    }
}

int main() {
    int choice = 0;
    while (choice != 6) {
        cout << "\n--- BKCL SYSTEM ---" << endl;
        cout << "1. Add Book\n2. View Catalogue\n3. Loan Book\n4. Return Book\n5. Search Book\n6. Exit" << endl;
        cout << "Choice: ";

        if (!(cin >> choice)) {
            cout << "Please enter a valid number." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        cin.ignore();
        if (choice == 1)
            addBook();
        else if (choice == 2)
            displayCatalogue();
        else if (choice == 3)
            loanBook();
        else if (choice == 4)
            returnBook();
        else if (choice == 5)
            searchBook();
        else if (choice == 6)
            cout << "Goodbye!" << endl;
        else
            cout << "Invalid choice!" << endl;
    }
    return 0;
}