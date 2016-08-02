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
 
 
const int maxv = 200 + 10, maxe = 200 * 200 + 100;
struct Edge {
    int edge, head[maxv], to[maxe], next[maxe];
    int cap[maxe];
    Edge() { edge = 0; memset(head, -1, sizeof head); }
    void addedge(int u, int v, int c) {
        to[edge] = v, next[edge] = head[u];
        cap[edge] = c;
        head[u] = edge++;
    }
} ;
 
class MaxFlowDinic {
    static const int maxnode = 200 + 10, maxedge = maxnode * maxnode;
    Edge e;
    int s, t;
    int cur[maxnode], que[maxnode], head, tail, dis[maxnode];
    bool vis[maxnode];
    MaxFlowDinic() {}
 
    bool BFS() {
        memset(vis, false, sizeof vis);
        que[head = tail = 0] = s;
        vis[s] = true;
        dis[s] = 0;
        while(head <= tail) {
            int u = que[head++];
            for(int i = e.head[u]; i != -1; i = e.next[i]) {
                int v = e.to[i], c = e.cap[i];
                if(c > 0 && !vis[v]) {
                    vis[v] = true;
                    dis[v] = dis[u] + 1;
                    que[++tail] = v;
                }
            }
        }
        return vis[t];
    }
 
    int DFS(int u, int a) {
        if(u == t || a == 0) return a;
        int flow = 0, f;
        for(int &i = cur[u]; i != -1; i = e.next[i]) {
            int v = e.to[i], c = e.cap[i];
            if(dis[v] == dis[u] + 1 && (f = DFS(v, min(a, c))) > 0) {
                e.cap[i] -= f, e.cap[i ^ 1] += f;
                flow += f, a -= f;
                if(a == 0) break;
            }
        }
        return flow;
    }
    public:
    MaxFlowDinic(Edge &e):e(e) {}
    int MaxFlow(int _s, int _t) {
        s = _s, t = _t;
        int flow = 0;
        while(BFS()) {
            memcpy(cur, e.head, sizeof cur);
            flow += DFS(s, INF);
        }
        return flow;
    }
};
 
const int maxn = 100 + 10;
int g[maxn][maxn], row[maxn], col[maxn];
int n, m, k;
void end(int pos) {
    puts("JIONG!");
    exit(0);
}
int main() {
    static Edge e = Edge();
    fr(n, m, k);
    rep(i, 1, n) fr(row[i]), row[i] = m - row[i];
    rep(i, 1, m) fr(col[i]), col[i] = n - col[i];
    rep(i, 1, n) if(row[i] < 0) {
        puts("JIONG!");
        return 0;
    }
    rep(i, 1, m) if(col[i] < 0) {
        puts("JIONG!");
        return 0;
    }
    rep(i, 1, k) {
        int a, b;
        fr(a, b);
        --row[a], --col[b];
        if((row[a] < 0) || (col[b] < 0)) {
            puts("JIONG!");
            return 0;
        }
        g[a][b] = 1;
    }
    int s = n + m + 1, t = n + m + 2;
    rep(i, 1, n) {
        e.addedge(s, i, row[i]);
        e.addedge(i, s, 0);
    }
    rep(i, 1, m) {
        e.addedge(n + i, t, col[i]);
        e.addedge(t, n + i, 0);
    }
    rep(i, 1, n) rep(j, 1, m) {
        if(g[i][j] == 0) {
            e.addedge(i, n + j, 1), e.addedge(n + j, i, 0);
        }
    }
 
    MaxFlowDinic *solver = new MaxFlowDinic(e);
    printf("%d\n", n * m - k - solver->MaxFlow(s, t));
 
    return 0;
}
