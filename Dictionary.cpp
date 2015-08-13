//Purpose: Reviewing Dictionary ADT implementation using a hash table as the underlying data structure
#include <iostream>
#include <string>
using namespace std;

//set number of buckets to a prime number
#define NUM_BUCKETS 13
#define ALPHABET_SIZE 128 //ascii characters only

class Node{
    public:
        string key;
        string value;
        Node *next;
        Node(string, string);
};

Node::Node(string key, string value){
    this->key = key;
    this->value = value;
    this->next = NULL;
}

class LinkedList{
    Node *head;
    public:
        LinkedList();
        LinkedList(string, string);
        ~LinkedList();
        string get_value(string);
        void set_value(string, string);
        void insert(string, string);
        void remove(string);
        void print();
};

LinkedList::LinkedList(){
    this->head = NULL;
}

LinkedList::LinkedList(string key, string value){
    Node *node = new Node(key, value);
    this->head = node;
}

LinkedList::~LinkedList(){
    Node *curr = this->head;
    while(curr != NULL){
        Node *next = curr->next;
        delete curr; 
        curr = next;
    }
}

string LinkedList::get_value(string key){
    string value = "";
    bool not_found = true;
    Node *curr = this->head;
    while(curr != NULL && not_found){
        if(curr->key == key){
            value = curr->value;
            not_found = false;
        }
        curr = curr->next;
    }
    return value;
}

void LinkedList::set_value(string key, string value){
    Node *curr = this->head;
    bool not_set = true;
    while(curr != NULL && not_set){
        if(curr->key == key){
            curr->value = value;
            not_set = false;
        }
        curr = curr->next;
    }
}

void LinkedList::insert(string key, string value){
    Node *node = new Node(key, value);
    node->next = this->head;
    this->head = node;
}

void LinkedList::remove(string key){
    //to do
}

void LinkedList::print(){
    Node *curr = this->head;
    while(curr != NULL){
        cout << "(" << curr->key << ", " << curr->value << ")" << endl;
        curr = curr->next;
    }
}

class Dictionary{
    //an array of LinkedList pointers
    LinkedList *list[NUM_BUCKETS];
    int get_bucket_index(string);
    unsigned long get_hashed_value(string);
    void insert_bucket(int, string, string);
    void replace(int, string, string);
    public:
        string key;
        string value;
        Dictionary();
        ~Dictionary();
        string get(string);
        void insert(string, string);
        void print();
};

Dictionary::Dictionary(){
    for(int i = 0; i < NUM_BUCKETS; i ++){
        this->list[i] = new LinkedList();
    }
}

Dictionary::~Dictionary(){
    for(int i = 0; i < NUM_BUCKETS; i ++){
        LinkedList *list = this->list[i];
        delete list;
        this->list[i] = NULL;
    }
}

//use Horner's Rule to evaluate a polynomial in linear time, O(n)
//this hash function is taken from the Algorithm Design Manual
//unsigned long at 32 bits can store a max value of around 4.2 billion
unsigned long Dictionary::get_hashed_value(string key){
    unsigned long sum = 0;
    for(unsigned int i = 0; i < key.length(); i ++){
        int val = key[i] - 'a';
        sum = (sum * ALPHABET_SIZE) + val;
    }
    return sum;
}

int Dictionary::get_bucket_index(string key){
    unsigned long hashed_value = get_hashed_value(key);
    int bucket_index = hashed_value % NUM_BUCKETS;
    return bucket_index;
}

string Dictionary::get(string key){
    string value = "";
    int bucket = get_bucket_index(key);
    if(bucket >= 0 && bucket < NUM_BUCKETS){
        LinkedList *list = this->list[bucket];
        value = list->get_value(key);
    }
    return value;
}

void Dictionary::insert_bucket(int bucket, string key, string value){
    if(bucket >= 0 && bucket < NUM_BUCKETS){
        LinkedList *list = this->list[bucket];
        list->insert(key, value);
    }
}

void Dictionary::replace(int bucket, string key, string value){
    if(bucket >= 0 && bucket < NUM_BUCKETS){
        LinkedList *list = this->list[bucket];
        list->set_value(key, value);
    }
}

void Dictionary::insert(string key, string value){
    string existing_value = get(key);
    int index = get_bucket_index(key);
    if(existing_value.empty()){
        insert_bucket(index, key, value);
    }
    else{
        //if the key is already contained in the hash table, then just replace it's value
        replace(index, key, value);
    }
}

void Dictionary::print(){
    for(int i = 0; i < NUM_BUCKETS; i ++){
        LinkedList *list = this->list[i];
        cout << "Bucket " << i << endl;
        list->print();
    }
}

int main(){
    Dictionary *dict = new Dictionary();
    dict->insert("hello", "world");
    dict->insert("goodbye", "planet");
    dict->insert("noodle", "oodle");
    dict->insert("goodbye", "jupiter");
    cout << "Dictionary Contents:" << endl;
    dict->print();
    cout << "Values:" << endl;
    cout << dict->get("noodle") << endl;
    cout << dict->get("goodbye") << endl;
    cout << dict->get("hello") << endl;
    delete dict;
    return 0;
}
