#include <iostream>
using namespace std;

class Solution
{
public:
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int n, m;

    bool dfs(int i, int j, int k1, int k2, vector<vector<char>> &grid,
             vector<vector<bool>> &visited)
    {
        visited[i][j] = true;

        for (int dir = 0; dir < 4; dir++)
        {
            int x = i + dx[dir];
            int y = j + dy[dir];

            if (x < n && y < m && x >= 0 && y >= 0)
            {
                if (grid[x][y] != grid[i][j])
                    continue;
                if (x == k1 && y == k2)
                    continue;
                if (visited[x][y])
                    return true;
                if (dfs(x, y, i, j, grid, visited))
                    return true;
            }
        }

        return false;
    }
    bool containsCycle(vector<vector<char>> &grid)
    {
        n = grid.size();
        m = grid[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, false));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!visited[i][j])
                {
                    if (dfs(i, j, -1, -1, grid, visited))
                        return true;
                }
            }
        }

        return false;
    }
};

// If i have to return how many cylcles
class Solution
{
public:
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int n, m;

    bool dfs(int i, int j, int pi, int pj, vector<vector<char>> &grid, vector<vector<bool>> &visited)
    {
        visited[i][j] = true;

        for (int dir = 0; dir < 4; dir++)
        {
            int x = i + dx[dir];
            int y = j + dy[dir];

            if (x >= 0 && x < n && y >= 0 && y < m)
            {
                if (grid[x][y] != grid[i][j])
                    continue;

                if (x == pi && y == pj)
                    continue;

                if (visited[x][y])
                    return true;

                if (dfs(x, y, i, j, grid, visited))
                    return true;
            }
        }

        return false;
    }

    int countCycles(vector<vector<char>> &grid)
    {
        n = grid.size();
        m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int cycleCount = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!visited[i][j])
                {
                    if (dfs(i, j, -1, -1, grid, visited))
                    {
                        cycleCount++;
                    }
                }
            }
        }

        return cycleCount;
    }
};

// Using Bfs
class Solution
{
public:
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
    int n, m;

    bool bfs(int i, int j, vector<vector<char>> &grid, vector<vector<bool>> &visited)
    {
        queue<pair<pair<int, int>, pair<int, int>>> q;
        q.push({{i, j}, {-1, -1}}); // ((x, y), (parent_x, parent_y))
        visited[i][j] = true;

        while (!q.empty())
        {
            auto [curr, parent] = q.front();
            q.pop();
            int x = curr.first, y = curr.second;
            int px = parent.first, py = parent.second;

            for (int dir = 0; dir < 4; dir++)
            {
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                // bounds check
                if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == grid[x][y])
                {
                    if (!visited[nx][ny])
                    {
                        visited[nx][ny] = true;
                        q.push({{nx, ny}, {x, y}});
                    }
                    else if (nx != px || ny != py)
                    {
                        // visited and not parent → cycle found
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool containsCycle(vector<vector<char>> &grid)
    {
        n = grid.size();
        m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (!visited[i][j])
                {
                    if (bfs(i, j, grid, visited))
                        return true;
                }
            }
        }

        return false;
    }
};

int main()
{
    return 0;
}