#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int mod = 19961993;

LL fpm(LL a, LL i, LL m) {
    LL r = 1;
    for (; i; i >>= 1, a = a * a % m)
        if (i & 1) r = r * a % m;
    return r;
}

bool isPrime(int a) {
    int rt = sqrt(a + .5);
    for (int i = 2; i <= rt; ++i)
        if (a % i == 0)
            return false;
    return true;
}

int P[61], rP[61], cP;

void init() {
    int i = 2;
    cP = 0;
    while (cP != 60) {
        if (isPrime(i)) {
            P[cP] = i;
            rP[cP] = fpm(i, mod - 2, mod);
            ++cP;
        }
        ++i;
    }
}

LL dcp(int s) {
    LL ret = 0;
    for (int i = 0; i < cP; ++i) {
        while (s % P[i] == 0) {
            s /= P[i];
            ret |= (1LL << i);
        }
    }
    return ret;
}

LL phi(LL n, LL s) {
    LL ret = n;
    for (int i = 0; i < cP; ++i) {
        if (s & (1LL << i)) {
            ret = ret * (1 - rP[i] + mod) % mod;
        }
    }
    return ret;
}

const int maxNode = (100000 + 100) << 2;

pair<long long, long long> tr[maxNode];

pair<long long, long long> combine(pair<LL, LL> a, pair<LL, LL> b) {
    return make_pair(a.first * b.first % mod, a.second | b.second);
}

void build(int l, int r, int rt) {
    if (l == r) {
        tr[rt] = make_pair(3, dcp(3));
        return ;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid +1, r, rt << 1 | 1);
    tr[rt] = combine(tr[rt << 1], tr[rt << 1| 1]);
}

void modify(int p, int v, int l, int r, int rt) {
    if (l == r) {
        tr[rt] = make_pair(v, dcp(v));
        return ;
    }
    int mid = (l + r) >> 1;
    if (p <= mid) modify(p, v, l, mid, rt << 1);
    else modify(p, v, mid + 1, r, rt << 1 | 1);
    tr[rt] = combine(tr[rt << 1], tr[rt << 1 | 1]);
}

pair<LL, LL> query(int ql, int qr, int l, int r, int rt) {
    if (ql <= l && r <= qr) {
        return tr[rt];
    }
    int mid = (l + r) >> 1;
    pair<LL, LL> ret = make_pair(1, 0);
    if (ql <= mid) ret = combine(ret, query(ql, qr, l, mid, rt << 1));
    if (mid < qr) ret = combine(ret, query(ql, qr, mid + 1, r, rt << 1 | 1));
    return ret;
}

int main() {

    freopen("10.in", "r", stdin);
    freopen("data.out", "w", stdout);

    init();

    int x;
    scanf("%d", &x);
    build(1, 100000, 1);
    while (x--) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        if (a == 0) {
            pair<LL, LL> res = query(b, c, 1, 100000, 1);
            printf("%d\n", phi(res.first, res.second));
        } else {
            modify(b, c, 1, 100000, 1);
        }
    }
    return 0;
}
