#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

// Structure representing an edge to a destination node with an associated weight
struct Edge {
    int dest;
    int weight;
};

class Graph {
private:
    int numVertices;
    // Adjacency List representation: A vector of vectors containing Edges
    vector<vector<Edge>> adjList;
    bool isDirected;

    // Recursive helper function used by the Depth First Search traversal
    void DFSHelper(int vertex, vector<bool>& visited) {
        visited[vertex] = true;
        cout << vertex << " ";

        // Traverse all adjacent nodes linked to this vertex
        for (const auto& edge : adjList[vertex]) {
            if (!visited[edge.dest]) {
                DFSHelper(edge.dest, visited);
            }
        }
    }

public:
    // Constructor matching parameters from the lecture
    Graph(int vertices, bool directed = false) {
        this->numVertices = vertices;
        this->isDirected = directed;
        adjList.resize(vertices);
    }

    // Adds an edge connection to the graph architecture (Handles both weighted and unweighted)
    void addEdge(int src, int dest, int weight = 1) {
        Edge edge1 = {dest, weight};
        adjList[src].push_back(edge1);

        // If the graph is undirected, map the return link from destination to source
        if (!isDirected) {
            Edge edge2 = {src, weight};
            adjList[dest].push_back(edge2);
        }
    }

    // 1. Breadth-First Search (BFS) Traversal Implementation
    // References Slide Parameters: Uses a Queue to traverse layer-by-layer uniformly
    void BFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        cout << "BFS Traversal starting from vertex " << startVertex << ": ";

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            // Explore neighbors of the current unqueued vertex
            for (const auto& edge : adjList[current]) {
                if (!visited[edge.dest]) {
                    visited[edge.dest] = true;
                    q.push(edge.dest);
                }
            }
        }
        cout << endl;
    }

    // 2. Depth-First Search (DFS) Traversal Implementation
    // References Slide Parameters: Uses a stack paradigm via recursion to dive deep along paths
    void DFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        cout << "DFS Traversal starting from vertex " << startVertex << ": ";
        DFSHelper(startVertex, visited);
        cout << endl;
    }

    // 3. Dijkstra's Single-Source Shortest Path Algorithm
    // References Slide Parameters: Evaluates short edge weights iteratively to build minimum pathways
    void dijkstra(int source) {
        // Distance lookup table initialized to INT_MAX (infinity)
        vector<int> dist(numVertices, INT_MAX);
        // Track completed nodes whose minimum path is permanently solved
        vector<bool> shortPathSet(numVertices, false);

        // Distance from source to itself is naturally zero
        dist[source] = 0;

        // Custom comparator structural lambda lambda for the min-priority queue tracking paths
        auto cmp = [](pair<int, int> left, pair<int, int> right) { return left.second > right.second; };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> minHeap(cmp);

        // Pair item format: {vertex_id, distance_weight}
        minHeap.push({source, 0});

        while (!minHeap.empty()) {
            int u = minHeap.top().first;
            minHeap.pop();

            // Ignore reprocessing if vertex is already part of the optimized shortest path set
            if (shortPathSet[u]) continue;
            shortPathSet[u] = true;

            // Relaxation sequence step for all neighboring links
            for (const auto& edge : adjList[u]) {
                int v = edge.dest;
                int weight = edge.weight;

                // Dynamic updates if a shorter traversal route to node 'v' is discovered through node 'u'
                if (!shortPathSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    minHeap.push({v, dist[v]});
                }
            }
        }

        // Output short path matrices matching standard lecture trace patterns
        cout << "\nDijkstra's Single-Source Shortest Paths from Vertex [" << source << "]:\n";
        cout << "---------------------------------------------\n";
        cout << "Destination Vertex \t Distance From Source\n";
        cout << "---------------------------------------------\n";
        for (int i = 0; i < numVertices; ++i) {
            cout << "\t" << i << " \t\t\t ";
            if (dist[i] == INT_MAX) {
                cout << "INF (Unreachable)\n";
            } else {
                cout << dist[i] << "\n";
            }
        }
        cout << "---------------------------------------------\n";
    }

    // Helper diagnostic display to inspect the structural adjacency arrays directly
    void printGraph() {
        cout << "\nAdjacency List Mapping of Graph Structure:\n";
        for (int i = 0; i < numVertices; ++i) {
            cout << "Vertex " << i << " links to: ";
            for (const auto& edge : adjList[i]) {
                cout << "-> " << edge.dest << " (w:" << edge.weight << ") ";
            }
            cout << "\n";
        }
        cout << endl;
    }
};

int main() {
    cout << "     UNIVERSAL GRAPH ENGINEERING DIAGNOSTIC SUITE      \n";

    // PHASE 1: COMPLEX WEIGHTED MESH CONSTRUCTION
    cout << "--- PHASE 1: Graph Architecture Initialization ---\n";
    
    // Instantiating a graph with 7 vertices (Nodes indexed 0 through 6)
    // The second parameter set to 'false' indicates an UNDIRECTED network mesh.
    Graph g(7, false);

    cout << "[Action] Mapping structural link matrices with explicit costs...\n";
    
    // Constructing an interconnected topology inspired by standard lecture slide examples:
    g.addEdge(0, 1, 4);  // Edge from 0 to 1, weight = 4
    g.addEdge(0, 2, 3);  // Edge from 0 to 2, weight = 3
    g.addEdge(1, 2, 1);  // Edge from 1 to 2, weight = 1
    g.addEdge(1, 3, 2);  // Edge from 1 to 3, weight = 2
    g.addEdge(1, 4, 7);  // Edge from 1 to 4, weight = 7
    g.addEdge(2, 4, 4);  // Edge from 2 to 4, weight = 4
    g.addEdge(3, 4, 1);  // Edge from 3 to 4, weight = 1
    g.addEdge(3, 5, 5);  // Edge from 3 to 5, weight = 5
    g.addEdge(4, 5, 3);  // Edge from 4 to 5, weight = 3
    g.addEdge(4, 6, 8);  // Edge from 4 to 6, weight = 8
    g.addEdge(5, 6, 2);  // Edge from 5 to 6, weight = 2

    // Print out the structural adjacency array lists to inspect memory pointers
    g.printGraph();


    // PHASE 2: TRAVERSAL TRACING COMPARISON
    cout << "--- PHASE 2: Systematic Graph Traversals ---\n";
    
    /* Breadth-First Search (BFS)
       Expected Behavior: Explores vertices in clean concentric levels. 
       Starting from 0, it discovers direct neighbors (1 and 2) before advancing to interior levels.
    */
    cout << "[Execute] Initializing Breadth-First Sweep...\n";
    g.BFS(0);
    cout << endl;

    /* Depth-First Search (DFS)
       Expected Behavior: Dives straight to the deepest branch boundary 
       via recursive tracking stacks before popping back to examine alternate pathways.
    */
    cout << "[Execute] Initializing Depth-First Sweep...\n";
    g.DFS(0);
    cout << "\n";


    // PHASE 3: DIJKSTRA'S SHORTEST PATH OPTIMIZATION RUNS
    cout << "--- PHASE 3: Dijkstra's Single-Source Shortest Path Optimization ---\n";
    
    /* Running from Origin Node [0]
       Verifies if path relaxation properly chooses indirect cheaper paths. 
    */
    cout << "[Compute] Calculating global minimum spanning path distances from Source Node [0]...";
    g.dijkstra(0);
    cout << endl;

    /* Alternate Root Verification Passing
       Running the optimization mapping again from a deep node inside the graph [Node 6]
       to check cost evaluations when moving in reverse across undirected routes.
    */
    cout << "[Compute] Running optimization diagnostics from interior Pivot Node [6]...";
    g.dijkstra(6);
    cout << endl;

    return 0;
}