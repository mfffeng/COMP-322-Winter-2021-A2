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
        DLLStructure(DLLStructure& dlls);

    private:
        Node *first;
        Node *last;
};

DLLStructure::DLLStructure():first(NULL), last(NULL){}      // Initialize an empty list.

DLLStructure::DLLStructure(int array[], int size){
    if (size == 0){     // Initialize an empty list if the array is empty.
        first = NULL;
        last = NULL;
    }
    else{
        Node *head = new Node(array[0], NULL, NULL);
        first = head;
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
    if (! (first == NULL && last == NULL)){
        Node *current = first;
        Node *nextNode = first -> next;
        while (nextNode != NULL){
            delete current;
            current = nextNode;
            nextNode = nextNode -> next;
        }
        delete last;        // The last node can't be deleted in the above loop, as the next node to the last node is NULL.
    }
}

void DLLStructure::PrintDLL(){
    Node *current = first;
    while (current -> next != NULL){
        cout << current -> data << " ";
        current = current -> next;
    }
    cout << last -> data << endl;   // I leave this last node out of the loop intentionally, beacuse I don't want to
}                                   // leave only endl on a cout line:).

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
    if (found){     // Target value found.
        insert -> next = current -> next;
        current -> next -> prev = insert;
        current -> next = insert;
        insert -> prev = current;
        if (current == last){       // If the target value itself is the "last", update the "last" state. 
            last = insert;
        }
    }
    else{           // Target value not found.
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
        if (current != first){
            int insertAfterNode = current -> prev -> data;      // Insert after the previous node == Insert before the target node.
            InsertAfter(insertAfterNode, valueToBeInserted);
        }
        else{
            Node *insert = new Node(valueToBeInserted, NULL, NULL); // The above way of using InsertAfter() doesn't work if the target
            first -> prev = insert;                                 // value is the "first" and has no previous node.
            insert -> next = first;
            first = insert;
        }
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
        if (current != last && current != first){   // If it's neither the last nor the first element.
            current -> prev -> next = current -> next;
            current -> next -> prev = current -> prev;
            delete current;
        }
        else if (current == last){   // If it is the last element.
            current -> prev -> next = NULL;
            last = current -> prev;
            delete current;
        }
        else if (current == first){     // If it is the first element.
            current -> next -> prev = NULL;
            first = current -> next;
            delete current;
        }
    }
}


void DLLStructure::Sort(){
    if (IsEmpty()){
        cout << "(Empty list!) ";
        return;
    }
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
    if (IsEmpty()){
        cout << "(Empty list!) ";
    }
    return first -> data;
}


int DLLStructure::GetTail(){
    if (IsEmpty()){
        cout << "(Empty list!) ";
    }
    return last -> data;
}


int DLLStructure::GetSize(){
    Node *pointer = first;
    int size = 0;
    while (pointer != NULL){
        size++;
        pointer = pointer -> next;
    }
    return size;
}


int DLLStructure::GetMax(){
    Sort();
    return last -> data;
}


int DLLStructure::GetMin(){
    Sort();
    return first -> data;
}


DLLStructure::DLLStructure(DLLStructure& dlls){
    if (dlls.IsEmpty()){
        first = NULL;
        last = NULL;
    }
    else{
        Node *pointer = dlls.first;
        while (pointer != NULL){
            Node *head = new Node(pointer -> data, NULL, NULL);
            this -> first = head;
            Node *lastLoop = head;
            pointer = pointer -> next;
            while (pointer != NULL){
                Node* current = new Node(pointer -> data, NULL, lastLoop);
                lastLoop -> next = current;
                lastLoop = current;
                pointer = pointer -> next;
            }
            this -> last = lastLoop;
        }
    }
}


int main () {
    // Q 1, 2, 3 should obviously be implemented successfully
    // in order to run the following code
    int array [5] = {11 ,2 ,7 ,22 ,4 };
    DLLStructure dll (array, 5) ; // note that 5 is the size of the array
    dll.PrintDLL(); // the output should be: 11, 2, 7, 22, 4
    // Q 4
    dll.InsertAfter(7, 13); // To insert 13 after the first occurence of 7
    dll.PrintDLL(); // the output should be: 11, 2, 7, 13, 22, 4
    dll.InsertAfter(25, 7); // To insert 7 after the first occurence of 25
    dll.PrintDLL(); // the output should be: 11, 2, 7, 13, 22, 4, 7
    // Q 5
    dll.InsertBefore(7, 26); // To insert 26 before the first occurence of 7
    dll.PrintDLL(); // the output should be: 11, 2, 26, 7, 13, 22, 4, 7
    dll.InsertBefore(19, 12); // To insert 12 before the first occurence of 19
    dll.PrintDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 22, 4, 7
    // Q 6
    dll.Delete(22);
    dll.PrintDLL(); // the output should be: 12, 11, 2, 26, 7, 13, 4, 7
    // Q 7
    dll.Sort();
    dll.PrintDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
    // Q 8
    if (dll.IsEmpty()){
        cout << "The list is empty" << endl;
    }
    // Q 9
    cout << "Head element is: " << dll.GetHead() << endl;
    cout << "Tail element is: " << dll.GetTail() << endl;
    // Q 10 theory question
    cout << "Q10: The best implementation for the size problem is just adding a field in this DLL \n"
            "class to record the size of the list, and update this field whenever a change \n"
            "to the size of the list occurs." << endl;
    // Q 10
    cout << "Number of elements in the list is: " << dll.GetSize() << endl;
    // Q 11
    cout << "Max element is: " << dll.GetMax() << endl;
    cout << "Min element is: " << dll.GetMin() << endl ;
    // Q 11 theory question
    // print to the screen the written answer for the theory question
    cout << "Q11: The best implementation would be also add two dedicated fields to the class that record \n"
            "the max and the min in the list. Whenever an entry is added to or deleted from the lisy \n"
            "compare the changed value with these two fields to decide if the max and the min field should \n"
            "be update after this operation." << endl; 
    // Q 12 theory question
    // print to the screen the written answer for the theory question
    cout << "Q12: The default copy constructor is not reliable, as it only does a shallow copy of the object. \n"
            "Thus, the copy and the original are still tied together (by their shared memory address), \n"
            "and one change in one of them would also manifest in the other." << endl;
    // Q 12
    DLLStructure dll2 (dll);
    dll2.PrintDLL(); // the output should be: 2, 4, 7, 7, 11, 12, 13, 26
    return 0;
}