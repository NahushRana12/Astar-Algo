
#include <cstdlib>
#include <bits/stdc++.h> 
#include "Node.h"
using namespace std;

int Column,Row;
vector<vector<Node>> Maze;
ofstream myfile;
struct compare{
  public:
  bool operator()(Node& a,Node& b) // overloading both operators 
  {
      return a.GetHeuristics() > b.GetHeuristics() ;
   }
};
priority_queue<Node, std::vector<Node>, compare> OpenQueue;
float CalHeuristics(int i,int j){
    return ((float)
        sqrt((Maze[i][j].x - Maze[Column -1 ][Row -1 ].x) * (Maze[i][j].x -Maze[Column -1 ][Row -1 ].x)
            + (Maze[i][j].y - Maze[Column -1 ][Row -1 ].y) * (Maze[i][j].y -Maze[Column -1 ][Row -1 ].y)));
}
void DisplayOpenQueue(priority_queue<Node, vector<Node>, compare > gq)
{
    priority_queue<Node, vector<Node>, compare> g = gq;
    cout<<"\nNode at the end of possible path: ";
    while (!g.empty()) {
        Node temp = g.top();
        cout <<" "<<temp.getName()<<"("<< temp.GetHeuristics()<<")";
       // temp.DisplayHeuritics();
        g.pop();
    }
}
void DisplayMaze(){
    for(int i =0 ;i<Column;i++){
        for(int j = 0 ;j< Row; j++){
           // cout<<i<<j<<"==";
            Maze[i][j].Display();cout<<"----";
           // Maze[i][j].DisplayHeuritics();
        }
        cout<<endl;
    }    
}
vector<string> SplitbyRegex(string s,string Regex){
    vector<string> tokens;
    regex re(Regex);
    sregex_token_iterator begin(s.begin(), s.end(), re),end;
    copy(begin, end,back_inserter(tokens));
    return tokens;
}

void read()  //Read the input for a maze.txt file
{
    ifstream myReadFile;
    myReadFile.open("maze.txt");
    string output;
    int count = 0;
    vector<string> Nodeinput;
    if (myReadFile.is_open()) {
        myReadFile >> Column >> Row;
        getline(myReadFile,output);
        vector<Node> nodeRow;
        int i = 0;
        while (!myReadFile.eof() and count < Row * Column) {


            myReadFile >> output;
            Nodeinput = SplitbyRegex(output,"[\\w]+");
            //cout<<"+"<<output<<endl;
            Node temp(Nodeinput);
            temp.PutIJ(make_pair(i/Row,i% Row));
            i++;
            nodeRow.push_back(temp);
            
            //nodeRow[count % Row].Display();
            //cout<<count/Row<<" "<<count%Row<<endl;
            if(count %Row == Row - 1){
                Maze.push_back(nodeRow);
                nodeRow.clear();
            }
            count++;
        }    
    }
    myReadFile.close();
   // cout<<Column<<Row;
}
void EnterInputs(){                 //Enter input for the maze
    cout<<"\nEnter the starting Node in the maze\n";
    
}   

float ActualDis(int i,int j,int itemp,int jtemp){
    float temp = (float)sqrt(pow(Maze[i][j].getX() - Maze[itemp][jtemp].getX(), 2) +  
                pow(Maze[i][j].getY() - Maze[itemp][jtemp].getY(), 2) ); 
    return temp;
}
void VerticleSearch(int i,int j,int dir)//Search node in verticle direction
{
    char Color = Maze[i][j].getColor();
    if(Color == 'R')
        Color = 'B';
    else
        Color = 'R';
    int itemp = i,jtemp = j;
    if(dir == 1)
        itemp++;
    else
        itemp--;
    //cout<<itemp<<"bn";
    cout<<" \nPossible Notes ="; 
    while( itemp < Column and itemp >= 0){
        
           if(Color == Maze[itemp][jtemp].getColor()){
            cout<<" "<<Maze[itemp][jtemp].getName()<<" ";
            bool y = Maze[itemp][jtemp].PutHeuristics(Maze[i][j].getG() + ActualDis(i,j,itemp,jtemp), CalHeuristics(itemp,jtemp),i,j );
            if(y == true )
            OpenQueue.push(Maze[itemp][jtemp]);
           }
           else if(Maze[itemp][jtemp].getColor() == 'O'){
               bool y = Maze[itemp][jtemp].PutHeuristics(Maze[i][j].getG() + ActualDis(i,j,itemp,jtemp), CalHeuristics(itemp,jtemp),i,j );
                if(y == true ){
                   cout<<" "<<Maze[itemp][jtemp].getName()<<" ";
                  //  Maze[itemp][jtemp].DisplayHeuritics();
                OpenQueue.push(Maze[itemp][jtemp]);}
           }
        
        if(dir == 1)
        itemp++;
        else
        itemp--;
    }
    cout<<endl;
}
void HorizontalSearch(int i,int j,int dir)//Search node in Horizontal direction
{
    char Color = Maze[i][j].getColor();
    if(Color == 'R')
        Color = 'B';
    else
        Color = 'R';
    int itemp = i,jtemp = j;
    if(dir == 1)
        jtemp++;
    else
        jtemp--;
    cout<<" \nPossible Notes ="; 
    while( jtemp < Row and jtemp >= 0){
        if(Color == Maze[itemp][jtemp].getColor()){
             cout<<" "<<Maze[itemp][jtemp].getName()<<" ";
            bool y = Maze[itemp][jtemp].PutHeuristics(Maze[i][j].getG() + ActualDis(i,j,itemp,jtemp), CalHeuristics(itemp,jtemp),i,j );
             if(y == true )
            OpenQueue.push(Maze[itemp][jtemp]);
        }
        else if(Maze[itemp][jtemp].getColor() == 'O'){
               bool y = Maze[itemp][jtemp].PutHeuristics(Maze[i][j].getG() + ActualDis(i,j,itemp,jtemp), CalHeuristics(itemp,jtemp),i,j );
                if(y == true ){
                  cout<<" "<<Maze[itemp][jtemp].getName()<<" ";
                 //   Maze[itemp][jtemp].DisplayHeuritics();
                OpenQueue.push(Maze[itemp][jtemp]);}
           }
        if(dir == 1)
        jtemp++;
        else
        jtemp--;    
    }
    cout<<endl;
}
void NW_And_SE_Search(int i,int j,int dir)//Search node in Northwest and Southeast direction
{
    char Color = Maze[i][j].getColor();
    if(Color == 'R')
        Color = 'B';
    else
        Color = 'R';
     int itemp = i,jtemp = j;
     if(dir == 1){
            jtemp++;itemp++;
        }
        else{
        jtemp--;itemp--;
     }
     cout<<" \nPossible Notes ="; 
    while( jtemp < Row and jtemp >= 0 and itemp < Column and itemp >= 0){
        if(Color == Maze[itemp][jtemp].getColor()){
             cout<<" "<<Maze[itemp][jtemp].getName()<<" ";
            bool y = Maze[itemp][jtemp].PutHeuristics(Maze[i][j].getG() + ActualDis(i,j,itemp,jtemp), CalHeuristics(itemp,jtemp),i,j );
            if(y == true )
            OpenQueue.push(Maze[itemp][jtemp]);
        }
        else if(Maze[itemp][jtemp].getColor() == 'O'){
               bool y = Maze[itemp][jtemp].PutHeuristics(Maze[i][j].getG() + ActualDis(i,j,itemp,jtemp), CalHeuristics(itemp,jtemp),i,j );
                cout<<" "<<Maze[itemp][jtemp].getName()<<" ";
               if(y == true ){
                   // Maze[itemp][jtemp].DisplayHeuritics();
                OpenQueue.push(Maze[itemp][jtemp]);}
           }
        if(dir == 1){
            jtemp++;itemp++;
        }
        else{
        jtemp--;itemp--;
        }
    }
     cout<<endl;
}
void SW_And_NE_Search(int i,int j,int dir)//Search node in Southwest and Northeast direction
{
    char Color = Maze[i][j].getColor();
    if(Color == 'R')
        Color = 'B';
    else
        Color = 'R';
    int itemp = i,jtemp = j;
    if(dir == 1){
            jtemp++;itemp--;
    }
    else{
        jtemp--;itemp++;
    }
    cout<<" \nPossible Notes ="; 
    while( jtemp < Row and jtemp >= 0 and itemp < Column and itemp >= 0){
        if(Color == Maze[itemp][jtemp].getColor()){
             cout<<" "<<Maze[itemp][jtemp].getName()<<" ";
            bool y = Maze[itemp][jtemp].PutHeuristics(Maze[i][j].getG() + ActualDis(i,j,itemp,jtemp), CalHeuristics(itemp,jtemp),i,j );
            if(y == true)
            OpenQueue.push(Maze[itemp][jtemp]);
        }else if(Maze[itemp][jtemp].getColor() == 'O'){
               bool y = Maze[itemp][jtemp].PutHeuristics(Maze[i][j].getG() + ActualDis(i,j,itemp,jtemp), CalHeuristics(itemp,jtemp),i,j );
                cout<<" "<<Maze[itemp][jtemp].getName()<<" "; 
               if(y == true ){
                   // Maze[itemp][jtemp].DisplayHeuritics();
                OpenQueue.push(Maze[itemp][jtemp]);}
           }
        if(dir == 1){
            jtemp++;itemp--;
        }
        else{
        jtemp--;itemp++;
        }
    }
    cout<<endl;
}

void traceBack(int i,int j){
    stack<string> dis;
    while(i != -1){
        string tempstr = "";
        Node temp = Maze[i][j];
        //temp.DisplayHeuritics();
        pair<int,int> x = temp.getParent();
        int tempi = i;
        int tempj = j;
        i = x.first;
        j = x.second;
       
        if(i != -1){
            tempstr = Maze[i][j].getName() + " to " + temp.getName() +" distance = " + to_string(ActualDis(i,j,tempi,tempj)); 
            dis.push(tempstr);
        }
        
    }
     cout<<"\n********************************************************";
    while (!dis.empty()) 
    { 
        cout <<endl << dis.top(); 
        dis.pop(); 
    } 
    cout<<"\n********************************************************\n";
        cout<<"total distance = "<<to_string(Maze[Column -1 ][Row -1].getG()); 


}
void Asearch(int i,int j,int actual){              //A* algorthim
    
    
    if( i < 0 and i >= Column and j < 0 and j >= Row){
        return;
    }
     //Maze[i][j].putbool(true);
    Maze[i][j].PutHeuristics(0,CalHeuristics(i,j),-1,-1);
    OpenQueue.push(Maze[i][j]);
    while(!OpenQueue.empty()){
        cout<<"\n********************************************************\n";
        Node temp = OpenQueue.top();
        OpenQueue.pop();
        if(temp.getbool() == true){
              continue; 
        }
        
        pair<int,int> x = temp.getIJ();
        i = x.first;
        j = x.second;
        Maze[i][j].putbool(true);
        if( i == Column -1 and j == Row -1){
            break;
         }   
        int dir = temp.Direction();
         cout<<"Selected node = "<<Maze[i][j].getName()<<endl;
        switch(dir){
        case 1 :
            VerticleSearch(i,j,1);
        break;
        case 2 :
            NW_And_SE_Search(i,j,1);
        break;
        case 3 :
            HorizontalSearch(i,j,1);
        break;
        case 4 :
            SW_And_NE_Search(i,j,1);
        break;
        case 5 :
            VerticleSearch(i,j,-1);
        break;
        case 6 :
            NW_And_SE_Search(i,j,-1);
        break;
        case 7 :
            HorizontalSearch(i,j,-1);
        break;
        case 8 :
            SW_And_NE_Search(i,j,-1);
        break;
        Default:
            cout<<"Error";
        }
    
    
  DisplayOpenQueue(OpenQueue);
  cout<<"\n********************************************************\n";
   }
   
   
}
   
int main(int argc, char** argv) {
   
    read();
   
    //EnterInputs();
    Asearch(0,0,0);DisplayMaze();
     traceBack(7,7);
    return 0;
}


