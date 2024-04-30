/*
 * Dictionary.h
 * 
 * Description: Dictonary Wrapper data collection ADT class using BST ADT as CDT for implementation.
 *              Link-based underlying BST implementation.
 *              Duplicated elements not allowed.
 *              
 * Author: Izaz Zubayer (301386899) & Zoe Stanley (301427509)
 * Date of last modification: March. 2024
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "BST.h"


class Dictionary {
   
private:

/* You cannot change the following data member of this class. */
    BST * keyValuePairs = nullptr;                  

/* Feel free to add private methods to this class. */
   
public:

// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one with which we will mark this assignment - 
// will not know about them since, in order to create it, we will have 
// used only the public method prototypes below.

   // Constructor and destructor:
   Dictionary();                             // Default constructor
   ~Dictionary();                            // Destructor 
   
   // Dictionary operations
      
   // Description: Returns the number of elements currently stored in the Dictionary.
   // Postcondition: This method does not change the Dictionary.
   unsigned int getElementCount() const;
    
   // Description: Puts "newElement" (association of key-value) into the Dictionary.
   // Precondition: "newElement" does not already exist in the Dictionary.
   //               This is to say: no duplication allowed.
   // Exception: Throws the exception "UnableToInsertException" 
   //            when newElement cannot be inserted in the Dictionary.  
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the Dictionary.  
   void put(WordPair & newElement);
 
   // Description: Gets "newElement" (i.e., the associated value of a given key) 
   //              from the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception ElementDoesNotExistException
   //            if the key is not found in the Dictionary.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
   // Postcondition: This method does not change the Dictionary.
   WordPair & get(WordPair & targetElement) const;

   // Description: Prints the content of the Dictionary.
   // Precondition: Dictionary is not empty.
   // Exception: Throws the exception EmptyDataCollectionException if the Dictionary is empty.
   // Postcondition: This method does not change the Dictionary.
   void displayContent(void visit(WordPair &)) const;
   
}; // end Dictionary
#endif
