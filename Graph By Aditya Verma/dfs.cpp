#include <iostream>
using namespace std;


class Solution
{
public:
    void solve(int node, vector<vector<int>> &adj, vector<int> &dfs, vector<bool> &isVisited)
    {

        if (isVisited[node])
            return;

        dfs.push_back(node);
        isVisited[node] = true;

        for (int &nextNode : adj[node])
        {
            if (!isVisited[nextNode])
            {
                solve(nextNode, adj, dfs, isVisited);
            }
        }
    }
    vector<int> dfs(vector<vector<int>> &adj)
    {
        // Code here
        int n = adj.size();

        vector<int> ans;
        vector<bool> isVisited(n, false);
        solve(0, adj, ans, isVisited);
        return ans;
    }
};

class Solution
{
public:
    vector<int> dfs(vector<vector<int>> &adj)
    {
        // Code here
        int n = adj.size();

        vector<int> ans;
        vector<bool> isVisited(n, false);

        stack<int> st;

        st.push(0);

        while(!st.empty()){

            int node = st.top();
            st.pop();

            if(!isVisited[node]){
                ans.push_back(node);
                isVisited[node] = true;
            }

            for(auto it = adj[node].rbegin(); it <= adj[node].rend(); it++){
                if(!isVisited[*it]){
                    st.push(*it);
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