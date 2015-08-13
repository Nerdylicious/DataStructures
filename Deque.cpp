//Purpose: Implementing a deque (double-ended queue) using a doubly linked list
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

class Deque{
    public:
        Node *front;
        Node *back;
        void push_front(int);
        void push_back(int);
        int pop_front();
        int pop_back();
        int peek_front();
        int peek_back();
        void print();
        Deque();
        ~Deque();
};

Deque::Deque(){
    this->front = NULL;
    this->back = NULL;
}

Deque::~Deque(){
    cout << "Calling destructor" << endl;
    Node *curr = this->front;
    while(curr != NULL){
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
}

void Deque::push_front(int key){
    Node *new_node = new Node(key);
    if(this->front == NULL){
        this->front = new_node;
        this->back = new_node;
    }
    else{
        this->front->prev = new_node;
        new_node->next = this->front;
        this->front = new_node;
    }
}

void Deque::push_back(int key){
    Node *new_node = new Node(key);
    if(this->front == NULL){
        this->front = new_node;
        this->back = new_node;
    }
    else{
        this->back->next = new_node;
        new_node->prev = this->back;
        this->back = new_node;
    }
}

int Deque::pop_front(){
    int key = -99999;
    if(this->front != NULL){
        //if there is only one element in the deque
        if(this->front == this->back){
            key = this->front->key;
            delete this->front;
            this->front = NULL;
            this->back = NULL;
        }
        else{
            key = this->front->key;
            this->front = this->front->next;
            delete this->front->prev;
            this->front->prev = NULL;
        }
    }
    return key;
}

int Deque::pop_back(){
    int key = -99999;
    if(this->front != NULL){
        if(this->front == this->back){
            key = this->front->key;
            delete this->front;
            this->front = NULL;
            this->back = NULL;
        }
        else{
            key = this->back->key;
            this->back = this->back->prev;
            delete this->back->next;
            this->back->next = NULL;
        }
    }
    return key;
}

int Deque::peek_front(){
    int key = -99999;
    if(this->front != NULL){
        key = this->front->key;
    }
    return key;
}

int Deque::peek_back(){
    int key = -99999;
    if(this->back != NULL){
        key = this->back->key;
    }
    return key;
}

void Deque::print(){
    Node *curr = this->front;
    while(curr != NULL){
        cout << curr->key << " ";
        curr = curr->next;
    }
    cout << endl;
}

int main(){
    Deque *d = new Deque();
    d->push_front(1);
    d->push_back(2);
    d->push_back(3);
    d->push_front(0);
    d->pop_front();
    d->pop_back();
    d->print();
    delete d;
    return 0;
}
