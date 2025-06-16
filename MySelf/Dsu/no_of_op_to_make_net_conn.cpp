#include <iostream>
#include <vector>
using namespace std;

// https://leetcode.com/problems/number-of-operations-to-make-network-connected/

class Solution
{
public:
    int findParent(int node, vector<int> &parent)
    {
        if (parent[node] != node)
            parent[node] = findParent(parent[node], parent);

        return parent[node];
    }
    int makeConnected(int n, vector<vector<int>> &connections)
    {

        // Edge case
        if (connections.size() < n - 1)
            return -1;

        vector<int> parent(n, 0);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }

        vector<int> rank(n, 0);
        int components = n;

        for (auto connection : connections)
        {
            int u = connection[0];
            int v = connection[1];

            int u_parent = findParent(u, parent);
            int v_parent = findParent(v, parent);

            if (u_parent == v_parent)
                continue;

            components--;
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

        return components - 1;
    }
};

int main()
{
    return 0;
}