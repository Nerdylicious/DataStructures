//Purpose: Implementing a Doubly Linked List
#include <iostream>
using namespace std;

class Node{
    public:
        int key;
        Node *prev;
        Node *next;
        Node(int);
};

Node::Node(int key){
    this->key = key;
    this->prev = NULL;
    this->next = NULL;
}

class DoublyLinkedList{
    public:
        Node *head;
        Node *tail;
        DoublyLinkedList();
        ~DoublyLinkedList();
        void insert(int);
        void insert_ordered(int);
        void remove(int);
        void traverse_forward();
        void traverse_backward();
};

DoublyLinkedList::DoublyLinkedList(){
    this->head = NULL;
    this->tail = NULL;
}

DoublyLinkedList::~DoublyLinkedList(){
    Node *curr = this->head;
    while(curr != NULL){
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
}

void DoublyLinkedList::insert(int key){
    Node *new_node = new Node(key);
    if(this->head == NULL){
        this->head = new_node;
        this->tail = new_node;
    }
    else{
        new_node->next = this->head;
        this->head->prev = new_node;
        this->head = new_node;
    }
}

void DoublyLinkedList::insert_ordered(int key){
    Node *new_node = new Node(key);
    if(this->head == NULL){                     //if list is empty
        this->head = new_node;
        this->tail = new_node;
    }
    //implement all cases, then cut down any duplicate code
    //coding all cases gives extra assurance that we have
    //not missed any cases, then we can optimize further
    /*
    else if(this->head == this->tail){
        Node *first = this->head;
        if(first->key >= key){
            new_node->next = first;
            first->prev = new_node;
            this->head = new_node;
        }
        else{
            new_node->prev = first;
            first->next = new_node;
            this->tail = new_node;
        }
    }
    */
    else{
        bool found_greater = false;
        Node *curr = this->head;
        Node *target = NULL;
        while(curr != NULL && !found_greater){
            if(curr->key >= key){
                found_greater = true;
                target = curr;
            }
            curr = curr->next;
        }
        if(found_greater){
            if(this->head == target){           //insert at beginning of the list
                new_node->next = target;
                target->prev = new_node;
                this->head = new_node; 
            }
            /*
            else if(this->tail == target){
                new_node->next = target;
                new_node->prev = target->prev;
                target->prev->next = new_node;
                target->prev = new_node;
            }
            */
            else{                               //insert in middle of the list
                new_node->next = target;
                new_node->prev = target->prev;
                target->prev->next = new_node;
                target->prev = new_node;
            }
        }
        else{                                   //insert at end of the list
            new_node->prev = this->tail;
            this->tail->next = new_node;
            this->tail = new_node;
        }
    }
}

void DoublyLinkedList::remove(int key){
    if(this->head != NULL){                     //verify that list is not empty
        if(this->head == this->tail){           //if list has a single node
            Node *temp = this->head;
            this->head = NULL;
            this->tail = NULL;
            delete temp;
        }
        else if(this->head->key == key){        //if the node to delete is the head node
            Node *temp = this->head;
            this->head = this->head->next;
            this->head->prev = NULL;
            delete temp;
        }
        else if(this->tail->key == key){        //if the node to delete is a tail node
            Node *temp = this->tail;
            this->tail->prev->next = NULL;
            this->tail = this->tail->prev;
            delete temp;
        }
        else{                                   //if the node to delete is in the middle of the list
            bool found = false;
            Node *curr = this->head;
            Node *target = NULL;
            while(curr != NULL && !found){
                if(curr->key == key){
                    found = true;
                    target = curr;
                }
                curr = curr->next;
            }
            if(found){
                target->prev->next = target->next;
                target->next->prev = target->prev;
                delete target;
            }
        }
    }
}

void DoublyLinkedList::traverse_forward(){
    Node *curr = this->head;
    while(curr != NULL){
        cout << curr->key << " ";
        curr = curr->next;
    }
    cout << endl;
}

void DoublyLinkedList::traverse_backward(){
    Node *curr = this->tail;
    while(curr != NULL){
        cout << curr->key << " ";
        curr = curr->prev;
    }
    cout << endl;
}

int main(){
    DoublyLinkedList *list = new DoublyLinkedList();
    list->insert_ordered(10);
    list->insert_ordered(1);
    list->insert_ordered(99);
    list->insert_ordered(5);
    list->insert_ordered(2);
    list->insert_ordered(98);
    list->insert_ordered(95);
    list->insert_ordered(-95);
    list->traverse_forward();
    delete list;
    return 0;
}
