#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define Edges(_i, _u, _e) for(int _i = _e.head[_u]; _i != -1; _i = _e.next[_i])
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
const int maxn = 4e5+100, maxe = maxn<<1;
struct Edge {
	int edge, head[maxn], to[maxe], next[maxe];
	int wei[maxe];
	Edge() { edge = 0; memset(head, -1, sizeof head); }
	void addEdge(int u, int v, int w) {
		to[edge] = v, next[edge] = head[u];
		wei[edge] = w;
		head[u] = edge++;

		to[edge] = u, next[edge] = head[v];
		wei[edge] = w;
		head[v] = edge++;
	}
} e;

LL c[maxn];
int lim;
void modify(int p, int d) {
	for(; p <= lim; c[p] += d, p += p&-p); 
}
LL get_sum(int p) {
	LL ret = 0;
	for(; p; ret += c[p], p -= p&-p);
	return ret;
}


int n, L, Wt;
LL ans;
bool vis[maxn];
int q[maxn], h, t;
int fa[maxn];
int d, Md;

int g[maxn], f[maxn];

int getD(int s) {
	h = 1, t = 0;
	fa[s] = 0, g[s] = f[s] = 0;
	q[++t] = s;
	int d = -1;
	while (h <= t) {
		int u = q[h++];
		Edges(i, u, e) {
			int v = e.to[i];
			if (vis[v] || v == fa[u])
				continue;
			fa[v] = u;
			q[++t] = v;
			g[v] = f[v] = 0;
		}
	}
	red(i, t, 1) {
		int u = q[i], p = fa[u];
		f[p] += (++f[u]);
		g[p] = max(g[p], f[u]);
		g[u] = max(g[u], t-f[u]);
		if (d == -1 || g[u] < g[d])
			d = u;
	}
	vis[d] = true;
	return d;
}

pair<int, int> a[maxn];
int dep[maxn], dis[maxn];
void calc(int p, int o) {
	h = 1, t = 0;
	q[++t] = p, fa[p] = -1;
	while (h <= t) {
		int u = q[h++];
		Edges(i, u, e) {
			int v = e.to[i], w = e.wei[i];
			if (vis[v] || v == fa[u])
				continue;
			dep[v] = dep[u]+1;
			dis[v] = dis[u]+w;
			fa[v] = u;
			q[++t] = v;
		}
	}
	lim = dep[q[t]]+1;
	memset(c+1, 0, sizeof(*c)*lim);
	rep(i, 1, t)
		a[i] = mp(dis[q[i]], dep[q[i]]);
	sort(a+1, a+t+1);

	for(int i = t, j = 1; i; --i) {
		while(j <= t && a[j].first+a[i].first <= Wt)
			modify(a[j++].second+1, 1);
		ans += o*get_sum(max(0, min(lim, L-a[i].second+1)));
	}
}

void solve(int p) {
	dis[p] = dep[p] = 0;
	calc(p, 1);
	Edges(i, p, e) {
		int v = e.to[i];
		if (!vis[v])
			calc(v, -1);
	}
	Edges(i, p, e) {
		int v = e.to[i];
		if (!vis[v]) {
			solve(getD(v));
		}
	}
}

int main() {
#ifdef love_sbit
	file(293E);
#endif
	fr(n, L, Wt);
	reu(i, 1, n) {
		int v, w;
		fr(v, w);
		e.addEdge(v, i+1, w);
	}
	solve(getD(1));
	Wn((ans-n)>>1);

	return 0;
}
