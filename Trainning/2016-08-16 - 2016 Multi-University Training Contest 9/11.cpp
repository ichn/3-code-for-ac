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

};
using namespace my_zone;
const int maxN = 222;
int n, m, l;

vector<int> f[maxN];
int pro[maxN];
vector<pair<int, int> > g;
bool ok[maxN];

static const int maxE = 50000+100, maxV = 400 + 100;
struct MaxFlow {
	int e, h[maxV], to[maxE], nxt[maxE];
	LL cap[maxE];
	void init() {
		cls(h, -1);
		e = 0;
	}
	void addEdge(int u,int v, LL c) {
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

	LL dfs(int u, LL a = 0) {
		if (u == t || a == 0)
			return a;
		LL flow = 0, f;
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
		return flow;
	}

	LL maxFlow() {
		LL flow = 0;
		while (bfs())
			flow += dfs(s, INF);
		return flow;
	}
};

MaxFlow mf;


LL calc(int M) {
	memset(ok, false, sizeof ok);
	for (int j = 0; j < n; ++j)
		if (g[j].second <= M)
			ok[j] = true;
	LL ret = 0;
	mf.init();
	mf.s = n + m + 1;
	mf.t = n + m + 2;
	for (int j = 0; j < m; ++j) {
		bool flg = true;
		for (int k = 0; k < (int)f[j].size(); ++k)
			if (!ok[f[j][k]]) {
				flg = false;
				break;
			}
		if (flg) {
			ret += pro[j];
			mf.addEdge(mf.s, j, pro[j]);
			for (int k = 0; k < (int)f[j].size(); ++k)
				mf.addEdge(j, m + f[j][k], INF);
		}
	}
	for (int j = m; j < n + m; ++j)
		if (ok[j-m])
			mf.addEdge(j, mf.t, g[j-m].first);
	return ret - mf.maxFlow();
}

int main() {
#ifdef lol
	freopen("11.in", "r", stdin);
	freopen("11.out", "w", stdout);
#endif

	int T;
	scanf("%d", &T);
	for (int tt = 1; tt <= T; ++tt) {
		scanf("%d %d %d", &n, &m, &l);
		g.resize(n);
		for (int i = 0; i < n; ++i) {
			scanf("%d %d", &g[i].first, &g[i].second);
		}
		for (int i = 0; i < m; ++i) {
			scanf("%d", &pro[i]);
			int k;
			scanf("%d", &k);
			f[i].resize(k);
			for (int j = 0; j < k; ++j) {
				scanf("%d", &f[i][j]);
				--f[i][j];
			}
		}
		int L = 0, R = 1e9 + 100;
		while (L < R) {
			int M = (L+R)>>1;
			if (calc(M) < l)
				L = M+1;
			else R = M;
		}
		if (L > 1e9) {
			printf("Case #%d: impossible\n", tt);
		} else {
			printf("Case #%d: %d %lld\n", tt, L, calc(L));
		}
	}
 
	return 0;
}

