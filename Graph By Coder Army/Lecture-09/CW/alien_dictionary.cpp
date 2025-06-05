#include <iostream>
#include <unordered_set>
using namespace std;

// https://www.geeksforgeeks.org/problems/alien-dictionary/1?page=1&difficulty%5B%5D=2&category%5B%5D=Graph&sortBy=submissions

// Using Bfs
class Solution
{
public:
    string findOrder(vector<string> &words)
    {

        int size = words.size();

        vector<vector<int>> adj(26);
        vector<int> inDeg(26, 0);

        unordered_set<char> usedChars;
        for (string &s : words)
        {
            for (char ch : s)
                usedChars.insert(ch);
        }

        for (int k = 0; k < size - 1; k++)
        {
            string first = words[k];
            string second = words[k + 1];

            int i = 0;
            int j = 0;
            while (i < first.size() && j < second.size())
            {
                if (first[i] != second[j])
                {
                    adj[first[i] - 'a'].push_back(second[j] - 'a');
                    inDeg[second[j] - 'a']++;
                    break;
                }
                i++;
                j++;
            }
            if (i == second.size() && i < first.size())
                return "";
        }

        // Now we have our adjacency list and Indeg

        // Applying Kanh's Algo
        queue<int> q;
        for (int i = 0; i < 26; i++)
        {
            if (inDeg[i] == 0 && usedChars.count('a' + i))
                q.push(i);
        }

        string ans;

        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            ans.push_back(node + 'a');

            for (int nbr : adj[node])
            {
                inDeg[nbr]--;
                if (!inDeg[nbr])
                    q.push(nbr);
            }
        }

        return ans.size() == usedChars.size() ? ans : "";
    }
};

int main()
{
    return 0;
}