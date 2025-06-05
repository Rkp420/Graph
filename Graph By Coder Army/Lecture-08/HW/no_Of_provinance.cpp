#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/problems/number-of-provinces/1

class Solution
{
public:
    void dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, int V)
    {
        visited[node] = true;

        for (int i = 0; i < V; i++)
        {
            if (adj[node][i] == 1 && !visited[i])

                dfs(i, adj, visited, V);
        }
    }

    int numProvinces(vector<vector<int>> adj, int V)
    {

        int n = adj.size();
        vector<bool> visited(V, false);

        int count = 0;
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                count++;
                dfs(i, adj, visited, V);
            }
        }

        return count;
    }
};

int main()
{
    return 0;
}