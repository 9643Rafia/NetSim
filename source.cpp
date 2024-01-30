#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#define INF 999
using namespace std;

//routing pair
class Pair
{
public:
    string router;
    string destination;
};
template<class T>
class Priority_Q
{
    int size;
    T* H;
public:
    Priority_Q()
    {
        size = 50;
        H = new T[size];
    }

    ~Priority_Q()
    {
        //delete[]H;
    }
    int parent(int i)
    {

        return (i - 1) / 2;
    }

    // Function to return the index of the
    // left child of the given node
    int leftChild(int i)
    {

        return ((2 * i) + 1);
    }

    // Function to return the index of the
    // right child of the given node
    int rightChild(int i)
    {

        return ((2 * i) + 2);
    }

    // Function to shift up the node in order
    // to maintain the heap property
    void shiftUp(int i)
    {
        while (i > 0 && H[parent(i)].Priority < H[i].Priority) {

            // Swap parent and current node

            T temp = H[parent(i)];
            H[parent(i)] = H[i];
            H[i] = temp;
            // Update i to parent of i
            i = parent(i);
        }
    }

    // Function to shift down the node in
    // order to maintain the heap property
    void shiftDown(int i)
    {
        int maxIndex = i;

        // Left Child
        int l = leftChild(i);

        if (l <= size && H[l].Priority > H[maxIndex].Priority) {
            maxIndex = l;
        }

        // Right Child
        int r = rightChild(i);

        if (r <= size && H[r].Priority > H[maxIndex].Priority) {
            maxIndex = r;
        }

        // If i not same as maxIndex
        if (i != maxIndex) {
            T temp = H[i];
            H[i] = H[maxIndex];
            H[maxIndex] = temp;
            shiftDown(maxIndex);
        }
    }

    // Function to insert a new element
    // in the Binary Heap
    void insert(T p)
    {
        size = size + 1;
        H[size] = p;

        // Shift Up to maintain heap property
        shiftUp(size);
    }

    // Function to extract the element with
    // maximum priority
    T extractMax()
    {
        T result = H[0];

        // Replace the value at the root
        // with the last leaf
        H[0] = H[size];
        size = size - 1;

        // Shift down the replaced element
        // to maintain the heap property
        shiftDown(0);
        return result;
    }

    // Function to change the priority
    // of an element
    void changePriority(int i, int p)
    {
        int oldp = H[i];
        H[i] = p;

        if (p > oldp) {
            shiftUp(i);
        }
        else {
            shiftDown(i);
        }
    }

    // Function to get value of the current
    // maximum element
    int getMax()
    {
        return H[0];
    }

    // Function to remove the element
    // located at given index
    void remove(int i)
    {
        H[i] = getMax() + 1;

        // Shift the node to the root
        // of the heap
        shiftUp(i);

        // Extract the node
        extractMax();
    }
};
template<class T>
class Node
{
    T VAL;
    Node<T>* NEXT;

public:
    Node(T value)
    {
        VAL = value;
        NEXT = NULL;

    }

    T getData()
    {
        return VAL;
    }

    void setData(T TEMP)
    {
        VAL = TEMP;
    }

    Node <T>* getNext()
    {
        return NEXT;
    }

    void setNext(Node<T>* ARRAY)
    {
        NEXT = ARRAY;
    }

};


template<class T>
class Queue
{
    Node<T>* FRONT;
    Node<T>* REAR;

public:
    Queue()
    {
        FRONT = NULL;
        REAR = NULL;
    }

    Node<T>* getRear()
    {
        return REAR;
    }

    void enqueue(T VAL)
    {
        Node<T>* PTR = new Node<T>(VAL);
        if (REAR == NULL)
        {
            FRONT = PTR;
            REAR = PTR;
        }
        else
        {
            REAR->setNext(PTR);
            REAR = PTR;
        }
    }

    void dequeue(T& data)
    {
        if (FRONT != NULL)
        {

            Node<T>* PTR = FRONT;
            FRONT = FRONT->getNext();
            if (FRONT == NULL)
            {
                REAR = NULL;
            }
            data = PTR->getData();
            delete PTR;


        }

    }

    bool isEmpty()
    {
        if (REAR != NULL || FRONT != NULL)
        {
            return false;
        }
        return true;

    }

    T peek()
    {
        if (!isEmpty())
        {
            return FRONT->getData();

        }

    }
};

class Message
{
public:
    int Message_id;
    int Priority;
    string Source_address;
    string Destination_address;
    string Payload;
    string Trace;
    Message() {

    }
    Message(int id, int pr, string src, string dst, string pd, string tr) {
        Message_id = id;
        Priority = pr;
        Source_address = src;
        Destination_address = dst;
        Payload = pd;
        Trace = tr;
    }
};


//linked list for routing table


template <typename T>

class LinkedList
{
    Node <T>* HEAD;


public:

    LinkedList()
    {
        HEAD = NULL;

    }
    void setHead(Node<T>* POINTER)
    {
        HEAD = POINTER;
    }

    Node <T>* getHead()
    {
        return HEAD;
    }


    void print()
    {
        Node<T>* TEMP;
        TEMP = HEAD;
        while (TEMP != NULL)
        {
            cout << TEMP->getData();
            TEMP = TEMP->getNext();

        }
    }



    bool insert(T DAT)
    {
        Node <T>* ADD = new Node <T>(DAT);
        Node <T>* TEMP;
        if (HEAD != NULL)
        {
            TEMP = HEAD;
            while (TEMP->getNext() != NULL)
            {
                TEMP = TEMP->getNext();
            }
            TEMP->setNext(ADD);

            return true;
        }
        else
        {

            HEAD = ADD;
            return true;
        }
    }
    int counter()
    {
        int count = 0;
        Node<T>* TEMP = HEAD;
        while (TEMP->getNext() != NULL)
        {
            count++;
            TEMP = TEMP->getNext();
        }
        return count;
    }

};

class Router
{
public:
    string id;
    Priority_Q <Message>p;
    LinkedList<Pair> table;
    Queue<Message>q;
    Router() {};
    Router(string id)
    {
        id = id;
    }

};
class Machine
{
public:
    string id;
    Queue<Message>outgoing;
    Queue<Message>incoming;
    Machine() {};
    Machine(string id)
    {
        id = id;
    }

};
LinkedList<string> tokenizer(string line)
{
    LinkedList<string>routlist;
    string elm = ""; int i = 0;
    for (i = 0; i < line.length(); i++)
    {
        if (line[i] != ',')
        {
            elm += line[i];
        }
        else
        {
            routlist.insert(elm);

            elm = "";
        }

    }
    routlist.insert(elm);

    return routlist;

}



int main()
{

    LinkedList<Machine> machines;
    LinkedList<Router>routers;
    cout << "    Welcome" << endl;
    ifstream file("network.csv");//file to populate matrix from
    string line;
    file >> line;
    LinkedList<string>darr = tokenizer(line);

    //initializing routing matrix
    int** arr = new int* [darr.counter()];
    for (int i = 0; i < darr.counter(); i++)
    {
        arr[i] = new int[darr.counter()];
    }

    string elm = "";

    for (int i = 0; i < darr.counter(); i++) //populating routing matrix from csv file
    {
        file >> line;
        stringstream ss(line);
        getline(ss, elm, ',');
        if (elm[0] == 'M')
        {
            machines.insert(Machine(elm));
        }
        else if (elm[0] == 'R')
        {
            routers.insert(Router(elm));
        }
        for (int j = 0; j < darr.counter(); j++)
        {
            getline(ss, elm, ',');

            if (elm == "?")
            {
                arr[i][j] = -1;
            }
            else
            {
                arr[i][j] = stoi(elm);
            }

        }
    }
    for (int i = 0; i < darr.counter(); i++)
    {
        for (int j = 0; j < darr.counter(); j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }










    /*
    for (int i = 0; i < darr.counter(); i++)
    {
        for (int j = 0; j < darr.counter(); j++)
        {
            cout << arr[i][j];
        }
    }*/



    return 0;


}
