#include <iostream>
#include <vector>
using namespace std;

// https://www.geeksforgeeks.org/problems/articulation-point2616/1

// Optimised + Cleaner 
class Solution
{
    int V;
    vector<int> disc, low;
    vector<bool> visited, isArtPoint;
    int time;
    vector<vector<int>> adj;

    void dfs(int node, int parent)
    {
        visited[node] = true;
        disc[node] = low[node] = time++;
        int childCount = 0;

        for (int neigh : adj[node])
        {
            if (neigh == parent)
                continue;

            if (!visited[neigh])
            {
                childCount++;
                dfs(neigh, node);

                low[node] = min(low[node], low[neigh]);

                // Non-root articulation condition
                if (parent != -1 && low[neigh] >= disc[node])
                    isArtPoint[node] = true;
            }
            else
            {
                // Back edge
                low[node] = min(low[node], disc[neigh]);
            }
        }

        // Root articulation condition
        if (parent == -1 && childCount > 1)
            isArtPoint[node] = true;
    }

public:
    vector<int> articulationPoints(int n, vector<vector<int>> &edges)
    {
        V = n;
        adj.assign(V, {});
        for (auto &edge : edges)
        {
            int u = edge[0], v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        disc.assign(V, -1);
        low.assign(V, -1);
        visited.assign(V, false);
        isArtPoint.assign(V, false);
        time = 0;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                dfs(i, -1);
        }

        vector<int> ans;
        for (int i = 0; i < V; i++)
            if (isArtPoint[i])
                ans.push_back(i);

        return ans.empty() ? vector<int>{-1} : ans;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> edges = {{0, 1}, {1, 2}, {2, 0}, {1, 3}};
    int V = 4;

    vector<int> result = sol.articulationPoints(V, edges);

    cout << "Articulation Points: ";
    for (int x : result)
        cout << x << " ";
    cout << endl;

    return 0;
}