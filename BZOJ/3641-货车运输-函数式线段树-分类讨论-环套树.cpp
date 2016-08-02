#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
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


int e, h[maxn], to[maxn*2], nxt[maxn*2], dis[maxn*2], rnk[maxn*2];
void addEdge(int u, int v, int c, int d) {
	nxt[e] = h[u], to[e] = v, rnk[e] = c, dis[e] = d, h[u] = e++;
	nxt[e] = h[v], to[e] = u, rnk[e] = c, dis[e] = d, h[v] = e++;
}

int V[maxn], W[maxn];
int n, m, q;

int fa[maxn], pa[maxn][21], cir[maxn], cCnt, onCir[maxn], dep[maxn], owner[maxn], lnk[maxn];

void get_cir(int u) {
	//printf("%d\n", u);
	for (int i=h[u]; i !=-1; i=nxt[i]) {
		if (i != fa[u]) {
			if (dep[to[i]] > 0) {
				cir[++cCnt] = u;
				lnk[cCnt] = fa[u];
				while (u != to[i]) {
					u = to[fa[u]];
					cir[++cCnt] = u;
					lnk[cCnt] = fa[u];
				}
				lnk[cCnt] = i;
				break;
			}
			fa[to[i]] = i^1;
			dep[to[i]] = dep[u]+1;
			get_cir(to[i]);
			if (cCnt != 0) break;
		}
	}
}

const int maxNode = ((maxn<<2)+maxn*30)*2;
#define cn cmt_node
#define lc ch[0]
#define rc ch[1]
struct cmt_node {
	cn*ch[2];
	double a, b;
	cn() {
		ch[0] = ch[1] = NULL;
		a = b = 0.0;
	}
} pool[maxNode], *loc=pool, *root, *trt[maxn], *crt[maxn];

void build(int l, int r, cn*&rt) {
	if (rt == NULL)
		rt = loc++;
	if (l == r) return ;
	int mid=(l+r)>>1;
	build(l, mid, rt->lc);
	build(mid+1, r, rt->rc);
}

int rk;
double aa, ab;
void insert(int l, int r, cn*&rt, cn*pre) {
	rt = loc++;
	rt->a = pre->a+aa, rt->b = pre->b+ab;
	if (l == r) return ;
	int mid = (l+r)>>1;
	if (rk <= mid) rt->rc=pre->rc, insert(l, mid, rt->lc, pre->lc);
	else rt->lc=pre->lc, insert(mid+1, r, rt->rc, pre->rc);
}
double queryA(int ql, int qr, int l, int r, cn*ra, cn*rb, cn*f) {
	if (ql <= l && r <= qr) {
		return ra->a + rb->a - 2.0*f->a;
	}
	int mid = (l+r)>>1;
	double ret = 0.0;
	if (ql <= mid) ret += queryA(ql, qr, l, mid, ra->lc, rb->lc, f->lc);
	if (mid < qr) ret += queryA(ql, qr, mid+1, r, ra->rc, rb->rc, f->rc);
	return ret;
}
double queryB(int ql, int qr, int l, int r, cn*ra, cn*rb, cn*f) {
	if (ql <= l && r <= qr) {
		return ra->b + rb->b - 2.0*f->b;
	}
	int mid = (l+r)>>1;
	double ret = 0.0;
	if (ql <= mid) ret += queryB(ql, qr, l, mid, ra->lc, rb->lc, f->lc);
	if (mid < qr) ret += queryB(ql, qr, mid+1, r, ra->rc, rb->rc, f->rc);
	return ret;
}
double queryA(int ql, int qr, int l, int r, cn*ra, cn*rb) {
	if (ql <= l && r <= qr) {
		return rb->a - ra->a;
	}
	int mid = (l+r)>>1;
	double ret = 0.0;
	if (ql <= mid) ret += queryA(ql, qr, l, mid, ra->lc, rb->lc);
	if (mid < qr) ret += queryA(ql, qr, mid+1, r, ra->rc, rb->rc);
	return ret;
}
double queryB(int ql, int qr, int l, int r, cn*ra, cn*rb) {
	if (ql <= l && r <= qr) {
		return rb->b - ra->b;
	}
	int mid = (l+r)>>1;
	double ret = 0.0;
	if (ql <= mid) ret += queryB(ql, qr, l, mid, ra->lc, rb->lc);
	if (mid < qr) ret += queryB(ql, qr, mid+1, r, ra->rc, rb->rc);
	return ret;
}

void dfs(int u, int f, int top) {
	/*
	if (u == 93078) {
		printf("93078 %d\n", top);
	}
	if (u == 14257) {
		printf("14257 %d\n", top);
	}
	*/
	owner[u] = top;
	//pa[u][0] = f;
	for (int i=h[u]; i!=-1; i=nxt[i])
		if (to[i] != f && !onCir[to[i]]) {
			pa[to[i]][0] = u;
			dep[to[i]] = dep[u]+1;
			rk = rnk[i];
			aa = (DB)dis[i]*W[rk];
			ab = (DB)dis[i]/V[rk]*W[rk];
			insert(1, m, trt[to[i]], trt[u]);
			dfs(to[i], u, top);
		}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	red(i, 20, 0)
		if (dep[pa[u][i]] >= dep[v])
			u = pa[u][i];
	if (u == v) return u;
	red(i, 20, 0)
		if (pa[u][i] != pa[v][i])
			u=pa[u][i], v=pa[v][i];
	return pa[u][0];
}

vector<int> rV;
vector<int>::iterator it;
int getRank(int u) {
	it = upper_bound(rV.begin(), rV.end(), u);
	if (it == rV.end()) return 1;
	int v = it-rV.begin();
	return m-v+1;
}
double qMinCost(int s, int t, int u, int r) {
	if (s == t) return 0;
	int f = lca(s, t);
	double ret = 0.0;
	if (1 <= r-1) ret += queryA(1, r-1, 1, m, trt[s], trt[t], trt[f])/u;
	if (r <= m) ret += queryB(r, m, 1, m, trt[s], trt[t], trt[f]);
	return ret;
}
double qMinCost2(int s, int t, int u, int r) {
	if (t <= s) return 0;
	double ret = 0.0;
	if (1 <= r-1) ret += queryA(1, r-1, 1, m, crt[s], crt[t])/(double)u;
	if (r <= m) ret += queryB(r, m, 1, m, crt[s], crt[t]);
	return ret;
}

int main() {
#ifdef love_lhy
	freopen("3641.in", "r", stdin);
	freopen("3641.out", "w", stdout);
#endif
	fr(n, m, q);
	root = NULL;
	build(1, m, root);
	trt[0] = crt[0] = root;
	rep(i, 1, n) trt[i] = NULL;
	e = 0, pse(h, -1);
	int a, b, c, d;
	rep(i, 1, n) {
		fr(a, b), fr(d, c);
		addEdge(a, b, c, d);
	}
	rep(i, 1, m)
		fr(V[i], W[i]);
	pse(fa, -1);
	dep[1] = 1;
	get_cir(1);
	rep(i, 1, cCnt)
		onCir[cir[i]] = i;
	dep[0] = 0;
	crt[0] = root;
	rep(i, 1, cCnt) {
		dep[cir[i]] = 1;
		trt[cir[i]] = root;
		dfs(cir[i], 0, cir[i]);
		crt[i] = NULL;
		int p = (i==1?lnk[cCnt]:lnk[i-1]);
		rk = rnk[p];
		aa = (DB)dis[p]*W[rk];
		ab = (DB)dis[p]*W[rk]/V[rk];
		insert(1, m, crt[i], crt[i-1]);
	}
	rep(j, 1, 20)
		rep(i, 1, n)
		pa[i][j] = pa[pa[i][j-1]][j-1];

	rep(i, 1, m)
		rV.pb(V[i]);
	reverse(rV.begin(), rV.end());
	int s, t, u, r;
	while (q--) {
		fr(s, t, u);
		double ans = 0.0;
		r = getRank(u);
		if (owner[s] == owner[t]) {
			ans = qMinCost(s, t, u, r);
		} else {
			if (onCir[owner[t]] < onCir[owner[s]])
				swap(s, t);
			ans += qMinCost(s, owner[s], u, r);
			ans += qMinCost(t, owner[t], u, r);
			double x = qMinCost2(onCir[owner[s]], onCir[owner[t]], u, r);
			double y = qMinCost2(1, onCir[owner[s]], u, r);
			double z = qMinCost2(onCir[owner[t]], cCnt, u, r);
			double w = qMinCost2(0, 1, u, r);
			ans += min(x, y+z+w);
		}
		printf("%lf\n", (double)ans);
	}

	return 0;
}

