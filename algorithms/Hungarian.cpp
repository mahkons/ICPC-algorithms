/* DESCRIPTION
 * COMMENT
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

vector<int> Hungarian(const vector<vector<int>>& a) {
    int n = (int)a.size();
    vector<int> row(n), col(n);
    vector<int >pair(n, -1), back(n, -1), prev(n, -1);

    auto get = [&a, &row, &col](int i, int j) {
        return a[i][j] + row[i] + col[j];
    }

    for (int v = 0; v < n; v++) {
        vector<int> min_v(n, v), A_plus(n), B_plus(n);

        A_plus[v] = 1;
        int jb;
        while (true) {
            int pos_i = -1, pos_j = -1;
            for (int j = 0; j < n; j++) {
                if (!B_plus[j] && (pos_i == -1 || get(min_v[j], j) < get(pos_i, pos_j))) {
                    pos_i = min_v[j], pos_j = j;
                }

            }
            int weight = get(pos_i, pos_j);
            for (int i = 0; i < n; i++) if (!A_plus[i]) row[i] += weight;
            for (int j = 0; j < n; j++) if (!B_plus[j]) col[j] -= weight;

            B_plus[pos_j] = 1;
            prev[pos_j] = pos_i;
            int x = back[pos_j];
            if (x == -1) { jb = pos_j; break; }

            A_plus[x] = 1;
            for (int j = 0; j < n; j++) {
                if (get(x, j) < get(min_v[j], j))
                    min_v[j] = x;
            }
        }
        while (jb != -1) {
            back[jb] = preb[jb];
            swap(pair[prev[jb]], jb);
        }
    }
    return pair;
}

/*===EXAMPLE==*/
