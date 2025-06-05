#include <iostream>
using namespace std;

// First Follow Up : if i have to return all valid paths frome src to destination

vector<vector<int>> allPathsBetweenNodes(
    vector<pair<int, int>> &edges,
    int n, int m, int s, int t)
{
    vector<vector<int>> adj(n);
    for (auto &edge : edges)
    {
        int u = edge.first - 1;
        int v = edge.second - 1;
        adj[u].push_back(v);
        adj[v].push_back(u); // Since the graph is undirected
    }

    vector<vector<int>> result;
    vector<int> path;
    vector<bool> visited(n, false);

    function<void(int)> dfs = [&](int node)
    {
        if (node == t - 1)
        {
            path.push_back(t);
            result.push_back(path);
            path.pop_back();
            return;
        }

        visited[node] = true;
        path.push_back(node + 1); // Store 1-based node

        for (int nbr : adj[node])
        {
            if (!visited[nbr])
            {
                dfs(nbr);
            }
        }

        path.pop_back();
        visited[node] = false; // backtrack
    };

    dfs(s - 1);
    return result;
}

// Second Follow Up : What if i have to return only Best Paths list
// ✅ Key Strategy:
// 1. Use BFS to calculate the shortest distance to each node from source.
// 2. Use DFS + Backtracking to collect only those paths that follow the shortest distance route to t.

vector<vector<int>> allShortestPaths(
    vector<pair<int, int>> &edges,
    int n, int m, int s, int t)
{
    vector<vector<int>> adj(n);
    for (auto &edge : edges)
    {
        int u = edge.first - 1;
        int v = edge.second - 1;
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // Step 1: BFS to calculate minimum distance from source
    vector<int> dist(n, INT_MAX);
    queue<int> q;
    dist[s - 1] = 0;
    q.push(s - 1);

    while (!q.empty())
    {
        int node = q.front();
        q.pop();

        for (int nbr : adj[node])
        {
            if (dist[nbr] > dist[node] + 1)
            {
                dist[nbr] = dist[node] + 1;
                q.push(nbr);
            }
        }
    }

    // Step 2: DFS to collect only shortest paths
    vector<vector<int>> result;
    vector<int> path;

    function<void(int)> dfs = [&](int node)
    {
        if (node == t - 1)
        {
            path.push_back(t);
            result.push_back(path);
            path.pop_back();
            return;
        }

        path.push_back(node + 1); // Store 1-based node

        for (int nbr : adj[node])
        {
            if (dist[nbr] == dist[node] + 1)
            { // Only move along shortest path
                dfs(nbr);
            }
        }

        path.pop_back(); // backtrack
    };

    if (dist[t - 1] != INT_MAX)
        dfs(s - 1); // Only run if path exists

    return result;
}

// ✅ Alternative Approach: BFS-based Parent Tracking + Backtracking

vector<vector<int>> allShortestPathsAlt(vector<pair<int, int>> &edges, int n, int m, int s, int t)
{
    vector<vector<int>> adj(n);
    for (auto &[u, v] : edges)
    {
        adj[u - 1].push_back(v - 1);
        adj[v - 1].push_back(u - 1);
    }

    vector<int> dist(n, INT_MAX);
    vector<vector<int>> parents(n);
    queue<int> q;

    dist[s - 1] = 0;
    q.push(s - 1);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int v : adj[u])
        {
            if (dist[v] > dist[u] + 1)
            {
                dist[v] = dist[u] + 1;
                parents[v].clear();
                parents[v].push_back(u);
                q.push(v);
            }
            else if (dist[v] == dist[u] + 1)
            {
                parents[v].push_back(u);
            }
        }
    }

    vector<vector<int>> result;
    vector<int> path;

    function<void(int)> backtrack = [&](int node)
    {
        path.push_back(node + 1); // store as 1-based
        if (node == s - 1)
        {
            vector<int> temp = path;
            reverse(temp.begin(), temp.end());
            result.push_back(temp);
        }
        else
        {
            for (int par : parents[node])
            {
                backtrack(par);
            }
        }
        path.pop_back();
    };

    if (dist[t - 1] != INT_MAX)
        backtrack(t - 1); // only backtrack if a path exists

    return result;
}

// Third Follow Up : Minimum cost during Shortest Path Between any src to destination

class Solution
{
public:
    int minCostToReachDestination(vector<vector<int>> &adj, int src, int dest)
    {
        int N = adj.size();

        vector<int> dist(N, -1);
        vector<bool> visited(N, false);
        queue<int> q;

        q.push(src);
        visited[src] = true;
        dist[src] = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int nbr : adj[node])
            {
                if (!visited[nbr])
                {
                    visited[nbr] = true;
                    dist[nbr] = dist[node] + 1;
                    q.push(nbr);
                }
            }
        }

        return dist[dest]; // returns -1 if not reachable
    }
};

// Fourth Follow Up : if i have to return one Shortest path between src to dest

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