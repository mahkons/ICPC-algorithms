#pragma once

#include <algorithm>
#include <random>

#include "mod-op.h"
#include "miller-rabin.h"

namespace ICPC {
    typedef long long ll;
    
    inline ll pollard(ll n) {
        static std::mt19937_64 gen;
        static const int LOG = 50;
        if (n <= 1 || miller_rabin_det(n)) return 1;
        if (!(n & 1)) return 2;

        auto f = [n](ll x) { return mmul(x, x, n) + 1; }; // it is ok if 0 == n
        for (int st = 2, lg = 0; ; st = gen() % n) {
            ll cur = 1;
            for (ll x = st, y = f(st); x != y; x = f(x), y = f(f(y))) {
                if (ll c = mmul(cur, std::abs(x - y), n); c) cur = c;
                if (lg++ == LOG) {
                    lg = 0;
                    if (ll val = std::__gcd(cur, n); val != 1) return val;
                }
            }
        }
        return 1;
    }

} // namespace ICPC
