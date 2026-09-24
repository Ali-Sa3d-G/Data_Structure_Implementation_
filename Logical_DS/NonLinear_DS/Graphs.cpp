#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <functional>

using namespace std;

/**
 * ============================================================================
 *                         GRAPH - LEARNING GUIDE
 * ============================================================================
 *
 * A Graph consists of:
 *
 *   - Vertices (Nodes)
 *   - Edges (Connections)
 *
 * This implementation uses an ADJACENCY LIST.
 *
 * Example:
 *
 *       0 -------- 1
 *       |        / |
 *       |      /   |
 *       2 ----     3
 *
 * Adjacency List:
 *
 *       0 -> 1, 2
 *       1 -> 0, 2, 3
 *       2 -> 0, 1
 *       3 -> 1
 *
 * For an undirected graph:
 *
 *       addEdge(0, 1)
 *
 * stores:
 *
 *       0 -> 1
 *       1 -> 0
 *
 * Algorithms included:
 *
 *   1. BFS
 *      Uses a Queue and explores level by level.
 *
 *   2. DFS
 *      Goes as deep as possible before backtracking.
 *
 *   3. Dijkstra
 *      Finds the shortest distance from one source
 *      to all reachable vertices.
 *
 * Dijkstra requires NON-NEGATIVE edge weights.
 *
 * Time Complexity:
 *   BFS                    : O(V + E)
 *   DFS                    : O(V + E)
 *   Dijkstra (Min Heap)    : O((V + E) log V)
 *
 * Space Complexity: O(V + E)
 *
 * V = number of vertices
 * E = number of edges
 *
 * ============================================================================
 */

 // =========================== EDGE STRUCTURE ===========================

 /**
  * Represents one edge in the adjacency list.
  *
  * Example:
  *
  *       { destination = 3, weight = 5 }
  *
  * means:
  *
  *       current vertex ----5----> vertex 3
  */
struct Edge
{
    int destination;
    int weight;
};

// =========================== GRAPH CLASS ===========================

class Graph
{
private:
    int numberOfVertices;
    bool directed;

    /*
     * Adjacency List
     *
     * adjList[0] -> all edges connected to vertex 0
     * adjList[1] -> all edges connected to vertex 1
     * ...
     */
    vector<vector<Edge>> adjList;

    // ==================== DFS HELPER ====================

    /**
     * DFS recursively explores one path as deeply as possible.
     */
    void DFSHelper(int vertex, vector<bool>& visited) const
    {
        visited[vertex] = true;

        cout << vertex << " ";

        // Visit every unvisited neighbor.
        for (const Edge& edge : adjList[vertex])
        {
            if (!visited[edge.destination])
            {
                DFSHelper(edge.destination, visited);
            }
        }
    }

public:

    // ==================== CONSTRUCTOR ====================

    /**
     * Creates a graph with the given number of vertices.
     *
     * directed = false -> undirected graph
     * directed = true  -> directed graph
     */
    Graph(int vertices, bool directedGraph = false)
    {
        numberOfVertices = vertices;
        directed = directedGraph;

        adjList.resize(vertices);
    }

    // ==================== ADD EDGE ====================

    /**
     * ADD EDGE
     *
     * Adds a connection from source to destination.
     *
     * For an undirected graph:
     *
     *       source <------> destination
     *
     * So we store BOTH directions.
     */
    void addEdge(int source, int destination, int weight = 1)
    {
        adjList[source].push_back({ destination, weight });

        if (!directed)
        {
            adjList[destination].push_back({ source, weight });
        }
    }

    // ==================== BFS ====================

    /**
     * BFS - BREADTH FIRST SEARCH
     *
     * BFS explores the graph level by level.
     *
     * Visualization:
     *
     *                 0
     *               /   \
     *              1     2      <- Level 1
     *             / \
     *            3   4          <- Level 2
     *
     * Starting from 0:
     *
     *       0 -> 1 -> 2 -> 3 -> 4
     *
     * A QUEUE is used:
     *
     *       First discovered -> First processed
     *
     * Time Complexity: O(V + E)
     */
    void BFS(int start) const
    {
        if (start < 0 || start >= numberOfVertices)
            return;

        vector<bool> visited(numberOfVertices, false);

        queue<int> q;

        // Start with the source vertex.
        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            cout << current << " ";

            /*
             * Add unvisited neighbors to the queue.
             *
             * Mark them visited when adding them,
             * so the same vertex is not added multiple times.
             */
            for (const Edge& edge : adjList[current])
            {
                if (!visited[edge.destination])
                {
                    visited[edge.destination] = true;
                    q.push(edge.destination);
                }
            }
        }

        cout << endl;
    }

    // ==================== DFS ====================

    /**
     * DFS - DEPTH FIRST SEARCH
     *
     * DFS follows one path as far as possible,
     * then goes back and tries another path.
     *
     * Visualization:
     *
     *       0
     *      / \
     *     1   2
     *    /
     *   3
     *
     * DFS may go:
     *
     *       0 -> 1 -> 3 -> 2
     *
     * Recursion acts like a Stack.
     *
     * Time Complexity: O(V + E)
     */
    void DFS(int start) const
    {
        if (start < 0 || start >= numberOfVertices)
            return;

        vector<bool> visited(numberOfVertices, false);

        DFSHelper(start, visited);

        cout << endl;
    }

    // ==================== DIJKSTRA ====================

    /**
     * DIJKSTRA'S ALGORITHM
     *
     * Finds the shortest distance from one source
     * to every reachable vertex.
     *
     * Example:
     *
     *       0 --4-- 1 --2-- 3
     *        \
     *         3
     *          \
     *           2
     *
     * From 0 to 3:
     *
     *       0 -> 1 -> 3
     *       cost = 4 + 2 = 6
     *
     *       0 -> 2 -> 3
     *       may be cheaper depending on the weights.
     *
     * Main idea:
     *
     *   Always process the vertex with the smallest
     *   currently known distance.
     *
     * Then try to improve the distances of its neighbors.
     *
     * This improvement is called RELAXATION.
     *
     * IMPORTANT:
     *   Dijkstra does not work correctly with negative edge weights.
     *
     * Time Complexity: O((V + E) log V)
     */
    void dijkstra(int source) const
    {
        if (source < 0 || source >= numberOfVertices)
            return;

        vector<int> distance(
            numberOfVertices,
            INT_MAX
        );

        /*
         * Min-Heap:
         *
         *       {distance, vertex}
         *
         * The smallest distance is always on top.
         */
        priority_queue<
            pair<int, int>,
            vector<pair<int, int>>,
            greater<pair<int, int>>
        > minHeap;

        distance[source] = 0;

        minHeap.push({ 0, source });

        while (!minHeap.empty())
        {
            int currentDistance = minHeap.top().first;
            int currentVertex = minHeap.top().second;

            minHeap.pop();

            /*
             * The heap may contain an old entry for the same vertex.
             * Ignore it if it is no longer the best known distance.
             */
            if (currentDistance != distance[currentVertex])
                continue;

            // Try to improve every neighbor's distance.
            for (const Edge& edge : adjList[currentVertex])
            {
                int nextVertex = edge.destination;
                int newDistance =
                    currentDistance + edge.weight;

                /*
                 * Relaxation:
                 *
                 * If:
                 *
                 *       current path + edge < old path
                 *
                 * then update the shortest known distance.
                 */
                if (newDistance < distance[nextVertex])
                {
                    distance[nextVertex] = newDistance;

                    minHeap.push(
                        { newDistance, nextVertex }
                    );
                }
            }
        }

        // Print final shortest distances.
        cout << "Shortest distances from vertex "
            << source << ":\n";

        for (int i = 0; i < numberOfVertices; i++)
        {
            cout << "Vertex " << i << ": ";

            if (distance[i] == INT_MAX)
                cout << "INF";
            else
                cout << distance[i];

            cout << endl;
        }
    }

    // ==================== DISPLAY GRAPH ====================

    /**
     * Prints the adjacency list.
     *
     * Example:
     *
     *       0 -> 1(4) 2(3)
     *
     * means vertex 0 is connected to:
     *
     *       1 with weight 4
     *       2 with weight 3
     */
    void printGraph() const
    {
        cout << "Adjacency List:\n";

        for (int i = 0; i < numberOfVertices; i++)
        {
            cout << i << " -> ";

            for (const Edge& edge : adjList[i])
            {
                cout << edge.destination
                    << "(" << edge.weight << ") ";
            }

            cout << endl;
        }
    }
};

// =========================== MAIN FUNCTION ===========================

int main()
{
    /*
     * Create an undirected weighted graph.
     *
     * Vertices:
     *
     *       0  1  2  3  4  5  6
     */
    Graph graph(7, false);

    // ==================== BUILD GRAPH ====================

    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 4, 7);
    graph.addEdge(2, 4, 4);
    graph.addEdge(3, 4, 1);
    graph.addEdge(3, 5, 5);
    graph.addEdge(4, 5, 3);
    graph.addEdge(4, 6, 8);
    graph.addEdge(5, 6, 2);

    cout << "--- GRAPH ---" << endl;

    graph.printGraph();

    // ==================== BFS ====================

    cout << "\n--- BFS ---" << endl;

    cout << "BFS from 0: ";
    graph.BFS(0);

    // ==================== DFS ====================

    cout << "\n--- DFS ---" << endl;

    cout << "DFS from 0: ";
    graph.DFS(0);

    // ==================== DIJKSTRA ====================

    cout << "\n--- DIJKSTRA ---" << endl;

    graph.dijkstra(0);

    return 0;
}