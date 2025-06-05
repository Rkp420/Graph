#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/problems/prerequisite-tasks/1?page=2&difficulty%5B%5D=1&category%5B%5D=Graph&sortBy=submissions

// Using Dfs
class Solution
{
public:
    bool isCyclePresent(int node, vector<vector<int>> &adj, vector<bool> &path, vector<bool> &visited)
    {
        visited[node] = true;
        path[node] = true;

        for (int nextNode : adj[node])
        {
            if (path[nextNode])
                return true;

            if (visited[nextNode])
                continue;

            if (!visited[nextNode] && isCyclePresent(nextNode, adj, path, visited))
                return true;
        }

        path[node] = false;
        return false;
    }

    bool isPossible(int N, int P, vector<pair<int, int>> &prerequisites)
    {
        // Code here
        vector<vector<int>> adj(N);

        for (auto &prerequisite : prerequisites)
        {
            adj[prerequisite.second].push_back(prerequisite.first);
        }

        vector<bool> visited(N, false);
        vector<bool> path(N, false);

        for (int i = 0; i < N; i++)
        {
            if (!visited[i])
            {
                if (isCyclePresent(i, adj, path, visited))
                    return false;
            }
        }

        return true;
    }
};

// Using Bfs (Kanh's Algo)
class Solution
{
public:
    bool isPossible(int N, int P, vector<pair<int, int>> &prerequisites)
    {

        // Step 1 : Creating a Adj and InDeg
        vector<vector<int>> adj(N);
        vector<int> inDeg(N, 0);

        for (auto &prerequisite : prerequisites)
        {
            adj[prerequisite.second].push_back(prerequisite.first);
            inDeg[prerequisite.first]++;
        }

        // Apply Kanh's Algo
        queue<int> q;
        for (int i = 0; i < N; i++)
        {
            if (inDeg[i] == 0)
                q.push(i);
        }

        int count = 0;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            count++;

            for (int nbr : adj[node])
            {
                inDeg[nbr]--;
                if (inDeg[nbr] == 0)
                    q.push(nbr);
            }
        }

        return count == N;
    }
};

int main()
{
    return 0;
}