
#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
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
 
/*
 * 这道题的做法大体上分为两种：
 * 1. 树链剖分套权值线段树，回答时二分答案，复杂度$O(n\log^4n)$，怀疑暴力暴力都可以过
 * 2. 离线主席树$O(n\log^2n)$万岁！
 * 这里写的是主席树的做法，修改用个树状数组套起来就行了。实现起来有很多小细节。这里讲讲我的做法：
 * 1. 节点在dfs序中第一次出现看作插入操作，最后一次看作删除，那么从根到某节点的dfs序列刚好就是此节点到根的路径。
 * 2. 以上，便可以dfs树一遍，求出dfs序，把dfs序用树状数组套主席树维护，修改直接进行。
 * 3. 关于树状数组套主席树，一种是树状数组直接套权值线段树（动态开节点），还有一种是先建出主席树，在另外的空间上建修改树，套起来。
 * 4. 其实这题可以有一个常数更小的做法，就是建出每个节点到根的主席树，修改在树状数组套权值线段树维护的dfs序上进行，回答(u,v)时只需把+ChairManTree(u),+ChairManTree(v),-ChairManTree(lca(u,v)),-ChairManTree(fa(lca(u,v))),+Modify(u),+Modify(v),-Modify(lca(u,v)),-Modify(fa(lca(u,v)))上二分下去就行了。
 * */

const int maxn = 80000 + 1000;
const int maxv = maxn, maxe = maxn * 2;
struct Edge {
	int edge, head[maxv], to[maxe], next[maxe];
	Edge() { edge = 0; memset(head, -1, sizeof head); }
	void addedge(int u, int v) {
		to[edge] = v, next[edge] = head[u];
		head[u] = edge++;
	}
	void add() {
		int u, v;
		fr(u, v);
		addedge(u, v), addedge(v, u);
	}
} e;

#define sg seg_node
#define ctrl ChairmanTreeRootList
#define ftrl FenwickTreeRootList
struct seg_node {
	int l, r, w;
} T[maxn * 80];
int loc = 0, ChairmanTreeRootList[maxn], FenwickTreeRootList[maxn];

struct Discretization {
	int val[maxn << 2], tot;
	void add(int Val) {
		val[++tot] = Val;
	}
	void init() {
		sort(val + 1, val + tot + 1);
		tot = unique(val + 1, val + tot + 1) - val - 1;
	}
	int recovery(int x) {
		return val[x];
	}
	void discretize(int *p, int t) {
		rep(i, 1, t) {
			p[i] = lower_bound(val + 1, val + tot + 1, p[i]) - val;
		}
	}
	int get(int p) {
		return lower_bound(val + 1, val + tot + 1, p) - val;
	}
} Disc;

int val[maxn], n, q, a[maxn], b[maxn], c[maxn];
int lca[maxn], fa[maxn];
vector<ipir> lcaQuery[maxn];
int findfa(int u) {
	return fa[u] == u ? u : fa[u] = findfa(fa[u]);
}

int dep[maxn], lft[maxn], rht[maxn], f[maxn], dfn;
bool vis[maxn];

void insert(int l, int r, int v, int adj, int&rt) {
	T[++loc].l = T[rt].l, T[loc].r = T[rt].r, T[loc].w = T[rt].w + adj, rt = loc;
	if(l == r) return ;
	int mid = (l+r)>>1;
	if(v <= mid) insert(l, mid, v, adj, T[rt].l);
	else insert(mid+1, r, v, adj, T[rt].r);
}

void modify(int p, int v, int adj) {
	for(; p <= dfn; p += p&-p)
		insert(1, Disc.tot, v, adj, ftrl[p]);
}

#define qia QueryInforOfAdd
#define cqia CntQueryInforOfAdd
#define qir QueryInforOfReduce
#define cqir CntQueryInforOfReduce
int QueryInforOfAdd[maxn * 2], CntQueryInforOfAdd, 
	QueryInforOfReduce[maxn * 2], CntQueryInforOfReduce;

int query(int k, int l = 1, int r = Disc.tot) {
	for(; l < r;) {
		int sum = 0;
		rep(i, 1, cqia) sum += T[T[qia[i]].r].w;
		rep(i, 1, cqir) sum -= T[T[qir[i]].r].w;
		if(k <= sum) {
			rep(i, 1, cqia) qia[i] = T[qia[i]].r;
			rep(i, 1, cqir) qir[i] = T[qir[i]].r;
			l = ((l+r)>>1)+1;
		} else {
			k -= sum;
			rep(i, 1, cqia) qia[i] = T[qia[i]].l;
			rep(i, 1, cqir) qir[i] = T[qir[i]].l;
			r = ((l+r)>>1);
		}
	}
	return Disc.val[l];
}

void get(int *l, int &cnt, int u) {
	for(l[++cnt] = ctrl[u], u = lft[u]; u; l[++cnt] = ftrl[u], u -= u&-u);
}

void dfs(int u) {
	ctrl[u] = ctrl[f[u]], insert(1, Disc.tot, val[u], 1, ctrl[u]);
	lft[u] = ++dfn;
	for(int i = e.head[u]; i != -1; i = e.next[i]) {
		int v = e.to[i];
		if(f[u] != v) {
			f[v] = u;
			dep[v] = dep[u] + 1;
			dfs(v);
			fa[v] = u;
		}
	}
	rht[u] = dfn, vis[u] = true;
	foreach(i, lcaQuery[u])
		if(vis[i->first]) {
			lca[i->second] = findfa(i->first);
		}
}

 
int main() {
	T[0].l = 0, T[0].r = 0, T[0].w = 0;
	fr(n, q);
	rep(i, 1, n) 
		fr(val[i]),
		Disc.add(val[i]),
		fa[i] = i;
	rep(i, 2, n) e.add();
	rep(i, 1, q) {
		fr(a[i], b[i], c[i]);
		if(!a[i])
			Disc.add(c[i]);
		else
			lcaQuery[b[i]].pb(mp(c[i], i)),
			lcaQuery[c[i]].pb(mp(b[i], i));
	}
	Disc.init(), Disc.discretize(val, n);
	dep[(n+1)>>1] = 1;
	dfs((n + 1)>>1);
	rep(i, 1, q) {
		if(!a[i]) {
			int p = b[i], v = Disc.get(c[i]);
			modify(lft[p], val[p], -1), modify(rht[p] + 1, val[p], 1);
			modify(lft[p], v, 1), modify(rht[p] + 1, v, -1);
			val[p] = v;
		} else {
			int u = b[i], v = c[i];
			if(dep[u]+dep[v]-dep[lca[i]]-dep[f[lca[i]]] < a[i]) {
				puts("invalid request!");
				continue;
			}
			cqia = cqir = 0;
			get(qia, cqia, u), get(qia, cqia, v);
			get(qir, cqir, lca[i]), get(qir, cqir, f[lca[i]]);
			printf("%d\n", query(a[i]));
		}
	}
	return 0;
}


