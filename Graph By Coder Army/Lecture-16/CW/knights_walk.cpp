#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// https://www.geeksforgeeks.org/problems/knight-walk4521/1?page=2&difficulty%5B%5D=1&category%5B%5D=Graph&sortBy=submissions

// Simple Bfs : Don't Think too much

class Solution
{
public:
    int N;
    int M;

    int dx[8] = {-1, -1, 1, 1, -2, -2, 2, 2};
    int dy[8] = {-2, 2, -2, 2, -1, 1, -1, 1};

    bool isValid(int row, int col)
    {
        return row >= 0 && row < N && col >= 0 && col < M;
    }

    int minStepToReachTarget(vector<int> &KnightPos, vector<int> &TargetPos, int n)
    {
        // Edge Case
        if (KnightPos == TargetPos)
            return 0;

        N = n, M = n;

        // Prepare a Mat
        vector<vector<int>> chess(n, vector<int>(n, 1));

        // Bfs Approach
        int x = KnightPos[0] - 1;
        int y = KnightPos[1] - 1;

        queue<pair<int, int>> q;
        q.push({x, y});

        // Marking the source node as visited
        chess[x][y] = 0;
        int steps = 0;

        while (!q.empty())
        {
            int currSize = q.size();

            while (currSize--)
            {
                auto cord = q.front();
                q.pop();

                for (int i = 0; i < 8; i++)
                {
                    int row = cord.first + dx[i];
                    int col = cord.second + dy[i];

                    if (isValid(row, col) && chess[row][col] == 1)
                    {
                        // Check for destination
                        if (row + 1 == TargetPos[0] && col + 1 == TargetPos[1])
                            return steps + 1;

                        // Marking visited
                        chess[row][col] = 0;
                        q.push({row, col});
                    }
                }
            }

            steps++;
        }

        return -1;
    }
};

int main()
{
    return 0;
}