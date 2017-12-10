#ifndef Queue_h
#define Queue_h

template <typename T>
class Queue
{
    struct Node
    {
        T value = T();
        Node* next;
    };
    Node* headPtr;
    Node* tailPtr;
    int siz;
    T dummy = T();
public:
    Queue();
    Queue(const Queue<T>& original);
    ~Queue();
    Queue<T>& operator=(const Queue<T>& value);
    void pop();
    void clear();
    void push(const T& value);
    T& front();
    T& back();
    int size() const;
};
template <typename T>
Queue<T>::Queue()
{
    headPtr = nullptr;
    tailPtr = nullptr;
    siz = 0;
}
template <typename T>
Queue<T>::Queue(const Queue<T>& original)
{
    headPtr = nullptr;
    tailPtr = nullptr;
    siz = original.siz;
    for(Node* ptr = original.headPtr; ptr; ptr = ptr->next)
    {
        Node* temp = new Node;
        temp->value = ptr->value;
        temp->next = nullptr;
        
        if(tailPtr)
            tailPtr->next = temp;
        else
            headPtr = temp;
        
        tailPtr = temp;
    }
}
template <typename T>
Queue<T>::~Queue()
{
    while (headPtr)
    {
        Node* ptr = headPtr; //temp pointer
        headPtr = headPtr->next;
        delete ptr;
    }
}
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& original)
{
    if (this != &original)
    {
        while (headPtr)
        {
            Node* ptr = headPtr->next;
            delete headPtr;
            headPtr = ptr;
        }
        
        tailPtr = nullptr;
        for (Node* ptr = original.headPtr; ptr; ptr = ptr->next)
        {
            Node* temp = new Node;
            temp->value = ptr->value;
            temp->next = nullptr;
            if (tailPtr)
                tailPtr->next = temp;
            else
                headPtr = temp;
            tailPtr = temp;
        }
        siz = original.siz;
    }
    return *this;
}
template <typename T>
void Queue<T>::pop()
{
    if (headPtr)
    {
        Node* ptr = headPtr;
        headPtr = headPtr->next;
        delete ptr;
        siz--;
    }
    if (siz == 0)
        tailPtr = nullptr;
}
template <typename T>
void Queue<T>::clear()
{
    while (headPtr)
    {
        Node* ptr = headPtr;
        headPtr = headPtr->next;
        delete ptr;
        siz--;
    }
    
    tailPtr = nullptr;
}
template <typename T>
void Queue<T>::push(const T& value)
{
    Node* temp = new Node;
    temp->value = value;
    temp->next = nullptr;
    if(tailPtr)
        tailPtr->next = temp;
    else
        headPtr = temp;
    tailPtr = temp;
    siz++;
}
template <typename T>
T& Queue<T>::front()
{
    if (headPtr)
        return headPtr->value;
    else
        return dummy;
}
template <typename T>
T& Queue<T>::back()
{
    if(tailPtr)
        return tailPtr->value;
    else
        return dummy;
}
template <typename T>
int Queue<T>::size() const
{
    return siz;
}
#endif
