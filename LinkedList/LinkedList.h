template<class T>
class ListNode;

template<class T>
class LinkedList
{
    public:
        LinkedList();
        ~LinkedList();

        //Iterator
        class list_iterator
        {
            friend class LinkedList<T>;
            public:
                list_iterator();
                list_iterator(ListNode<T> *ln);
                T val();
                list_iterator operator++(int);
                list_iterator operator++();
                list_iterator operator--(int);
                list_iterator operator--();
                void operator=(const list_iterator &li);
                void operator=(const ListNode<T> &ln);
                bool operator==(const list_iterator &li);
                bool operator!=(const list_iterator &li);

            private:
                ListNode<T> *node;

        };
        typename LinkedList<T>::list_iterator begin();
        typename LinkedList<T>::list_iterator end();

        //Insert functions
        void push_front(T &newVal);
        void push_back(T &newVal);
        typename LinkedList<T>::list_iterator insert(T &newVal, list_iterator li);

        //Remove functions
        T pop_front();
        T pop_back();
        typename LinkedList<T>::list_iterator remove(list_iterator li);

        //Search functions
        T front();
        T back();
        bool empty();
        bool find_first(T searchVal,list_iterator &pos);
        typename LinkedList<T>::list_iterator find_last(T searchVal);
        int size;

        //Sorting and sorting helper functions
        void sort_list();

    private:
        ListNode<T> *head;
        ListNode<T> *tail; 
        ListNode<T> *endNode;  //Different than tail - theoretical 'next' node
        int numNodes;
         
};
