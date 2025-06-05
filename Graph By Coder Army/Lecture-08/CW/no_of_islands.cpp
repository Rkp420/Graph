#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/problems/find-the-number-of-islands/1

class Solution
{
public:
    int r;
    int c;

    int row[8] = {-1, -1, -1, 1, 1, 1, 0, 0};
    int col[8] = {-1, 0, 1, -1, 0, 1, -1, 1};

    bool valid(int x, int y)
    {
        return x >= 0 && x < r && y >= 0 && y < c;
    }
    int countIslands(vector<vector<char>> &grid)
    {
        r = grid.size();
        c = grid[0].size();

        int isLands = 0;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (grid[i][j] == 'L')
                {
                    isLands++;
                    queue<pair<int, int>> q;
                    q.push({i, j});

                    while (!q.empty())
                    {
                        int currSize = q.size();

                        while (currSize--)
                        {
                            auto currLand = q.front();
                            q.pop();

                            for (int k = 0; k < 8; k++)
                            {
                                int x = currLand.first + row[k];
                                int y = currLand.second + col[k];

                                if (valid(x, y) && grid[x][y] == 'L')
                                {
                                    grid[x][y] = 'W';
                                    q.push({x, y});
                                }
                            }
                        }
                    }
                }
            }
        }

        return isLands;
    }
};

int main()
{
    return 0;
}