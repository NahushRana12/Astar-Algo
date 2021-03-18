
#include "Node.h"

Node::Node() {
    this->h = INT_MAX;this->g = INT_MAX;this->f = INT_MAX; this->visited = false;
}

Node::Node(vector<string> na){
    this->name = na[0];
    this->direction = na[1];
    this->x = stoi(na[2]);
    this->y = stoi(na[3]);
   this->visited = false;
    this->h = INT_MAX;this->g = INT_MAX;this->f = INT_MAX;
}
Node::Node(const Node& orig){
    this->name = orig.name;
    this->direction = orig.direction;
    this->x = orig.x;
    this->y = orig.y;
    this->h = orig.h;this->g = orig.g;this->f = orig.f;
    this->Parent[0] = orig.Parent[0];
    this->Parent[1] = orig.Parent[1];
    this->i = orig.i;
    this->j = orig.j;
    this->visited = orig.visited;
}
void Node::Display(){
    cout<<" "<<i<<j<<name<<" "<<direction<<" "<<x<<" "<<y;
}
Node::~Node() {};
