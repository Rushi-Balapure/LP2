#include <iostream>
#include <vector>
using namespace std;

class Game {
private:
    int N;
    vector<vector<int>> board_backtrack;
    vector<vector<int>> board_branch_and_bound;
    vector<vector<int>> slash_diag;
    vector<vector<int>> backslash_diag;
    vector<bool> row_lookup;
    int num_diags;
    vector<bool> slash_lookup;
    vector<bool> backslash_lookup;

public:
    Game(int n) : N(n), board_backtrack(n, vector<int>(n, 0)), board_branch_and_bound(n, vector<int>(n, 0)),
                  slash_diag(n, vector<int>(n, 0)), backslash_diag(n, vector<int>(n, 0)),
                  row_lookup(n, false), num_diags(2 * n - 1),
                  slash_lookup(2 * n - 1, false), backslash_lookup(2 * n - 1, false) {
        initMatrices();
    }

    bool checkOverlap(int i, int j) {
        for (int k = 0; k < N; ++k) {
            if (board_backtrack[i][k] == 1 || board_backtrack[k][j] == 1) {
                return true;
            }
        }
        for (int k = 0; k < N; ++k) {
            for (int l = 0; l < N; ++l) {
                if ((k + l == i + j) || (k - l == i - j)) {
                    if (board_backtrack[k][l] == 1) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool NQueensBacktracking(int n) {
        if (n == 0) {
            return true;
        }
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if ((!checkOverlap(i, j)) && (board_backtrack[i][j] != 1)) {
                    board_backtrack[i][j] = 1;
                    if (NQueensBacktracking(n - 1)) {
                        return true;
                    }
                    board_backtrack[i][j] = 0;
                }
            }
        }
        return false;
    }

    void initMatrices() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                slash_diag[i][j] = i + j;
                backslash_diag[i][j] = i - j + (N - 1);
            }
        }
    }

    bool isSafe(int r, int c) {
        if (slash_lookup[slash_diag[r][c]] || backslash_lookup[backslash_diag[r][c]] || row_lookup[r]) {
            return false;
        }
        return true;
    }

    bool NQueensBranchAndBound(int c) {
        if (c >= N) {
            return true;
        }
        for (int i = 0; i < N; ++i) {
            if (isSafe(i, c)) {
                board_branch_and_bound[i][c] = 1;
                row_lookup[i] = true;
                slash_lookup[slash_diag[i][c]] = true;
                backslash_lookup[backslash_diag[i][c]] = true;
                if (NQueensBranchAndBound(c + 1)) {
                    return true;
                }
                board_branch_and_bound[i][c] = 0;
                row_lookup[i] = false;
                slash_lookup[slash_diag[i][c]] = false;
                backslash_lookup[backslash_diag[i][c]] = false;
            }
        }
        return false;
    }

    void runner() {
        cout << "Solution by Backtracking - " << endl;
        NQueensBacktracking(N);
        for (auto& row : board_backtrack) {
            for (int cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }

        cout << "Solution by Branch and Bound - " << endl;
        NQueensBranchAndBound(0);
        for (auto& row : board_branch_and_bound) {
            for (int cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n;
    cout << "Enter number of queens - ";
    cin >> n;
    Game g(n);
    g.runner();
    return 0;
}