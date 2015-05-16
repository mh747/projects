#include<iostream>
#include "ListNode.h"
using namespace std;

template<class T>
ListNode<T>::ListNode()
{
    prev = NULL;
    next = NULL;
}

template<class T>
ListNode<T>::~ListNode()
{
}

template<class T>
ListNode<T> *ListNode<T>::get_next()
{
    return next;
}

template<class T>
void ListNode<T>::set_next(ListNode<T> *node)
{
    next = node;
}

template<class T>
ListNode<T> *ListNode<T>::get_prev()
{
    return prev;
}

template<class T>
void ListNode<T>::set_prev(ListNode<T> *node)
{
    prev = node;
}

template<class T>
T *ListNode<T>::data()
{
        return nodeData;
}

template<class T>
void ListNode<T>::set_data(T *nData)
{
    nodeData = nData;
}

/*int main()
{
    ListNode<int> ln1;
    ListNode<int> ln2;

    ln1.set_data(1);
    ln2.set_data(3);

    ln1.set_next(&ln2);
    ln2.set_prev(&ln1);

    cout << "List Node 1:\nValue: " << ln1.data() << "\n\nList Node 2:\nValue"
         << ln1.get_next()->data() << "\n\n\nExiting...";

    return 0;
}*/
