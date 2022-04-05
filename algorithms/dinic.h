#pragma once

#include <vector>

namespace ICPC {

using std::vector;
typedef long long ll;

struct Dinic {

    const int INF = 1'000'000'007;

    Dinic(int n, int S, int T) : n(n), S(S), T(T), g(n) {}

    struct Edge {
        int fr, to, c, f;
    };

    void add_edge(int fr, int to, int c) {
        g[fr].push_back(edges.size());
        edges.push_back({fr, to, c, 0});
        g[to].push_back(edges.size());
        edges.push_back({to, fr, 0, 0}); 
    }

    ll find_max_flow() {
        ptr.resize(n);
        d.resize(n);

        ll flow = 0;
        for (int K = (1 << 30); K > 0; K >>= 1) {
            while (bfs(K)) {
                fill(ptr.begin(), ptr.end(), 0);
                ll add_flow;
                while ((add_flow = dfs(S, INF))) {
                    flow += add_flow;
                }
            }
        }
        return flow;
    }

private:
    bool bfs(int K) {
        fill(d.begin(), d.end(), INF);
        d[S] = 0;
        vector<int> q(n);
        q[0] = S;
        for (int l = 0, r = 1; l < r;) {
            int v = q[l++];
            for (int ei : g[v]) {
                const Edge& e = edges[ei];
                if (e.c - e.f >= K && d[e.to] == INF) {
                    d[e.to] = d[v] + 1;
                    q[r++] = e.to;
                }
            }

        }
        return d[T] != INF;
    }

    int dfs(int v, int push) {
        if (v == T) {
            return push;
        }
        for (int& it = ptr[v]; it < (int)g[v].size(); it++) {
            int ei = g[v][it];
            Edge& e = edges[ei];
            if (d[v] + 1 != d[e.to] || e.f == e.c) continue;
            if (int fl = dfs(e.to, std::min(e.c - e.f, push)); fl) {
                e.f += fl;
                edges[ei ^ 1].f -= fl;
                return fl;
            }
        }
        return 0;
    }

private:
    int n, S, T;
    vector<vector<int>> g;
    vector<Edge> edges;
    vector<int> ptr, d;
};

} // namespace ICPC
