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
	const int INF = 0x3f3f3f3f;
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
const int maxn = 200000+100;

int n, q;
struct Point {
	int x, y;
} p[maxn];

#define kn kdt_node
#define ls ch[0]
#define rs ch[1]
const double ratio = 0.05;
struct kdt_node {
	kn*ch[2];
	int sz;
	int x, y;
	int id;
	int mn[2], mx[2];
	kn() {
		sz = 0;
		ls = rs = NULL;
	}
} pool[maxn], *root, *bu[maxn], *loc;

void init_kdt() {
	root = NULL;
	loc = pool;
}

int dep;
bool cmp(const kn* lhs, const kn* rhs) {
	return dep&1? lhs->x<rhs->x : lhs->y<rhs->y;
}
void build(int l, int r, kn*&at) {
	if (r < l) return ;
	dep ^= 1;
	int mid = (l+r)>>1;
	nth_element(bu+l, bu+mid, bu+r+1, cmp);
	at = bu[mid];
	int rec = dep;
	build(l, mid-1, at->ls);
	build(mid+1, r, at->rs);
	dep = rec;

	at->sz = (at->ls? at->ls->sz : 0) + (at->rs? at->rs->sz : 0) + 1;
	if (at->ls) {
		at->mn[0] = min(at->mn[0], at->ls->mn[0]);
		at->mx[0] = max(at->mx[0], at->ls->mx[0]);
		at->mn[1] = min(at->mn[1], at->ls->mn[1]);
		at->mx[1] = max(at->mx[1], at->ls->mx[1]);
	}
	if (at->rs) {
		at->mn[0] = min(at->mn[0], at->rs->mn[0]);
		at->mx[0] = max(at->mx[0], at->rs->mx[0]);
		at->mn[1] = min(at->mn[1], at->rs->mn[1]);
		at->mx[1] = max(at->mx[1], at->rs->mx[1]);
	}
}

int l, r;

#define sqr(x) ((LL)(x)*(x))

LL func(int x, int y, kn*at) {
	if (at == NULL) return LLONG_MAX;
	LL ret = 0;
	if (x < at->mn[0]) ret += sqr(x-(at->mn[0]));
	if (at->mx[0] < x) ret += sqr(x-(at->mx[0]));
	if (y < at->mn[1]) ret += sqr(y-(at->mn[1]));
	if (at->mx[1] < y) ret += sqr(y-(at->mx[1]));
	return ret;
}

LL dist(int x, int y, kn*at) {
	return sqr(x-(at->x)) + sqr(y-(at->y));
}

LL res;
int Id;
int rId;
void query(int x, int y, kn*at) {
	dep ^= 1;
	int rec = dep;
	if (at == NULL)
		return ;
	LL tmp = dist(x, y, at);
	if (at->id != rId) {
		if (tmp < res) {
			res = tmp;
			Id = at->id;
		}
		if (tmp == res) {
			if (p[Id].x > p[at->id].x || (p[Id].x == p[at->id].x && p[Id].y > p[at->id].y))
				Id = at->id;
		}
	}
	LL func_ls = func(x, y, at->ls);
	LL func_rs = func(x, y, at->rs);
	if (func_ls <= func_rs) {
		if (func_ls <= res)
			query(x, y, at->ls);
		if (func_rs <= res)
			query(x, y, at->rs);
	} else {
		if (func_rs <= res)
			query(x, y, at->rs);
		if (func_ls <= res)
			query(x, y, at->ls);
	}
	dep = rec;
};
		
void query(int x, int y) {
	dep = 0;
	res = LLONG_MAX;
	Id = -1;
	query(x, y, root);
	assert(Id != rId);
};

int cls[maxn];
int rcls[maxn];

const DB eps = 1e-8;
int sgn(DB x) {
	return x < -eps ? -1 : eps < x;
}

DB dist(int a, int b) {
	return sqrt((0.0 + p[a].x - p[b].x) * (0.0 + p[a].x - p[b].x) + (0.0 + p[a].y - p[b].y) * (0.0 + p[a].y - p[b].y));
}

struct Edge {
	int h[maxn], to[maxn<<1], nxt[maxn<<1];
	int e;
	void init() {
		e = 0;
		memset(h, -1, sizeof h);
	}
	void addEdge(int u,int v) {
		to[e] = v, nxt[e] = h[u], h[u] = e++;
	}
} E;

int onCir[maxn], cCir;
DB cirSize[maxn];
vector<DB> disc[maxn];
int lord[maxn], ind[maxn];
DB disToL[maxn];
bool vis[maxn];
void dfs(int u, int l, DB d) {
	vis[u] = true;
	for (int i = E.h[u]; i != -1; i = E.nxt[i]) {
		int v = E.to[i];
		if (!onCir[v]) {
			lord[v] = l;
			disToL[v] = d + dist(v, u);
			dfs(v, l, disToL[v]);
		}
	}
}
int pos[maxn];
DB distOnCir(int a, int b) {
	int CC = onCir[a];
	if (a == b) return 0;
	if (pos[a] < pos[b])
		return disc[CC][pos[b]-1] - (pos[a] == 0 ? 0 : disc[CC][pos[a]]);
	else return disc[CC][disc[CC].size()-1] - distOnCir(b, a);
}

queue<int> que;

int main() {
#ifdef lol
	freopen("1001.in", "r", stdin);
	freopen("1001.out", "w", stdout);
#endif
	int T = fr();
	for (int tt = 1; tt <= T; ++tt) {
		int n, q;
		scanf("%d %d", &n, &q);
		init_kdt();
		for (int i = 1; i <= n; ++i) {
			fr(p[i].x, p[i].y);
			bu[i] = loc++;
			bu[i]->id = i;
			bu[i]->x = p[i].x;
			bu[i]->y = p[i].y;
			bu[i]->mn[0] = bu[i]->x;
			bu[i]->mx[0] = bu[i]->x;
			bu[i]->mn[1] = bu[i]->y;
			bu[i]->mx[1] = bu[i]->y;
			bu[i]->ls = bu[i]->rs = NULL;
		}
		build(1, n, root);
		E.init();
		for (int i = 1; i <= n; ++i) {
			rId = i;
			query(p[i].x, p[i].y);
			cls[i] = Id;
			E.addEdge(Id, i);
		}
		cCir = 0;
		memset(onCir, 0, sizeof onCir);
		memset(ind, 0, sizeof ind);
		for (int i = 1; i <= n; ++i)
			++ind[cls[i]];
		while (!que.empty()) que.pop();
		for (int i = 1; i <= n; ++i)
			if (ind[i] == 0) que.push(i);
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			--ind[cls[u]];
			if (ind[cls[u]] == 0)
				que.push(cls[u]);
		}
		for (int i = 1; i <= n; ++i) {
			if (ind[i] == 1 && !onCir[i]) {
				++cCir;
				int t = i;
				int tt = 0;
				int last = 0;
				while (onCir[t] != cCir) {
					pos[t] = tt++;
					if (last != 0) disc[cCir].push_back(dist(i, last));
					onCir[t] = cCir;
					last = t;
					t = cls[t];
				}
				disc[cCir].pb(dist(last, t));
			}
		}
		for (int i = 1; i <= n; ++i) {
			lord[i] = i;
			disToL[i] = 0;
		}
		memset(vis, 0, sizeof vis);
		for (int i = 1; i <= n; ++i) {
			if (onCir[i]) {
				dfs(i, i, 0);
				vis[i] = true;
			}
		}
	//	for (int i = 1; i <= n; ++i) {
	//		if (!vis[i]) {
	//			printf("%d\n", i);
	//		}
	//	}
	//	for (int i = 1; i <= n; ++i)
	//		if (!onCir[lord[i]]) {
	//			printf("%d %d\n", i, lord[i]);
	//		}
	//	return 0;
		printf("Case #%d:\n", tt);
		for (int i = 1, j, k; i <= q; ++i) {
			scanf("%d %d", &j, &k);
			if (onCir[lord[j]] != onCir[lord[k]]) {
				puts("NO");
			} else {
				DB ds1 = disToL[j] + distOnCir(lord[j], lord[k]);
				DB ds2 = disToL[k];
				DB ds3 = fabs(ds1 - ds2) / disc[onCir[lord[j]]][disc[onCir[lord[j]]].size()-1];
				if (sgn(ds3 * disc[onCir[lord[j]]][disc[onCir[lord[j]]].size()-1] - fabs(ds1 - ds2)) == 0) {
					puts("YES");
					continue;
				}
				ds1 = disToL[k] + distOnCir(lord[k], lord[j]);
				ds2 = disToL[j];
				ds3 = fabs(ds1 - ds2) / disc[onCir[lord[j]]][disc[onCir[lord[j]]].size()-1];
				if (sgn(ds3 * disc[onCir[lord[j]]][disc[onCir[lord[j]]].size()-1] - fabs(ds1 - ds2)) == 0) {
					puts("YES");
					continue;
				}
				puts("NO");
			}
		}
	}

	return 0;
}

