/* Finds maximum flow in O(V E \log C) time
 * tested on
 *      links to problems
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

const int INF = 1'000'000'123;

struct Dinic {
    struct Edge {
        int fr, to, cp, fl, id;
    };

    int n, S, T;
    vector<Edge> es;
    vector<vector<int>> g;
    vector<int> dist, ptr;

    Dinic(int n, int S, int T) : n(n), S(S), T(T), g(n) {}

    void add_edge(int fr, int to, int cp, int id) {
        g[fr].push_back((int)es.size());
        es.push_back({fr, to, cp, id, 0});
        g[to].push_back((int)es.size());
        es.push_back({to, fr, 0, -1, 0});
    }

    bool bfs(int K) {
        dist.assign(n, INF);
        dist[S] = 0;
        queue<int> q {{S}};
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int pos : g[v]) {
                Edge &e = es[pos];
                if (e.fl + K <= e.cp &&
                        dist[e.to] > dist[e.fr] + 1) {
                    dist[e.to] = dist[e.fr] + 1;
                    q.push(e.to);
                }
            }
        }
        return dist[T] < INF;
    }

    int dfs(int v, int push) {
        if (v == T || !push) return push;
        for (int &it = ptr[v]; it < (int)g[v].size(); it++) {
            Edge e = es[g[v][it]];
            if (dist[e.to] != dist[e.fr] + 1) continue;
            if (int val = dfs(e.to, min(push, e.cp - e.fl)); val) {
                e.fl += val;
                es[g[v][it] ^ 1].fl -= val;
                return val;
            }
        }
        return 0;
    }

    ll find_max_flow() {
        ll max_flow = 0;
        for (int K = 1 << 30; K > 0; K >>= 1) {
            while (bfs(K)) {
                ptr.assign(n, 0);
                int add_flow;
                while ((add_flow = dfs(S, INF)))
                    max_flow += add_flow;
            }
        }
        return max_flow;
    }

    bool go(int v, const vector<int>& F, vector<int>& path) {
        if (v == T) return 1;
        for (int ps : g[v]) {
            if (F[ps] && go(es[ps].to, F, path)) {
                path.push_back(ps);
                return 1;
            }
        }
        return 0;
    }

    vector<pair<int, vector<int>>> decomposition() {
        find_max_flow();
        vector<int> F((int)es.size()), path;
        vector<pair<int, vector<int>>> dcmp;
        for (int i = 0; i < (int)es.size(); i++)
            F[i] = es[i].fl;
        while (go(S, F, path)) {
            int mn = INF;
            for (int ps : path) mn = min(mn, F[ps]);
            for (int ps : path) F[ps] -= mn;

            vector<int> add;
            for (int ps : path) add.push_back(es[ps].id);
            reverse(add.begin(), add.end());
            dcmp.push_back({mn, add});
            path.clear();
        }
        return dcmp;
    }


 };


/*===EXAMPLE==*/
