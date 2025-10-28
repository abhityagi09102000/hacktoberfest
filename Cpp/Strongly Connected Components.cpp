#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs1(int node, vector<bool>& visited, stack<int>& st, vector<vector<int>>& adj) {
    visited[node] = true;
    for (int v : adj[node])
        if (!visited[v])
            dfs1(v, visited, st, adj);
    st.push(node);
}

void dfs2(int node, vector<bool>& visited, vector<vector<int>>& adjT) {
    visited[node] = true;
    cout << node << " ";
    for (int v : adjT[node])
        if (!visited[v])
            dfs2(v, visited, adjT);
}

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> adj(V);
    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    stack<int> st;
    vector<bool> visited(V, false);

    for (int i = 0; i < V; i++)
        if (!visited[i])
            dfs1(i, visited, st, adj);

    // Transpose graph
    vector<vector<int>> adjT(V);
    for (int u = 0; u < V; u++)
        for (int v : adj[u])
            adjT[v].push_back(u);

    fill(visited.begin(), visited.end(), false);
    cout << "\nStrongly Connected Components:\n";

    while (!st.empty()) {
        int node = st.top();
        st.pop();
        if (!visited[node]) {
            dfs2(node, visited, adjT);
            cout << endl;
        }
    }

    return 0;
}
