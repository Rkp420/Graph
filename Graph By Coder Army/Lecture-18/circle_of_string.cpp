#include <iostream>
#include <vector>
using namespace std;

// https://www.geeksforgeeks.org/problems/circle-of-strings4530/1?page=1&difficulty%5B%5D=1&category%5B%5D=Graph&sortBy=submissions

class Solution
{
public:
    void dfs(int u, vector<int> adj[], vector<bool> &visited)
    {
        visited[u] = true;

        for (int v : adj[u])
        {
            if (!visited[v])
                dfs(v, adj, visited);
        }
    }

    int isCircle(vector<string> &arr)
    {
        // Making Edge Relation Between words
        vector<int> adj[26];
        vector<int> inDeg(26, 0);
        vector<int> outDeg(26, 0);
        for (string &s : arr)
        {
            int u = s[0] - 'a';
            int v = s[s.size() - 1] - 'a';

            adj[u].push_back(v);
            outDeg[u]++;
            inDeg[v]++;
        }

        // Check if any non zero deg node with not fullfilling
        // the condition : !(inDeg[i] == outDeg[i]) -->  Not an Eulerian circuit
        for (int i = 0; i < 26; i++)
        {
            if (inDeg[i] != outDeg[i])
                return 0;
        }

        // Check for Cycle with simple dfs
        int start = -1;
        for (int i = 0; i < 26; i++)
        {
            if (outDeg[i] > 0)
            {
                start = i;
                break;
            }
        }

        if (start == -1)
            return 1; // if All Nodes arr Seperate then

        vector<bool> visited(26, false);
        dfs(start, adj, visited);

        for (int i = 0; i < 26; i++)
        {
            if ((inDeg[i] > 0 || outDeg[i] > 0) && !visited[i])
                return 0;
        }

        return 1;
    }
};

int main()
{
    return 0;
}