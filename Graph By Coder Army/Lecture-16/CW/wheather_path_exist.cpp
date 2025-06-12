#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// https://www.geeksforgeeks.org/problems/find-whether-path-exist5238/1?page=1&difficulty%5B%5D=1&category%5B%5D=Graph&sortBy=submissions

class Solution
{
public:
    int N;
    int M;

    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    bool isValid(int row, int col)
    {
        return row >= 0 && row < N && col >= 0 && col < M;
    }

    bool solve(pair<int, int> &src, pair<int, int> &dest, vector<vector<int>> &grid)
    {
        // Start Bfs from start
        int x = src.first;
        int y = src.second;

        queue<pair<int, int>> q;
        q.push({x, y});
        grid[x][y] = 0;

        while (!q.empty())
        {
            int currSize = q.size();

            while (currSize--)
            {
                pair<int, int> cord = q.front();
                q.pop();

                for (int i = 0; i < 4; i++)
                {
                    int row = cord.first + dx[i];
                    int col = cord.second + dy[i];

                    if (isValid(row, col) && grid[row][col] == 3)
                    {

                        // Check for Destination
                        if (row == dest.first && col == dest.second)
                            return true;

                        grid[row][col] = 0;
                        q.push({row, col});
                    }
                }
            }
        }

        return false;
    }

    bool is_Possible(vector<vector<int>> &grid)
    {
        // first is to find source and destination
        N = grid.size();
        M = grid[0].size();

        pair<int, int> src;
        pair<int, int> dest;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (grid[i][j] == 1)
                {
                    src.first = i;
                    src.second = j;
                    grid[i][j] = 3;
                }

                if (grid[i][j] == 2)
                {
                    dest.first = i;
                    dest.second = j;
                    grid[i][j] = 3;
                }
            }
        }

        // Apply Bfs on the grid
        return solve(src, dest, grid);
    }
};

int main()
{
    return 0;
}