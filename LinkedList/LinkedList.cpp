#include<iostream>
#include "ListNode.cpp"
#include "LinkedList.h"
using namespace std;

template<class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    tail = NULL;
    size = 0;

    endNode = new ListNode<T>;
    endNode->set_next(NULL);
    endNode->set_prev(NULL);
}

template<class T>
LinkedList<T>::~LinkedList()
{
    delete endNode;
}

template<class T>
void LinkedList<T>::push_front(T newVal)
{
    ListNode<T> *ln = new ListNode<T>;
    ln->set_prev(NULL);
    ln->set_next(head);
    ln->set_data(newVal);  

    if(empty()) {
        tail = ln;
        endNode->set_prev(tail);
        ln->set_next(endNode);
    }
    else {
        head->set_prev(ln);
    }
    head = ln;
    size++;
}

template<class T>
void LinkedList<T>::push_back(T newVal)
{
    ListNode<T> *ln = new ListNode<T>;
    ln->set_prev(tail);
    ln->set_next(endNode);
    ln->set_data(newVal);

    if(empty())
        head = ln;
    else
        tail->set_next(ln);

    tail = ln;
    size++;
}

template<class T>
typename LinkedList<T>::list_iterator LinkedList<T>::insert(T newVal, list_iterator li)
{
    if(li == begin()) {
        push_front(newVal);
    } else if(li == end()) {
        push_back(newVal);
    } else {
        ListNode<T> *ln = new ListNode<T>; 
        ln->set_data(newVal);
        ln->set_prev(li.node->get_prev());
        ln->set_next(li.node);
        ln->get_prev()->set_next(ln);
        ln->get_next()->set_prev(ln);
        size++;
    }
    li--;

    return li;
}

template<class T>
T LinkedList<T>::pop_front()
{
    T rtnVal;
    if(empty()) {
        cout << "pop_front() failed, list is empty. Exiting...\n";
        exit (1);
    } else {
        rtnVal = head->data();
        ListNode<T> *handle = head;
        if(size == 1) {
            head = NULL;
            tail = NULL;
            endNode->set_prev(NULL);
        } else {
            head = head->get_next();
            head->set_prev(NULL);
        }
        size--;
        delete handle;
    }

    return rtnVal;
}

template<class T>
T LinkedList<T>::pop_back()
{
    T rtnVal;
    if(empty()) {
        cout << "pop_back() failed, list is empty. Exiting...\n";
        exit (1);
    } else {
        rtnVal = tail->data();
        ListNode<T> *handle = tail;
        if(size == 1) {
            head = NULL;
            tail = NULL;
            endNode->set_prev(NULL);
        } else {
            tail = tail->get_prev();
            tail->set_next(endNode);
            endNode->set_prev(tail);
        }
        size--;
        delete handle;
    }

    return rtnVal;
}

template<class T>
typename LinkedList<T>::list_iterator LinkedList<T>::remove(list_iterator li)
{
    list_iterator rtn;

    if(li.node == head) {
        pop_front();
        rtn = begin();
    } else if(li.node == tail) {
        pop_back();
        rtn = end();
        rtn--;
    } else {
        li.node->get_prev()->set_next(li.node->get_next());
        li.node->get_next()->set_prev(li.node->get_prev());
        rtn.node = li.node->get_next();
        delete li.node;
        size--;
    }

    return rtn;
}        

template<class T>
T LinkedList<T>::front()
{
    if(empty()) {
        cout << "front() failed, list is empty. Exiting...\n";
        exit (1);
    }
    return head->data();
}

template<class T>
T LinkedList<T>::back()
{
    if(empty()) {
        cout << "back() failed, list is empty. Exiting...\n";
        exit (1);
    }
    return tail->data();
}

template<class T>
bool LinkedList<T>::empty()
{
    return (size <= 0);
}

template<class T>
typename LinkedList<T>::list_iterator LinkedList<T>::find_first(T searchVal)
{
    list_iterator rtn(NULL);
    list_iterator li;

    for(li=begin(); li!=end(); li++) {
        if(li.val() == searchVal) {
            if(rtn.node == NULL) {    //if nothing was found yet
                rtn.node = li.node;
                break;
            }
        }
    }

    return rtn;
}

template<class T>
typename LinkedList<T>::list_iterator LinkedList<T>::find_last(T searchVal)
{
    list_iterator rtn(NULL);
    list_iterator li;

    for(li=begin(); li!=end(); li++) {
        if(li.val() == searchVal) {
            rtn.node = li.node;
        }
    }

    return rtn;
}

/*Sort function that uses the insertion sort algorithm.
  Most sort algorithms like quicksort are very inefficient
  if performed on sequential data structures. Merge sort would be
  a better option over insertion, so i'll eventually add that to 
  this class.*/
template<class T>
void LinkedList<T>::sort_list()
{
    ListNode<T> *pos;
    bool isLast = 0;

    tail->set_next(NULL);
    pos = head->get_next();

    while(!isLast) {
        bool shouldSwap = 0;
        ListNode<T> *element = pos;
        ListNode<T> *comparer = pos->get_prev();
        if(pos->get_next() == NULL) {
            isLast = 1;
        } else {
            pos = pos->get_next();
        }

        while((comparer != NULL) && (element->data() <= comparer->data())) {
            comparer = comparer->get_prev();
            shouldSwap = 1;
        }
        if(shouldSwap) {
            //Removing element from its place in the list
            element->get_prev()->set_next(element->get_next());
            if(element->get_next() != NULL) {
                element->get_next()->set_prev(element->get_prev());
            } else {
                tail = element->get_prev();
            }

            if(comparer == NULL) {    //if element belongs in the head of the list
                element->set_prev(NULL);
                element->set_next(head);
                head->set_prev(element);
                head = element;
            } else {
                element->set_next(comparer->get_next());
                element->set_prev(comparer->get_prev());
                comparer->set_next(element);
                element->get_next()->set_prev(element);
            }
        }
    }

    //Redifining the endNode
    tail->set_next(endNode);
    endNode->set_prev(tail);
}

template<class T>
typename LinkedList<T>::list_iterator LinkedList<T>::begin()
{
    list_iterator rtn(head);
    return rtn;
}

template<class T>
typename LinkedList<T>::list_iterator LinkedList<T>::end()
{
    list_iterator rtn(endNode);
    return rtn;
}

template<class T>
LinkedList<T>::list_iterator::list_iterator()
{
    node = NULL;
}

template<class T>
LinkedList<T>::list_iterator::list_iterator(ListNode<T> *ln)
{
    node = ln;
}

template<class T>
T LinkedList<T>::list_iterator::val()
{
    if(node == NULL) {
        return NULL;
    }
    return node->data();
}

template<class T>
typename LinkedList<T>::list_iterator LinkedList<T>::list_iterator::operator++(int)
{
    if((node == NULL) | (node->get_next() == NULL)) {
        cout << "Failed to increment list_iterator: out of bounds. Exiting...\n";
        exit(1); 
    }
    list_iterator old(node);
    node = node->get_next();

    return old;
}

template<class T>
typename LinkedList<T>::list_iterator LinkedList<T>::list_iterator::operator++()
{
    if((node == NULL) | (node->get_next() == NULL)) {
        cout << "Failed to increment list_iterator: out of bounds. Exiting...\n";
        exit(1);
    }
    node = node->get_next();

    return list_iterator(node);
}

template<class T>
typename LinkedList<T>::list_iterator LinkedList<T>::list_iterator::operator--()
{
    if((node == NULL) | (node->get_prev() == NULL)) {
        cout << "Failed to decrement list_iterator: out of bounds. Exiting...\n";
        exit(1);
    }
    node = node->get_prev();

    return list_iterator(node);
}

template<class T>
typename LinkedList<T>::list_iterator LinkedList<T>::list_iterator::operator--(int)
{
    if((node == NULL) | (node->get_prev() == NULL)) {
        cout << "Failed to decrement list_iterator: out of bounds. Exiting...\n";
        exit(1);
    }
    list_iterator old(node);

    node = node->get_prev();
    return old;
}

template<class T>
void LinkedList<T>::list_iterator::operator=(const list_iterator &li)
{
    node = li.node;
}

template<class T>
void LinkedList<T>::list_iterator::operator=(const ListNode<T> &ln)
{
    node = &ln;
}

template<class T>
bool LinkedList<T>::list_iterator::operator==(const list_iterator &li)
{
    return (node == li.node);
}

template<class T>
bool LinkedList<T>::list_iterator::operator!=(const list_iterator &li)
{
    return (node != li.node);
}

int main()
{
    LinkedList<int> ll;
    ll.push_front(3);
    ll.push_front(2);
    ll.push_front(1);
    LinkedList<int>::list_iterator li;

    for(li=ll.begin(); li!=ll.end(); ++li)
        cout << "Value: \t" << li.val() << "\n";

    ll.pop_front();
    ll.push_back(4);
    cout << "new size: " << ll.size << endl;

    LinkedList<char> ll2;
    for(char i='a'; i<='z'; i++)
        ll2.push_front(i);

    LinkedList<char>::list_iterator li2;
    for(li2=ll2.begin(); li2!=ll2.end(); li2++)
        cout << "Character: \t" << li2.val() << "\n";

    cout << "\nPopping last 4 elements...\n\n";
    for(int i=0; i<4; i++)
        cout << "Popping value: " << ll2.pop_back() << "\n\n";

    cout << "New list:\n";
    for(li2=ll2.begin(); li2!=ll2.end(); li2++)
        cout << "Character: \t" << li2.val() << "\n";

    li2 = ll2.begin();
    for(int i=0; i<5; i++)
        li2++;

    LinkedList<char>::list_iterator li3 = ll2.insert('E',li2);

    cout << "\n\nInserting 'E' at 5th element.\n\nNew List:\n";

    for(li2=ll2.begin(); li2!=ll2.end(); li2++)
        cout << "Character: \t" << li2.val() << "\n";

    cout << "\nReturn value for last insert: " << li3.val() << "\n\n";

    cout << "Removing new value from list...\n\nNew List:\n";

    li3 = ll2.remove(li3);

    for(li2=ll2.begin(); li2!=ll2.end(); li2++)
        cout << "Character: \t" << li2.val() << "\n";

    cout << "\nValue of returned iterator: " << li3.val() << "\n\n";

    cout << "\nRemoving first element using remove.\n\n";
    li3 = ll2.begin();
    li3 = ll2.remove(li3);

    cout << "New begin value: " << ll2.begin().val() << "\nNew li3 value: " << li3.val() << "\n\n";

    cout << "\n\nSearching for first occurance of value: c\n\n";
    li3 = ll2.find_first('c');

    cout << "\nfound " << li3.val() << "\n\n";

    cout << "\n\nSearching for first occurence of E\n\n"; //testing null return
    li3 = ll2.find_first('E');

    cout << "\nfound " << li3.val() << "\n\n";


    cout << "Adding another 'c' to the list.\nNew List:\n";
    ll2.push_back('c');
    ll2.push_back('c');

    for(li2=ll2.begin(); li2!=ll2.end(); li2++)
        cout << "Character: \t" << li2.val() << "\n";

    li3 = ll2.find_last('c');
    cout << "found " << li3.val() << "\nNow removing last instance of c\n\n";

    li3 = ll2.remove(li3);

    cout << "\nNew List:\n\n";
    for(li2=ll2.begin(); li2!=ll2.end(); li2++)
        cout << "Character: \t" << li2.val() << "\n";

    cout << "\n\nAdding 'a' to end of list...\n\n";
    ll2.push_back('a');

    cout << "\nSorting ll2...\n\n";

   ll2.sort_list();

    cout << "\n\nNew List\n";
    for(li2=ll2.begin(); li2!=ll2.end(); li2++)
        cout << "Character: \t" << li2.val() << "\n";


    cout << "Finished executing. Exiting...\n\n";
    
    return 0;
}
