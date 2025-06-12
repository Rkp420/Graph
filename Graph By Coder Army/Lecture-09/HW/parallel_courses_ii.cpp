#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// https://leetcode.com/problems/parallel-courses-ii/description/

// My Approach is Failing for large testCases where multiple ways exist to complete the task and we have to find the minimum so we have to go with the dp approach where we momoise these multiple ways using Bitmask Dp Approach

// My Approach

class Solution
{
public:
    int minNumberOfSemesters(int n, vector<vector<int>> &relations, int k)
    {

        vector<vector<int>> adj(n);
        vector<int> inDeg(n, 0);

        for (auto &relation : relations)
        {
            int u = relation[0] - 1;
            int v = relation[1] - 1;

            adj[u].push_back(v);
            inDeg[v]++;
        }

        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (inDeg[i] == 0)
                q.push(i);
        }

        int count = 0;
        while (!q.empty())
        {
            int currSize = q.size();
            int take = min(k, currSize);

            while (take--)
            {
                int node = q.front();
                q.pop();

                for (int nbr : adj[node])
                {
                    inDeg[nbr]--;
                    if (!inDeg[nbr])
                        q.push(nbr);
                }
            }
            count++;
        }

        return count;
    }
};

// BitMask Dp Approach

class Solution
{
public:
    int minNumberOfSemesters(int n, vector<vector<int>> &relations, int k)
    {
        vector<int> prereq(n, 0);
        for (auto &rel : relations)
        {
            int u = rel[0] - 1;
            int v = rel[1] - 1;
            prereq[v] |= (1 << u);
        }

        int ALL_DONE = (1 << n) - 1;
        vector<int> dp(1 << n, INT_MAX);
        dp[0] = 0;

        for (int mask = 0; mask < (1 << n); ++mask)
        {
            if (dp[mask] == INT_MAX)
                continue;

            // find all courses that can be taken
            vector<int> available;
            for (int i = 0; i < n; ++i)
            {
                if ((mask & (1 << i)) == 0 && (prereq[i] & mask) == prereq[i])
                {
                    available.push_back(i);
                }
            }

            int sz = available.size();
            // try all subsets of available courses with size <= k
            for (int sub = 0; sub < (1 << sz); ++sub)
            {
                if (__builtin_popcount(sub) > k)
                    continue;
                int newMask = mask;
                for (int j = 0; j < sz; ++j)
                {
                    if (sub & (1 << j))
                    {
                        newMask |= (1 << available[j]);
                    }
                }
                if (newMask != mask)
                {
                    dp[newMask] = min(dp[newMask], dp[mask] + 1);
                }
            }
        }

        return dp[ALL_DONE];
    }
};

int main()
{
    return 0;
}