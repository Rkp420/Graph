#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "Enter No of Vertices : ";
    cin >> n;

    int totalEdges = (n * (n - 1)) / 2;
    long long totalGraphs = 1LL << totalEdges;
    
    return 0;
}