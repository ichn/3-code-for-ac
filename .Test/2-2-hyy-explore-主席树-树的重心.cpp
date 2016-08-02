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
//#define generator_sbit

// 第一问可以主席树解决；第二问这样想，如果当前重心满足答案，就ok，否则如果有一颗以上子树内包含非法路径，就无解，否则走那唯一一个不满足条件的子树，递归进行。

const int maxn = 5e5 + 1000;
const int maxm = maxn * 2;
int edge;
int to[maxm], next[maxm], head[maxn];
int n, m;
int s[maxn], t[maxn], d[maxn];

// 每次清空head


void addEdge() {
	int u, v;
	fr(u, v);
	next[edge] = head[u], to[edge] = v, head[u] = edge++;
	next[edge] = head[v], to[edge] = u, head[v] = edge++;
}
int dep[maxn], pa[maxn][21];

int que[maxn], qh, qt;

// 以x为根建树
void setRoot(int x) {
	dep[x] = 1;
	pa[x][0] = 0;
	que[qh = qt = 1] = x;
	while (qh <= qt) {
		int u = que[qh++];
		for (int i = head[u]; i != -1; i = next[i]) {
			if (to[i] != pa[u][0]) {
				pa[to[i]][0] = u;
				dep[to[i]] = dep[u] + 1;
				que[++qt] = to[i];
			}
		}
	}
	for (int i = 1; i < 21; ++i)
		for (int j = 1; j <= n; ++j) 
			pa[j][i] = pa[pa[j][i-1]][i-1];
}
int LCA(int u, int v) {
	if (dep[u] <= dep[v])
		swap(u, v);
	for (int i = 20; 0 <= i; --i)
		if (dep[pa[u][i]] >= dep[v])
			u = pa[u][i];
	if (u == v) return u;
	for (int i = 20; 0 <= i; --i) 
		if (pa[u][i] != pa[v][i])
			u = pa[u][i], v = pa[v][i];
	return pa[u][0];
}

// 数组版主席树，给指针版跪了

#define ls ch[0]
#define rs ch[1]
struct cmt_node {
	int ch[2];
	int w;
} T[maxn * 20];
int loc, root[maxn];
void init() {
	memset(head, -1, sizeof (int) * (n + 3));
	loc = edge = 0;
	for (int i = 0; i <= n + 100; ++i) {
		T[i].ls = T[i].rs = 0;
		T[i].w = 0;
	}
}
void insert(int &rt, int l, int r, int p) {
	T[++loc] = T[rt], ++T[rt = loc].w;
	if (l >= r) return ;
	int mid = (l+r)>>1;
	if (p <= mid) insert(T[rt].ls, l, mid, p);
	else insert(T[rt].rs, mid+1, r, p);
}

// 通过bfs序建主席树
void build() {
	root[0] = 0;
	for (int i = 1; i <= qt; ++i) {
		int u = que[i];
		root[u] = root[pa[u][0]];
		insert(root[u], 1, n, u);
	}
}

#define lc(a) T[T[a].ch[0]].w
#define rc(a) T[T[a].ch[1]].w
int query(int a, int b, int c, int l, int r) {
	if (l == r) return l;
	int mid = (l+r)>>1;
	if (lc(a) + lc(b) - lc(c) < (mid - l + 1))
		return query(T[a].ls, T[b].ls, T[c].ls, l, mid);
	else return query(T[a].rs, T[b].rs, T[c].rs, mid+1, r);
}

bool vis[maxn];
int fa[maxn], sz[maxn];

void dfs(int u) {
	sz[u] = 1;
	for (int i = head[u]; i != -1; i = next[i]) {
		if (to[i] != fa[u] && !vis[to[i]]) {
			fa[to[i]] = u;
			dfs(to[i]);
			sz[u] += sz[to[i]];
		}
	}
}

int rmx, c;
void getd(int u, int f, int s) {
	int mx = 0;
	sz[u] = 1;
	for (int i = head[u]; i != -1; i = next[i]) {
		int v = to[i];
		if (v != f && !vis[v]) {
			getd(v, u, s);
			sz[u] += sz[v];
			mx = max(mx, sz[v]);
		}
	}
	mx = max(mx, s - sz[u]);
	if (mx < rmx) rmx = mx, c = u;
}

int findCenter(int p) {
	fa[p] = 0;
	dfs(p);
	rmx = INF, c = p;
	getd(p, 0, sz[p]);
	return c;
}

bool bad[maxn];


bool exist(int u) {
	u = findCenter(u), vis[u] = true;
	setRoot(u);
	memset(bad, false, sizeof (bool) * (n + 2));
	for (int i = 1; i <= m; ++i) {
		int lca = LCA(s[i], t[i]);
		if (d[i] < dep[lca] - dep[u]) {
			bad[lca] = true;
		}
	}
	for (int i = qt; 1 <= i; --i) {
		if (bad[que[i]])
			bad[pa[que[i]][0]] = true;
	}
	int step = -1;
	for (int i = head[u]; i != -1; i = next[i]) {
		if (bad[to[i]]) {
			if (step == -1)
				step = to[i];
			else return false;
		}
	}
	if (step == -1) return true;
	return exist(step);
}

int main() {
	freopen("explore.in", "r", stdin), freopen("explore.out", "w", stdout);
	int TestCase = fr();
	while (TestCase--) {
		fr(n, m);
		init();
		for (int i = 2; i <= n; ++i)
			addEdge();
		setRoot(1);
		build();
		for (int i = 1; i <= m; ++i) {
			fr(s[i], t[i], d[i]);
			int lca = LCA(s[i], t[i]);
			if (lca != 1) {
				puts("1");
			} else {
				int ans = query(root[s[i]], root[t[i]], root[lca], 1, n);
				printf("%d\n", ans);
			}
		}
		memset(vis, false, sizeof (bool) * (n + 2));
		printf("%s\n", exist(1) ? "YES" : "NO");
	}

	return 0;
}
 
