#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxv = 1e5 + 5e4 + 100;
const int maxe = maxv * 2;

int e, h[maxv], to[maxe], nxt[maxe], dis[maxe];
void addEdge(int u, int v, int d) {
	nxt[e] = h[u], to[e] = v, dis[e] = d, h[u] = e++;
	nxt[e] = h[v], to[e] = u, dis[e] = d, h[v] = e++;
}

int n, Q, A;
long long last_ans, ans;
int age[maxv];

void getQuery(int&a, int&b) {
	long long ta = last_ans + a;
	long long tb = last_ans + b;
	ta %= A, tb %= A;
	if (tb < ta) swap(ta, tb);
	a = (int)ta, b = (int)tb;
}

int fa[maxv], dep[maxv], dis2fa[maxv], pa[maxv][21], da[maxv][21];

void dfs(int u) {
	for (int i = h[u]; i != -1; i = nxt[i]) {
		int v = to[i], d = dis[i];
		if (v != fa[u]) {
			fa[v] = u;
			dep[v] = dep[u] + 1;
			dis2fa[v] = d;
			dfs(v);
		}
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	for (int i = 20; 0 <= i; --i)
		if (dep[pa[u][i]] >= dep[v])
			u = pa[u][i];
	if (u == v) return u;
	for (int i = 20; 0 <= i; --i)
		if (pa[u][i] != pa[v][i])
			u = pa[u][i],
			v = pa[v][i];
	return pa[u][0];
}

int disOnTree(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	int ret = 0;
	for (int i = 20; 0 <= i; --i)
		if (dep[pa[u][i]] >= dep[v])
			ret += da[u][i],
			u = pa[u][i];
	if (u == v) return ret;
	for (int i = 20; 0 <= i; --i)
		if (pa[u][i] != pa[v][i])
			ret += da[u][i],
			ret += da[v][i],
			u = pa[u][i],
			v = pa[v][i];
	return ret + da[u][0] + da[v][0];
}

int belong[21][maxv];


#define DACN DivideAndConquerNode

vector<pair<int, long long> >::iterator itl, itr;

struct DivideAndConquerNode {
	int cc;
	DACN *ch[3];
	int dep, id, c, fa;
	vector<pair<int, long long> > sz, val;
	DACN() {
		ch[0] = ch[1] = ch[2] = NULL;
		cc = 0;
		sz.clear(), val.clear();
	}
	bool has(int p) {
		return belong[dep][p] == id;
	}
	
	void init() {
		sort(sz.begin(), sz.end());
		sort(val.begin(), val.end());
		
		int nSz = (int)sz.size(), cSz = 0;
		int nVal = (int)val.size(), cVal = 0;
		
		for (int i = 0; i < nSz; ) {
			sz[cSz] = sz[i];
			++i;
			while (i < nSz && sz[cSz].first == sz[i].first) {
				sz[cSz].second += sz[i].second;
				++i;
			}
			++cSz;
		}
		
		for (int i = 0; i < nVal; ) {
			val[cVal] = val[i];
			++i;
			while (i < nVal && val[cVal].first == val[i].first) {
				val[cVal].second += val[i].second;
				++i;
			}
			++cVal;
		}

		sz.resize(nSz = cSz);
		val.resize(nVal = cVal);
	
		for (int i = 1; i < nSz; ++i)
			sz[i].second += sz[i - 1].second;
		for (int i = 1; i < nVal; ++i)
			val[i].second += val[i - 1].second;
	}
	
	long long qrySz(int l, int r) {
		itl = lower_bound(sz.begin(), sz.end(), make_pair(l, 0LL));
		itr = upper_bound(sz.begin(), sz.end(), make_pair(r, LLONG_MAX));
		if (itl == itr) return 0LL;
		--itr;
		if (itl == sz.begin()) {
			return itr->second;
		}
		--itl;
		return itr->second - itl->second;
	}
	
	long long qryVal(int l, int r) {

		itl = lower_bound(val.begin(), val.end(), make_pair(l, 0LL));
		itr = upper_bound(val.begin(), val.end(), make_pair(r, LLONG_MAX));
		if (itl == itr) return 0LL;
		--itr;
		if (itl == val.begin()) {
			return itr->second;
		}
		--itl;
		return itr->second - itl->second;
	}
	
} pl[maxv], *loc = pl, *root;

int que[maxv], qh, qt, sz[maxv], dis2x[maxv];
bool ban[maxv];

DivideAndConquerNode*build(int x, int dep, int father) {

	que[qh = qt = 0] = x;
	dis2x[x] = 0;
	fa[x] = 0;
	while (qh <= qt) {
		int u = que[qh++];
		sz[u] = 0;
		for (int i = h[u]; i != -1; i = nxt[i]) {
			int v = to[i], d = dis[i];
			if (v != fa[u] && !ban[v]) {
				dis2x[v] = dis2x[u] + d;
				fa[v] = u;
				que[++qt] = v;
			}
		}
	}
	for (int i = qt; 0 <= i; --i) {
		int u = que[i];
		++sz[u];
		sz[fa[u]] += sz[u];
	}
	
	int c = x, sm = INF;
	
	for (int i = 0; i <= qt; ++i) {
		int u = que[i];
		int rmx = 0;
		for (int j = h[u]; j != -1; j = nxt[j])
			if (!ban[to[j]] && to[j] != fa[u])
				rmx = max(rmx, sz[to[j]]);
		rmx = max(rmx, sz[x] - sz[u]);
		if (rmx < sm) {
			sm = rmx;
			c = u;
		}
	}
	
	DACN *cur = loc++;
	cur->id = x;
	cur->c = c;
	cur->dep = dep;
	cur->fa = father;
	ban[c] = true;
 
    for (int i = 0; i <= qt; ++i) {
    	int u = que[i];
    	belong[dep][u] = x;
    	cur->sz.push_back(make_pair(age[u], 1LL));
    	cur->val.push_back(make_pair(age[u], (long long)dis2x[u]));
    }
 
    cur->init();
 
	for (int i = h[c]; i != -1; i = nxt[i]) {
		int v = to[i];
		if (!ban[v])
			cur->ch[cur->cc++] = build(v, dep + 1, c);
	}

	return cur;
}

void pre() {
	e = 0;
	memset(h, -1, sizeof h);
	memset(ban, false, sizeof ban);
	scanf("%d %d %d", &n, &Q, &A);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &age[i]);
	}
	for (int i = 1; i < n; ++i) {
		int u, v, d;
		scanf("%d %d %d", &u, &v, &d);
		addEdge(u, v, d);
	}
	fa[1] = -1;
	dep[1] = 0;
	dfs(1);
	for (int i = 1; i <= n; ++i) {
		pa[i][0] = fa[i];
		da[i][0] = dis2fa[i];
	}
	for (int i = 1; i <= 20; ++i)
		for (int j = 1; j <= n; ++j) {
			pa[j][i] = pa[pa[j][i - 1]][i - 1];
			da[j][i] = da[j][i - 1] + da[pa[j][i - 1]][i - 1];
		}

	root = build(1, 0, -1);
	
}

int u, a, b;

void solve(DACN*rt) {
	if (rt == NULL) return ;
	long long sumSz = 0;
	long long sumVal = 0;
	
	int x = rt->c;
	for (int i = 0; i < rt->cc; ++i) {
		if (!rt->ch[i]->has(u)) {
			sumSz = rt->ch[i]->qrySz(a, b);
			sumVal = rt->ch[i]->qryVal(a, b);
			ans += sumSz * disOnTree(rt->ch[i]->id, u) + sumVal;
		}
	}
	if (a <= age[x] && age[x] <= b) {
		ans += disOnTree(x, u);
	}

	//printf("%d %lld %d %lld\n", x, sumSz, disOnTree(x, u), sumVal);

	//ans += sumSz * disOnTree(x, u) + sumVal;
	
	for (int i = 0; i < rt->cc; ++i)
		if (rt->ch[i]->has(u))
			solve(rt->ch[i]);
}

void top() {

	while (Q--) {
		scanf("%d %d %d", &u, &a, &b);
		getQuery(a, b);
	//	printf("query is %d %d %d\n", u, a, b);
		ans = 0;
		solve(root);
		printf("%lld\n", last_ans = ans);
	}
	
}

int main() {
	
	freopen("shop.in", "r", stdin);
	freopen("shop.out", "w", stdout);
	
	pre();
	top();

	return 0;	
}

