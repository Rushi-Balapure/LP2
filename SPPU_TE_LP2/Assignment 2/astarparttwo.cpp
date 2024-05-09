#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,pair<string,vector<vector<int>>>> P;

int match(vector<vector<int>>& inter,vector<vector<int>>& grid){
    int ans=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(inter[i][j]==0){
                continue;
            }
            else if(inter[i][j]!=grid[i][j]){
                ans+=1;
            }
        }
    }
    return ans;
}
vector<vector<int>> moveup(vector<vector<int>>& grid,int i,int j){
    if(i<1){
        return {{-1}};
    }
    vector<vector<int>> temp=grid;
    swap(temp[i][j],temp[i-1][j]);
    return temp;
}
vector<vector<int>> movedown(vector<vector<int>>& grid,int i,int j){
    if(i>1){
        return {{-1}};
    }
    vector<vector<int>> temp=grid;
    swap(temp[i][j],temp[i+1][j]);
    return temp;
}
vector<vector<int>> moveleft(vector<vector<int>>& grid,int i,int j){
    if(j<1){
        return {{-1}};
    }
    vector<vector<int>> temp=grid;
    swap(temp[i][j],temp[i][j-1]);
    return temp;
}
vector<vector<int>> moveright(vector<vector<int>>& grid,int i,int j){
    if(j>1){
        return {{-1}};
    }
    vector<vector<int>> temp=grid;
    swap(temp[i][j],temp[i][j+1]);
    return temp;
}

pair<int,int> findblank(vector<vector<int>>& grid){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(grid[i][j]==0){
                return {i,j};
            }
        }
    }
    return {-1,-1};
}

void display(vector<vector<int>>& grid){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(grid[i][j]==0){
                cout<<"X ";
            }
            else{
                cout<<grid[i][j]<<" ";
            }
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}
void displayPath(string s,vector<vector<int>>& grid,int i,int j){
    display(grid);
    int n=s.length();
    for(int k=0;k<n;k++){
        if(s[k]=='U'){
            grid=moveup(grid,i,j);
            i-=1;
            display(grid);
        }
        else if(s[k]=='D'){
            grid=movedown(grid,i,j);
            i+=1;
            display(grid);
        }
        else if(s[k]=='L'){
            grid=moveleft(grid,i,j);
            j-=1;
            display(grid);
        }
        else if(s[k]=='R'){
            grid=moveright(grid,i,j);
            j+=1;
            display(grid);
        }
    }
}
vector<vector<vector<int>>> st;
bool check(vector<vector<int>>& mat){
    int n=st.size();
    for(int i=0;i<n;i++){
        if(st[i]==mat){
            return true;
        }
    }
    return false;
}
void displayPQ(vector<vector<int>>& last,priority_queue<P,vector<P>,greater<P>> pq){
    while (!pq.empty())
    {
        P ele=pq.top();
        pq.pop();
        cout<<"F(n): "<<ele.first<<"  ";
    }
    cout<<endl;
}
bool solvePuzzle(vector<vector<int>>& last,priority_queue<P,vector<P>,greater<P>>& pq){
    string ans="";
    vector<vector<int>> matrix=pq.top().second.second;
    pair<int,int> tm=findblank(matrix);
    while(!pq.empty()){
        displayPQ(last,pq);
        P ele=pq.top();
        pq.pop();
        string path=ele.second.first;
        // display(ele.second.second);

        if(ele.first==path.length()){
            ans=path;
            break;
        }

        // if(ele.first==0){
        //     ans=path;
        //     break;
        // }

        pair<int,int> index=findblank(ele.second.second);
        int i=index.first;
        int j=index.second;
        vector<vector<int>> mat;
        mat=moveup(ele.second.second,i,j);
        if(!check(mat)){
            int cmp=match(mat,last);
            st.push_back(mat);
            pq.push({cmp+path.length()+1,{path+"U",mat}});
        }
        mat=movedown(ele.second.second,i,j);
        if(!check(mat)){
            int cmp=match(mat,last);
            st.push_back(mat);
            pq.push({cmp+path.length()+1,{path+"D",mat}});
        }
        mat=moveleft(ele.second.second,i,j);
        if(!check(mat)){
            int cmp=match(mat,last);
            st.push_back(mat);
            pq.push({cmp+path.length()+1,{path+"L",mat}});
        }
        mat=moveright(ele.second.second,i,j);
        if(!check(mat)){
            int cmp=match(mat,last);
            st.push_back(mat);
            pq.push({cmp+path.length()+1,{path+"R",mat}});
        }
    }
    displayPath(ans,matrix,tm.first,tm.second);
    cout<<ans<<endl<<endl;
    return true;
}
int main(){
    priority_queue<P,vector<P>,greater<P>> pq;
    vector<vector<int>> grid(3,vector<int>(3,0));
    vector<vector<int>> last={{1,2,3},{4,5,6},{7,8,0}};
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            int t;
            cout<<"Enter Block at ("<<i+1<<","<<j+1<<") : ";
            cin>>t;
            grid[i][j]=t;
        }
    }
    pq.push({match(grid,last),{"",grid}});
    st.push_back(grid);
    st.push_back({{-1}});
    cout<<solvePuzzle(last,pq);
    return 0;
}
/*
1 2 3
4 5 6
7 8 0
*/