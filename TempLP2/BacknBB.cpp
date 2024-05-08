#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class nqueens {
  int n;
  vector<vector<bool>> board_branchnbound;
  vector<vector<bool>> board_backtracking;
  vector<bool> fdiag;
  vector<bool> bdiag;
  vector<bool> nrow;

public:
  nqueens(int n) {
    this->n = n;
    board_branchnbound.resize(n, vector<bool>(n, false));
    board_backtracking.resize(n, vector<bool>(n, false));
    fdiag.resize(2 * n - 1, false);
    bdiag.resize(2 * n - 1, false);
    nrow.resize(n, false);
  }
  bool isoverlapping(int row, int col) {
    for (int i = 0; i < n; i++) {
      if (board_backtracking[row][i] || board_backtracking[i][col]) {
        return true;
      }
    }
    for (int x = row, y = col; x >= 0 && y >= 0; x--, y--) {
      if (board_backtracking[x][y]) {
        return true;
      }
    }
    for (int x = row, y = col; x >= 0 && y < n; x--, y++) {
      if (board_backtracking[x][y]) {
        return true;
      }
    }
    return false;
  }

  bool backtracking(int col) {
    if (col == n) {
      printboard_back();
      return true;
    }

    for (int row = 0; row < n; row++) {
      if (!isoverlapping(row, col)) {
        board_backtracking[row][col] = true;
        if (backtracking(col + 1)) {
          return true;
        }
        board_backtracking[row][col] = false;
      }
    }
    return false;
  }

  bool isSafe(int row, int col) {
    if (nrow[row] || fdiag[row + col] || bdiag[(n - 1) - (col - row)]) {
      return false;
    }
    return true;
  }

  bool branchnbound(int col) {
    if (col == n) {
      printboard_bb();
      return true;
    }

    for (int row = 0; row < n; row++) {
      if (isSafe(row, col)) {
        nrow[row] = true;
        fdiag[row + col] = true;
        bdiag[(n - 1) - (col - row)] = true;
        board_branchnbound[row][col] = true;

        if (branchnbound(col + 1))
          return true;

        nrow[row] = false;
        fdiag[row + col] = false;
        bdiag[(n - 1) - (col - row)] = false;
        board_branchnbound[row][col] = false;
      }
    }
    return false;
  }

  void printboard_back() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        board_backtracking[i][j] ? cout << "Q " : cout << ". ";
      }
      cout << endl;
    }
  }
  void printboard_bb() {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        board_branchnbound[i][j] ? cout << "Q " : cout << ". ";
      }
      cout << endl;
    }
  }
};

int main() {
  nqueens q(4);
  cout << "Back\n";
  q.backtracking(0);
  // q.printboard_back();
  cout << endl;
  cout << "Branch\n";
  q.branchnbound(0);
  // q.printboard_bb();
}