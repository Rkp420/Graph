#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

// https://www.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1

class Solution
{
public:
    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges)
    {
        vector<vector<vector<int>>> adj(n);
        for (auto &edge : edges)
        {
            int a = edge[0] - 1;
            int b = edge[1] - 1;
            int w = edge[2];

            adj[a].push_back({b, w});
            adj[b].push_back({a, w});
        }

        vector<int> dist(n, INT_MAX);
        vector<int> parent(n, -1);
        dist[0] = 0; // source is node 1 (0-indexed)
        vector<bool> Explored(n, false);

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 0});

        while (!pq.empty())
        {
            int node = pq.top().second;
            pq.pop();

            if (Explored[node])
                continue;
            Explored[node] = true;

            for (auto &nbr : adj[node])
            {
                int nbrNode = nbr[0];
                int weight = nbr[1];

                if (!Explored[nbrNode] && (dist[node] + weight < dist[nbrNode]))
                {
                    dist[nbrNode] = dist[node] + weight;
                    parent[nbrNode] = node;
                    pq.push({dist[nbrNode], nbrNode});
                }
            }
        }

        if (dist[n - 1] == INT_MAX)
            return {-1};

        vector<int> ans;
        int currNodeParent = n - 1;
        while (currNodeParent != -1)
        {
            ans.push_back(currNodeParent + 1); // Convert back to 1-indexed
            currNodeParent = parent[currNodeParent];
        }

        reverse(ans.begin(), ans.end());
        ans.insert(ans.begin(), dist[n - 1]); // Insert total weight
        return ans;
    }
};

int main()
{
    return 0;
}