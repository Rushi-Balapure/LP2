#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <map>
#include <limits>

using namespace std;

class Edge {
    public: 
        int dest;
        int weight;  

        Edge(int e, int w){
            dest = e ;
            weight = w ;
        }      
};

class Vertex {
    public : 
    int id;
    vector<Edge> neighbors;

        Vertex(int v){
            id = v ;
        }
        bool operator==(const Vertex& other) const {
            return id == other.id;
        }

    friend class graph ;
};

class graph{
    vector<Vertex> vertices ; 
    public: 
        int findVertex(int v){
            for (int i = 0 ; i < vertices.size() ; i ++){
                if(vertices[i].id == v){
                    return i;
                }
            }
        }

        void AddVertex(int v){
            vertices.push_back(Vertex(v));
        }
        
        void AddEdge(int s,int e, int w){
            s = findVertex(s);
            vertices[s].neighbors.push_back(Edge(e,w));
        }

        vector<pair<Vertex,int> > DijkstraSingleSourceShortestPath (int sourceId){
            vector<pair<Vertex,int> > distances ; 
            map<Vertex,bool> visited ;
            queue<Vertex> toExplore ;

            for(int i = 0 ; i < vertices.size() ; i ++){
                if(vertices[i].id != sourceId){
                    distances.push_back(make_pair(vertices[i],99999999));
                    visited[vertices[i]] = false ; 
                }
                else{
                    distances.push_back(make_pair(vertices[i],0));
                    visited[vertices[i]] = true ; 
                    toExplore.push(vertices[i]) ;
                }
            }

            while(!toExplore.empty()){
                Vertex currVertex = toExplore.front();
                toExplore.pop() ;

                for (Edge edge : currVertex.neighbors ){
                    if(visited[vertices[findVertex(edge.dest)]] == false ){
                        visited[vertices[findVertex(edge.dest)]] = true ;
                        toExplore.push(vertices[findVertex(edge.dest)]) ;
                    }
                    distances[findVertex(edge.dest)].second = min(distances[findVertex(edge.dest)].second,(distances[findVertex(currVertex.id)].second + edge.weight));
                }
            }
            return distances ;
        }

};

int main() {
// Create a graph object
    graph g;

    // Add some vertices to the graph
    g.AddVertex(1);
    g.AddVertex(2);
    g.AddVertex(3);
    g.AddVertex(4);
    g.AddVertex(5);

    // Add some edges to the graph
    g.AddEdge(1, 2, 5);  // Edge from vertex 1 to vertex 2 with weight 5
    g.AddEdge(1, 3, 10); // Edge from vertex 1 to vertex 3 with weight 10
    g.AddEdge(2, 3, 3);  // Edge from vertex 2 to vertex 3 with weight 3
    g.AddEdge(3, 4, 7);  // Edge from vertex 3 to vertex 4 with weight 7
    g.AddEdge(4, 5, 2);  // Edge from vertex 4 to vertex 5 with weight 2

    // Find the shortest paths from a source vertex (e.g., vertex 1)
    int sourceId = 1;
    vector<pair<Vertex, int> > shortestPaths = g.DijkstraSingleSourceShortestPath(sourceId);

    // Print the shortest paths
    cout << "Shortest paths from source vertex " << sourceId << ":" << endl;
    // for (const auto& pair : shortestPaths) {
    //     cout << "Vertex " << pair.first.id << ": " << pair.second << endl;
    // }
    return 0;
}
