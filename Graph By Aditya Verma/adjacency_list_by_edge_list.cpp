#include <iostream>
using namespace std;

class Solution
{
public:
    // Function to return the adjacency list for each vertex.
    vector<vector<int>> printGraph(int V, vector<pair<int, int>> &edges)
    {
        // Code here
        vector<vector<int>> ans(V);

        for (auto &v : edges)
        {
            int x = v.first;
            int y = v.second;
            ans[x].push_back(y);
            ans[y].push_back(x);
        }

        return ans;
    }
};

int main()
{
    return 0;
}