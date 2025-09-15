#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/problems/strongly-connected-component-tarjanss-algo-1587115621/1?page=1&difficulty%5B%5D=2&category%5B%5D=Graph&sortBy=submissions

// First Approach using Kosaraju
class Solution
{
public:
    stack<int> topoSort;
    void dfs(int src, vector<bool> &visited, vector<int> adj[])
    {
        visited[src] = true;

        for (auto neigh : adj[src])
        {
            if (!visited[neigh])
                dfs(neigh, visited, adj);
        }

        topoSort.push(src);
    }
    void dfs2(int src, vector<bool> &visited, vector<vector<int>> &adj, vector<int> &temp)
    {
        visited[src] = true;
        temp.push_back(src);

        for (auto neigh : adj[src])
        {
            if (!visited[neigh])
                dfs2(neigh, visited, adj, temp);
        }
    }
    vector<vector<int>> tarjans(int nodes, vector<int> adj[])
    {
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
        vector<vector<int>> ans;
        vector<bool> visited2(nodes, false);
        while (!topoSort.empty())
        {
            int topNode = topoSort.top();
            topoSort.pop();
            if (!visited2[topNode])
            {
                vector<int> temp;
                dfs2(topNode, visited2, reverseAdj, temp);
                sort(temp.begin(), temp.end());
                ans.push_back(temp);
            }
        }

        // At last sort all SCCs
        sort(ans.begin(), ans.end());
        return ans;
    }
};

// Second : The Tarjan's Algorithm

class Solution
{
public:
    vector<vector<int>> ans;
    stack<int> st;

    void dfs(int node, int &visitedTime, vector<bool> &inStack, vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<int> adj[])
    {
        visited[node] = true;
        disc[node] = low[node] = visitedTime++;
        st.push(node);
        inStack[node] = true;

        for (auto neigh : adj[node])
        {
            if (!visited[neigh])
            {
                dfs(neigh, visitedTime, inStack, visited, disc, low, adj);
                low[node] = min(low[node], low[neigh]);
            }
            else if (inStack[neigh])
            {
                low[node] = min(low[node], disc[neigh]);
            }
        }

        if (low[node] == disc[node])
        {
            vector<int> temp;
            while (!st.empty())
            {
                int el = st.top();
                st.pop();
                inStack[el] = false;
                temp.push_back(el);
                if (el == node)
                    break;
            }
            sort(temp.begin(), temp.end());
            ans.push_back(temp);
        }
    }
    vector<vector<int>> tarjans(int V, vector<int> adj[])
    {
        vector<int> disc(V, -1), low(V, -1);

        vector<bool> visited(V, false), inStack(V, false);
        int visitedTime = 0;
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                dfs(i, visitedTime, inStack, visited, disc, low, adj);
        }

        sort(ans.begin(), ans.end());
        return ans;
    }
};

int main()
{
    return 0;
}