#include <iostream>
using namespace std;

// Using Bfs
class Solution
{
public:
    // 8 possible moves of a knight
    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
    int minStepToReachTarget(vector<int> &knightPos, vector<int> &targetPos, int N)
    {
        // Code here
        vector<vector<bool>> visited(N + 1, vector<bool>(N + 1, false));

        queue<pair<pair<int, int>, int>> q;
        q.push({{knightPos[0], knightPos[1]}, 0});
        visited[knightPos[0]][knightPos[1]] = true;

        while (!q.empty())
        {
            pair<pair<int, int>, int> temp = q.front();
            q.pop();

            int x = temp.first.first;
            int y = temp.first.second;
            int steps = temp.second;

            if (x == targetPos[0] && y == targetPos[1])
                return steps;

            // Possible Moves From this Point
            for (int i = 0; i < 8; i++)
            {
                int newX = x + dx[i];
                int newY = y + dy[i];

                if (newX >= 1 && newX <= N && newY >= 1 && newY <= N && !visited[newX][newY])
                {
                    visited[newX][newY] = true;
                    q.push({{newX, newY}, steps + 1});
                }
            }
        }

        return -1;
    }
};

// Using Dfs + Memoisation
class Solution
{
public:
    int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
    int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    int dfs(int x, int y, int targetX, int targetY, int N,
            vector<vector<bool>> &visited, int currSteps, int maxDepth,
            vector<vector<int>> &dp)
    {

        if (x < 1 || y < 1 || x > N || y > N)
            return INT_MAX;
        if (visited[x][y])
            return INT_MAX;
        if (currSteps > maxDepth)
            return INT_MAX;

        if (x == targetX && y == targetY)
            return 0;

        if (dp[x][y] != -1)
            return dp[x][y]; // memoized

        visited[x][y] = true;
        int mini = INT_MAX;

        for (int i = 0; i < 8; i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];

            int subSteps = dfs(newX, newY, targetX, targetY, N, visited, currSteps + 1, maxDepth, dp);
            if (subSteps != INT_MAX)
            {
                mini = min(mini, 1 + subSteps);
            }
        }

        visited[x][y] = false;
        dp[x][y] = mini;
        return dp[x][y];
    }

    int minStepToReachTarget(vector<int> &knightPos, vector<int> &targetPos, int N)
    {
        vector<vector<bool>> visited(N + 1, vector<bool>(N + 1, false));
        vector<vector<int>> dp(N + 1, vector<int>(N + 1, -1));
        int maxDepth = N * N; // max depth allowed
        int ans = dfs(knightPos[0], knightPos[1], targetPos[0], targetPos[1], N, visited, 0, maxDepth, dp);
        return (ans == INT_MAX) ? -1 : ans;
    }
};

int main(){

    return 0;
}