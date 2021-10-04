#include "Node.hpp"

template<typename ItemType>
Node<ItemType>::Node() : next(nullptr)
{} // end default constructor

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{} // end constructor

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr) : item(anItem), next(nextNodePtr)
{} // end constructor

template<typename ItemType>
void Node<ItemType>::setItem(const ItemType& anItem)
{
  item = anItem;
} // end setItem

template<typename ItemType>
void Node<ItemType>::setNext(Node<ItemType>* nextNodePtr)
{
  next = nextNodePtr;
} // end setNext

template<typename ItemType>
ItemType Node<ItemType>::getItem() const
{
  return item;
} // end getItem

template<typename ItemType>
Node<ItemType>* Node<ItemType>::getNext() const
{
  return next;
} // end getNext
