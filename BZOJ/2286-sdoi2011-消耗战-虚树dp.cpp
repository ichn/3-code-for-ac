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
const int maxv = 250000+1000, maxe = maxv*2;
struct Edge {
	int edge, head[maxv], to[maxe], next[maxe], wei[maxe];
	Edge() { edge = 0; memset(head, -1, sizeof head); }
	void addEdge() {
		int u = fr(), v = fr(), w = fr();
		to[edge] = v, next[edge] = head[u], wei[edge] = w;
		head[u] = edge++;
		to[edge] = u, next[edge] = head[v], wei[edge] = w;
		head[v] = edge++;
	}
} e;

int n, m, k;
int b[maxv], f[maxv];
LL dp[maxv];

int pa[maxv][22], vl[maxv][22], dep[maxv];
int dfs_clock, first_vis[maxv], last_vis[maxv];

void dfs(int u) {
	first_vis[u] = ++dfs_clock;
	for (int i = e.head[u]; i != -1; i = e.next[i]) {
		int v = e.to[i];
		if (v != pa[u][0]) {
			pa[v][0] = u;
			vl[v][0] = e.wei[i];
			dep[v] = dep[u] + 1;
			dfs(v);
		}
	}
	last_vis[u] = dfs_clock;
}

int lca(int u, int v) {
	if (dep[u] < dep[v])
		swap(u, v);
	for (int i=21; 0<=i; --i)
		if (dep[pa[u][i]] >= dep[v])
			u = pa[u][i];
	if (u == v) return u;
	for (int i=21; 0<=i; --i)
		if (pa[u][i] != pa[v][i])
			u = pa[u][i], v = pa[v][i];
	return pa[u][0];
}

int mn_val(int u, int v) {
	int ret = INF;
	if (dep[u] < dep[v])
		swap(u, v);
	for (int i=21; 0<=i; --i)
		if (dep[pa[u][i]] >= dep[v])
			ret = min(ret, vl[u][i]), u = pa[u][i];
	return ret;
	if (u == v) return ret;
	for (int i=21; 0<=i; --i) {
		if (pa[u][i] != pa[v][i])
			ret = min(ret, min(vl[u][i], vl[v][i])), u = pa[u][i], v = pa[v][i];	
	}
	return min(ret, min(vl[u][0], vl[v][0]));
}



int stk[maxv], top, is_ask[maxv];
int fa[maxv], val[maxv];

bool cmp(const int&a, const int&b) {
	return first_vis[a] < first_vis[b];
}

int main() {
#ifdef love_lhy
	file(2286);
#endif

	fr(n);
	rep(i, 2, n) {
		e.addEdge();
	}
	dep[1] = 1;
	vl[1][0] = INF;
	pa[1][0] = 0;
	dfs(1);
	for (int i = 1; i < 22; ++i)
		for (int u = 1; u <= n; ++u) {
			vl[u][i] = min(vl[pa[u][i-1]][i-1], vl[u][i-1]);
			pa[u][i] = pa[pa[u][i-1]][i-1];
		}
	fr(m);
	while (m--) {
		fr(k);

		rep(i, 1, k)
			fr(b[i]), is_ask[b[i]] = 1;
		int cnt = k;
		sort(b+1, b+k+1, cmp);
		for (int i = 1; i < k; ++i) {
			b[++cnt] = lca(b[i], b[i+1]);
		}
		b[++cnt] = 1;
		sort(b+1, b+cnt+1, cmp);
		cnt = unique(b+1, b+cnt+1) - b - 1;
		top = 0;
		for (int i=1; i<=cnt; ++i) {
			while (0 < top && last_vis[b[stk[top]]] < first_vis[b[i]])
				--top;
			fa[i] = 0<top? stk[top] : 0;
			stk[++top] = i;
		}
		for (int i=1; i<=cnt; ++i) {
			if (fa[i]) {
				val[i] = mn_val(b[i], b[fa[i]]);
			}
		}
		memset(dp, 0, sizeof (LL) * (cnt+3));
		for (int i=cnt; 0<i; --i) {
			if (is_ask[b[i]])
				dp[i] = INF;
			if (fa[i] != 0)
				dp[fa[i]] += min(dp[i], (LL)val[i]);
		}
		printf("%lld\n", dp[1]);
		for (int i=1; i<=cnt; ++i)
			is_ask[b[i]] = 0;
	}

	return 0;
}
