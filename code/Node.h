
#ifndef NODE_H
#define NODE_H
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
class Node {
protected:
    bool visited = false;
    int i,j;
    float f,g,h;
    int Parent[2];
    string name,direction;
public:
    int x,y;
    string getName(){
        return name;
    }
    void DisplayHeuritics(){
        cout<<"F = "<<f<<" G = "<<g<<" h = " <<h<<endl;
    }
    void putG(float Gtemp){
        g = Gtemp;
    }
    float getG(){
        return g;
    }
    
    void PutIJ(pair<int,int> x){
        i = x.first;
        j = x.second;
    }
    pair<int,int> getParent(){
        pair <int,int> x =  make_pair(Parent[0],Parent[1]);

        return x;
    }
    pair<int,int> getIJ(){
        pair <int,int> x =  make_pair(i,j);

        return x;
    }
       bool PutHeuristics(float Gtemp,float Htemp,int i,int j){
        if(Gtemp  < this->g){
          //  cout<<"\nrun\n";
            this->Parent[0] = i;
            this->Parent[1] = j;
            this->g = Gtemp;this->h = Htemp;
            this->f = this->h + this->g;
           // cout<<"\nPutHeuristics =  "<<this->f<<" "<<this->g<<" "<<this->h;
            return true;
       }
       // cout<<"\nnot selected"<<Gtemp <<" >"<<this->g<<endl;
        return false;
    }
    float GetHeuristics(){
        return f;
    }
    int getX(){return x;}
    int getY(){return y;}
    Node();
    Node( vector<string> output);
    Node(const Node& orig);
    virtual ~Node();
    void putbool(bool b){
        visited = b;
    }
    bool getbool(){
        return visited;
    }
    void Display();
    char getColor(){
        return name[0];
    }
    int Direction(){
        if(direction == "S")
            return 1;
        else if(direction == "SE")
            return 2;
        else if(direction == "E")
            return 3;
        else if(direction == "NE")
            return 4;
        else if(direction == "N")
            return 5;
        else if(direction == "NW")
            return 6;
        else if(direction == "W")
            return 7;
        else if(direction == "SW")
            return 8;
        else 
            return 10;
    }
private:

};

#endif /* NODE_H */

