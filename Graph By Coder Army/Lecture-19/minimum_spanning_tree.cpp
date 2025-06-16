#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

// https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article

// BruteForce
class Solution
{
public:
    int spanningTree(int V, vector<vector<int>> adj[])
    {

        vector<bool> visited(V, false);

        visited[0] = true;

        int totalCost = 0;
        for (int i = 1; i < V; i++)
        {
            int minWeight = INT_MAX, u = -1, v = -1;

            for (int i = 0; i < V; i++)
            {
                if (visited[i])
                {
                    for (auto nbr : adj[i])
                    {
                        if (!visited[nbr[0]] && minWeight > nbr[1])
                        {
                            minWeight = nbr[1];
                            v = nbr[0];
                        }
                    }
                }
            }

            if (v != -1)
            {
                visited[v] = true;
                totalCost += minWeight;
            }
        }

        return totalCost;
    }
};
// Optimised : Using priority queue
class Solution
{
public:
    int spanningTree(int V, vector<vector<int>> adj[])
    {

        vector<bool> visited(V, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push({0, 0}); // {weight, node}
        int totalCost = 0;

        while (!pq.empty())
        {
            auto curr = pq.top();
            pq.pop();
            int wt = curr.first;
            int node = curr.second;

            if (visited[node])
                continue;
            visited[node] = true;
            totalCost += wt;

            for (auto nbr : adj[node])
            {
                int adjNode = nbr[0];
                int edgeWt = nbr[1];
                if (!visited[adjNode])
                {
                    pq.push({edgeWt, adjNode});
                }
            }
        }

        return totalCost;
    }
};

// With Parent Node and BruteForce
class Solution
{
public:
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);   // To track the parent of each node in MST
        vector<int> key(V, INT_MAX); // To track minimum edge weight to reach node

        key[0] = 0; // Start from node 0
        parent[0] = -1;

        int totalCost = 0;

        for (int count = 0; count < V; count++)
        {
            int u = -1;
            int minWeight = INT_MAX;

            // Pick the unvisited node with the smallest key value
            for (int i = 0; i < V; i++)
            {
                if (!visited[i] && key[i] < minWeight)
                {
                    minWeight = key[i];
                    u = i;
                }
            }

            if (u == -1)
                break; // All reachable nodes visited
            visited[u] = true;
            totalCost += key[u];

            // Update key and parent for adjacent unvisited nodes
            for (auto &nbr : adj[u])
            {
                int v = nbr[0];
                int wt = nbr[1];

                if (!visited[v] && wt < key[v])
                {
                    key[v] = wt;
                    parent[v] = u;
                }
            }
        }

        // Optional: Print MST edges
        // for (int i = 1; i < V; i++) {
        //     cout << parent[i] << " - " << i << endl;
        // }

        return totalCost;
    }
};

// Optimised
class Solution
{
public:
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        vector<int> parent(V, -1);
        vector<int> key(V, INT_MAX);
        vector<bool> visited(V, false);

        // Min-Heap: {weight, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Start from node 0
        key[0] = 0;
        pq.push({0, 0});

        int totalCost = 0;

        while (!pq.empty())
        {
            auto [wt, u] = pq.top();
            pq.pop();

            if (visited[u])
                continue;

            visited[u] = true;
            totalCost += wt;

            for (auto &nbr : adj[u])
            {
                int v = nbr[0];
                int edgeWt = nbr[1];

                if (!visited[v] && edgeWt < key[v])
                {
                    key[v] = edgeWt;
                    pq.push({edgeWt, v});
                    parent[v] = u; // u is now parent of v
                }
            }
        }

        // Optional: Print MST edges
        // for (int i = 1; i < V; i++) {
        //     cout << parent[i] << " - " << i << " : weight = " << key[i] << endl;
        // }

        return totalCost;
    }
};
int main()
{
    return 0;
}