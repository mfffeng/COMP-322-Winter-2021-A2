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

    private:
        Node *first;
        Node *last;
};

DLLStructure::DLLStructure():first(NULL), last(NULL){}

DLLStructure::DLLStructure(int array[], int size){
    Node *head = new Node(array[0], NULL, NULL);
    this -> first = head;
    Node *lastLoop = head;
    for (int i = 1; i < size; i++){
        Node* current = new Node(array[i], NULL, lastLoop);
        current -> prev -> next = current;
        lastLoop = current;
    }
    this -> last = lastLoop;
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
