#include <iostream>
using namespace std;

class Solution
{
public:
    // Function to return Breadth First Traversal of given graph.
    vector<int> bfs(vector<vector<int>> &adj)
    {
        // Code here

        int n = adj.size();

        vector<int> ans;
        vector<bool> isVisited(n, false);

        queue<int> q;
        q.push(0);
        ans.push_back(0);
        isVisited[0] = true;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            vector<int> connectedNodes = adj[node];

            for (int &node : connectedNodes)
            {
                if (!isVisited[node])
                {
                    q.push(node);
                    ans.push_back(node);
                    isVisited[node] = true;
                }
            }
        }

        return ans;
    }
};

int main()
{
    return 0;
}