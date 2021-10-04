#include "LinkedList.hpp"
#include <stdexcept>

template<typename T>
LinkedList<T>::LinkedList() : head(nullptr), count(0) {}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs) {
    if (rhs.head == nullptr) {
        head = nullptr;
        count = 0;
    } else {
        head = new Node<T>(rhs.head->getItem(), rhs.head->getNext());
        count = 1;
        Node<T> *curr = head;
        Node<T> *next = rhs.head->getNext();
        while (next != nullptr) {
            curr->setNext(new Node<T>(next->getItem(), next->getNext()));
            count++;
            curr = curr->getNext();
            next = next->getNext();
        }
    }
}

template<typename T>
LinkedList<T> &LinkedList<T>::operator=(LinkedList rhs) {
    if (this != &rhs) {
        LinkedList<T> temp(rhs);
        swap(*this, rhs);
        count = rhs.count;
    }
    return *this;
}

template<typename T>
LinkedList<T>::~LinkedList() {
    Node<T> *curr = head;
    while (curr != nullptr) {
        head = head->getNext();
        delete curr;
        curr = head;
    }
}

template<typename T>
bool LinkedList<T>::isEmpty() const {
    return count == 0;
}

template<typename T>
int LinkedList<T>::getLength() const {
    return count;
}

template<typename T>
bool LinkedList<T>::insert(int newPosition, const T &newEntry) {
    if (newPosition == 1) {
        Node<T> *temp = head;
        head = new Node<T>(newEntry, temp);
    } else {
        Node<T> *old = getNodeAt(newPosition);
        if (old == nullptr) { return false; }
        Node<T> *newNode = new Node<T>(newEntry, old->getNext());
        old->setNext(newNode);
    }
    count++;
    return true;
}

template<typename T>
bool LinkedList<T>::remove(int position) {
    if (isEmpty()) { return false; }
    Node<T> *remove;
    if (position == 1) {
        remove = head;
        head = head->getNext();
    } else {
        Node<T> *old = getNodeAt(position);
        if (old == nullptr) { return false; }
        remove = old->getNext();
        old->setNext(old->getNext()->getNext());
    }
    delete remove;
    count--;
    return true;
}

template<typename T>
void LinkedList<T>::clear() {
    Node<T> *curr = head;
    while (curr != nullptr) {
        Node<T> *temp = curr;
        curr = curr->getNext();
        delete temp;
    }
    head = nullptr;
    count = 0;
}

template<typename T>
T LinkedList<T>::getEntry(int position) const {
    T item;
    if (position == 1) {
        item = head->getItem();
    } else {
        Node<T> *node = getNodeAt(position);
        if (node == nullptr) { throw std::logic_error("Index out of bounds."); }
        item = node->getNext()->getItem();
    }
    return item;
}

template<typename T>
T LinkedList<T>::setEntry(int position, const T &newValue) {
    T temp;
    if (position == 1) {
        temp = head->getItem();
        head->setItem(newValue);
    } else {
        Node<T> *old = getNodeAt(position);
        if (old == nullptr) { throw std::logic_error("Index out of bounds."); }
        temp = old->getNext()->getItem();
        old->getNext()->setItem(newValue);
    }
    return temp;
}

template<typename T>
void LinkedList<T>::swap(LinkedList &lhs, LinkedList &rhs) {
    Node<T> *temp = lhs.head;
    lhs.head = rhs.head;
    rhs.head = temp;
}

template<typename T>
Node<T> *LinkedList<T>::getNodeAt(int position) const {
    if ((position >= 1) && (position <= this->getLength() + 1)) {
        if (position == 1) { return head; }
        int currentPos = 1;
        Node<T> *curr = head;
        while (curr != nullptr) {
            if (currentPos + 1 == position) {
                return curr;
            }
            currentPos++;
            curr = curr->getNext();
        }
    }
    return nullptr;
}
