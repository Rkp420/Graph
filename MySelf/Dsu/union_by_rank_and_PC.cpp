#include <iostream>
#include <vector>
using namespace std;


int findParent(int node, vector<int>& parent){
    if(parent[node] != node) parent[node] = findParent(parent[node], parent);

    return parent[node];
}
void findUnion(int x , int y, vector<int>& parent, vector<int>& rank){
    int x_parent = findParent(x, parent);
    int y_parent = findParent(y, parent);

    if(x_parent == y_parent) return;

    if(rank[x_parent] > rank[y_parent]){
        parent[y_parent] = x_parent;
    }
    else if(rank[x_parent] < rank[y_parent]){
        parent[x_parent] = y_parent;
    }
    else{
        parent[y_parent] = x_parent;
        // Increase Rank by one
        rank[x_parent]++;
    }
}



int main()
{
    // Assume you have this
    int V;
    vector<vector<int>> edges;

    vector<int> parent(V, 0);
    for (int i = 0; i < V; i++)
    {
        parent[i] = i;
    }

    vector<int> rank(V, 0);
    
    return 0;
}