#include <iostream>
#include <vector>
using namespace std;

// https://www.geeksforgeeks.org/problems/euler-circuit-and-path/1?page=3&difficulty%5B%5D=1&category%5B%5D=Graph&sortBy=submissions


class Solution {
  public:
    void dfs(int node, vector<int> adj[], vector<int> &visited){
        visited[node] = true;
        
        for(int nbr : adj[node]){
            if(!visited[nbr]) dfs(nbr, adj, visited);
        }
        
        return;
    }
    
    int isEulerCircuit(int V, vector<int> adj[]) {
        
        // Calculating the Deg of Each Node
        vector<int> NodeDeg(V, 0);
        for(int i = 0; i < V; i++){
            NodeDeg[i] = adj[i].size();
        }
        
        // Check if any of Node has Odd Degree
        int odd = 0;
        for(int deg : NodeDeg) {
            if(deg % 2 != 0){
                odd++;
            }
        }
        
        // Now it's time to check if it's Possible to traverse 
        // all the nodes in one go of dfs 
        vector<int> visited(V, 0);
        int start = -1;
        for(int i = 0; i < V; i++){
            if(NodeDeg[i] > 0) {
                start = i;
                break;
            }
        }
        
        // if There is no any Edge , Treated as Eulerian Circuit
        if(start == -1) return 2;
        
        dfs(start, adj, visited);
        
        for(int i = 0; i < V; i++){
            if(!visited[i] && NodeDeg[i] != 0){
                return 0;
            }
        }
        
        if(odd == 0) return 2;
        else if(odd == 2) return 1;
        else return 0;
    }
};

int main()
{
    return 0;
}