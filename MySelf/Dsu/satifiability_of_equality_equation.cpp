#include <iostream>
#include <vector>
using namespace std;

// https : // leetcode.com/problems/satisfiability-of-equality-equations/description/

class Solution
{
public:
    int findParent(int node, vector<int> &parent)
    {
        if (parent[node] != node)
            parent[node] = findParent(parent[node], parent);

        return parent[node];
    }
    void findUnion(int x, int y, vector<int> &parent, vector<int> &rank)
    {
        int x_parent = findParent(x, parent);
        int y_parent = findParent(y, parent);

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
            parent[y_parent] = x_parent;
            // Increase Rank by one
            rank[x_parent]++;
        }
    }
    bool equationsPossible(vector<string> &equations)
    {
        vector<int> parent(26, 0);
        for (int i = 0; i < 26; i++)
        {
            parent[i] = i;
        }

        vector<int> rank(26, 0);

        for (auto equation : equations)
        {
            if (equation[1] == '=')
                findUnion(equation[0] - 'a', equation[3] - 'a', parent, rank);
        }

        for (auto equation : equations)
        {
            if (equation[1] == '!')
            {
                int u_parent = findParent(equation[0] - 'a', parent);
                int v_parent = findParent(equation[3] - 'a', parent);

                if (u_parent == v_parent)
                    return false;
            }
        }

        return true;
    }
};

int main()
{
    return 0;
}