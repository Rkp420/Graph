#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// https:// www.geeksforgeeks.org/problems/replace-os-with-xs0052/1?page=2&difficulty%5B%5D=1&category%5B%5D=Graph&sortBy=submissions

class Solution
{
public:
    int r;
    int c;

    int row[4] = {0, 0, -1, 1};
    int col[4] = {-1, 1, 0, 0};

    bool valid(int x, int y) { return x >= 0 && x < r && y >= 0 && y < c; }

    vector<vector<char>> fill(vector<vector<char>> &mat)
    {
        r = mat.size();
        c = mat[0].size();

        // Upper Boundary Traversal
        for (int j = 0; j < c; j++)
        {
            if (mat[0][j] == 'O')
            {
                queue<pair<int, int>> q;
                q.push({0, j});
                mat[0][j] = 'T';

                while (!q.empty())
                {
                    int currSize = q.size();

                    while (currSize--)
                    {
                        auto currPos = q.front();
                        q.pop();

                        for (int i = 0; i < 4; i++)
                        {
                            int x = currPos.first + row[i];
                            int y = currPos.second + col[i];

                            if (valid(x, y) && mat[x][y] == 'O')
                            {
                                q.push({x, y});
                                mat[x][y] = 'T';
                            }
                        }
                    }
                }
            }
        }

        // lower Boundary Traversal
        for (int j = 0; j < c; j++)
        {
            if (mat[r - 1][j] == 'O')
            {
                queue<pair<int, int>> q;
                q.push({r - 1, j});
                mat[r - 1][j] = 'T';

                while (!q.empty())
                {
                    int currSize = q.size();

                    while (currSize--)
                    {
                        auto currPos = q.front();
                        q.pop();

                        for (int i = 0; i < 4; i++)
                        {
                            int x = currPos.first + row[i];
                            int y = currPos.second + col[i];

                            if (valid(x, y) && mat[x][y] == 'O')
                            {
                                q.push({x, y});
                                mat[x][y] = 'T';
                            }
                        }
                    }
                }
            }
        }

        // left Boundary Traversal
        for (int j = 1; j < r; j++)
        {
            if (mat[j][0] == 'O')
            {
                queue<pair<int, int>> q;
                q.push({j, 0});
                mat[j][0] = 'T';

                while (!q.empty())
                {
                    int currSize = q.size();

                    while (currSize--)
                    {
                        auto currPos = q.front();
                        q.pop();

                        for (int i = 0; i < 4; i++)
                        {
                            int x = currPos.first + row[i];
                            int y = currPos.second + col[i];

                            if (valid(x, y) && mat[x][y] == 'O')
                            {
                                q.push({x, y});
                                mat[x][y] = 'T';
                            }
                        }
                    }
                }
            }
        }

        // Right Boundary Traversal
        for (int j = 1; j < r; j++)
        {
            if (mat[j][c - 1] == 'O')
            {
                queue<pair<int, int>> q;
                q.push({j, c - 1});
                mat[j][c - 1] = 'T';

                while (!q.empty())
                {
                    int currSize = q.size();

                    while (currSize--)
                    {
                        auto currPos = q.front();
                        q.pop();

                        for (int i = 0; i < 4; i++)
                        {
                            int x = currPos.first + row[i];
                            int y = currPos.second + col[i];

                            if (valid(x, y) && mat[x][y] == 'O')
                            {
                                q.push({x, y});
                                mat[x][y] = 'T';
                            }
                        }
                    }
                }
            }
        }

        // Now it's Time to Convert the matrix
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (mat[i][j] == 'T')
                    mat[i][j] = 'O';
                else if (mat[i][j] == 'O')
                    mat[i][j] = 'X';
            }
        }

        return mat;
    }
};


// Following DRY Principal

// User function Template for C++

class Solution
{
public:
    int r;
    int c;

    int row[4] = {0, 0, -1, 1};
    int col[4] = {-1, 1, 0, 0};

    bool valid(int x, int y)
    {
        return x >= 0 && x < r && y >= 0 && y < c;
    }

    void bfs(int i, int j, vector<vector<char>> &mat)
    {
        queue<pair<int, int>> q;
        q.push({i, j});
        mat[i][j] = 'T';

        while (!q.empty())
        {
            int currSize = q.size();

            while (currSize--)
            {
                auto currPos = q.front();
                q.pop();

                for (int i = 0; i < 4; i++)
                {
                    int x = currPos.first + row[i];
                    int y = currPos.second + col[i];

                    if (valid(x, y) && mat[x][y] == 'O')
                    {
                        q.push({x, y});
                        mat[x][y] = 'T';
                    }
                }
            }
        }
    }

    vector<vector<char>> fill(vector<vector<char>> &mat)
    {
        r = mat.size();
        c = mat[0].size();

        // Upper and lower Boundary Traversal
        for (int j = 0; j < c; j++)
        {
            if (mat[0][j] == 'O')
                bfs(0, j, mat);
            if (mat[r - 1][j] == 'O')
                bfs(r - 1, j, mat);
        }

        // left and right Boundary Traversal
        for (int j = 1; j < r; j++)
        {
            if (mat[j][0] == 'O')
                bfs(j, 0, mat);
            if (mat[j][c - 1] == 'O')
                bfs(j, c - 1, mat);
        }

        // Now it's Time to Convert the matrix
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (mat[i][j] == 'T')
                    mat[i][j] = 'O';
                else if (mat[i][j] == 'O')
                    mat[i][j] = 'X';
            }
        }

        return mat;
    }
};

int main()
{
    return 0;
}