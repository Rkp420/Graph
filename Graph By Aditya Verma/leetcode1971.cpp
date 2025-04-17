#include <iostream>
using namespace std;

// https://leetcode.com/problems/find-if-path-exists-in-graph/description/

class Solution
{
public:
    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        vector<vector<int>> adj(n);

        for (vector<int> &edge : edges)
        {
            int a = edge[0];
            int b = edge[1];

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vector<bool> isVisited(n, false);

        stack<int> st;
        st.push(source);

        while (!st.empty())
        {
            int node = st.top();
            st.pop();

            // Check if We are on Destination
            if (node == destination)
                return true;

            if (!isVisited[node])
            {
                isVisited[node] = true;
            }

            for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it)
            {
                if (!isVisited[*it])
                    st.push(*it);
            }
        }

        return false;
    }
};

class Solution
{
public:
    void solve(int source, vector<vector<int>> &adj, vector<bool> &isVisited)
    {
        if (isVisited[source])
            return;

        isVisited[source] = true;

        for (auto &node : adj[source])
        {
            if (!isVisited[node])
                solve(node, adj, isVisited);
        }
    }
    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        vector<vector<int>> adj(n);

        for (vector<int> &edge : edges)
        {
            int a = edge[0];
            int b = edge[1];

            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        vector<bool> isVisited(n, false);
        solve(source, adj, isVisited);

        return isVisited[destination];
    }
};

int main()
{
    return 0;
}