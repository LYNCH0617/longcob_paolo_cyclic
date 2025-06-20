#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

/**
 * @brief Utility function to print the adjacency matrix.
 * @param adjMatrix The graph's adjacency matrix.
 */
void printGraph(const std::vector<std::vector<int>>& adjMatrix) {
    std::cout << "Graph Adjacency Matrix:" << std::endl;
    for (size_t i = 0; i < adjMatrix.size(); ++i) {
        for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
            std::cout << adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
}

/**
 * @brief Detects if a cycle exists in a directed graph using BFS (Kahn's Algorithm).
 * @param adjMatrix The graph's adjacency matrix.
 */
void detectCycleBFS(const std::vector<std::vector<int>>& adjMatrix) {
    int numVertices = adjMatrix.size();
    if (numVertices == 0) {
        std::cout << "Graph is empty." << std::endl;
        return;
    }

    std::vector<int> inDegree(numVertices, 0);
    std::vector<int> parent(numVertices, -1);

    // Calculate in-degrees for all vertices
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (adjMatrix[i][j] == 1) {
                inDegree[j]++;
            }
        }
    }

    // Initialize queue with all vertices having an in-degree of 0
    std::queue<int> q;
    for (int i = 0; i < numVertices; ++i) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }

    int processedCount = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        processedCount++;

        // Iterate through all neighbors of u
        for (int v = 0; v < numVertices; ++v) {
            if (adjMatrix[u][v] == 1) {
                inDegree[v]--;
                // In Kahn's, a node can have multiple predecessors.
                // We just store one to help trace back a cycle path.
                // This is not a unique parent tree but sufficient for our goal.
                parent[v] = u; 
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
    }

    // Check if a cycle exists
    if (processedCount < numVertices) {
        std::cout << "Result (BFS): Graph is CYCLIC." << std::endl;

        // Find a node that is part of a cycle (in-degree > 0)
        int cycleNode = -1;
        for (int i = 0; i < numVertices; ++i) {
            if (inDegree[i] > 0) {
                cycleNode = i;
                break;
            }
        }

        // Reconstruct cycle by tracing back parents
        std::vector<int> cyclePath;
        std::vector<bool> visitedInCycle(numVertices, false);
        int current = cycleNode;
        
        while (!visitedInCycle[current]) {
            visitedInCycle[current] = true;
            current = parent[current];
        }

        // `current` is the start of the cycle
        int cycleStartNode = current;
        do {
            cyclePath.push_back(current);
            current = parent[current];
        } while (current != cycleStartNode);
        
        std::reverse(cyclePath.begin(), cyclePath.end());
        
        std::cout << "Vertices in a cycle: ";
        for (size_t i = 0; i < cyclePath.size(); ++i) {
            std::cout << cyclePath[i] << (i == cyclePath.size() - 1 ? "" : " -> ");
        }
        std::cout << " -> " << cyclePath[0] << std::endl;

    } else {
        std::cout << "Result (BFS): Graph is ACYCLIC." << std::endl;
    }
}

int main() {
    std::cout << "--- BFS Cycle Detection (Kahn's Algorithm) ---" << std::endl;

    // Example 1: Cyclic Graph
    std::cout << "\n--- Test Case 1: Cyclic Graph ---" << std::endl;
    std::vector<std::vector<int>> cyclicGraph = {
        {0, 1, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 0, 0},
        {0, 1, 0, 0} // Edge 3 -> 1 creates a cycle 1->3->1
    };
    printGraph(cyclicGraph);
    detectCycleBFS(cyclicGraph);

    // Example 2: Acyclic Graph
    std::cout << "\n--- Test Case 2: Acyclic Graph ---" << std::endl;
    std::vector<std::vector<int>> acyclicGraph = {
        {0, 1, 1, 0},
        {0, 0, 0, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 0}
    };
    printGraph(acyclicGraph);
    detectCycleBFS(acyclicGraph);

    // Example 3: Disconnected Graph with a cycle
    std::cout << "\n--- Test Case 3: A different Cyclic Graph ---" << std::endl;
    std::vector<std::vector<int>> disconnectedGraph = {
        {0, 1, 0, 0, 0}, 
        {0, 0, 1, 0, 0}, 
        {1, 0, 0, 1, 0}, // Edge 2->0 creates cycle 0->1->2->0
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0}
    };
    printGraph(disconnectedGraph);
    detectCycleBFS(disconnectedGraph);

    return 0;
}
