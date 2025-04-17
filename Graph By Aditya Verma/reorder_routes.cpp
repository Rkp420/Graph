#include <iostream>
using namespace std;

// https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/
class Solution
{
public:
    void solve(int node, vector<bool> &visited, vector<vector<int>> &forward, vector<vector<int>> &backward, int &ans)
    {
        visited[node] = true;

        // Forward neighbors: edge from node → nbr needs to be reversed
        for (int nbr : forward[node])
        {
            if (!visited[nbr])
            {
                ans += 1; // this edge needs to be reversed
                solve(nbr, visited, forward, backward, ans);
            }
        }

        // Backward neighbors: edge from nbr → node is correct
        for (int nbr : backward[node])
        {
            if (!visited[nbr])
            {
                solve(nbr, visited, forward, backward, ans);
            }
        }
    }

    int minReorder(int n, vector<vector<int>> &connections)
    {
        vector<vector<int>> forward(n), backward(n);

        for (vector<int> &v : connections)
        {
            int a = v[0], b = v[1];
            forward[a].push_back(b);  // directed edge a → b (may need to reverse)
            backward[b].push_back(a); // reverse direction is correct
        }

        int ans = 0;
        vector<bool> visited(n, false);
        solve(0, visited, forward, backward, ans); // Start DFS from city 0
        return ans;
    }
};
int main()
{
    return 0;
}