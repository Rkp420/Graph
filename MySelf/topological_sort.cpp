#include <iostream>
using namespace std;

// Using Dfs

class Solution
{
public:
    void dfs(int currNode, vector<vector<int>> &adj, vector<bool> &visited, stack<int> &st)
    {
        visited[currNode] = true;

        for (int nbr : adj[currNode])
        {
            if (!visited[nbr])
                dfs(nbr, adj, visited, st);
        }

        st.push(currNode);
    }
    vector<int> topoSort(int V, vector<vector<int>> &edges)
    {
        // code here
        vector<vector<int>> adj(V);

        for (auto &edge : edges)
        {
            int x = edge[0], y = edge[1];

            // Directed Graph
            adj[x].push_back(y);
        }

        vector<bool> visited(V, false);
        stack<int> st;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                dfs(i, adj, visited, st);
        }

        vector<int> ans;
        while (!st.empty())
        {
            ans.push_back(st.top());
            st.pop();
        }

        return ans;
    }
};


// Using Bfs (Kanh's Algo)

class Solution
{
public:
    void dfs(int currNode, vector<vector<int>> &adj, vector<bool> &visited, stack<int> &st)
    {
        visited[currNode] = true;

        for (int nbr : adj[currNode])
        {
            if (!visited[nbr])
                dfs(nbr, adj, visited, st);
        }

        st.push(currNode);
    }
    vector<int> topoSort(int V, vector<vector<int>> &edges)
    {
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

        return ans;
    }
};

int main()
{
    return 0;
}