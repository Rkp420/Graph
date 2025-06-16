#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article

// Using Simple Sorting 
class Solution
{
public:
    vector<int> parent;
    vector<int> rank;

    int findParent(int x)
    {
        if (x == parent[x])
            return x;

        return parent[x] = findParent(parent[x]);
    }

    void Union(int x, int y)
    {
        int x_parent = findParent(x);
        int y_parent = findParent(y);

        if (x_parent == y_parent)
            return;

        if (rank[x_parent] > rank[y_parent])
        {
            parent[y_parent] = x_parent;
        }
        else if (rank[x_parent] < rank[y_parent])
        {
            parent[x_parent] = y_parent;
        }
        else
        {
            parent[x_parent] = y_parent;
            rank[y_parent]++;
        }
    }

    int Kruskal(vector<vector<int>> edges)
    {
        int cost = 0;
        for (auto &edge : edges)
        {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            int u_parent = findParent(u);
            int v_parent = findParent(v);

            if (u_parent != v_parent)
            {
                Union(u, v);
                cost += wt;
            }
        }

        return cost;
    }
    int spanningTree(int V, vector<vector<int>> adj[])
    {

        parent.resize(V);
        rank.resize(V, 0);

        // initialize parent[i] = i
        for (int i = 0; i < V; ++i)
        {
            parent[i] = i;
        }

        // Extract and Make an Edge List with weight
        vector<vector<int>> edges;
        for (int u = 0; u < V; u++)
        {
            for (auto &temp : adj[u])
            {
                int v = temp[0];
                int wt = temp[1];

                edges.push_back({u, v, wt});

                // push only one direction : Little Optimised
                // if (u < v)
                // {
                //     edges.push_back({u, v, wt});
                // }
            }
        }

        // Sort on the basis of wt
        auto comparator = [&](vector<int> &vec1, vector<int> &vec2)
        {
            return vec1[2] < vec2[2];
        };

        sort(edges.begin(), edges.end(), comparator);

        return Kruskal(edges);
    }
};

// Using Priority queue
// Trying new Thing like Tuple
// You can use vector for this
class Solution
{
public:
    vector<int> parent;
    vector<int> rank;

    int findParent(int x)
    {
        if (x == parent[x])
            return x;
        return parent[x] = findParent(parent[x]); // Path compression
    }

    void Union(int x, int y)
    {
        int px = findParent(x);
        int py = findParent(y);

        if (px == py)
            return;

        if (rank[px] > rank[py])
        {
            parent[py] = px;
        }
        else if (rank[px] < rank[py])
        {
            parent[px] = py;
        }
        else
        {
            parent[py] = px;
            rank[px]++;
        }
    }

    int spanningTree(int V, vector<vector<int>> adj[])
    {
        parent.resize(V);
        rank.resize(V, 0);

        for (int i = 0; i < V; i++)
        {
            parent[i] = i;
        }

        // Use Min-Heap to store edges by weight
        using Edge = tuple<int, int, int>; // (weight, u, v)
        priority_queue<Edge, vector<Edge>, greater<Edge>> minHeap;

        vector<vector<bool>> visited(V, vector<bool>(V, false));

        for (int u = 0; u < V; u++)
        {
            for (auto &nbr : adj[u])
            {
                int v = nbr[0];
                int wt = nbr[1];
                if (!visited[u][v])
                {
                    minHeap.push({wt, u, v});
                    visited[u][v] = visited[v][u] = true; // avoid duplicate undirected edges
                }
            }
        }

        int cost = 0;

        while (!minHeap.empty())
        {
            auto [wt, u, v] = minHeap.top();
            minHeap.pop();

            if (findParent(u) != findParent(v))
            {
                Union(u, v);
                cost += wt;
            }
        }

        return cost;
    }
};

// Without Tupple
class Solution
{
public:
    vector<int> parent;
    vector<int> rank;

    int findParent(int x)
    {
        if (x == parent[x])
            return x;

        return parent[x] = findParent(parent[x]);
    }

    void Union(int x, int y)
    {
        int x_parent = findParent(x);
        int y_parent = findParent(y);

        if (x_parent == y_parent)
            return;

        if (rank[x_parent] > rank[y_parent])
        {
            parent[y_parent] = x_parent;
        }
        else if (rank[x_parent] < rank[y_parent])
        {
            parent[x_parent] = y_parent;
        }
        else
        {
            parent[x_parent] = y_parent;
            rank[y_parent]++;
        }
    }

    int spanningTree(int V, vector<vector<int>> adj[])
    {

        parent.resize(V);
        rank.resize(V, 0);

        for (int i = 0; i < V; i++)
        {
            parent[i] = i;
        }

        // Define custom comparator for min-heap of vector<int>
        auto cmp = [](const vector<int> &a, const vector<int> &b)
        {
            return a[2] > b[2]; // min-heap based on weight
        };

        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> minHeap(cmp);

        vector<vector<bool>> visited(V, vector<bool>(V, false));

        for (int u = 0; u < V; u++)
        {
            for (auto &nbr : adj[u])
            {
                int v = nbr[0];
                int wt = nbr[1];
                if (!visited[u][v])
                {
                    minHeap.push({u, v, wt});
                    visited[u][v] = visited[v][u] = true;
                }
            }
        }

        int cost = 0;

        while (!minHeap.empty())
        {
            auto edge = minHeap.top();
            minHeap.pop();

            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];

            if (findParent(u) != findParent(v))
            {
                Union(u, v);
                cost += wt;
            }
        }

        return cost;
    }
};

int main()
{
    return 0;
}