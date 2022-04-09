#pragma once

#include <random>

#include "mod-op.h"

namespace ICPC {
    typedef long long ll;

    inline bool miller_rabin_random(ll n) {
        static std::mt19937_64 gen;

        if (n <= 2) return (n == 2);
        if (n % 2 == 0) return false;
        ll d = n - 1;
        while (!(d & 1)) d >>= 1;
        
        ll a = gen() % (n - 1) + 1;
        a = mpow(a, d, n);

        if (a == 1) return true;
        for (ll nd = d; nd != n - 1 && a != n - 1; nd <<= 1) a = mmul(a, a, n);
        return (a == n - 1);
    }

    inline bool miller_rabin_det(ll n) {
        static const ll bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23}; // works for n < 3.8e18
        //static const int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}; // n < 3.1e23
        
        if (n <= 2) return (n == 2);
        if (n % 2 == 0) return false;
        ll d = n - 1;
        while (!(d & 1)) d >>= 1;

        for (ll a : bases) {
            if (a == n) return true;
            a = mpow(a, d, n);
            if (a == 1) continue;
            for (ll nd = d; nd != n - 1 && a != n - 1; nd <<= 1) a = mmul(a, a, n);
            if (a != n - 1) return false;
        }
        return true;
    }
} // namespace ICPC
