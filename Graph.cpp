//Purpose: Reviewing graph implementation using an adjacency list (good for sparse and most graph problems)
//the other alternative is an adjacency matrix which is good for dense graphs
#include <iostream>
using namespace std;

#define MAXV 1000 //maximum number of vertices

class Node{
    public:
        int key;
        Node *next;
        Node(int);
};

Node::Node(int key){
    this->key = key;
    this->next = NULL;
}

class Queue{
    Node *head;
    public:
        Queue();
        Queue(int);
        ~Queue();
        void enqueue(int);
        int dequeue();
        bool empty();
        void print();
};

Queue::Queue(){
    this->head = NULL;
}

Queue::Queue(int key){
    Node *node = new Node(key);
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

void Queue::enqueue(int key){
    Node *node = new Node(key);
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

int Queue::dequeue(){
    int value = -1;
    if(this->head != NULL){
        value = this->head->key;
        Node *temp = this->head;
        this->head = this->head->next;
        delete temp;
    }
    return value;
}

bool Queue::empty(){
    bool result = false;
    if(this->head == NULL){
        result = true;
    }
    return result;
}

void Queue::print(){
    Node *curr = this->head;
    while(curr != NULL){
        cout << curr->key << endl;
        curr = curr->next;
    }
}

class EdgeNode{
    public:
        int key;
        int weight;
        EdgeNode *next;
        EdgeNode(int);
        EdgeNode(int, int);
};

EdgeNode::EdgeNode(int key){
    this->key = key;
    this->weight = 0;
    this->next = NULL;
}

EdgeNode::EdgeNode(int key, int weight){
    this->key = key;
    this->weight = weight;
    this->next = NULL;
}

class Graph{

    EdgeNode *edges[MAXV + 1];
    int degree[MAXV + 1];
    int nedges;
    bool directed;

    //data members for graph traversal
    bool processed[MAXV + 1]; //which vertices have been processed
    bool discovered[MAXV + 1]; //which vertices have been found
    int parent[MAXV + 1]; //discovery relation

    //function members for graph traversal
    void initialize_search();
    void process_vertex_early(int);
    void process_vertex_late(int);
    void process_edge(int, int);
    
    public:
        Graph(bool);
        ~Graph();
        void insert_edge(int, int, bool);
        void print_graph();
        void breadth_first_search(int);
        void depth_first_search(int);
        void find_path(int, int);
};

Graph::Graph(bool directed){
    
    this->nedges = 0;
    this->directed = directed;

    for(int i = 0; i <= MAXV; i ++){
        this->edges[i] = NULL;
        this->degree[i] = 0;
    }
}

Graph::~Graph(){
    for(int i = 0; i <= MAXV; i ++){
        EdgeNode *e = this->edges[i];
        while(e != NULL){
            EdgeNode *temp = e;
            e = e->next;
            delete temp;
            temp = NULL;
        }
    }
}

void Graph::insert_edge(int x, int y, bool directed){
    
    //create new edge
    EdgeNode *edge = new EdgeNode(y);
    //insert new edge as the head of the list
    edge->next = this->edges[x];
    this->edges[x] = edge;
    this->degree[x] ++;

    if(!directed){
        insert_edge(y, x, true);
    }
    else{
        this->nedges ++;
    }
}

void Graph::print_graph(){
    //interate through vertices
    for(int v; v <= MAXV; v ++){
        if(this->degree[v] > 0){
            //interate through edges of the vertex
            cout << "Vertex " << v << endl;
            EdgeNode *e = this->edges[v];
            while(e != NULL){
                cout << e->key << endl;
                e = e->next;
            }
        }
    }
}

void Graph::process_vertex_early(int v){
    cout << "Processed vertex " << v << endl;
}

void Graph::process_vertex_late(int v){
}

void Graph::process_edge(int x, int y){
    cout << "Processed edge (" << x << "," << y << ")" << endl;
}

void Graph::initialize_search(){
    for(int i = 0; i <= MAXV; i ++){
        this->processed[i] = false;
        this->discovered[i] = false;
        this->parent[i] = -1;
    }
}

void Graph::breadth_first_search(int start_vertex){

    initialize_search();
    Queue *queue = new Queue(); //queue of vertices still left to visit
    int current_v;  //current vertex
    EdgeNode *p; //temporary pointer

    queue->enqueue(start_vertex);
    this->discovered[start_vertex] = true;

    while(!queue->empty()){
        current_v = queue->dequeue();
        process_vertex_early(current_v);
        p = this->edges[current_v];
        while(p != NULL){
            int neighbor_v = p->key;
            if(!this->discovered[neighbor_v]){
                //add to Q and set to discovered
                queue->enqueue(neighbor_v);
                this->discovered[neighbor_v] = true;
                this->parent[neighbor_v] = current_v;
            }
            if(!this->processed[neighbor_v] || this->directed){
                process_edge(current_v, neighbor_v);
            }
            p = p->next;
        }
        this->processed[current_v] = true;
    }
    delete queue;
    initialize_search();
}

//DFS is similar to BFS with the difference being the order in which vertices are explored
//main difference is that DFS uses a stack instead of a queue
//DFS is done recursively to make use of the implicit stack from recursion
//as opposed to an iterative DFS with an explicit stack
void Graph::depth_first_search(int start_vertex){

    int current_v = start_vertex;
    this->discovered[current_v] = true;
    EdgeNode *p = this->edges[current_v];
    process_vertex_early(current_v);

    while(p != NULL){
        int neighbor_v = p->key;
        if(!this->discovered[neighbor_v]){
            //this->discovered[neighbor_v] = true;
            this->parent[neighbor_v] = current_v;
            process_edge(current_v, neighbor_v);
            depth_first_search(neighbor_v);
        }
        //2nd case is needed because 1st case isn't enough to visit all edges (because 1st case sets all neighbors
        //to discovered which excludes some visits to edges later)
        else if(((!this->processed[neighbor_v]) && (this->parent[current_v] != neighbor_v)) || (this->directed)){
            process_edge(current_v, neighbor_v);
        }
        p = p->next;
    }
    this->processed[current_v] = true;
}

/*
void Graph::find_path(int start, int end){
    cout << end << endl;
    if(start != end){
        find_path(start, this->parent[end]);
    }
}
*/

int main(){
    Graph *g = new Graph(false);
    g->insert_edge(1, 2, false);
    g->insert_edge(1, 5, false);
    g->insert_edge(1, 6, false);
    g->insert_edge(2, 5, false);
    g->insert_edge(2, 3, false);
    g->insert_edge(5, 4, false);
    g->insert_edge(3, 4, false);
    g->print_graph();
    //g->breadth_first_search(1);
    g->depth_first_search(1);
    delete g;
    return 0;
}
