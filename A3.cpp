#include <bits/stdc++.h>
using namespace std;
int V=0;
map<string,int> city_name;
int minKey(vector<int> key, vector<bool> mstSet)
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
 
    return min_index;
}
 
// A utility function to print the
// constructed MST stored in parent[]
void printMST(vector<int> parent, vector<vector<int>> graph)
{
    cout << "Edge \tWeight\n";
    for (int i = 1; i < V; i++)
        cout << parent[i] << " - " << i << " \t"
             << graph[i][parent[i]] << " \n";
}
 
// Function to construct and print MST for
// a graph represented using adjacency
// matrix representation
void primMST(vector<vector<int>> graph)
{
    // Array to store constructed MST
    vector<int> parent(V);
 
    // Key values used topick minimum weight edge in cut
    vector<int> key(V);
 
    // To represent set of vertices included in MST
    vector<bool> mstSet(V);
    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first
    // vertex.
    key[0] = 0;
   
    // First node is always root of MST
    parent[0] = -1;
 
    // The MST will have V vertices
    for (int count = 0; count < V - 1; count++) {
         
        // Pick the minimum key vertex from the
        // set of vertices not yet included in MST
        int u = minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of
        // the adjacent vertices of the picked vertex.
        // Consider only those vertices which are not
        // yet included in MST
        for (int v = 0; v < V; v++)
 
            // graph[u][v] is non zero only for adjacent
            // vertices of m mstSet[v] is false for vertices
            // not yet included in MST Update the key only
            // if graph[u][v] is smaller than key[v]
            if (graph[u][v] && mstSet[v] == false
                && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
 
    // Print the constructed MST
    printMST(parent, graph);
}
 
// Driver's code
int main()
{
    cout<<"Welcome to traveling saleman Problem"<<endl;
    cout<<"Enter the number of cities:";
    cin>>V;
    vector<vector<int>> graph(V,vector<int>(V,0));
    cout<<"Enter the city names:"<<endl;
    for(int i=0;i<V;i++)
    {
        string temp;
        cout<<"Enter City"<<i+1<<":";
        cin>>temp;
        city_name[temp]=i;
    }
    int e;
    cout<<"Enter the number of edges:";
    cin>>e;
    for(int i=0;i<e;i++)
    {
        cout<<"Edge "<<i+1<<endl;
        string c1,c2;
        int wt;
        cout<<"Enter City 1:";
        cin>>c1;
        cout<<"Enter City 2:";
        cin>>c2;
        cout<<"Enter the Travel Cost:";
        cin>>wt;
        graph[city_name[c1]][city_name[c2]]=wt;
        graph[city_name[c2]][city_name[c1]]=wt;
    }
    primMST(graph);
 
    return 0;
}
 