#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/course-schedule-iv/description/

// First Approach : Using Bfs or Dfs For Checkin if There exist a path from u to v for each query;

class Solution
{
public:
    bool dfs(int u, int v, vector<vector<int>> &adj, vector<int> &visited)
    {
        visited[u] = true;
        if (u == v)
            return true;

        bool res = false;
        for (int nbr : adj[u])
        {
            if (!visited[nbr])
                res = res || dfs(nbr, v, adj, visited);
        }

        return res;
    }

    vector<bool> checkIfPrerequisite(int numCourses,
                                     vector<vector<int>> &prerequisites,
                                     vector<vector<int>> &queries)
    {

        vector<vector<int>> adj(numCourses);

        for (auto &prerequisite : prerequisites)
        {
            int u = prerequisite[0];
            int v = prerequisite[1];

            adj[u].push_back(v);
        }

        vector<bool> res;
        for (auto &query : queries)
        {
            int u = query[0];
            int v = query[1];

            vector<int> visited(numCourses, 0);

            res.push_back(dfs(u, v, adj, visited));
        }

        return res;
    }
};

// Second Approach : PreProcessed Information Regarding the info

class Solution
{
public:
    void preprocess(int n, vector<vector<bool>> &isPrerequisite,
                    vector<vector<int>> &adj)
    {
        for (int i = 0; i < n; i++)
        {
            queue<int> q;
            q.push(i);

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                for (int nbr : adj[node])
                {
                    if (!isPrerequisite[i][nbr])
                    {
                        isPrerequisite[i][nbr] = true;
                        q.push(nbr);
                    }
                }
            }
        }
    }

    vector<bool> checkIfPrerequisite(int numCourses,
                                     vector<vector<int>> &prerequisites,
                                     vector<vector<int>> &queries)
    {

        vector<vector<int>> adj(numCourses);
        for (auto &prerequisite : prerequisites)
        {
            int u = prerequisite[0];
            int v = prerequisite[1];

            adj[u].push_back(v);
        }

        vector<vector<bool>> isPrerequisite(numCourses,
                                            vector<bool>(numCourses, false));
        preprocess(numCourses, isPrerequisite, adj);

        vector<bool> res;
        for (auto &query : queries)
        {
            int u = query[0];
            int v = query[1];

            res.push_back(isPrerequisite[u][v]);
        }

        return res;
    }
};



// Third Appraoch : Using Kanh's Algo
class Solution
{
public:
    vector<bool> checkIfPrerequisite(int numCourses,
                                     vector<vector<int>> &prerequisites,
                                     vector<vector<int>> &queries)
    {

        vector<vector<int>> adj(numCourses);
        vector<int> inDeg(numCourses, 0);
        for (auto &prerequisite : prerequisites)
        {
            int u = prerequisite[0];
            int v = prerequisite[1];

            adj[u].push_back(v);
            inDeg[v]++;
        }

        unordered_map<int, unordered_set<int>> nodePrerequisites;

        queue<int> q;
        for (int i = 0; i < numCourses; i++)
            if (inDeg[i] == 0)
                q.push(i);

        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int nbr : adj[node])
            {
                nodePrerequisites[nbr].insert(node);
                for (auto prnodesOfnodes : nodePrerequisites[node])
                {
                    nodePrerequisites[nbr].insert(prnodesOfnodes);
                }

                inDeg[nbr]--;
                if (!inDeg[nbr])
                    q.push(nbr);
            }
        }

        vector<bool> res;
        for (auto &query : queries)
        {
            int u = query[0];
            int v = query[1];

            res.push_back(nodePrerequisites[v].contains(u));
        }

        return res;
    }
};


// Fourth Appraoch : Using Floyd Warshall Algo 
// Uploaded Soon

int main()
{
    return 0;
}