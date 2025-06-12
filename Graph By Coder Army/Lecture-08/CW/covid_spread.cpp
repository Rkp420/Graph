#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// https://www.geeksforgeeks.org/problems/covid-spread--141631/1

class Solution
{
public:
    int r;
    int c;
    int row[4] = {0, 0, 1, -1};
    int col[4] = {-1, 1, 0, 0};

    bool valid(int x, int y)
    {
        return x >= 0 && x < r && y >= 0 && y < c;
    }

    int helpaterp(vector<vector<int>> hospital)
    {
        r = hospital.size();
        c = hospital[0].size();

        queue<pair<int, int>> infectedPatients;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (hospital[i][j] == 2)
                    infectedPatients.push({i, j});
            }
        }

        int totalTime = 0;
        while (!infectedPatients.empty())
        {
            int currSize = infectedPatients.size();
            bool infectionSpread = false;
            while (currSize--)
            {
                auto currPatient = infectedPatients.front();
                infectedPatients.pop();

                for (int i = 0; i < 4; i++)
                {
                    int x = currPatient.first + row[i];
                    int y = currPatient.second + col[i];
                    if (valid(x, y) && hospital[x][y] == 1)
                    {
                        hospital[x][y] == 2;
                        infectedPatients.push({x, y});
                        infectionSpread = true;
                    }
                }
            }

            if (infectionSpread)
                totalTime++;
        }

        // Edge Case
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (hospital[i][j] == 1)
                    return -1;
            }
        }

        return totalTime;
    }
};

int main()
{
    return 0;
}