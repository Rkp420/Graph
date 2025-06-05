#include <iostream>
using namespace std;

// https://www.geeksforgeeks.org/problems/rotten-oranges2536/1?page=1&difficulty%5B%5D=1&category%5B%5D=Graph&sortBy=submissions

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

    int orangesRotting(vector<vector<int>> &mat)
    {

        r = mat.size();
        c = mat[0].size();

        int freshOranges = 0;

        queue<pair<int, int>> q;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (mat[i][j] == 2)
                    q.push({i, j});
                if (mat[i][j] == 1)
                    freshOranges++;
            }
        }

        int totalTime = 0;
        while (!q.empty())
        {
            int currSize = q.size();
            bool isRotted = false;

            while (currSize--)
            {
                auto currOrange = q.front();
                q.pop();

                for (int i = 0; i < 4; i++)
                {
                    int x = currOrange.first + row[i];
                    int y = currOrange.second + col[i];

                    if (valid(x, y) && mat[x][y] == 1)
                    {
                        freshOranges--;
                        mat[x][y] = 2;
                        q.push({x, y});
                        isRotted = true;
                    }
                }
            }

            if (isRotted)
                totalTime++;
        }

        return freshOranges > 0 ? -1 : totalTime;
    }
};

int main()
{
    return 0;
}