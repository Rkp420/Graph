#include <iostream>
#include <vector>
using namespace std;

int helperForFindParent(int node, vector<int> &parent)
{
    // Path Compression
    if (parent[node] != node)
        parent[node] = helperForFindParent(parent[node], parent);

    return parent[node];
}

int findParent(int V, vector<vector<int>> edges)
{

    vector<int> parent(V, 0);
    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
    }

    // Now process the edge
    for (auto edge : edges)
    {
        int u = edge[0];
        int v = edge[1];

        int p1 = helperForFindParent(u, parent);
        int p2 = helperForFindParent(v, parent);

        if (p1 == p2)
            continue;

        // Now it's time to merge the one node into the another
        parent[p1] = p2;
    }
}

int main()
{

    return 0;
}