#include <iostream>
using namespace std;

// Using DFS
class Solution
{
public:
    bool solve(int node, vector<vector<int>> &adj, vector<bool> &path, vector<bool> &visited)
    {
        path[node] = true;

        for (int nbr : adj[node])
        {
            if (path[nbr])
                return true;

            if (visited[nbr])
                continue;

            if (solve(nbr, adj, path, visited))
                return true;
        }

        path[node] = false;

        return false;
    }

    bool isCyclic(int V, vector<vector<int>> &edges)
    {
        // code here
        vector<vector<int>> adj(V);

        for (auto &edge : edges)
        {
            int x = edge[0];
            int y = edge[1];

            adj[x].push_back(y);
        }

        vector<bool> visited(V, false);
        vector<bool> path(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                if (solve(i, adj, path, visited))
                    return true;
                visited[i] = true;
            }
        }

        return false;
    }
};

class Solution
{
public:
    bool solve(int node, vector<vector<int>> &adj, vector<bool> &path, vector<bool> &visited)
    {
        path[node] = true;
        visited[node] = true;

        for (int nbr : adj[node])
        {
            if (path[nbr])
                return true;

            if (!visited[nbr] && solve(nbr, adj, path, visited))
                return true;
        }

        path[node] = false;

        return false;
    }

    bool isCyclic(int V, vector<vector<int>> &edges)
    {
        // code here
        vector<vector<int>> adj(V);

        for (auto &edge : edges)
        {
            int x = edge[0];
            int y = edge[1];

            adj[x].push_back(y);
        }

        vector<bool> visited(V, false);
        vector<bool> path(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                if (solve(i, adj, path, visited))
                    return true;
            }
        }

        return false;
    }
};
// Using BFS

class Solution
{
public:
    bool isCyclic(int V, vector<vector<int>> &edges)
    {
        // code here
        // code here
        vector<vector<int>> adj(V);

        for (auto &edge : edges)
        {
            int x = edge[0], y = edge[1];

            // Directed Graph
            adj[x].push_back(y);
        }

        vector<int> indeg(V, 0);

        for (int i = 0; i < V; i++)
        {
            for (int nbr : adj[i])
                indeg[nbr]++;
        }

        // Push All Elements to queue
        queue<int> q;
        for (int i = 0; i < V; i++)
        {
            if (!indeg[i])
                q.push(i);
        }

        vector<int> ans;
        while (!q.empty())
        {
            int node = q.front();
            ans.push_back(node);
            q.pop();

            for (int nbr : adj[node])
            {
                indeg[nbr]--;
                if (indeg[nbr] == 0)
                    q.push(nbr);
            }
        }

        int count = ans.size();

        return count != V;
    }
};


int main()
{
    return 0;
}