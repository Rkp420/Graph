#include <iostream>
using namespace std;

// In Case Of Undirected Graph
// Using Dfs

class Solution
{
public:
    bool detectCycle(int currNode, int parentNode, vector<vector<int>> &adj, vector<bool> &visited)
    {
        visited[currNode] = 1;

        for (int nbr : adj[currNode])
        {
            if (nbr == parentNode)
                continue;
            else if (visited[nbr])
                return true;
            else
            {
                if (detectCycle(nbr, currNode, adj, visited))
                    return true;
            }
        }

        return false;
    }

    bool isCycle(int V, vector<vector<int>> &edges)
    {
        // Code here
        vector<vector<int>> adj(V);
        for (vector<int> &edge : edges)
        {
            int x = edge[0], y = edge[1];

            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        vector<bool> visited(V, false);

        // May Be Multiple Graphs Means Not Connected 
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                if (detectCycle(i, -1, adj, visited))
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
    bool detectCycle(int currNode, vector<bool>& visited, vector<vector<int>> &adj){
        queue<pair<int, int>> q;
        q.push({currNode, -1});

        while(!q.empty()){
            pair<int, int> curr = q.front();
            q.pop();

            int node = curr.first;
            int parent = curr.second;
            visited[node] = true;
            for(int nbr : adj[node]){
                if(nbr == parent) continue;
                else if(visited[nbr]) return true;
                else{
                    q.push({nbr, node});
                }
            }
        }

        return false;
    }
    bool isCycle(int V, vector<vector<int>> &edges)
    {
        // Code here
        vector<vector<int>> adj(V);
        for (vector<int> &edge : edges)
        {
            int x = edge[0], y = edge[1];

            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        vector<bool> visited(V, false);

        // May Be Multiple Graphs Means Not Connected
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                if (detectCycle(i, visited, adj))
                    return true;
            }
        }

        return false;
    }
};


int main()
{
    return 0;
}