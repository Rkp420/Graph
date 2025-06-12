#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Making a shortest Path array from Source Node But In Case of Directed_weighted_graph

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