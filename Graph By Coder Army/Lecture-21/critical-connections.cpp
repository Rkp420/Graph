#include <iostream>
#include <vector>
using namespace std;

// https://leetcode.com/problems/critical-connections-in-a-network/description/

// BruteForce

class Solution
{
public:
    bool isReachable(int src, int des, vector<bool> &visited,
                     vector<vector<int>> &adj, int bu, int bv)
    {
        if (src == des)
            return true;
        visited[src] = true;
        for (int neighbour : adj[src])
        {
            if (visited[neighbour])
                continue;
            if ((src == bu && neighbour == bv) ||
                (src == bv && neighbour == bu))
                continue;

            if (isReachable(neighbour, des, visited, adj, bu, bv))
                return true;
        }
        return false;
    }

    vector<vector<int>> criticalConnections(int n,
                                            vector<vector<int>> &connections)
    {
        vector<vector<int>> ans;
        vector<vector<int>> adj(n);

        for (auto &connection : connections)
        {
            adj[connection[0]].push_back(connection[1]);
            adj[connection[1]].push_back(connection[0]);
        }

        for (auto &connection : connections)
        {
            int src = connection[0];
            int des = connection[1];

            vector<bool> visited(n, false);

            if (!isReachable(src, des, visited, adj, src, des))
            {
                ans.push_back(connection);
            }
        }

        return ans;
    }
};

// Using Tarjan's Algorithm (Optimal)

class Solution
{
public:
    vector<vector<int>> ans;
    void dfs(int node, int parent, int &time, vector<int> &des,
             vector<int> &low, vector<bool> &visited,
             vector<vector<int>> &adj)
    {
        visited[node] = true;
        des[node] = low[node] = time++;

        for (int neigh : adj[node])
        {
            if (neigh == parent)
                continue;

            if (!visited[neigh])
            {
                dfs(neigh, node, time, des, low, visited, adj);
                low[node] = min(low[node], low[neigh]);

                if (low[neigh] > des[node])
                {
                    ans.push_back({node, neigh});
                }
            }
            else
            {
                low[node] = min(low[node], low[neigh]);
            }
        }
    }
    vector<vector<int>> criticalConnections(int n,
                                            vector<vector<int>> &connections)
    {

        // Making an Adjacency List
        vector<vector<int>> adj(n);
        for (vector<int> &connection : connections)
        {
            adj[connection[0]].push_back(connection[1]);
            adj[connection[1]].push_back(connection[0]);
        }

        vector<int> des(n), low(n);
        vector<bool> visited(n, false);
        int time = 0;

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
                dfs(i, -1, time, des, low, visited, adj);
        }

        return ans;
    }
};

int main()
{
    return 0;
}