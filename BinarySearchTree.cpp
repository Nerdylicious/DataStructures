//Purpose: Reviewing BST implementation in C++
#include <iostream>
using namespace std;

class TreeNode{
    public:
        TreeNode(int);
        int key;
        TreeNode *left;
        TreeNode *right;
};

TreeNode::TreeNode(int key){
    this->key = key;
    this->left = NULL;
    this->right = NULL;
}

class Node{
    public:
        TreeNode *tnode;
        Node *next;
        Node(TreeNode *);
};

Node::Node(TreeNode *tnode){
    this->tnode = tnode;
    this->next = NULL;
}

class Queue{
    Node *head;
    public:
        Queue();
        Queue(TreeNode *);
        ~Queue();
        void enqueue(TreeNode *);
        TreeNode *dequeue();
        bool empty();
        void print();
};

Queue::Queue(){
    this->head = NULL;
}

Queue::Queue(TreeNode *tnode){
    Node *node = new Node(tnode);
    this->head = node;
}

Queue::~Queue(){
    Node *curr = this->head;
    while(curr != NULL){
        Node *temp = curr;
        curr = curr->next;
        delete temp;
        temp = NULL;
    }
}

void Queue::enqueue(TreeNode *tnode){
    Node *node = new Node(tnode);
    if(this->head == NULL){
        this->head = node;
    }
    else{
        Node *curr = this->head;
        while(curr->next != NULL){
            curr = curr->next;
        }
        curr->next = node;
    }
}

TreeNode *Queue::dequeue(){
    TreeNode *tnode = NULL;
    if(this->head != NULL){
        tnode = this->head->tnode;
        Node *temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
    return tnode;
}

bool Queue::empty(){
    bool result = false;
    if(this->head == NULL){
        result = true;
    }
    return result;
}

class BinaryTree{
    TreeNode *root;
    bool search_tree(TreeNode *, int);
    void insert_tree(TreeNode *, int);
    void in_order(TreeNode *);
    void level_order(TreeNode *);
    void clean_up(TreeNode *);
    public:
        BinaryTree();        
        BinaryTree(int);
        ~BinaryTree();
        //helper functions
        bool search(int);
        void insert(int);
        void traverse_in_order();
        void traverse_level_order();
};

BinaryTree::BinaryTree(){
    this->root = NULL;
}

BinaryTree::BinaryTree(int key){
    this->root = new TreeNode(key);
}

void BinaryTree::clean_up(TreeNode *node){
    //need to traverse post-order for cleaning up (deallocate child nodes first)
    if(node != NULL){
        clean_up(node->left);
        clean_up(node->right);
        delete node;
    }
}

BinaryTree::~BinaryTree(){
    //de-allocate all nodes
    clean_up(this->root);
}

bool BinaryTree::search(int key){
    return this->search_tree(this->root, key);
}

//assumes bst ordering
bool BinaryTree::search_tree(TreeNode *node, int key){
    if(node == NULL){
        return false;
    }
    else if(key < node->key){
        return this->search_tree(node->left, key);
    }
    else if(key > node->key){
        return this->search_tree(node->right, key);
    }
    else{ //key == node->key
        return true;
    }
}

void BinaryTree::insert(int key){
    this->insert_tree(this->root, key);
}

void BinaryTree::insert_tree(TreeNode *node, int key){
    if(node == NULL){
        //node = new TreeNode(key); //assigning to node doesn't work
        this->root = new TreeNode(key);
    }
    else if(key < node->key && node->left == NULL){
        //allocate new node
        node->left = new TreeNode(key);
    }
    else if(key >= node->key && node->right == NULL){
        node->right = new TreeNode(key);
    }
    else{
        if(key < node->key){
            this->insert_tree(node->left, key);
        }
        else{
            this->insert_tree(node->right, key);
        }
    }
}

void BinaryTree::traverse_in_order(){
    this->in_order(this->root);
}

void BinaryTree::in_order(TreeNode *node){
    if(node != NULL){
        in_order(node->left);
        cout << node->key << endl;
        in_order(node->right);
    }
}

void BinaryTree::traverse_level_order(){
    this->level_order(this->root);
}

void BinaryTree::level_order(TreeNode *root){

    Queue *queue = new Queue();
    TreeNode *current_v;
    queue->enqueue(root);

    while(!queue->empty()){
        current_v = queue->dequeue();
        cout << current_v->key << endl;
        if(current_v->left != NULL){
            queue->enqueue(current_v->left);
        }
        if(current_v->right != NULL){
            queue->enqueue(current_v->right);
        }
    }
    delete queue;
}

int main(){
    BinaryTree *bst = new BinaryTree();
    bst->insert(10);
    bst->insert(6);
    bst->insert(1);
    bst->insert(8);
    bst->insert(7);
    bst->insert(9);
    bst->insert(15);
    bst->insert(13);
    bst->insert(11);
    bst->insert(99);
    bst->traverse_level_order();
    delete bst;
    return 0;
}
