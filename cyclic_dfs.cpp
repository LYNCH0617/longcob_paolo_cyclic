#include <iostream>
#include <vector>
using namespace std;

bool dfs(int v, vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<bool>& recStack, vector<int>& path) {
    visited[v] = true;
    recStack[v] = true;
    path.push_back(v);

    for (int u = 0; u < adjMatrix.size(); ++u) {
        if (adjMatrix[v][u]) {
            if (!visited[u]) {
                if (dfs(u, adjMatrix, visited, recStack, path))
                    return true;
            } else if (recStack[u]) {
                path.push_back(u); // To show the cycle
                return true;
            }
        }
    }

    recStack[v] = false;
    path.pop_back();
    return false;
}

bool isCyclicDFS(vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false), recStack(n, false);
    vector<int> path;

    for (int i = 0; i < n; ++i) {
        if (!visited[i] && dfs(i, adjMatrix, visited, recStack, path)) {
            cout << "Cycle detected (DFS). Vertices in cycle (approximate): ";
            for (int v : path) cout << v << " ";
            cout << endl;
            return true;
        }
    }

    cout << "No cycle found (DFS)." << endl;
    return false;
}

int main() {
    vector<vector<int>> adjMatrix = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}  // Creates a cycle 0->1->2->0
    };

    isCyclicDFS(adjMatrix);
    return 0;
}
