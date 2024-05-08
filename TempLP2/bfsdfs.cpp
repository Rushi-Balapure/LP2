#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class graph {
  vector<vector<int>> adj;
  int v, e;
  map<int, vector<int>> dfslevel;
  map<int, vector<int>> bfslevel;

public:
  graph(int v, int e) {
    this->v = v;
    this->e = e;
    adj.resize(v);
    cout << "Enter the edges: " << endl;
    for (int i = 0; i < e; i++) {
      int x, y;
      cout << "start - end : ";
      cin >> x >> y;
      adj[x].push_back(y);
      adj[y].push_back(x);
    }
  }

  void dfs(int src, vector<bool> &visited, int lev) {
    visited[src] = true;
    dfslevel[lev].push_back(src);
    cout << src << " ";
    for (auto i : adj[src]) {
      if (!visited[i]) {
        dfs(i, visited, lev + 1);
      }
    }
  }

  void bfs(queue<pair<int, int>> &q, vector<bool> &visited) {
    if (q.empty())
      return;

    int src = q.front().first;
    int lev = q.front().second;
    q.pop();
    bfslevel[lev].push_back(src);
    cout << src << " ";
    for (auto i : adj[src]) {
      if (!visited[i]) {
        visited[i] = true;
        q.push({i, lev + 1});
      }
    }
    bfs(q, visited);
  }

  void printdfs() {
    for (auto level : dfslevel) {
      cout << endl;
      cout << "Level " << level.first << " :";
      for (auto i : level.second) {
        cout << i << " ";
      }
    }
  }

  void printbfs() {
    for (auto level : bfslevel) {
      cout << endl;
      cout << "Level " << level.first << " :";
      for (auto i : level.second) {
        cout << i << " ";
      }
    }
  }
};

int main() {
  cout << "\nEnter the number of vertices and edges: ";
  int n, e;
  cin >> n >> e;
  graph g(n, e);
  vector<bool> visdfs(n, false);
  g.dfs(0, visdfs, 0);
  g.printdfs();

  queue<pair<int, int>> q;
  q.push({0, 0});
  vector<bool> visbfs(n, false);
  visbfs[0] = true;
  g.bfs(q, visbfs);
  g.printbfs();
}