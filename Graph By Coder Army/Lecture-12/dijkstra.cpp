#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// https://www.geeksforgeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1?page=1&difficulty%5B%5D=1&category%5B%5D=Graph&sortBy=submissions

// First Approach
class Solution
{
public:
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src)
    {

        vector<vector<vector<int>>> adj(V);

        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];

            adj[u].push_back({v, weight});
            adj[v].push_back({u, weight});
        }

        // We have our weighted Graph
        vector<int> dist(V, INT_MAX);
        vector<bool> Explored(V, false);
        dist[src] = 0;

        int count = V;
        while (count--)
        {
            int node = -1, value = INT_MAX;

            for (int i = 0; i < V; i++)
            {
                if (!Explored[i] && dist[i] < value)
                {
                    node = i;
                    value = dist[i];
                }
            }

            // Edge Case: All remaining nodes are unreachable
            if (node == -1)
                break;

            Explored[node] = 1;

            for (auto &nbr : adj[node])
            {
                int nbrNode = nbr[0];
                int weight = nbr[1];

                if (!Explored[nbrNode] && (dist[node] + weight < dist[nbrNode]))
                {
                    dist[nbrNode] = dist[node] + weight;
                }
            }
        }

        return dist;
    }
};

// Second Approach : Using Priority Queue(Min_heap)

class Solution
{
public:
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src)
    {

        vector<vector<vector<int>>> adj(V);

        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];

            adj[u].push_back({v, weight});
            adj[v].push_back({u, weight});
        }

        // We have our weighted Graph
        vector<int> dist(V, INT_MAX);
        vector<bool> Explored(V, false);
        dist[src] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> p;

        p.push({0, src});
        while (!p.empty())
        {
            int node = p.top().second;
            p.pop();

            if (Explored[node])
                continue;

            Explored[node] = 1;

            for (auto &nbr : adj[node])
            {
                int nbrNode = nbr[0];
                int weight = nbr[1];

                if (!Explored[nbrNode] && (dist[node] + weight < dist[nbrNode]))
                {
                    dist[nbrNode] = dist[node] + weight;
                    p.push({dist[nbrNode], nbrNode});
                }
            }
        }

        return dist;
    }
};

int main()
{
    return 0;
}