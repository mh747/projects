template<class T>
class ListNode
{
    public:
        ListNode();
        ~ListNode();
        
        ListNode<T> *get_next();
        void set_next(ListNode<T> *node);

        ListNode<T> *get_prev();
        void set_prev(ListNode<T> *node);

        T data();
        void set_data(T nData);

    private:
        ListNode<T> *prev;
        ListNode<T> *next;
        T nodeData;
}; 
