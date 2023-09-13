/// TODO: Update your header comment

// You cannot use any libraries beyond the ones we have given below.
// You must use output streams, file streams, vectors, and strings.
// You are not allowed to use any other containers or objects.
// You may not use structs, pointers, or dynamic memory allocations.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

using namespace std;

// Function prototypes for all the glorious function decomposition
void printMenu();
void displayLibrary(vector<string> &bookTitles, vector<string> &ISBN, vector<int> &status);
bool loadLibraryFromFile(vector<string> &bookTitles, vector<string> &ISBN, vector<int> &checkoutStatus);
string checkStatus(int status);
bool isValidISBN(const string &isbn);
void outputLibrary(vector<string> &bookTitles, vector<string> &ISBN, vector<int> &checkoutStatus);
void printCheckout(vector<int> &checkoutStatus);
void removeFromLibrary(vector<string> &bookTitles,vector<string> &ISBN, vector<int> &status);
void removeByName(vector<string> &bookTitles,vector<string> &ISBN, vector<int> &status);
void removeByISBN(vector<string> &bookTitles,vector<string> &ISBN, vector<int> &status);
void searchLibrary(vector<string> &bookTitles, vector<string> &ISBNs, vector<int> &checkoutStatus);
void searchByName(vector<string> &bookTitles, vector<string> &ISBNs, vector<int> &checkoutStatus);
void searchByNum(vector<string> &bookTitles, vector<string> &ISBNs, vector<int> &checkoutStatus);
void listInvalid(vector<string> &bookTitles, vector<string> &ISBNs, vector<int> &checkoutStatus);

vector<string> bookTitles;
vector<string> ISBNs;
vector<int> checkoutStatus;

int main()
{
    string command;

    // TODO: define your variables

    cout << "Welcome to the Library Management System" << endl;
    cout << "----------------------------------------" << endl;
    cout << endl;

    do 
    {

        
        // Output the menu and acquire a user selection
        printMenu();
        cout << endl << "Enter a command (case does not matter): ";

        // We use getline for all user input to avoid needing to handle
        // input buffer issues relating to using both >> and getline
        getline(cin, command);
        cout << endl;

        // TODO: Execute non-exit commands

        if (command == "x" || command == "X")
        {
            break;
        }

        if (command == "a" || command == "A")
        {
            string title, ISBN;

            cout << "What is the book title?" << endl;
            getline(cin, title);

            if (title.find(',') != string::npos)
            {
                cout << "the book title cannot contain commas." << endl;
            }
            else
            {
                cout << "What is the 13-digit ISBN (with hyphens)?" << endl;
                getline(cin, ISBN);

                bookTitles.push_back(title);
                ISBNs.push_back(ISBN);
                checkoutStatus.push_back(0);

                cout << "The Following Entry Was Added" << endl;
                cout << "-----------------------------" << endl;
                cout << title << " --- " << ISBN << " --- In Library" << endl;
            }
        }

        else if (command == "d" || command == "D")
        {
            displayLibrary(bookTitles, ISBNs, checkoutStatus);
        }

        else if (command == "c" || command == "C")
        {
            bookTitles.clear();
            ISBNs.clear();
            checkoutStatus.clear();
            cout << "Your library is now empty." << endl;
        }

        else if (command == "l" || command == "L")
        {
            loadLibraryFromFile(bookTitles, ISBNs, checkoutStatus);
           
        }

        else if (command == "o" || command == "O")
        {
            outputLibrary(bookTitles, ISBNs, checkoutStatus);
        }

        else if (command == "p" || command == "P")
        {
            printCheckout(checkoutStatus);
        }

        else if (command == "r" || command == "R") 
        {
            removeFromLibrary(bookTitles, ISBNs, checkoutStatus);
        }

        else if (command == "s" || command == "S") 
        {
            searchLibrary(bookTitles, ISBNs, checkoutStatus);
        }

        else if (command == "i" || command == "I") 
        {
            listInvalid(bookTitles, ISBNs, checkoutStatus);
        }

        cout << endl;
        
    } while (!(command == "x" || command == "X"));

    return 0;
}

// Function definitions for all the glorious function decomposition
// Tip: alphabetical order makes it easy to find things if you have
//      a lot of function decomposition.

/// @brief print out the main menu of the management system
void printMenu()
{
    cout << "Library Management Menu" << endl;
    cout << "-----------------------" << endl;
    cout << "A - Add Item To Library" << endl;
    cout << "C - Clear The Library Of All Entries" << endl;
    cout << "D - Display Library Entries" << endl;    
    cout << "I - List Invalid Library Entries" << endl;
    cout << "L - Load Library From File" << endl;    
    cout << "O - Output Library To File" << endl;
    cout << "P - Print Out Checkout Stats" << endl;
    cout << "R - Remove A Library Entry" << endl;      
    cout << "S - Search For A Library Entry" << endl;    
    cout << "X - Exit Program" << endl;
}

//function to display library by checking bookTitles and couting with a for loop. also assigned status to books.
void displayLibrary(vector<string> &bookTitles, vector<string> &ISBN, vector<int> &status)
{
    cout << "Your Current Library" << endl;
    cout << "--------------------" << endl;

    if (bookTitles.empty())
    {
        cout << "The library has no books." << endl;
    }
    else
    {
        for (size_t i = 0; i < bookTitles.size(); ++i)
        {
            cout << bookTitles[i] << " --- " << ISBN[i] << " --- ";
            if (status[i] == 0)
            {
                cout << "In Library";
            }
            else if (status[i] == 1)
            {
                cout << "Checked Out";
            }
            else if (status[i] == 2)
            {
                cout << "On Loan";
            }
            else if (status[i] == 3)
            {
                cout << "Unknown State";
            }
            else
            {
                cout << "Invalid State";
            }
            cout << endl;
        }
    }
}


//function to read lines from files by parsing the contents as vectors
bool loadLibraryFromFile(vector<string>& bookTitles, vector<string>& ISBNs, vector<int>& checkoutStatus)
{
    string filename;
    cout << "What database to read from? ";
    getline(cin, filename);
    cout << endl;

    ifstream datafile(filename);

    if (!datafile.is_open())
    {
        cout <<"Could not find the database file.";
        return false;
    }

    string line;
    int count = 0;

    while (getline(datafile, line))
    {

        size_t pos = line.find(',');

        if (pos == string::npos)
        {
            bookTitles.push_back(line);
            ISBNs.push_back("000-0-00-000000-0");
            checkoutStatus.push_back(0);
        }
        else
        {
            string title = line.substr(0, pos);
            string remaining = line.substr(pos + 2);

            if (remaining.empty())
            {
                bookTitles.push_back(title);
                ISBNs.push_back("000-0-00-000000-0");
                checkoutStatus.push_back(0);
            }
            else
            {
                pos = remaining.find(',');
                if (pos == string::npos)
                {
                    bookTitles.push_back(title);
                    ISBNs.push_back(remaining);
                    checkoutStatus.push_back(0);
                }
                else
                {
                    bookTitles.push_back(title);
                    ISBNs.push_back(remaining.substr(0, pos));
                    checkoutStatus.push_back(stoi(remaining.substr(pos + 1)));
                }
            }
        }

        count++;
    }

    datafile.close();
    
    cout << "Read in " << count << " lines from the file."<<endl;
    return true;
}

//function to assign status to books
string checkStatus(int status)
{
    if (status == 0)
    {
        return "In Library";
    }
    else if (status == 1)
    {
        return "Checked Out";
    }
    else if (status == 2)
    {
        return "On Loan";
    }
    else if (status == 3)
    {
        return "Unknown State";
    }
    else
    {
        return "Invalid State";
    }
}


//function to make sure ISBN falls under the entry guidelines
bool isValidISBN(const string &isbn)
{
    
    string cleanedISBN = "";
    for (char c : isbn)
    {
        if (c != '-')
        {
            cleanedISBN += c;
        }
    }

    
    if (cleanedISBN.length() != 13)
    {
        return false;
    }

    
    int sum = 0;
    for (int i = 0; i < 12; i++)
    {
        int digit = cleanedISBN[i] - '0';
        sum += (i % 2 == 0) ? digit : 3 * digit;
    }
    int checkDigit = (10 - (sum % 10)) % 10;

    
    return (checkDigit == (cleanedISBN[12] - '0'));
}

//function to output library
void outputLibrary(vector<string> &bookTitles, vector<string> &ISBN, vector<int> &checkoutStatus)
{
    string outputFile;
    ofstream file;
    cout << "Where should database output to?";

    getline(cin,outputFile);
    file.open(outputFile);

    if(!file.is_open())
    {
        cout << "Could not open database file for writing.";
        return;
    }

    for(int i = 0; i < bookTitles.size(); i++)
    {
        file << bookTitles.at(i) << ", " << ISBN.at(i) << ", " << checkoutStatus.at(i) << endl;
    }
    file.close();
}


//function to display the number of books with a certain status
void printCheckout(vector<int> &checkoutStatus)
{
    int inLibrary = 0;
    int checkedOut = 0;
    int loaned = 0;
    int unknown = 0;
    int invalid = 0;

    cout << "Your Current Library's Stats" << endl;
    cout << "----------------------------" << endl;
    cout << "Total Books: " << checkoutStatus.size() << endl;

    for (int i = 0; i < checkoutStatus.size(); i++)
    {
        if(checkoutStatus.at(i) == 0)
        {
            inLibrary++;
        }

        else if(checkoutStatus.at(i) == 1)
        {
            checkedOut++;
        }

        else if(checkoutStatus.at(i) == 2)
        {
            loaned++;
        }

        else if(checkoutStatus.at(i) == 3)
        {
            unknown++;
        }

        else
        {
            invalid++;
        }
    }

    cout << "   In Library: " << inLibrary << endl;
    cout << "   Checked Out: " << checkedOut << endl;
    cout << "   On Loan: " << loaned << endl;
    cout << "   Unknown: " << unknown << endl;
    cout << "   Other: " << invalid << endl;

}


//parent function for removing library entries
void removeFromLibrary(vector<string> &bookTitles, vector<string> &ISBN, vector<int> &status)
{
    int choice;
    string temp;
    cout << "Would you like remove by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin, temp);
    choice = stoi(temp);
    cout << endl;

    if (choice == 1)
    {
        removeByName(bookTitles, ISBN, status);
    }
    else if (choice == 2)
    {
        removeByISBN(bookTitles, ISBN, status);
    }
    else
    {
        cout << "Invalid remove by choice option." << endl;
        return;
    }
}


//child function for removing library entries using a number
void removeByName(vector<string> &bookTitles, vector<string> &ISBN, vector<int> &status)
{
    string bookname;
    int numMatches = 0;
    int lastMatchIndex = -1;

    cout << "Enter the book name: ";
    getline(cin, bookname);
    cout << endl;
    cout << "The Following Entry Was Removed From The Library" << endl;
    cout << "------------------------------------------------" << endl;

    for (int i = 0; i < bookTitles.size(); i++)
    {
        if (bookTitles.at(i) == bookname)
        {
            numMatches++;
            lastMatchIndex = i;
        }
    }

    if (numMatches > 0 && lastMatchIndex != -1)
    {
        cout << bookTitles.at(lastMatchIndex) << " --- " << ISBN.at(lastMatchIndex) << " --- " << checkStatus(status.at(lastMatchIndex)) << endl;
        bookTitles.erase(bookTitles.begin() + lastMatchIndex);
        ISBN.erase(ISBN.begin() + lastMatchIndex);
        status.erase(status.begin() + lastMatchIndex);
    }
    else
    {
        cout << "No matching entry found in the library." << endl;
    }

    return;
}


//child function to remove library entries using an ISBN
void removeByISBN(vector<string> &bookTitles, vector<string> &ISBN, vector<int> &status)
{
    string ISB;
    int numMatches = 0;
    int lastMatchIndex = -1;

    cout << "Enter the book 13-digit ISBN (with dashes): ";
    getline(cin, ISB);
    cout << endl;
    cout << "The Following Entry Was Removed From The Library" << endl;
    cout << "------------------------------------------------" << endl;

    for (int i = 0; i < ISBN.size(); i++)
    {
        if (ISBN.at(i) == ISB)
        {
            numMatches++;
            lastMatchIndex = i;
        }
    }

    if (numMatches > 0 && lastMatchIndex != -1)
    {
        cout << bookTitles.at(lastMatchIndex) << " --- " << ISBN.at(lastMatchIndex) << " --- " << checkStatus(status.at(lastMatchIndex)) << endl;
        bookTitles.erase(bookTitles.begin() + lastMatchIndex);
        ISBN.erase(ISBN.begin() + lastMatchIndex);
        status.erase(status.begin() + lastMatchIndex);
    }
    else
    {
        cout << "No matching entry found in the library." << endl;
    }

    return;
}


//parent function to search the library for a specific entry
void searchLibrary(vector<string> &bookTitles, vector<string> &ISBNs, vector<int> &checkoutStatus)
{
    int choice;
    string temp;
    cout << "Would you like to search by (1) name or (2) ISBN." << endl;
    cout << "Enter the numeric choice: ";
    getline(cin, temp);
    choice = stoi(temp);
    cout << endl;

    if (choice == 1)
    {
        searchByName(bookTitles, ISBNs, checkoutStatus);
    }
    else if (choice == 2)
    {
        searchByNum(bookTitles, ISBNs, checkoutStatus);
    }
    else
    {
        cout << "Invalid search by choice option." << endl;
        return;
    }
}


//child function to search the library using a name
void searchByName(vector<string> &bookTitles, vector<string> &ISBNs, vector<int> &checkoutStatus)
{
    string bookname;
    int numMatches = 0;
    int lastMatchIndex = -1;

    cout << "Enter the book name: ";
    getline(cin, bookname);
    cout << endl;
    cout << "The Following Are Your Search Results" << endl;
    cout << "-------------------------------------" << endl;

    for (int i = 0; i < bookTitles.size(); i++)
    {
        if (bookTitles.at(i) == bookname)
        {
            numMatches++;
            lastMatchIndex = i;
        }
    }

    if (numMatches > 0 && lastMatchIndex != -1)
    {
        cout << bookTitles.at(lastMatchIndex) << " --- " << ISBNs.at(lastMatchIndex) << " --- " << checkStatus(checkoutStatus.at(lastMatchIndex)) << endl;
    }
    else
    {
        cout << "No matching entry found in the library." << endl;
    }
}

//child function to search the library using an ISBN
void searchByNum(vector<string> &bookTitles, vector<string> &ISBNs, vector<int> &checkoutStatus)
{
    string ISB;
    int numMatches = 0;
    int lastMatchIndex = -1;

    cout << "Enter the book 13-digit ISBN (with dashes): ";
    getline(cin, ISB);
    cout << endl;
    cout << "The Following Are Your Search Results" << endl;
    cout << "-------------------------------------" << endl;

    for (int i = 0; i < bookTitles.size(); i++)
    {
        if (ISBNs.at(i) == ISB)
        {
            numMatches++;
            lastMatchIndex = i;
        }
    }

    if (numMatches > 0 && lastMatchIndex != -1)
    {
        cout << bookTitles.at(lastMatchIndex) << " --- " << ISBNs.at(lastMatchIndex) << " --- " << checkStatus(checkoutStatus.at(lastMatchIndex)) << endl;
    }
    else
    {
        cout << "No matching entry found in the library." << endl;
    }
}


//function to output entries that have the "Invalid" status
void listInvalid(vector<string> &bookTitles, vector<string> &ISBNs, vector<int> &status)
{
    bool hasInvalidEntries = false;

    if (bookTitles.empty())
    {
        cout << "The Following Library Entries Have Invalid Data" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "The library has no books." << endl;
        return;
    }

    cout << "The Following Library Entries Have Invalid Data" << endl;
    cout << "-----------------------------------------------" << endl;

    for (int i = 0; i < ISBNs.size(); i++)
    {
        // Check if the ISBN is invalid
        if (!isValidISBN(ISBNs[i]))
        {
            cout << bookTitles[i] << " --- " << ISBNs[i] << " --- " << checkStatus(status[i]) << endl;
            hasInvalidEntries = true;
        }
    }

    if (!hasInvalidEntries)
    {
        cout << "The library has no invalid entries." << endl;
    }
}


