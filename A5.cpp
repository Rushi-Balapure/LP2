#include<bits/stdc++.h>
using namespace std;
struct Edge{
    int src,dest,wt;
};
int findParent(int vertex,vectr<int> &parent)
{
    return (parent[vertex]==-1)?vertex:findParent(parent[vertex],parent)
}
void unionSets(int x,int y,vector<int> &parent)
{
    parent[x]=y;
}

void kruskalMST(vector<Edge> &edges,int V)
{
    sort(edges.begin(),edges.end(),[](const Edge& a,const Edge& b){
        return a.wt<b.wt;
    });
    vector<int> parent(V,-1);
    vector<Edge> result;
    int edgeCnt=0;
    for( auto edge:edges)
    {
        int x=findParent(edge.scr,parent);
        int y=findParent(edge.dest,parent);
        if(x!=y)
        {
            result.push_back(edge);
            unionSet(x,y,parent);
            edgeCnt++;
        }
        if(edgeCnt==V-1)break;
    }
    cout << "Edges in MST:" << endl;
    for (const Edge& edge : result)
        cout << edge.src << " - " << edge.dest << endl;
}
int main()
{
     int V, E;
    cin >> V >> E;

    vector<Edge> edges(E);
    for (int i = 0; i < E; ++i)
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;

    kruskalMST(edges, V);

    return 0;
}
