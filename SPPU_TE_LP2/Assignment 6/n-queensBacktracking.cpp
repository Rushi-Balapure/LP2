#include <iostream>
#include <vector>

using namespace std ; 

void print(vector<vector<int> > board){
    for (int i = 0 ; i < board.size() ; i ++){
        for(int j = 0 ; j < board[0].size() ; j ++){
            cout << board[i][j] <<" ";
        }
        cout <<endl ; 
    }
    cout <<endl ;  
}

bool isSafe(int r , int c , vector<vector<int> > board){
    // Check this row on left side
    for (int i = 0 ; i < c ; i ++){
        if(board[r][i]){
            return false ;
        }
    }

    // Check upper diagonal on left side
    for(int i = r , j = c ; i >= 0 && j >= 0 ; i -- , j--){
        if(board[i][j]){
            return false ;
        }
    }
    
    // Check lower diagonal on left side
    for(int i = r , j = c ;  j >=0 && i < board.size() ; i ++ , j -- ){
        if(board[i][j]){
            return false ;
        }
    }
    return true ;
}

bool solve(int col , vector<vector<int> > &board){
    if(col >= board.size()){
        return true ;
    }

    for(int i = 0; i < board.size() ; i ++){
        if(isSafe(i,col,board)){
            board[i][col] = 1 ; 
            if(solve(col+1,board)){
                return true ;
            }
            board[i][col] = 0 ;
        }
    }
    return false ;
}

int main(){
    int n = 5 ;
    vector<vector<int> > board (n,vector<int>(n,0));
    if(solve(0,board)){
        print(board);
    }
    else{
        cout << "Solution not exists" ;
    }

}

