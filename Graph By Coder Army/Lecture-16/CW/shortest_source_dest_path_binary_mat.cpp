#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// https://www.geeksforgeeks.org/problems/shortest-source-to-destination-path3544/1?page=1&difficulty%5B%5D=1&category%5B%5D=Graph&sortBy=submissions

// Most Optimised : Avoid Using of Visited Array -> Instead this mark that cord by '0'

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

    int shortestDistance(int n, int m, vector<vector<int>> A, int X, int Y)
    {
        // Edge cases
        if (X == 0 && Y == 0)
            return 0;
        if (A[0][0] == 0)
            return -1;

        N = n;
        M = m;

        // Start Bfs from start
        queue<pair<int, int>> q;
        q.push({0, 0});
        A[0][0] = 0;
        int steps = 0;

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

                    if (isValid(row, col) && A[row][col] == 1)
                    {

                        // Check for Destination
                        if (row == X && col == Y)
                            return steps + 1;

                        A[row][col] = 0;
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