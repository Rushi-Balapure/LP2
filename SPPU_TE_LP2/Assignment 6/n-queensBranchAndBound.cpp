#include <iostream>
#include <vector>

using namespace std;

void print(vector<vector<int> > board){
    for (int i = 0 ; i < board.size() ; i ++){
        for (int j = 0 ; j <board[0].size() ;  j ++ ){
            cout << board[i][j] <<" " ; 
        }
        cout <<endl ;
    }
    cout <<endl ;
}
bool isSafe(int r , int c , vector<bool> rows , vector<bool> leftDiagonals , vector<bool> rightDiagonals){
    if(rows[r] || leftDiagonals[r+c] || rightDiagonals[c-r+rows.size()-1]){
        return false ;
    } 
    return true ;
}

bool solve(vector<vector<int> > &board , int col , vector<bool> rows , vector<bool> leftDiagonals , vector<bool> rightDiagonals){
    if(col >= rows.size()){
        return true ;
    }
    for (int i = 0 ; i < rows.size() ; i ++){
        if(isSafe(i,col,rows,leftDiagonals,rightDiagonals)){
            rows[i] = true ; 
            leftDiagonals[i+col] = true ;
            rightDiagonals[col-i+rows.size()-1] = true ;
            board[i][col] = 1 ;

            if(solve(board,col+1,rows,leftDiagonals,rightDiagonals) == true){
                return true ;
            }

            rows[i] = false ; 
            leftDiagonals[i+col] = false ;
            rightDiagonals[col-i+rows.size()-1] = false ;
            board[i][col] = 0 ;

        }
    }
    return false ; 
}

int main (){
    int n = 5 ; 
    vector<vector<int> > board (n,vector<int>(n,0));
    vector<bool> rows (n,false);
    vector<bool> leftDiagonals((2*n)-1,false);
    vector<bool> rightDiagonals((2*n)-1,false);

    if(solve(board,0,rows,leftDiagonals,rightDiagonals)){
        print(board);
    }else{
        print(board);
        cout<<"Solution does not exist";
    }
    return 0 ;
}