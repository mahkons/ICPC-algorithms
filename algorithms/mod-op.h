#pragma once

namespace {

typedef long long ll;

template <typename T>
constexpr T msum(T a, T b, T mod) {
    if ((a += b) >= mod) a -= mod;
    return a;
}

template <typename T>
constexpr T msub(T a, T b, T mod) {
    if ((a -= b) < mod) a += mod;
    return a;
}

constexpr int mmul(int a, int b, int mod) {
    return (static_cast<ll>(a) * b) % mod;
}

constexpr ll mmul(ll a, ll b, ll mod) {
    return (static_cast<__int128>(a) * b) % mod;
}

template <typename T, typename K>
constexpr T mpow(T a, K n, T mod) {
    T res = 1;
    for (T now = a; n; n >>= 1, now = mmul(now, now, mod)) {
        if (n & 1) res = mmul(res, now, mod);
    }
    return res;
}

} // namespace ICPC
