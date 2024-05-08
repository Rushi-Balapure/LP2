// Online C++ compiler to run C++ program online
#include <bits/stdc++.h>
using namespace std;
class graph
{
  public:
  int n;
  unordered_map<int,vector<int>> adjList;
  graph()
  {
      n=0;
  }
  void addedge(int i,int j)
  {
      adjList[i].push_back(j);
      adjList[j].push_back(i);
  }
  int find(map<int,vector<int>> &level,int id)
  {
      for(auto i:level)
      {
          for(auto j:i.second)
          {
              if(j==id)return i.first;
          }
      }
      return -1;
  }
  void input()
  {
      cout<<"Enter a number of vertices :- ";
        cin>>n;
        cout<<"Input"<<endl;
        for (int i=0;i<n;i++) 
        {
            int v1;
            cout<<"Enter a vertex :- ";
            cin>>v1;
            cout<<endl;
            int cnt;
            cout<<"Enter number of adjacent vertices :- ";
            cin>>cnt;
            cout<<endl;
            for (int j=0;j<cnt;j++) {
                int v2;
                cout<<"Enter a adjacent vertex:- ";
                cin>>v2;
                addedge(v1,v2);
                cout<<endl;
            }
        }
  }
  void bfs(int st)
  {
      vector<int> ans;
      map<int,int> visited;
      map<int,vector<int>> level;
      queue<int> q;
      visited[st]=1;
      level[0].push_back(st);
      q.push(st);
      while(!q.empty())
      {
          int t=q.front();
          q.pop();
          ans.push_back(t);
          for(auto j:adjList[t])
          {
              if(visited.find(j)==visited.end())
              {
                  visited[j]=1;
                  int val=find(level,t);
                  cout<<"Visited Node:-"<<j<<" at level:-"<<val+1<<endl;
                  level[val+1].push_back(j);
                  q.push(j);
              }
          }
      }
      cout<<"BFS"<<endl;
      for(auto i:ans)
      {
          cout<<i<<" ";
      }
      cout<<endl;
      cout<<"Level Wise:"<<endl;
      for(auto i:level)
      {
          cout<<"Level "<<i.first<<":-";
          for(auto j:i.second)cout<<j<<" ";
          cout<<endl;
      }
  }
  void dfs(int st,vector<int> &ans,map<int,vector<int>> &level,map<int,int> &visited)
  {
      visited[st]=1;
      ans.push_back(st);
      for(auto j:adjList[st])
      {
          if(visited.find(j)==visited.end())
          {
              visited[j]=1;
                  int val=find(level,st);
                  cout<<"Visited Node:-"<<j<<" at level:-"<<val+1<<endl;
                  level[val+1].push_back(j);
                  dfs(j,ans,level,visited);
          }
      }
  }
  void dfs_print(int st)
  {
      vector<int> ans;
      map<int,int> visited;
      map<int,vector<int>> level;
      level[0].push_back(st);
      dfs(st,ans,level,visited);
      cout<<"DFS"<<endl;
      for(auto i:ans)
      {
          cout<<i<<" ";
      }
      cout<<endl;
      cout<<"Level Wise:"<<endl;
      for(auto i:level)
      {
          cout<<"Level "<<i.first<<":-";
          for(auto j:i.second)cout<<j<<" ";
          cout<<endl;
      }
  }
  
};
int main() {
     graph g;

    int choice;

    char c='y';

    while (c=='y') {
        cout<<"========MENU==========\n1.Create\n2.BFS\n3.DFS\n4.Exit."<<endl;
        cout<<"Enter a choice :- ";
        cin>>choice;

        if (choice==1) {
            g.input();
        }

        else if (choice==2) {
            int st;
            cout<<"Enter a start node :- ";
            cin>>st;
            g.bfs(st);
        }

        else if (choice==3) {
            int st;
            cout<<"Enter a start node :- ";
            cin>>st;
            g.dfs_print(st);
        }

        else
        break;

        cout<<"Do you want to continue :- ";
        cin>>c;
    }

    return 0;

}
