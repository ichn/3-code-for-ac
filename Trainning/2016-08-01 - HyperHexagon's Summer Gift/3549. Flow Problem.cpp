#include <bits/stdc++.h>
using namespace std;
namespace my_zone {
#define rep(_i, _k, _j) for(int _i = _k; _i < _j; ++_i)
#define rgo(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define clr(t) memset(t, 0, sizeof t);
#define clo(t, v) memcpy(t, v, sizeof t);
#define cls(t, v) memset(t,v,sizeof t);
#define pc(c) putchar(c)
#define gc() getchar()
    typedef pair<int, int> ipir;
    typedef vector<int> ivec;
    typedef set<int> iset;
    typedef long long LL;
    typedef double DB;
    inline char gchar(char r=gc()) {
        for(;r==' '||r=='\n'||r=='\r';
                r=gc());return r;}
    template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
        if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
        ret = ret * flag;
    }
    inline int fr() { int x; fr(x); return x; }
    template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }

};
using namespace my_zone;

const int INF = 0x7f7f7f7f;

static const int maxE = 5000, maxV = 200 + 100;
struct MaxFlow {
    int e, h[maxV], to[maxE], nxt[maxE], cap[maxE];
    void init() {
        cls(h, -1);
        e = 0;
    }
    void addEdge(int u,int v, int c) {
    //    printf("%d %d %d\n", u, v, c==INF?-1:c);
        to[e] = v, nxt[e] = h[u], cap[e] = c, h[u] = e++;
        to[e] = u, nxt[e] = h[v], cap[e] = 0, h[v] = e++;
    }

    int dis[maxV], que[maxE * 20], qh, qt;
    bool inq[maxV];
    int s, t;

    bool bfs() {
        que[qh = qt = 0] = s;
        clr(inq);
        cls(dis, INF);
        dis[s] = 0;
        inq[s] = 1;
        while (qh <= qt) {
            int u = que[qh++];
            for (int i = h[u]; i != -1; i = nxt[i])
                if (cap[i] > 0 && !inq[to[i]]) {
                    int v = to[i];
                    inq[v] = 1;
                    dis[v] = dis[u] + 1;
                    que[++qt] = v;
                }
        }
        return dis[t] != INF;
    }

    int dfs(int u, int a = 0) {
        if (u == t || a == 0)
            return a;
        int flow = 0, f;
        for (int i = h[u]; i != -1; i = nxt[i])
            if (dis[to[i]] == dis[u]+1 && (f = dfs(to[i], min(a, cap[i]))) > 0) {
                flow += f;
                cap[i] -= f;
                cap[i^1] += f;
                a -= f;
                //if (a == 0) break;
                if (a == 0) {
                    return flow;
                }
            }
        dis[u] = -1;
        // 原来我写了两年的网络流算法都是错的 = = 膜拜wmj大爷
        // wmj orz, he let me know that my network flow algorithm
        // that i write for 2 years is totally wrong!
        return flow;
    }

    int maxFlow() {
        int flow = 0;
        while (bfs())
            flow += dfs(s, INF);
        return flow;
    }
};

MaxFlow mf;

int n, m;

int main() {
#ifdef lol
    freopen("1005.in", "r", stdin);
    freopen("1005.out", "w", stdout);
#endif
    int T = fr();
    for (int tt = 1; tt <= T; ++tt) {
        scanf("%d %d", &n, &m);
        mf.init();
        mf.s = 1;
        mf.t = n;
        for (int i = 1; i <= m; ++i) {
            int u, v, w;
            fr(u, v, w);
            mf.addEdge(u, v, w);
        }
        printf("Case %d: %d\n", tt, mf.maxFlow());
    }

    return 0;
}
