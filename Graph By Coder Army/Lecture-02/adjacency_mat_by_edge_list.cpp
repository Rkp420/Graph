#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    // Function to return the adjacency Mat for each vertex.
    vector<vector<int>> printGraph(int V, vector<pair<int, int>> &edges)
    {
        // Answer Matrix
        vector<vector<int>> ans(V, vector<int> (V, 0));

        for (auto &v : edges)
        {
            int x = v.first;
            int y = v.second;
            ans[x][y] = 1;
            ans[y][x] = 1;
        }

        return ans;
    }
};

int main()
{
    return 0;
}