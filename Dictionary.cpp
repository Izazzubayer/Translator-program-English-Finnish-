/*
 * Dictionary.cpp
 * 
 * Description: Dictonary (Wrapper) data collection ADT class using BST (ADT class) as 
 *              CDT for implementation.
 * Requirements:Underlying data structure is always a BST; 
 *              Dictionary public interface unchanged and calls BST public methods;
 *              Does not produce degenerate tree under best conditions (unsorted data file; not an AVL);
 *              I/O-free implementation for maximal portability;
 *              Link-based underlying BST implementation;
 *              Duplicated elements not allowed.
 *              
 * Author: Izaz Zubayer (301386899) & Zoe Stanley (301427509)
 * Date of last modification: March. 2024
 */

#include "Dictionary.h"
#include <iostream>


// Constructor and destructor:
    
// Default constructor
Dictionary::Dictionary() {
    keyValuePairs = new BST();
}                           

// Destructor
Dictionary::~Dictionary() {
    delete keyValuePairs;
}
   
// Dictionary operations
      
// Description: Returns the number of elements currently stored in the Dictionary.
// Postcondition: This method does not change the Dictionary.
unsigned int Dictionary::getElementCount() const {
    return keyValuePairs->getElementCount(); // utilize BST method
}
    
// Description: Puts "newElement" (association of key-value) into the Dictionary.
// Precondition: "newElement" does not already exist in the Dictionary.
//               This is to say: no duplication allowed.
// Exception: Throws the exception "UnableToInsertException" 
//            when newElement cannot be inserted in the Dictionary.  
// Exception: Throws the exception "ElementAlreadyExistsException" 
//            if "newElement" already exists in the Dictionary.  
void Dictionary::put(WordPair & newElement) {

    // Note: exceptions will be thrown by delegation to BST methods
    keyValuePairs->insert(newElement);
}
 
// Description: Gets "newElement" (i.e., the associated value of a given key) 
//              from the Dictionary.
// Precondition: Dictionary is not empty.
// Exception: Throws the exception ElementDoesNotExistException
//            if the key is not found in the Dictionary.
// Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
// Postcondition: This method does not change the Dictionary.
WordPair & Dictionary::get(WordPair & targetElement) const {
    return keyValuePairs->retrieve(targetElement);
}

// Description: Prints the content of the Dictionary.
// Precondition: Dictionary is not empty.
// Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
// Postcondition: This method does not change the Dictionary.
void Dictionary::displayContent(void visit(WordPair &)) const {
    if (getElementCount() == 0) {
        throw EmptyDataCollectionException("Dictionary is empty.");
    } else {
            keyValuePairs->traverseInOrder(visit);
        }
    }
   
 // end Dictionary