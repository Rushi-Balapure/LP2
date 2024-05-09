
#include <bits/stdc++.h>>

int minimumSpanningTree(vector<vector<int>>& edges, int n)
{
  vector<vector<pair<int, int>>> adj(n);
  for(auto edge : edges){
    int u = edge[0];
    int v = edge[1];
    int w = edge[2];

    adj[u].push_back({v,w});
    adj[v].push_back({u,w});
  }

  vector<bool> visited(n, false);
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
  int sum = 0;

  pq.push({0,0});

  while(!pq.empty()){
    pair<int, int> curr = pq.top();
    pq.pop();

    if(visited[curr.second]){
      continue;
    }

    visited[curr.second] = true;
    sum += curr.first;

    for(auto node : adj[curr.second]){
      if(!visited[node.first]){
        pq.push({node.second, node.first});
      }
    }
  }

  return sum;
}