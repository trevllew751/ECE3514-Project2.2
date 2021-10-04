#ifndef LINKED_LIST_
#define LINKED_LIST_

#include <utility> //for swap

#include "AbstractList.hpp"
#include "Node.hpp"

/**
 * This is a LinkedList class. It uses Nodes to store data.
 */  
template<typename T>
class LinkedList : public AbstractList<T>
{
public:
   LinkedList();
    
   /** This is the copy constructor. It make a copy of the parameter.  It is also used by the operator= in the copy-swap paradigm.
    @param rhs - the LinkedList we are copying during construction
   */
   LinkedList(const LinkedList& rhs);
    
   virtual ~LinkedList();
    
   /** This is the assignment operator. It uses the copy-swap paradigm to create a copy of the parameter
    @param rhs - the LinkedList we are assigning to this
    @return a reference to the list that was copied into, a.k.a. *this
   */
  LinkedList& operator=( LinkedList rhs );

   /** Sees whether this list is empty.
    @return  True if the list is empty; otherwise returns false.
   */
   bool isEmpty() const;
    
   /** Gets the current number of entries in this list.
    @return  The integer number of entries currently in the list.
   */
   int getLength() const;
    
   /** Inserts an entry into this list at a given position.
    @pre None.
    @post  If 1 <= position <= getLength() + 1 and the insertion is
        successful, newEntry is at the given position in the list,
        other entries are renumbered accordingly, and the returned
        value is true.
    @param newPosition  The list position at which to insert newEntry.
    @param newEntry  The entry to insert into the list.
    @return  True if the insertion is successful, or false if not.
   */
   bool insert(int newPosition, const T& newEntry);
    
   /** Removes the entry at a given position from this list.
    @pre  None.
    @post  If 1 <= position <= getLength() and the removal is successful,
        the entry at the given position in the list is removed, other
        items are renumbered accordingly, and the returned value is true.
    @param position  The list position of the entry to remove.
    @return  True if the removal is successful, or false if not.
   */
   bool remove(int position);
    
   /** Removes all entries from this list.
    @post  The list contains no entries and the count of items is 0.
   */
   void clear();
   
   /** Gets the entry at the given position in this list.
    @pre  1 <= position <= getLength().
    @post  The desired entry has been returned.
    @param position  The list position of the desired entry.
    @return  The entry at the given position.
   */
   T getEntry(int position) const ;

   /** Sets the entry at the given position in this list with the new value.
    @pre  1 <= position <= getLength().
    @post  The value at the given position has new value
    @param position  The list position of the entry to set the new value
    @param newVAlue  The new value to set at the givien position.
    @return  The replaced entry.
   */
   T setEntry(int position, const T& newValue);

   /**This is the swap method. It will swap the internals of the two lists.  Notably it is used in the operator= to implement the copy swap paradigm.  It is also used by other C++ paradigms.
     @param lhs - the LinkedList on the left...Left Hand Side (lhs)
	 @param rhs - the LinkedList on the right...Right Hand Side (rhs)
   */
	void swap(LinkedList& lhs, LinkedList& rhs);
    
    /** Prints the content of the list to the screen. */
    void printList();
    
private:
    Node<T>* head; // Pointer to first node in the chain
                   //(contains the first entry in the list)
     
    int count;     // Current count of list items
    
    /** Locates a specified node in this linked list.
     @pre  position is the number of the desired node;
           position >= 1 and position <= itemCount.
     @post  The node is found and a pointer to it is returned.
     @param position  The number of the node to locate.
     @return  A pointer to the node at the given position.
    */
    Node<T>* getNodeAt(int position) const;

}; // end LinkedList

#include "LinkedList.txx"

#endif 
