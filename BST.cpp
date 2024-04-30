/*
 * BST.cpp
 * 
 * Description: Binary Search Tree data collection ADT class.
 *              Link-based implementation.
 *              Duplicated elements are not allowed.
 *
 * Class invariant: It is always a BST.
 * 
 * Author: Izaz Zubayer (301386899) & Zoe Stanley (301427509)
 * Date of last modification: March. 2024
 */
 
#include "BST.h"
#include "WordPair.h"

using std::nothrow;


// You cannot change the prototype of the public methods of this class.
// Remember, if you add public methods to this class, our test driver 
// - the one with which we will mark this assignment - 
// will not know about them since, in order to create it, we will have 
// used only the public method prototypes below.


/* Constructors and destructor */

   // Default constructor
   BST::BST() { }            

   //Copy Constructor
   BST::BST(const BST & aBST) : root(nullptr), elementCount(0) {

      if (aBST.root != nullptr) {
         root = copyR(aBST.root);
         elementCount = aBST.elementCount;
      }
   }                
   

   //Call Destructor
   BST::~BST() {
      clearR(root);
      root = nullptr;
      elementCount = 0;
   }
   
/* Getters and setters */

   // Description: Returns the number of elements currently stored in the binary search tree.   
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(1)
   unsigned int BST::getElementCount() const {     

     return this->elementCount;
	 
   }
   

   // Description: Recursive preorder
   BSTNode* BST::copyR(BSTNode * current) {
      if (current == nullptr) {
         return nullptr;
      } 
      BSTNode * newNode = new BSTNode(current->element);
      newNode->left = copyR(current->left);
      newNode->right = copyR(current->right);
      return newNode;
      

   }

   //Description: Recursive postorder
   void BST::clearR(BSTNode * current) {

      if (current != nullptr) {
         clearR(current->left);
         clearR(current->right);
         delete current;
         current = nullptr;
      }
   }
   

/* BST Operations */

   // Description: Inserts an element into the binary search tree.
   //              This is a wrapper method which calls the recursive insertR( ).
   // Precondition: "newElement" does not already exist in the binary search tree.
   // Exception: Throws the exception "UnableToInsertException" when newElement 
   //            cannot be inserted because the "new" operator failed. 
   // Exception: Throws the exception "ElementAlreadyExistsException" 
   //            if "newElement" already exists in the binary search tree.
   // Time efficiency: O(log2 n)   
   void BST::insert(WordPair & newElement) {
         
       // create a new node with the newElement  
         BSTNode * newBSTNode = new BSTNode(newElement);
         if (newBSTNode == nullptr) //Base case - If newBSTNode is null, then memory allocation failed.
            throw UnableToInsertException("Memory allocation failed.");
         
         if (elementCount == 0) {
            root = newBSTNode;
            elementCount++;
         }
         else {
            if (!insertR(newBSTNode, root)) {
               delete newBSTNode;
               throw ElementAlreadyExistsException("Element exists in the data collection.");
            } else {
               elementCount++;
            }
         }
   } 
   
   // Description: Recursive insertion into a binary search tree.
   //              Returns true when "anElement" has been successfully inserted into the 
   //              binary search tree. Otherwise, returns false.
   bool BST::insertR(BSTNode * newBSTNode, BSTNode * current) {  

      if (newBSTNode->element == current->element) // IF the element already exists in the BST then return false
         return false;
      else if (newBSTNode->element < current->element) { //ELSE IF the element is less than the current node's element then go left
         if (current->left == nullptr) {
            current->left = newBSTNode;
            return true;
         }
         else {
            return insertR(newBSTNode, current->left);
         }
      }
      else {
         if (current->right == nullptr) {
            current->right = newBSTNode;
            return true;
         }
         else {
            return insertR(newBSTNode, current->right);
         }
      }
		
   }

   
   // Description: Retrieves "targetElement" from the binary search tree.
   //              This is a wrapper method which calls the recursive retrieveR( ).
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Exception: Propagates the exception "ElementDoesNotExistException" 
   //            thrown from the retrieveR(...)
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(log2 n)
   WordPair& BST::retrieve(WordPair & targetElement) const {
      
     if (elementCount == 0)  
        throw EmptyDataCollectionException("Data collection is empty!");
	
     WordPair& translated = retrieveR(targetElement, root);
	 
     return translated;
   }

   // Description: Recursive retrieval from a binary search tree.
   // Exception: Throws the exception "ElementDoesNotExistException" 
   //            if "targetElement" is not found in the binary search tree.
   // Postcondition: This method does not change the binary search tree.
   WordPair& BST::retrieveR(WordPair & targetElement, BSTNode * current) const {

      if (current == nullptr)  // If the current node is null, then the element does not exist in the BST.
         throw ElementDoesNotExistException("Element does not exist in the data collection.");

      else if (targetElement == current->element) // If the target element is found, then return the element.
         return current->element;

      else if (targetElement < current->element)  // If the target element is less than the current node's element then go left
         return retrieveR(targetElement, current->left);

      else  // If the target element is greater than the current node's element then go right
         return retrieveR(targetElement, current->right);
   } 
         
   
   // Description: Traverses the binary search tree in order.
   //              This is a wrapper method which calls the recursive traverseInOrderR( ).
   //              The action to be done on each element during the traverse is the function "visit".
   // Precondition: Binary search tree is not empty.
   // Exception: Throws the exception "EmptyDataCollectionException" 
   //            if the binary search tree is empty.
   // Postcondition: This method does not change the binary search tree.
   // Time efficiency: O(n)     
   void BST::traverseInOrder(void visit(WordPair &)) const {
     
     if (elementCount == 0)  
       throw EmptyDataCollectionException("Data collection is empty.");

     traverseInOrderR(visit, root);
     
     return;
   }

   // Description: Recursive in order traversal of a binary search tree.   
   // Postcondition: This method does not change the binary search tree. 
   void BST::traverseInOrderR(void visit(WordPair &), BSTNode* current) const { 

      if (current != nullptr) {
         traverseInOrderR(visit, current->left);
         visit(current->element);
         traverseInOrderR(visit, current->right);
      }
   }