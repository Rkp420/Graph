#include <iostream>
#include <queue>
using namespace std;

// https://www.naukri.com/code360/problems/shortest-path-in-an-unweighted-graph_981297?leftPanelTabValue=SUBMISSIO

class Solution
{
public:
    vector<int> shortestPath(vector<vector<int>> &adj, int src)
    {

        int N = adj.size();

        vector<int> dist(N, -1);
        vector<int> visited(N, 0);
        queue<int> q;
        q.push(src);
        visited[src] = 1;
        dist[src] = 0;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int nbr : adj[node])
            {
                if (visited[nbr] == 0)
                {
                    q.push(nbr);
                    visited[nbr] = 1;
                    dist[nbr] = dist[node] + 1;
                }
            }
        }

        return dist;
    }
};

int main()
{
    return 0;
}