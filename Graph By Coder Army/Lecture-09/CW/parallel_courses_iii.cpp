#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// https://leetcode.com/problems/parallel-courses-iii/description/

class Solution
{
public:
    int minimumTime(int n, vector<vector<int>> &relations, vector<int> &time)
    {
        vector<vector<int>> adj(n);
        vector<int> inDeg(n, 0);

        for (auto &relation : relations)
        {
            adj[relation[0] - 1].push_back(relation[1] - 1);
            inDeg[relation[1] - 1]++;
        }

        vector<int> courseTime(n, 0);
        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (inDeg[i] == 0)
                q.push(i);
        }

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            for (int nbr : adj[curr])
            {
                inDeg[nbr]--;
                if (inDeg[nbr] == 0)
                    q.push(nbr);

                courseTime[nbr] = max(courseTime[nbr], time[curr] + courseTime[curr]);
            }
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            ans = max(ans, courseTime[i] + time[i]);
        }

        return ans;
    }
};


// Another But Same Approach
class Solution
{
public:
    int minimumTime(int n, vector<vector<int>> &relations, vector<int> &time)
    {
        vector<vector<int>> adj(n);
        vector<int> inDeg(n, 0);

        // Correct direction: a -> b (a before b)
        for (auto &relation : relations)
        {
            int u = relation[0] - 1;
            int v = relation[1] - 1;
            adj[u].push_back(v);
            inDeg[v]++;
        }

        vector<int> courseTime(n, 0);
        queue<int> q;

        // Initialize with courses having no prerequisites
        for (int i = 0; i < n; i++)
        {
            if (inDeg[i] == 0)
            {
                q.push(i);
                courseTime[i] = time[i]; // base time for independent courses
            }
        }

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            for (int nbr : adj[curr])
            {
                inDeg[nbr]--;

                // Update time to finish neighbor
                courseTime[nbr] = max(courseTime[nbr], courseTime[curr] + time[nbr]);

                if (inDeg[nbr] == 0)
                {
                    q.push(nbr);
                }
            }
        }

        return *max_element(courseTime.begin(), courseTime.end());
    }
};

int main()
{
    return 0;
}