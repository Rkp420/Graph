#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// https : // leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/

class Solution
{
public:
    vector<int> parent;
    vector<int> rank;

    int find(int x)
    {
        if (x == parent[x])
            return x;

        return parent[x] = find(parent[x]);
    }

    void Union(int x, int y)
    {
        int x_parent = find(x);
        int y_parent = find(y);

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

    long long countPairs(int n, vector<vector<int>> &edges)
    {
        parent.resize(n, 0);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;

        // Step 2 : Ready the components
        for (auto edge : edges)
        {
            int u = edge[0];
            int v = edge[1];

            Union(u, v);
        }

        // Step 3 : Storing the components size
        unordered_map<int, int> mp;
        for (int i = 0; i < n; i++)
        {
            int parentNode = find(i);
            mp[parentNode]++;
        }

        // Step 4 : Processing the map
        long long res = 0;
        long long remainingNodes = n;
        for (auto &it : mp)
        {
            int size = it.second;

            res += size * (remainingNodes - size);
            remainingNodes -= size;
        }

        return res;
    }
};

int main()
{
    return 0;
}