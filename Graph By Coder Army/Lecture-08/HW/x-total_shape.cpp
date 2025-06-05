#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/problems/x-total-shapes3617/1?page=2&difficulty%5B%5D=1&category%5B%5D=Graph&sortBy=submissions

class Solution
{
public:
    int r;
    int c;

    int row[4] = {0, 0, -1, 1};
    int col[4] = {-1, 1, 0, 0};

    bool valid(int x, int y)
    {
        return x >= 0 && y >= 0 && x < r && y < c;
    }

    int xShape(vector<vector<char>> &grid)
    {
        r = grid.size();
        c = grid[0].size();

        int count = 0;

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (grid[i][j] == 'X')
                {
                    count++;
                    queue<pair<int, int>> q;
                    grid[i][j] = 'O';
                    q.push({i, j});

                    while (!q.empty())
                    {
                            auto currX = q.front();
                            q.pop();

                            for (int i = 0; i < 4; i++)
                            {
                                int x = currX.first + row[i];
                                int y = currX.second + col[i];

                                if (valid(x, y) && grid[x][y] == 'X')
                                {
                                    grid[x][y] = 'O';
                                    q.push({x, y});
                                }
                            }
                    }
                }
            }
        }

        return count;
    }
};

int main()
{
    return 0;
}