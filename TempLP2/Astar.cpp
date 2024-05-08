#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>
using namespace std;

class node {
public:
  pair<int, int> pos;
  int h, g, f;
  node *parent;

  node(pair<int, int> p, int g, int h, node *par) {
    pos = p;
    this->h = h;
    this->g = g;
    this->f = h + g;
    this->parent = par;
  }
  friend class astar;
};

class CompareNode {
public:
  bool operator()(const node *lhs, const node *rhs) const {
    return lhs->f > rhs->f;
  }
};

class astar {
  priority_queue<node *, vector<node *>, CompareNode> open_list;
  set<pair<int, int>> closed_list;
  vector<vector<int>> mat;
  pair<int, int> start;
  pair<int, int> end;

public:
  astar(vector<vector<int>> m, pair<int, int> s, pair<int, int> e) {
    mat = m;
    start = s;
    end = e;
  }
  vector<pair<int, int>> solve() {
    node *start_node = new node(start, 0, 0, nullptr);
    open_list.push(start_node);

    while (!open_list.empty()) {
      node *current = open_list.top();
      open_list.pop();
      closed_list.insert(current->pos);

      if (current->pos == this->end) {
        vector<pair<int, int>> path;
        while (current->parent) {
          path.push_back(current->pos);
          current = current->parent;
        }
        path.push_back(current->pos);
        reverse(path.begin(), path.end());
        return path;
      }

      vector<pair<int, int>> directions = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

      for (auto direction : directions) {
        pair<int, int> new_position = {current->pos.first + direction.first,
                                       current->pos.second + direction.second};

        if (new_position.first < 0 || new_position.first >= mat.size() ||
            new_position.second < 0 || new_position.second >= mat[0].size() ||
            mat[new_position.first][new_position.second] != 0 ||
            closed_list.find(new_position) != closed_list.end()) {
          continue;
        }

        node *new_node = new node(new_position, current->g + 1,
                                  abs(new_position.first - end.first) +
                                      abs(new_position.second - end.second),
                                  current);

        open_list.push(new_node);
      }
    }
    return {};
  }
};

int main() {
  vector<vector<int>> matrix = {{0, 0, 0, 0, 0, 0}, {0, 1, 1, 0, 1, 0},
                                {0, 1, 0, 0, 0, 0}, {0, 0, 1, 0, 0, 1},
                                {0, 1, 0, 0, 0, 0}, {0, 0, 0, 1, 1, 0}};

  pair<int, int> start_loc = make_pair(0, 0);
  pair<int, int> end_loc = make_pair(5, 5);
  astar a(matrix, start_loc, end_loc);

  vector<pair<int, int>> path = a.solve();

  cout << "\nPath length is: " << path.size() << endl;
  if (!path.empty()) {
    cout << "Path found:";
    for (const auto &pos : path) {
      cout << " (" << pos.first << "," << pos.second << ")";
    }
    cout << endl;
  } else {
    cout << "No path found." << endl;
  }

  return 0;
}
