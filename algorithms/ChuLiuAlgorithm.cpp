/* Finds minimum spanning tree in directed weighted graph in O(VE) time
 *  TODO there exist a simple O(E \log V) implementation
 *  test on problems
 *      TODO
 * */

/*===TEMPLATE===*/

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <bitset>
#include <random>
#include <memory>
#include <iomanip>

typedef long long ll;
typedef long double ld;

using namespace std;

/*===CODE===*/

struct Edge {
    int to = -1, w = -1, id = -1;
    bool operator < (const Edge& o) const { return w < o.w; }
};

// there should be no edges to root, (root is 0)
vector<Edge> findMST(const vector<vector<Edge>>& g) {
    int n = (int)g.size();
    vector<Edge> emin(n);
    for (int i = 0; i < n; i++) {
        if (!g[i].empty())
            emin[i] = *min_element(g[i].begin(), g[i].end());
    }

    vector<vector<int>> cycles;
    vector<int> col(n), used(n, -1);
    iota(col.begin(), col.end(), 0);
    for (int s = 1; s < n; s++) {
        if (used[s] != -1) continue;

        int x = s;
        while (x != -1 && used[x] == -1) {
            used[x] = s;
            x = emin[x].to;
        }
        if (x == -1 || used[x] != s) continue;
        vector<int> cycle = {x};
        for (int y = emin[x].to; y != x; y = emin[y].to) {
            cycle.push_back(y);
            col[y] = x;
        }
        cycles.push_back(cycle);
    }
    if (cycles.empty())
        return emin;

    vector<vector<Edge>> next_graph(n);
    for (int s = 0; s < n; s++) {
        for (const Edge& e : g[s]) {
            if (col[e.to] != col[s])
                next_graph[col[s]].push_back({col[e.to],
                        e.w - emin[s].w, e.id});
        }
    }
    vector<Edge> tree = findMST(next_graph);
    for (const auto& cycle : cycles) {
        Edge out = tree[col[cycle[0]]];
        for (int v : cycle) {
            tree[v] = emin[v];
            for (const Edge& e : g[v])
                if (e.id == out.id)
                    tree[v] = e;
        }
    }
    return tree;
}




/*===EXAMPLE===*/
//TODO
