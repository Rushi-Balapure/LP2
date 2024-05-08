#include <bits/stdc++.h>
#include <iostream>
using namespace std;
class Prims {
  vector<vector<pair<int, int>>> adj;
  int n;
  vector<bool> vis;
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      pq;
  vector<pair<int, int>> mst;

public:
  Prims() {
    int N, E;
    cout << "Vertices ,Edges ";
    cin >> N >> E;
    n = N;
    adj.resize(n);
    vis.resize(n, false);
    mst.resize(n, {-1, -1});
    int u, v, w;
    for (int i = 0; i < E; i++) {
      cout << "Start-End-Weight:";
      cin >> u >> v >> w;
      adj[u].push_back({w, v});
      adj[v].push_back({w, u});
    }
  }
  void prims(int Start) {
    pq.push({0, Start});
    int weight = 0;
    while (!pq.empty()) {
      int w = pq.top().first;
      int u = pq.top().second;
      pq.pop();
      if (vis[u])
        continue;
      vis[u] = true;
      weight += w;
      for (auto it : adj[u]) {
        if (!vis[it.second]) {
          pq.push({it.first, it.second});
          if (mst[it.second].first != -1 && mst[it.second].second < it.first) {
            continue;
          }
          mst[it.second] = {u, it.first};
        }
      }
    }
    cout << "MST";
    for (int i = 1; i < n; i++) {
      cout << i << " - " << mst[i].first << " = " << mst[i].second << endl;
    }
    cout << "Weight = " << weight;
  }
};

int main() {
  Prims p;
  p.prims(0);
}