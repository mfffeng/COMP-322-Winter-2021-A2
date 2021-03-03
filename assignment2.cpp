#include <iostream>
using namespace std;


class Node{
    public:
        Node();
        Node(int data, Node* next, Node* previous);
        ~Node();
        int data;
        Node *next;
        Node *prev;
};

Node::Node(): data(0), next(NULL), prev(NULL){}

Node::Node(int data, Node* next, Node* previous){
    this -> data = data;
    this -> next = next;
    this -> prev = previous;
}

Node::~Node(){}


class DLLStructure{
    public:
        DLLStructure();
        DLLStructure(int array[], int size);
        ~DLLStructure();
        void PrintDLL();
        void InsertAfter(int valueToInsertAfter, int valueToBeInserted);
        void InsertBefore(int valueToInsertAfter, int valueToBeInserted);
        void Delete(int value);
        void Sort();
        bool IsEmpty();
        int GetHead();
        int GetTail();
        int GetSize();
        int GetMax();
        int GetMin();

    private:
        Node *first;
        Node *last;
};

DLLStructure::DLLStructure():first(NULL), last(NULL){}

DLLStructure::DLLStructure(int array[], int size){
    if (size == 0){     // Initialize an empty list if the array is empty.
        DLLStructure();
    }
    else{
        Node *head = new Node(array[0], NULL, NULL);
        this -> first = head;
        Node *lastLoop = head;
        for (int i = 1; i < size; i++){
            Node* current = new Node(array[i], NULL, lastLoop);
            lastLoop -> next = current;
            lastLoop = current;
        }
        last = lastLoop;
    }
}

DLLStructure::~DLLStructure(){
    Node *current = first;
    Node *nextNode = first -> next;
    while (nextNode != NULL){
        delete current;
        current = nextNode;
        nextNode = nextNode -> next;
    }
    delete last;        // The last node can't be deleted in the above loop, as the next node to the last node is NULL.
    first = NULL;
    last = NULL;
}

void DLLStructure::PrintDLL(){
    Node *current = first;
    while (current -> next != NULL){
        cout << current -> data << " ";
        current = current -> next;
    }
    cout << last << endl;
}

void DLLStructure::InsertAfter(int valueToInsertAfter, int valueToBeInserted){
    bool found = false;
    Node *current = first;
    while (current != NULL){
        if (current -> data == valueToInsertAfter){
            found = true;
            break;
        }
        current = current -> next;
    }
    Node *insert = new Node(valueToBeInserted, NULL, NULL);
    if (found){
        insert -> next = current -> next;
        current -> next -> prev = insert;
        current -> next = insert;
        insert -> prev = current;
    }
    else{
        last -> next = insert;
        insert -> prev = last;
        last = insert;
    }
}


void DLLStructure::InsertBefore(int valueToInsertAfter, int valueToBeInserted){
    bool found = false;
    Node *current = first;
    while (current != NULL){
        if (current -> data == valueToInsertAfter){
            found = true;
            break;
        }
        current = current -> next;
    }
    if (!found){        // Target value not found, insert the value to the start of the list.
        Node *insert = new Node(valueToBeInserted, NULL, NULL);
        first -> prev = insert;
        insert -> next = first;
        first = insert;
    }
    else{       // Target value found.
        int insertAfterNode = current -> prev -> data;      // Insert after the previous node == Insert before the target node.
        InsertAfter(insertAfterNode, valueToBeInserted);
    }
}


void DLLStructure::Delete(int value){
    Node *current = first;
    while (current != NULL){
        if (current -> data == value){
            break;
        }
        current = current -> next;
    }
    if (current != NULL){       // If the value to be deleted is in the list.
        if (current != last){   // If it's not the last element.
            current -> prev -> next = current -> next;
            current -> next -> prev = current -> prev;
            delete current;
        }
        else{   // If it is the last element.
            current -> prev -> next = NULL;
            last = current -> prev;
            delete current;
        }
    }
}


void DLLStructure::Sort(){
    Node *boundary = last;
    Node *pointer = first;
    int i = 0;
    int j = 0;
    while (boundary -> prev != NULL){       //  A bubble sort here.
        while (pointer != boundary){
            if (pointer -> data > pointer -> next -> data){
                int swap = pointer -> data;
                pointer -> data = pointer -> next -> data;
                pointer -> next -> data = swap;
            }
            pointer = pointer -> next;
        }
        pointer = first;
        boundary = boundary -> prev;
    }
}


bool DLLStructure::IsEmpty(){
    return first == NULL && last == NULL;
}


int DLLStructure::GetHead(){
    return first -> data;
}


int DLLStructure::GetTail(){
    return last -> data;
}