#include <iostream>
using namespace std;

// https : // leetcode.com/problems/rotting-oranges/description/

class Solution
{
public:
    int orangesRotting(vector<vector<int>> &mat)
    {
        // Code here
        int n = mat.size();
        int m = mat[0].size();

        vector<vector<int>> visited(n, vector<int>(m, false));
        queue<pair<int, int>> q;

        int freshOranges = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (mat[i][j] == 2)
                {
                    q.push({i, j});
                    visited[i][j] = true;
                }
                else if (mat[i][j] == 1)
                    freshOranges++;
            }
        }

        int time = 0;
        // Now it's time to Apply Bfs
        int rotted = 0;
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        while (!q.empty())
        {
            int size = q.size();
            bool anyRottenThisMinute = false;

            for (int k = 0; k < size; k++)
            {
                pair<int, int> temp = q.front();
                q.pop();

                int x = temp.first;
                int y = temp.second;

                for (int dir = 0; dir < 4; dir++)
                {
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];

                    if (nx >= 0 && ny >= 0 && nx < n && ny < m && !visited[nx][ny] && mat[nx][ny] == 1)
                    {
                        q.push({nx, ny});
                        visited[nx][ny] = true;
                        rotted++;
                        anyRottenThisMinute = true;
                    }
                }
            }

            if (anyRottenThisMinute)
                time++;
        }

        if (rotted != freshOranges)
            return -1;
        return time;
    }
};

int main()
{
    return 0;
}