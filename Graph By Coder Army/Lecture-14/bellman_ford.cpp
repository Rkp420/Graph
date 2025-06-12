#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// https://www.geeksforgeeks.org/problems/distance-from-the-source-bellman-ford-algorithm/1

// If a vertex is unreachable from the source, its distance should be marked as 1e8 

class Solution
{
public:
    vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src)
    {

        // dist array from src
        vector<int> dist(V, 1e8);

        // Initializing src node
        dist[src] = 0;

        for (int i = 1; i <= V; i++)
        {
            bool isChanged = false;
            for (auto &edge : edges)
            {
                int a = edge[0];
                int b = edge[1];
                int wt = edge[2];

                if (dist[a] != 1e8 && (dist[a] + wt) < dist[b])
                {
                    dist[b] = dist[a] + wt;
                    isChanged = true;
                }
            }

            if (isChanged == false)
                return dist;
        }

        return {-1};
    }
};


// You Can Apply Bellman ford algo for undirected graph also
// But as we know This algo traverse the edges so we have to 
// Make an array of edges which has Both the edge info like u->v & v->u
// But you have to make attention here that After making Both side edges array You already Built an cyclic graph 
// if any of the edge has -ve weight Bellford algo "Toh Bhaiya gyo kaam se"
// or Naa hi Dijkstra Algo Lagega kyunki -ve Weight par wo kaam hi nhi karta 
// So we have to learn something new to handle these Situations

// One Example of Bellman ford algo for undirected with +ve edge weight


int main()
{

    int V = 4;
    int src = 0;

    // Edges (undirected, so both sides stored):
    vector<vector<int>> edges = {
        {0, 1, 2}, {1, 0, 2}, {0, 2, 4}, {2, 0, 4}, {1, 3, 1}, {3, 1, 1}, {2, 3, 3}, {3, 2, 3}};

    Solution sol;
    vector<int> result = sol.bellmanFord(V, edges, src);

    // Output distances from src=0 to all nodes
    for (int d : result)
        cout << d << " ";

    return 0;
}