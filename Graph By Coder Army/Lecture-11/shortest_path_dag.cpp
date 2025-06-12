#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

// https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1

class Solution
{
public:
    void dfs(int src, stack<int> &st, vector<vector<pair<int, int>>> &adj, vector<bool> &visited)
    {
        visited[src] = true;

        for (auto &nbr : adj[src])
        {
            int node = nbr.first;
            int weight = nbr.second;

            if (!visited[node])
                dfs(node, st, adj, visited);
        }

        st.push(src);
    }

    vector<int> shortestPath(int V, int E, vector<vector<int>> &edges)
    {
        // code here
        vector<vector<pair<int, int>>> adj(V);

        for (int i = 0; i < E; i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            int weight = edges[i][2];

            adj[u].push_back({v, weight});
        }

        // Now We have to find the topological Sort For Optimised Calculation of dist
        stack<int> st;
        vector<bool> visited(V, false);
        dfs(0, st, adj, visited);

        // Now We have our Topological Sort for the Source
        vector<int> dist(V, INT_MAX);
        dist[0] = 0;

        while (!st.empty())
        {
            int currNode = st.top();
            st.pop();

            for (auto &nbr : adj[currNode])
            {
                int node = nbr.first;
                int weight = nbr.second;

                dist[node] = min(dist[node], dist[currNode] + weight);
            }
        }

        for (int i = 0; i < V; i++)
        {
            if (dist[i] == INT_MAX)
                dist[i] = -1;
        }

        return dist;
    }
};

int main()
{
    return 0;
}