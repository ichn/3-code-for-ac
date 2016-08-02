#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<int, int>
#define ivec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define JINJINJIN #
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
    const int INF = 0x3f3f3f3f;
    typedef long long LL;
    typedef double DB;
    inline void pc(char c) { putchar(c); }
    template<class T> inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
    template<class T> inline void W(T p) { if(p < 0) pc('-'), p = -p; if(p / 10 != 0) W(p / 10); pc('0' + p % 10); } // warning!! slower than printf
    template<class T> inline void Wn(T p) { W(p), brl; } template<class T> inline void W(T a, T b) { W(a), pc(' '), W(b); }
    template<class T> inline void Wn(T a, T b) { W(a), pc(' '), Wn(b); }
    template<class T> inline void W(T a, T b, T c) { W(a), pc(' '), W(b), pc(' '), W(c); } 
    inline char gchar() { char ret = getchar(); for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar()); return ret; }
    template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
        if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
        ret = ret * flag;
    }
    inline int fr() { int x; fr(x); return x; }
    template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }
    template<class T> inline T fast_pow(T base, T index, T mod = 2147483647, T ret = 1) {
        for(; index; index >>= 1, base = base * base % mod) if(index & 1) ret = ret * base % mod;
        return ret;
    }
};
using namespace my_useful_tools;
 
const int maxn = 1e5 + 100;
const int maxf = 19;
const int maxv = maxn, maxe = maxn * 2;
struct Edge {
    int edge, head[maxv], to[maxe], next[maxe];
    Edge() { edge = 0; memset(head, -1, sizeof head); }
    void addedge(int u, int v) {
        to[edge] = v, next[edge] = head[u];
        head[u] = edge++;
    }
} e;
#define lc ch[0]
#define rc ch[1]
struct tree_node {
    int ch[2], w;
    tree_node() {
        ch[0] = ch[1] = w = 0;
    }
} T[maxn * 23];
int root[maxn], loc;
int n, m, val[maxn], d[maxn], id[maxn];
bool cmp(int i, int j) {
    return val[i] < val[j];
}
int dep[maxn], fa[maxn][maxf + 1];
void insert(int l, int r, int &rt, int v) {
    T[++loc] = T[rt], ++T[rt = loc].w;
    if(l == r) return ;
    int mid = (l + r) >> 1;
    if(v <= mid) insert(l, mid, T[rt].lc, v);
    else insert(mid + 1, r, T[rt].rc, v);
}
void dfs(int u) {
    root[u] = root[fa[u][0]];
    insert(1, n, root[u], d[u]);
    for(int i = 1; i <= maxf; ++i)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for(int i = e.head[u]; i != -1; i = e.next[i]) {
        int v = e.to[i];
        if(v != fa[u][0]) {
            fa[v][0] = u;
            dep[v] = dep[u] + 1;
            dfs(v);
        }
    }
}
int lca(int u, int v) {
    if(dep[u] < dep[v]) u ^= v ^= u ^= v;
    for(int i = maxf; 0 <= i; --i) if(dep[fa[u][i]] >= dep[v])
        u = fa[u][i];
    if(u == v) return u;
    for(int i = maxf; 0 <= i; --i) if(fa[u][i] != fa[v][i])
        u = fa[u][i], v = fa[v][i];
    return fa[u][0];
}
int query(const int& a, const int& b, const int& c, const int& d, const int& l, const int& r, const int& rk) {
    if(l == r) return l;
    int k = T[T[a].lc].w + T[T[b].lc].w - T[T[c].lc].w - T[T[d].lc].w, mid = (l + r) >> 1;
    if(rk <= k) return query(T[a].lc, T[b].lc, T[c].lc, T[d].lc, l, mid, rk);
    else return query(T[a].rc, T[b].rc, T[c].rc, T[d].rc, mid + 1, r, rk - k);
}
int re[maxn];
inline int query(const int&u, const int&v, const int&a, const int&rk) {
    int p = query(root[u], root[v], root[a], root[fa[a][0]], 1, n, rk);
    return re[p];
}
 
int main() {
    fr(n, m);
    rep(i, 1, n) fr(val[i]), id[i] = i;
    sort(id + 1, id + n + 1, cmp);
    rep(i, 1, n) d[id[i]] = i, re[i] = val[id[i]];
    rep(i, 2, n) {
        int u, v;
        fr(u, v);
        e.addedge(u, v), e.addedge(v, u);
    }
    fa[1][0] = 0;
    dep[0] = 0;
    dep[1] = 1;
    dfs(1);
    int t, u, v, a, sz, rk;
	int last_ans = 0;
    while(m--) {
        fr(u, v, t), u ^= last_ans, a = lca(u, v), sz = dep[u] + dep[v] - dep[a] * 2 + 1;
		rk = t;
    //  printf("%d %d %d %d\n", u, v, a, rk);
		printf("%d", (last_ans = query(u, v, a, rk)));
		if(m != 0) puts("");
    }
 
    return 0;
}
