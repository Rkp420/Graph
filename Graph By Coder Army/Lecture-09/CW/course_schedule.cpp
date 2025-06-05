#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/problems/course-schedule/1?page=2&difficulty%5B%5D=1&category%5B%5D=Graph&sortBy=submissions

// Using Dfs

class Solution
{
public:
    bool solve(int node, vector<vector<int>> &adj, vector<bool> &path, vector<bool> &visited)
    {
        visited[node] = true;
        path[node] = true;

        for (int nextNode : adj[node])
        {
            if (path[nextNode])
                return true;

            if (visited[nextNode])
                continue;

            if (!visited[nextNode] && solve(nextNode, adj, path, visited))
                return true;
        }

        path[node] = false;
        return false;
    }

    bool isCyclePresent(int N, vector<vector<int>> &adj)
    {
        vector<bool> visited(N, false);
        vector<bool> path(N, false);

        for (int i = 0; i < N; i++)
        {
            if (!visited[i])
            {
                if (solve(i, adj, path, visited))
                    return true;
            }
        }

        return false;
    }

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

    vector<int> findOrder(int n, vector<vector<int>> prerequisites)
    {

        // Making a Adjacency List
        vector<vector<int>> adj(n);

        for (auto &prerequisite : prerequisites)
        {
            adj[prerequisite[1]].push_back(prerequisite[0]);
        }

        // Now Detect First if Cycle is Present or Not
        if (isCyclePresent(n, adj))
            return {};

        vector<bool> visited(n, false);
        stack<int> st;

        for (int i = 0; i < n; i++)
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
    vector<int> findOrder(int n, vector<vector<int>> prerequisites)
    {

        // Making a Adjacency List
        vector<vector<int>> adj(n);
        vector<int> inDeg(n, 0);
        for (auto &prerequisite : prerequisites)
        {
            adj[prerequisite[1]].push_back(prerequisite[0]);
            inDeg[prerequisite[0]]++;
        }

        // Applying Kanh's Algo
        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (!inDeg[i])
                q.push(i);
        }

        vector<int> ans;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            ans.push_back(node);

            for (int nbr : adj[node])
            {
                inDeg[nbr]--;
                if (!inDeg[nbr])
                    q.push(nbr);
            }
        }

        return ans.size() == n ? ans : vector<int>{};
    }
};

int main()
{
    return 0;
}