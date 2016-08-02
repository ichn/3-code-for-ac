#include <bits/stdc++.h>
using namespace std;

const int maxN = 100000 + 100;
const int maxE = 1000000 + 100;

struct Edge {
    int a, b, c;
    void read() {
        scanf("%d %d %d", &a, &b, &c);
    }
    bool operator < (const Edge&rhs) const {
        return c < rhs.c;
    }
} e[maxE];
int n, m;
int fa[maxN];

struct adjEdge {
    int ec, h[maxN], to[maxN<<1], nxt[maxN<<1], cost[maxN<<1];
    void init() {
        ec = 0;
        memset(h, -1, sizeof h);
    }
    void addEdge(int u, int v, int c) {
        to[ec] = v,  cost[ec] = c, nxt[ec] = h[u], h[u] = ec++;
        to[ec] = u,  cost[ec] = c, nxt[ec] = h[v], h[v] = ec++;
    }
} eg;

typedef long long LL;

int findFa(int u) {
    return fa[u] == u ? u : (fa[u] = findFa(fa[u]));
}

int sz[maxN];

double ans2;

void dfs(int u) {
    sz[u] = 1;
    for (int i = eg.h[u]; i != -1; i = eg.nxt[i]) {
        int v = eg.to[i];
        if (fa[v] == -1) {
            fa[v] = u;
            dfs(v);
            sz[u] += sz[v];
            ans2 += 1.0 * eg.cost[i] * sz[v] * (n - sz[v]) / (n * (n - 1.0) / 2.0);
        }
    }
}

int main() {
#ifdef lol
    freopen("1.in", "r", stdin);
    freopen("1.out", "w", stdout);
#endif
    int tCase;
    scanf("%d", &tCase);
    while (tCase--) {
        scanf("%d %d", &n, &m);
        for (int i = 1; i <= m; ++i) {
            e[i].read();
        }
        sort(e + 1, e + m + 1);
        LL ans = 0;
        ans2 = 0;
        eg.init();
        for (int i = 1; i <= n; ++i)
            fa[i] = i;
        for (int i = 1; i <= m; ++i) {
            if (findFa(e[i].a) != findFa(e[i].b)) {
                ans += e[i].c;
                fa[findFa(e[i].a)] = findFa(e[i].b);
                eg.addEdge(e[i].a, e[i].b, e[i].c);
            }
        }
        memset(fa, -1, sizeof fa);
        memset(sz, 0, sizeof sz);
        fa[1] = 0;
        dfs(1);
        cout << ans;
        printf(" %.2f\n", ans2);
    }
    return 0;
}
