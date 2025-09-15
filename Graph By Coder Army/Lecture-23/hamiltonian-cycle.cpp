#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// https://www.geeksforgeeks.org/problems/hamiltonian-path2522/1

class Solution
{
public:
    bool dfs(int src, int visitedNodes, vector<bool> &visited, vector<vector<int>> &adj, int n, int start)
    {
        visited[src] = true;
        visitedNodes++;

        if (visitedNodes == n)
        {
            return find(adj[src].begin(), adj[src].end(), adj[src].begin()) != adj[src].end();
        }

        for (auto neigh : adj[src])
        {
            if (!visited[neigh])
            {
                if (dfs(neigh, visitedNodes, visited, adj, n, start))
                    return true;
            }
        }

        visited[src] = false;
        return false;
    }
    bool check(int n, int m, vector<vector<int>> edges)
    {
        vector<vector<int>> adj(n + 1);

        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        for (int i = 1; i <= n; i++)
        {
            vector<bool> visited(n + 1, false);
            if (dfs(i, 0, visited, adj, n, i))
                return true;
        }

        return false;
    }
};

int main()
{
    return 0;
}