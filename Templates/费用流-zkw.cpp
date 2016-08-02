#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<int, int>
#define ivec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define file_hza freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define file_gen(x) freopen(#x".in", "w", stdout);
    const int INF = 0x3f3f3f3f;
    typedef long long LL;
    typedef double DB;
    inline void pc(char c) { putchar(c); }
    template<class T> inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
    template<class T> inline void W(T p) { if(p < 0) pc('-'), p = -p; if(p / 10 != 0) W(p / 10); pc('0' + p % 10); }
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
 
const int maxv = 11000 + 100, maxe = maxv * 8;
 
const int maxn = 100;
 
class MCMF_zkw {
    public:
 
    int edge, head[maxv], to[maxe], next[maxe];
    int cap[maxe], cost[maxe];
    void addedge(int u, int v, int c, int w) {
        to[edge] = v, next[edge] = head[u];
        cap[edge] = c, cost[edge] = w;
        head[u] = edge++;
    }
    void addEdge(int u, int v, int c, int w) {
        addedge(u, v, c, w);
        addedge(v, u, 0, -w);
    }
 
    int s, t, loc;
     
    MCMF_zkw() {
        edge = 0;
        loc = 0;
        memset(head, -1, sizeof head);
    }

	int cur[maxv], dis[maxv], vis[maxv];
	int Flow, Cost, aug_flow;

	int augment(int u, int flow) {
		if (u == t) return flow;
		vis[u] = true;
		for (int &i=cur[u]; i!=-1; i=next[i]) {
			int v = to[i];
			if (cap[i]>0 && !vis[v] && dis[u]==dis[v]+cost[i]) {
				int tmp = augment(v, min(flow, cap[i]));
				cap[i]-=tmp, cap[i^1]+= tmp;
				if (tmp) return tmp;
			}
		}
		return 0;
	}
	bool modify_lable() {
		int d = INF;
		for (int u=0; u<loc; ++u)
			if (vis[u])
				for (int i=head[u]; i!=-1; i=next[i]) {
					int v = to[i];
					if (cap[i]>0 && !vis[v])
						d = min(d, dis[v]+cost[i]-dis[u]);
				}
		if (d==INF) return false;
		for (int i=0; i<loc; ++i)
			if (vis[i]) {
				vis[i] = false;
				dis[i] += d;
			}
		return true;
	}

	pair<int, int> mcmf() {
		Flow = Cost = 0;
		memset(dis, 0, sizeof(int)*loc);
		do {
			memcpy(cur, head, sizeof(int)*loc);
			do {
				memset(vis, 0, sizeof(int)*loc);
				aug_flow = augment(s, INF);
				Flow+=aug_flow, Cost+=aug_flow*dis[s];
			} while (aug_flow!=0);
		} while (modify_lable());
		return make_pair(Flow, Cost);
	}
};
 
MCMF_zkw sv;
int n, g[maxn][maxn];
 
int hash[maxn*maxn], ind[maxn];
int getID(int x, int y) {
    int p = (x-1)*n+y;
    if (hash[(x-1)*n+y])
        return hash[p];
    return hash[p] = ++sv.loc;
}
  
int main() {
 
    fr(n);
    int b = n*(n-1)/2;
    sv.s = 0;
    rep(i, 1, n)
        rep(j, 1, n) {
            g[i][j] = fr();
            if (i <= j)
                continue;
            if (g[i][j]==0) {
                sv.addEdge(getID(i, j), b+j, 1, 0);
                ++ind[j];
            } else if (g[i][j]==1) {
                sv.addEdge(getID(i, j), b+i, 1, 0);
                ++ind[i];
            } else if (g[i][j] == 2) {
                sv.addEdge(getID(i, j), b+j, 1, 0);
                ++ind[j];
                sv.addEdge(getID(i, j), b+i, 1, 0);
                ++ind[i];
            }
        }
    rep(i, 1, b) {
        sv.addEdge(sv.s, i, 1, 0);
    }
 
    sv.t = b+n+1;
    rep(i, 1, n) {
        int u = b+i;
        rep(j, 0, ind[i]-1)
            sv.addEdge(u, sv.t, 1, 2*j+1);
    }
 
    sv.loc = b+n+2;
    pair<int, int> res = sv.mcmf();
     
    int ans = n*(n-1)*(n-2)/2/3+n*(n-1)/2/2-res.second/2;
 
    printf("%d\n", ans);
    //printf("%d\n", res.second);
  
    rep(i, 1, n)
        rep(j, 1, n) {
            if (i<=j || g[i][j]!=2)
                continue;
            int u = getID(i, j);
            for (int s=sv.head[u]; s!=-1; s=sv.next[s]) {
                if (sv.to[s] > u && sv.cap[s] > 0) {
                    if (sv.to[s] == b+i)
                        g[i][j]=0, g[j][i]=1;
                    else g[i][j]=1, g[j][i]=0;
                }
            }
        }
    rep(i, 1, n)
        rep(j, 1, n)
            printf("%d%c", g[i][j], " \n"[j==n]);
 
    return 0;
}


