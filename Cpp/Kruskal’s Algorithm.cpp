#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

struct DSU {
    vector<int> parent, rank;
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

int main() {
    int V, E;
    cout << "Enter vertices and edges: ";
    cin >> V >> E;
    vector<Edge> edges(E);
    cout << "Enter edges (u v w):\n";
    for (int i = 0; i < E; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    sort(edges.begin(), edges.end());
    DSU dsu(V);
    int mstWeight = 0;
    vector<Edge> result;

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mstWeight += e.w;
            result.push_back(e);
        }
    }

    cout << "MST Edges:\n";
    for (auto& e : result)
        cout << e.u << " - " << e.v << " (" << e.w << ")\n";
    cout << "Total MST Weight: " << mstWeight << endl;
}
