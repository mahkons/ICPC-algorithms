/* Optimizes linear function under a set of linear constraints
 * Commonly works in O(nm) time. Yet actually it works in exponential time
 * tested on
 *      links to problems TODO
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
#include <valarray>

typedef long long ll;
typedef long double ld;

using namespace std;

/*===CODE===*/

struct Simplex {
    const ld eps = 1e-9;

    int n, m;
    vector<valarray<ld>> A;
    vector<int> basis;

    // 0 - is ok, 1 - no solution, 2 - unbounded solution
    int solve(const vector<vector<ld>>& c, const vector<ld>& f) {
        m = c.size();
        n = (int)c[0].size() - 1;

        A = vector<valarray<ld>>(m + 2, valarray<ld>(n + m + 2));
        for (int i = 0; i < m; i++) A[i][i] = 1;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j + m] = c[i][j];
            }
            A[i][n + m] = -1;
            A[i][n + m + 1] = c[i][n];
        }
        A[m][n + m] = -1;
        for (int j = 0; j < n; j++)
            A[m + 1][j + m] = f[j];

        basis.resize(m);
        iota(basis.begin(), basis.end(), 0);

        if (int err_code = make_kosher(); err_code)
            return err_code;
        if (int err_code = optimize(); err_code)
            return err_code;
        return 0;
    };

    void pivot(int i, int j) {
        int k = 0;
        while (fabs(A[k][i]) < eps) k++;
        A[k] /= A[k][j];
        for (int c = 0; c < (int)A.size(); c++) {
            if (c == k) continue;
            A[c] -= A[k] * A[c][j];
        }
        basis[k] = j;
    }

    int make_kosher() {
        int min_pos = 0;
        for (int pos = 0; pos < m; pos++) {
            if (A[pos][n] < A[min_pos][n])
                min_pos = pos;
        }
        if (A[min_pos][n] < 0) {
            pivot(basis[min_pos], n - 1);
            if (int err_code = optimize(); err_code)
                return err_code;
        }
        int basis_pos = find(basis.begin(), basis.end(), n - 1)
            - basis.begin();
        if (basis_pos != m) {
            if (A[basis_pos][n] > eps) return 1;
            for (int j = 0; j < n - 1; j++) {
                if (fabs(A[basis_pos][j]) > eps) {
                    pivot(n - 1, j);
                    break;
                }
            }
        }
        for (int j = 0; j < m + 2; j++) A[j][n - 1] = 0;
        swap(A[m], A[m + 1]);
        return 0;
    }

    int optimize() {
        while (true) {
            int j = 0;
            while (j < n && A[m][j] < eps) j++;
            if (j == n) break;

            int min_pos = -1;
            for (int pos = 0; pos < m; pos++) {
                if (A[pos][j] > eps) {
                    if (min_pos == -1 || A[min_pos][n] * A[pos][j] >
                            A[pos][n] * A[min_pos][j])
                        min_pos = pos;
                }
            }
            if (min_pos == -1) return 2;
            pivot(basis[min_pos], j);
        }
        return 0;
    }
};


/*===EXAMPLE==*/
