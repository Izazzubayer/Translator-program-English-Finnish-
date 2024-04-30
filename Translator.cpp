/*
 * Translator.cpp
 * 
 * Description: Translator program (English-Finnish) that instantiates Dictionary ADT class 
 *              (wrapper class) using BST ADT class as underlying data structure. 
 *              
 *              Translator.cpp adapted from BSTTestDriver.cpp. 
 * 
 *              Link-based implementation, per BST in Part 1 A3.
 *              Duplicated elements are not allowed.
 *
 * Dictionary Class invariant: Underlying data structure is always a BST; 
 *                  Dictionary public interface unchanged and calls BST public methods;
 *                  Does not produce degenerate tree under good conditions (unsorted data file) - but not AVL.
 *                  I/O-free implementation for maximal portability. 
 * 
 * 
 * Author: Izaz Zubayer (301386899) & Zoe Stanley (301427509)
 * Date of last modification: March. 2024
 */


#include "Dictionary.h"
#include "BST.h"
#include <iostream>
#include <fstream>
using std::ifstream;
using std::nothrow;
using std::cout;
using std::cin;
using std::endl;

// Adapted from (adapted) BSTTestDriver.cpp
int main(int argc, char *argv[]) {

    // Instantiate dictionary
    Dictionary dictionary;

    // Validate the file
    if (argc <= 1) {
        cout << "Missing data filename!" << endl;
        return -1;
    }

    string filename = argv[1];
    ifstream myfile(filename);
    
    // Check file opening success
    if (!myfile.is_open()) {
        cout << "Unable to open file: " << filename << endl;
        return -1;
    }

    // Parse the word pairs from the file and enter into dictionary object
    string aLine, englishW, translatedW;
    string delimiter = ":";
    
    while (getline(myfile, aLine)) {
        size_t pos = aLine.find(delimiter);
        englishW = aLine.substr(0, pos); // identify english word
        translatedW= aLine.substr(pos + delimiter.length()); // identify tranlation
        WordPair aWordPair(englishW, translatedW);

        // Error handling will propagate from the BST methods, but caught here:
        try {

        dictionary.put(aWordPair);

        } catch (const ElementAlreadyExistsException& e) {
            cout << "Duplicate entry found for: " << englishW << ". It will be skipped." << endl;
        } catch (const UnableToInsertException& e) {
            cout << "Insertion failed: " << e.what() << endl;
            return -1; // as this indicates a memory failure, we abort the program.
        }
    }
    myfile.close();

    // Perform a validation test before interactive loop
    if (dictionary.getElementCount() == 0) {
        cout << "The dictionary is empty. Please provide a valid file before proceeding." << endl;
        return -1;
    }

    // Begin the user-interactive loop
    cout << "\nHello! Enter an English word and press Enter to see its Finnish translation (enter 'display' to show all, and CTRL+D to exit): " << endl;
    string inputWord;

    while (cin >> inputWord) {  // evaluates to false if CTRL+D is entered
        if (inputWord == "display") {
            try {
                dictionary.displayContent([](WordPair& wp) { cout << wp; });
            } catch (EmptyDataCollectionException& e) {
                cout << "Cannot display contents: " << e.what() << endl;
            }

            cout << "Enter an English word, or 'display' to see all, or CTRL+D to exit." << endl;
            

        } else {
            // Provide translation, exception handling performed within dictionary's calls to BST except where new message needed 
            WordPair query(inputWord); // Create a WordPair with the input word
            try {
                WordPair& result = dictionary.get(query); // Look for the answer
                cout << result << endl; // Print with overloaded operator<< from WordPair
            } catch (const ElementDoesNotExistException&) {
                cout << "***Not Found!***" << endl; // Word isn't there, handled again here to implement correct message
            } catch (const EmptyDataCollectionException&) {
                cout << "Dictionary is empty." << endl; // Dictionary is empty (should never happen) 
            } 
            // continue loop
            cout << "Enter an English word, or 'display' to see all, or CTRL+D to exit." << endl;

        } 
    } cout << "Thanks for using this English-Finnish Dictionary! Come again soon, and please give us an A." << endl;

    return 0;
}
