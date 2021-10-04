
#ifndef _ABSTRACT_LIST_H_
#define _ABSTRACT_LIST_H_

#include <cstdlib>

template <typename T>
class AbstractList
{
public:

  // See whether this list is empty
  virtual bool isEmpty() const = 0;

  // Gets the current number of entries in this list.
  virtual int getLength() const = 0;

  // Inserts an entry into this list at a given position.
  virtual bool insert(int newPosition, const T& newEntry) = 0;

  // Removes the entry at a given position from this list.
  virtual bool remove(int position) = 0;

  // Removes all entries from this list.
  virtual void clear() = 0;
  
  // Gets the entry at the given position in this list.
  virtual T getEntry(int position) const = 0;

  // Sets the entry at the given position in this list with the new value.
  virtual T setEntry(int position, const T& newValue) = 0;
  
};

#endif // _ABSTRACT_LIST_H_
