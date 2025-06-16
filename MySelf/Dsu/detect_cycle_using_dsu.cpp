#include <iostream>
#include <vector>
using namespace std;

// https : // www.geeksforgeeks.org/problems/detect-cycle-using-dsu/1

class Solution
{
public:
    int findParent(int node, vector<int> &parent)
    {
        if (parent[node] != node)
            parent[node] = findParent(parent[node], parent);

        return parent[node];
    }

    int detectCycle(int V, vector<int> adj[])
    {

        vector<int> parent(V, 0);
        for (int i = 0; i < V; i++)
        {
            parent[i] = i;
        }

        vector<int> rank(V, 0);

        for (int u = 0; u < V; u++)
        {
            for (int v : adj[u])
            {
                if (u < v)
                {
                    int u_parent = findParent(u, parent);
                    int v_parent = findParent(v, parent);

                    if (u_parent == v_parent)
                        return 1;

                    if (rank[u_parent] > rank[v_parent])
                    {
                        parent[v_parent] = u_parent;
                    }
                    else if (rank[u_parent] < rank[v_parent])
                    {
                        parent[u_parent] = v_parent;
                    }
                    else
                    {
                        parent[v_parent] = u_parent;
                        // Increase Rank by one
                        rank[u_parent]++;
                    }
                }
            }
        }

        return 0;
    }
};

int main()
{
    return 0;
}