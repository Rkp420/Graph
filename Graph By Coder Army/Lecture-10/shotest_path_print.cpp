#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// https://www.naukri.com/code360/problems/shortest-path-in-an-unweighted-graph_981297?leftPanelTabValue=SUBMISSION

vector<int> shortestPath(vector<pair<int, int>> edges, int n, int m, int s, int t)
{

    vector<vector<int>> adj(n);

    for (auto &edge : edges)
    {
        int u = edge.first - 1;
        int v = edge.second - 1;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> parentNode(n, -1);
    vector<bool> visited(n, false);

    queue<int> q;
    q.push(s - 1);
    visited[s - 1] = true;

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (int nbr : adj[node])
        {
            if (!visited[nbr])
            {
                visited[nbr] = true;
                q.push(nbr);
                parentNode[nbr] = node;
            }
        }
    }

    vector<int> path;
    int curr = t - 1;

    while (curr != -1)
    {
        path.push_back(curr + 1);
        curr = parentNode[curr];
    }

    if (path.back() != s)
    {
        return {-1};
    }

    reverse(path.begin(), path.end());

    return path;
}

int main()
{
    return 0;
}