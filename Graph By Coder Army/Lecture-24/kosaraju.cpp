#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1

class Solution
{
public:
    stack<int> topoSort;
    void dfs(int src, vector<bool> &visited, vector<vector<int>> &adj)
    {
        visited[src] = true;

        for (auto neigh : adj[src])
        {
            if (!visited[neigh])
                dfs(neigh, visited, adj);
        }

        topoSort.push(src);
    }

    void dfs2(int src, vector<bool> &visited, vector<vector<int>> &adj)
    {
        visited[src] = true;

        for (auto neigh : adj[src])
        {
            if (!visited[neigh])
                dfs2(neigh, visited, adj);
        }
    }

    int kosaraju(vector<vector<int>> &adj)
    {
        int nodes = adj.size();

        // Preparing Topo Sort
        vector<bool> visited1(nodes, false);
        for (int i = 0; i < nodes; i++)
        {
            if (!visited1[i])
            {
                dfs(i, visited1, adj);
            }
        }

        // Now We have Our topoSort
        // Reversing The Edge
        vector<vector<int>> reverseAdj(nodes);
        for (int i = 0; i < nodes; i++)
        {
            for (auto neigh : adj[i])
            {
                reverseAdj[neigh].push_back(i);
            }
        }

        // Now it's time to Count SCC
        int ans = 0;
        vector<bool> visited2(nodes, false);
        while (!topoSort.empty())
        {
            int topNode = topoSort.top();
            topoSort.pop();
            if (!visited2[topNode])
            {
                ans++;
                dfs2(topNode, visited2, reverseAdj);
            }
        }

        return ans;
    }
};

int main()
{
    return 0;
}