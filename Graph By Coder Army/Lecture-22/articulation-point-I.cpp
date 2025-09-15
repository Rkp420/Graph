#include <iostream>
#include <vector>
using namespace std;

// https://www.geeksforgeeks.org/problems/articulation-point-1/1

// Optimal + Cleaner Version

class Solution
{
    int V;
    vector<int> disc, low;
    vector<bool> visited, isArtPoint;
    vector<int> ans;
    int time;
    vector<int> *adj;

    void dfs(int node, int parent)
    {
        visited[node] = true;
        disc[node] = low[node] = time++;
        int childCount = 0;

        for (int neigh : adj[node])
        {
            if (neigh == parent)
                continue;

            if (!visited[neigh])
            {
                childCount++;
                dfs(neigh, node);

                low[node] = min(low[node], low[neigh]);

                if (parent != -1 && low[neigh] >= disc[node])
                    isArtPoint[node] = true;
            }
            else
            {
                low[node] = min(low[node], disc[neigh]); // back edge
            }
        }

        if (parent == -1 && childCount > 1)
            isArtPoint[node] = true;
    }

public:
    vector<int> articulationPoints(int n, vector<int> adjList[])
    {
        V = n;
        adj = adjList;
        time = 0;
        disc.assign(V, -1);
        low.assign(V, -1);
        visited.assign(V, false);
        isArtPoint.assign(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                dfs(i, -1);
        }

        for (int i = 0; i < V; i++)
            if (isArtPoint[i])
                ans.push_back(i);

        return ans.empty() ? vector<int>{-1} : ans;
    }
};

// Optimal Approach

class Solution
{
public:
    void dfs(int node, int parent, int &time, vector<int> &disc, vector<int> &low, vector<int> adj[], vector<bool> &isArtPoint, vector<bool> &visited)
    {
        visited[node] = true;
        disc[node] = low[node] = time++;
        int childCount = 0;

        for (int neigh : adj[node])
        {
            if (neigh == parent)
                continue;

            if (!visited[neigh])
            {
                childCount++;
                dfs(neigh, node, time, disc, low, adj, isArtPoint, visited);

                low[node] = min(low[node], low[neigh]);

                if (parent != -1 && low[neigh] >= disc[node])
                {
                    isArtPoint[node] = true;
                }
            }
            else
            {
                low[node] = min(low[node], disc[neigh]);
            }
        }

        // Root condition
        if (parent == -1 && childCount > 1)
        {
            isArtPoint[node] = true;
        }
    }

    vector<int> articulationPoints(int V, vector<int> adj[])
    {

        vector<bool> isArtPoint(V, false);
        vector<bool> visited(V, false);
        int time = 0;

        vector<int> disc(V), low(V);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                dfs(i, -1, time, disc, low, adj, isArtPoint, visited);
            }
        }

        vector<int> ans;
        for (int i = 0; i < V; i++)
        {
            if (isArtPoint[i])
                ans.push_back(i);
        }

        if (ans.empty())
            return {-1};
        return ans;
    }
};


int main()
{
    return 0;
}