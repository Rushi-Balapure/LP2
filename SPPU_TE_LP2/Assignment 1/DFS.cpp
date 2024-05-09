#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <map>
#include <stack>

using namespace std;

class Node{

    private :
        int data ;
        Node* down ;
        Node* next ; 

    public:
        Node(int d){
            this->data = d ;
            this->down = NULL ;
            this->next = NULL ;
        }

        friend class Graph ;

};

class Graph{
    private : 
        Node* headPtr = NULL ;

    public:
        void addNode(int d){
            Node* newNode = new Node(d) ;
            if(headPtr == NULL){
                headPtr = newNode ;
            }
            else{
                Node* currPtr = headPtr ;
                while(currPtr->down != NULL){
                    currPtr = currPtr->down ;
                }
                currPtr -> down = newNode ; 
            }
        }

        Node* searchNode(int d){
            Node* currPtr = headPtr ;
            while(currPtr != NULL){
                if(currPtr->data == d){
                    return currPtr ;
                }
                currPtr = currPtr->down ;
            }
            return currPtr ;
        }

        void addEdge(int fromNode , int toNode){
            Node* fromNodePtr = searchNode(fromNode) ;
            Node* toNodePtr = searchNode(toNode) ;

            if(fromNodePtr == NULL || toNodePtr == NULL){
                cout << "Please enter value under the bound values"<<endl ;
                return ;
            }
            Node* currPtr = fromNodePtr ;
            while(currPtr->next != NULL){
                currPtr = currPtr->next ;
            }
            currPtr->next = new Node(toNode) ; 
        }

        void printAdjLis(){
            Node* downPtr = headPtr ; 
            Node* nextPtr = NULL ;

            while(downPtr != NULL){
                cout << downPtr->data ; 
                nextPtr = downPtr->next ;
                while(nextPtr != NULL){
                    cout << " -> " <<nextPtr->data ; 
                    nextPtr = nextPtr->next ;
                }
                downPtr = downPtr->down ;
                cout << " -> NULL \n\n|\nV\n\n" ;
            }
            cout << "NULL"<<endl ;
        }

        int printInDeg(int d){
            Node* currPtr = searchNode(d) ;
            int count = 0 ;

            Node* downPtr = headPtr ;
            Node* nextPtr = NULL ;

            if(currPtr == NULL){
                cout << "The values not exists in the Nodes list" ;
                return -1 ;
            }
            while(downPtr != NULL){
                nextPtr = downPtr->next ;
                while(nextPtr != NULL){
                    if(nextPtr->data == d){
                        count ++ ;
                    }
                    nextPtr = nextPtr->next ;
                }
                downPtr = downPtr->down ;
            }
            return count ;
        }

        int printOutDeg(int d){
            Node* currPtr = searchNode(d) ;
            int count = 0 ; 

            if(currPtr == NULL){
                cout << "The values not exists in the Nodes list" ;
                return -1 ;
            }

            currPtr = currPtr->next ;
            while (currPtr != NULL){
                count ++ ;
                currPtr = currPtr->next ;
            }
            return count ;
        }

        void BFS(int d){
            queue<Node*> Q ; 
            map<int,int> visited ;

            Q.push(headPtr) ;
            visited[headPtr->data] = 1 ;

            while(!Q.empty()){
                Node* currPtr = Q.front() ; 
                int currLevel = visited[currPtr->data] ;
                Q.pop() ;

                if(currPtr->data == d){
                    cout << "Element Found - "<<d <<" at level - "<<currLevel<<endl;
                    return ;
                }else{
                    cout<<"Element Visited - "<<currPtr->data<< " at level - "<<currLevel <<endl ;
                }

                currPtr = currPtr->next ;
                while(currPtr != NULL){
                    if(visited[currPtr->data] == 0){
                        Q.push(searchNode(currPtr->data)) ;
                        visited[currPtr->data] =  currLevel + 1;
                    }
                    currPtr = currPtr->next ;
                }
            }
            cout << "Element Not Found"<<endl ;

        }

        void DFS(int d){
            stack<Node*> S ; 
            map<int,int> visited ;

            S.push(headPtr) ;
            visited[headPtr->data] = 1 ;

            while(!S.empty()){
                Node* currPtr = S.top() ; 
                int currLevel = visited[currPtr->data] ;
                S.pop() ;

                if(currPtr->data == d){
                    cout << "Element Found - "<<d <<" at level - "<<currLevel<<endl;
                    return ;
                }else{
                    cout<<"Element Visited - "<<currPtr->data<< " at level - "<<currLevel <<endl ;
                }

                currPtr = currPtr->next ;
                while(currPtr != NULL){
                    if(visited[currPtr->data] == 0){
                        S.push(searchNode(currPtr->data)) ;
                        visited[currPtr->data] =  currLevel + 1;
                    }
                    currPtr = currPtr->next ;
                }
            }
            cout << "Element Not Found"<<endl ;

        }


};

int main (){
    Graph G ; 
    G.addNode(1);
    G.addNode(2);
    G.addNode(3);
    G.addNode(4);
    G.addNode(5);
    G.addEdge(1,2);
    G.addEdge(1,4);
    G.addEdge(2,5);
    G.addEdge(5,3);
    G.printAdjLis();
    G.BFS(5);
    G.DFS(5);
    return 0 ;
}

