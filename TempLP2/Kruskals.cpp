#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Kruskal{
  priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>> ,greater<tuple<int,int,int>>>pq;
  int n;
  vector<int>parent,rank;
public:
  Kruskal(){
    int N,E;
    cout<<"N E: ";
    cin>>N>>E;
    n=N;
    
    parent.resize(n,-1);
    rank.resize(n,1);
    
    for(int i=0;i<E;i++){
      int u,v,w;
      cout<<"u v w: ";
      cin>>u>>v>>w;
      pq.push({w,u,v});
    }
  }

  int find(int i){
    if(parent[i]==-1) return i;
    return parent[i]=find(parent[i]);
  }

  void unite(int u,int v){
    int s1 = find(u);
    int s2 = find(v);

    if(s1!=s2){
      if(rank[s1]<rank[s2]){
        parent[s1]=s2;
      }
      else if(rank[s1]>rank[s2]){
        parent[s2]=s1;
      }
      else{
        parent[s2]=s1;
        rank[s1]++;
      }
    }
  }

  void kruskal(){
    int weight=0;
    cout<<"MST:\n";
    while(!pq.empty()){
      int w=get<0>(pq.top());
      int u=get<1>(pq.top());
      int v=get<2>(pq.top());
      pq.pop();

      if(find(u)!=find(v)){
        unite(u,v);
        weight+=w;
        cout<<u<<" - "<<v<<" = "<<w<<"\n";
      }
    }
    cout<<"Weight: "<<weight;
  }
};


int main() {
  Kruskal k;
  k.kruskal();
}