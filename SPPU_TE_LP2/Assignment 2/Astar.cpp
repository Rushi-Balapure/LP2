#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class Node {
public:
    vector<vector<int> > board;
    int g;
    int h;
    int f;

    Node(vector<vector<int> > board, int g, int h) {
        this->board = board;
        this->g = g;
        this->h = h;
        this->f = g + h;
    }
};

void print(Node* node) {
    for (auto i : node->board) {
        for(auto j: i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int getH(vector<vector<int> > node, Node* target) {
    int h = 0; 
    for (int i = 0 ; i < node.size(); ++i) {
        for(int j = 0; j < node[0].size(); ++j) {
            if(node[i][j] != target->board[i][j]) {
                h++;
            }
        }
    }
    return h - 1;  
}

vector<Node*> getNeighbours(Node* node, Node* target) {
    vector<Node*> neighbours;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {1, -1, 0, 0};

    int blankX, blankY; 

    for (int i = 0; i < node->board.size(); ++i) {
        for(int j = 0; j < node->board[0].size(); ++j) {
            if(node->board[i][j] == 0) {
                blankX = i;
                blankY = j;
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        int newX = blankX + dx[i];
        int newY = blankY + dy[i];
        if (newX >= 0 && newX < node->board.size() && newY >= 0 && newY < node->board[0].size()) {
            vector<vector<int> > newBoard = node->board; 
            swap(newBoard[blankX][blankY] , newBoard[newX][newY]);
            neighbours.push_back(new Node(newBoard, node->g + 1, getH(newBoard, target)));
        }
    }
    return neighbours;
}

bool isGoal(Node* node, Node* target) {
    return node->board == target->board;
}

void solve(Node* start, Node* target) {
    Node* startNode = new Node(start->board , 0 , getH(start->board, target));

    priority_queue<pair<int, Node*>, vector<pair<int , Node*> >, greater<pair<int, Node*> > > pq;  
    map<Node* ,bool> visited ;

    pq.push(make_pair(startNode->f, startNode));

    while (!pq.empty()) {
        Node* currNode = pq.top().second ;
        pq.pop();

        print(currNode);

        if (isGoal(currNode, target)) {
            cout << "Goal state reached, total steps needed : " << currNode->g << endl << endl;
            return;
        }

        visited[currNode] = true;
        vector<Node*> neighbours = getNeighbours(currNode, target);
        for (auto n : neighbours) {
            print(n);
            cout << "f : " << n->f << " g : " << n->g << " h : " << n->h << endl << endl;
            if (!visited[n]) {
                pq.push(make_pair(n->f, n)) ;
            }
        }
    }
    cout << "No solution exists" << endl;
}

int main() {

    vector<vector<int> > startBoard = {
        {1, 2, 3},
        {0, 4, 6},
        {7, 5, 8}
    };

    vector<vector<int> > targetBoard = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}
    };


    Node* start = new Node(startBoard, 0, 0);
    Node* target = new Node(targetBoard, 0, 0);

    solve(start, target);

    return 0;
}
