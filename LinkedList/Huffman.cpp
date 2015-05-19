#include<iostream>
#include<fstream>
#include<string>
#include "HuffEncoder.cpp"
using namespace std;

void main_menu(char &option);
void dispatcher(char &option, bool &quit);
void encoder();
void decoder();
void show_file();
void delete_file();

void main_menu(char &option)
{
    system("clear");
    //Display menu
    cout << "----MAIN MENU----\n\n";
    cout << "1. Encode File\n";
    cout << "2. Decode File\n";
    cout << "3. Show File Contents\n";
    cout << "4. Delete File\n";
    cout << "5. Quit\n\n";
    cout << "Enter a command: ";

    //Read in command and direct it
    cin >> option;
    system("clear");
}

void dispatcher(char &option, bool &quit)
{
    if(option == '1') {
        encoder();
    } else if(option == '2') {
        decoder();
    } else if(option == '3') {
        show_file();
    } else if(option == '4') {
        delete_file();
    } else if(option == '5') {
        cout << "Exiting...\n";
        quit = 1; 
    } else {
        cout << "Please enter a valid option\n\n\n";
    }

    if(option != '5') {
        system( "read -n 1 -s -p \"Press any key to continue...\"");
    }
}

void encoder() {
    HuffEncoder he;
    string infile;
    string outfile;
    char shouldContinue;

    cout << "Enter file to be encoded: ";
    cin >> infile;
    cout << "\nEnter destination file: ";
    cin >> outfile;

    cout << "\n\nFile '" << infile << "' will be encoded and stored as '"
         << outfile << "'. Continue? (Y or N): ";
    cin >> shouldContinue;

    while(shouldContinue != 'Y' && shouldContinue != 'y'
          && shouldContinue != 'N' && shouldContinue != 'n') {
        cout << "\n\nValid responses are Y or N. Continue? ";
        cin >> shouldContinue;
    }
    if(shouldContinue == 'Y' || shouldContinue == 'y') {
        bool success = he.encode(infile, outfile);
        if(success)
            cout << "\nEncoding complete\n\n\n";
        else
            cout << "\nEncoding failed\n\n\n"; 
    } else if(shouldContinue == 'N' || shouldContinue == 'n')
        cout << "Aborting...\n\n\n";

}

void decoder() {
    HuffEncoder he;
    string infile;
    string outfile;
    char shouldContinue;

    cout << "Enter file to be decoded: ";
    cin >> infile;
    cout << "\nEnter destination file: ";
    cin >> outfile;

    cout << "\n\nFile '" << infile << "' will be decoded and stored as '"
         << outfile << "'. Continue? (Y or N): ";
    cin >> shouldContinue;

    while(shouldContinue != 'Y' && shouldContinue != 'y'
          && shouldContinue != 'N' && shouldContinue != 'n') {
        cout << "\n\nValid responses are Y or N. Continue? ";
        cin >> shouldContinue;
    }
    if(shouldContinue == 'Y' || shouldContinue == 'y') {
        bool success = he.decode(infile, outfile);
        if(success)
            cout << "\nDecoding complete\n\n\n";
        else
            cout << "\nDecoding failed\n\n\n";
    } else if(shouldContinue == 'N' || shouldContinue == 'n')
        cout << "Aborting...\n\n\n";

}

void show_file()
{
    string filename;
    ifstream infile;
    char ch;

    cout << "Enter filename to show: ";
    cin >> filename;

    infile.open(filename.c_str(), ios::in);
    if(!infile) {
        cout << "\n\nCould not open file '" << filename << "'.";
    } else {
        cout << "\n\nContents of '" << filename << "':\n";
        while(infile) {
            infile.get(ch);
            cout << ch;
        }
    }
}

void delete_file()
{
    string filename;
    char shouldContinue;

    cout << "Enter filename to delete: ";
    cin >> filename;

    cout << "\n\nWARNING: Once file is deleted, you will NOT be able to retrieve it."
         << " Do you wish to continue? (Y or N) ";
    cin >> shouldContinue;

    while(shouldContinue != 'Y' && shouldContinue != 'y'
          && shouldContinue != 'N' && shouldContinue != 'n') {
        cout << "\n\nValid responses are Y or N. Continue? ";
        cin >> shouldContinue;
    }
    if(shouldContinue == 'Y' || shouldContinue == 'y') {
        cout << "\n\nRemoving file...";
        remove(filename.c_str());
    } else {
        cout << "Aborting...\n\n\n";
    }
}

    

int main()
{
    HuffEncoder he, he2;
    bool quit = 0;
    char option;

    //Display menu
    while(quit == 0) {
        main_menu(option);
        dispatcher(option, quit);
    }
    return 0;
}
