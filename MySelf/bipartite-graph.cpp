#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/problems/bipartite-graph/1

// BFS Approach

class Solution
{
public:
    bool isBipartite(int V, vector<vector<int>> &edges)
    {

        // Making adjacency List
        vector<vector<int>> adj(V);
        for (auto &edge : edges)
        {
            int a = edge[0];
            int b = edge[1];

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vector<int> color(V, -1);

        for (int i = 0; i < V; i++)
        {
            if (color[i] == -1)
            {
                color[i] = 0;

                queue<int> q;
                q.push(i);
                while (!q.empty())
                {
                    int node = q.front();
                    q.pop();

                    for (int next : adj[node])
                    {
                        // if nextNode is not Colored
                        if (color[next] == -1)
                        {
                            color[next] = (color[node] + 1) % 2;
                            q.push(next);
                        }
                        else
                        {
                            if (color[next] == color[node])
                                return false;
                        }
                    }
                }
            }
        }

        return true;
    }
};

// Dfs Approach

class Solution
{
public:
    bool solve(int node, vector<vector<int>> &adj, vector<int> &color)
    {

        for (int next : adj[node])
        {
            if (color[next] == -1)
            {
                color[next] = (color[node] + 1) % 2;
                if (!solve(next, adj, color))
                    return false;
            }
            else
            {
                if (color[next] == color[node])
                    return false;
            }
        }

        return true;
    }
    bool isBipartite(int V, vector<vector<int>> &edges)
    {

        // Making adjacency List
        vector<vector<int>> adj(V);
        for (auto &edge : edges)
        {
            int a = edge[0];
            int b = edge[1];

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vector<int> color(V, -1);

        for (int i = 0; i < V; i++)
        {
            if (color[i] == -1)
            {
                color[i] = 0;

                if (!solve(i, adj, color))
                    return false;
            }
        }

        return true;
    }
};

int main()
{
    return 0;
}