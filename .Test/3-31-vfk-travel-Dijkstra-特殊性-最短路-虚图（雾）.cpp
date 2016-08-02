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

const int maxv = 1e5 + 100;
const int maxe = 2e5 + 100;
int e, h[maxv], t[maxe*2], wv[maxe*2], nxt[maxe*2];
void addEdge(int u, int v, int w) {
	nxt[e] = h[u], t[e] = v, wv[e] = w, h[u] = e++;
	nxt[e] = h[v], t[e] = u, wv[e] = w, h[v] = e++;
}

struct Edge {
	int u, v;
	LL w;
	bool operator < (const Edge&rhs) const {
		return w < rhs.w;
	}
} E[maxe];
int eCnt;
int fa[maxv];
int que[maxv*200], f, z, x, y;
int findfa(int u) {
	int x = u;
	while (fa[x] != x)
		x = fa[x];
	while (fa[u] != u) {
		int t = fa[u];
		fa[u] = x;
		u = t;
	}
	return x;
}

int dep[maxv];
int b[maxv][21];
LL d[maxv][21];

int lca(int u, int v) {
	if (dep[u] < dep[v]) swap(u, v);
	red(i, 20, 0)
		if (dep[b[u][i]] >= dep[v])
			u = b[u][i];
	if (u == v) return u;
	red(i, 20, 0)
		if (b[u][i] != b[v][i])
			u=b[u][i], v=b[v][i];
	return b[u][0];
}

LL w_lca(int u, int v) {
	LL ret = 0;
	if (dep[u] < dep[v]) swap(u, v);
	red(i, 20, 0)
		if (dep[b[u][i]] >= dep[v])
			ret = max(d[u][i], ret), u=b[u][i];
	if (u == v) return ret;
	red(i, 20, 0)
		if (b[u][i] != b[v][i])
			ret = max(ret, max(d[u][i], d[v][i])), u=b[u][i], v=b[v][i];
	return max(ret, max(d[u][0], d[v][0]));
}

int n, m;
char isM[maxv];
LL dis[maxv], rb;

struct Node {
	int u;
	LL d;
	bool operator < (const Node&rhs) const {
		return d > rhs.d;
	}
};
priority_queue<Node> pq;

int pre[maxv];

int main() {
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	e = 0, pse(h, -1);
	fr(n, m);
	scanf("%s", isM+1);
	rb = 0;
	rep(i, 1, m) {
		int u, v, w;
		fr(u, v, w);
		addEdge(u, v, w);
		rb = max(rb, (LL)w);
	}
	rb = rb * m;

	while (!pq.empty()) pq.pop();
	rep(i, 1, n)
		if (isM[i] == '1') {
			pq.push((Node){i, 0});
			dis[i] = 0;
			pre[i] = i;
		} else {
			pre[i] = -1;
			dis[i] = rb;
		}
	while (!pq.empty()) {
		int u = pq.top().u;
		pq.pop();
		for (int i=h[u]; i != -1; i=nxt[i])
			if (dis[u]+wv[i] < dis[t[i]]) {
				dis[t[i]] = dis[u] + wv[i];
				pre[t[i]] = pre[u];
				pq.push((Node){t[i], dis[t[i]]});
			}
	}
	for (int i=0; i < e; i+=2) {
		E[eCnt++] = (Edge){pre[t[i]], pre[t[i^1]], dis[t[i]]+wv[i]+dis[t[i^1]]};
	}
	sort(E, E+eCnt);
	//reu(i, 0, eCnt) {
	//	printf("%d %d %lld\n", E[i].u, E[i].v, E[i].w);
	//}
	rep(i, 0, n)
		fa[i] = i;
	for (int k = 1; k <= n; ++k)
		if (isM[k] == '1') {
			e = 0, pse(h, -1);
			int q, x, y;
			reu(i, 0, eCnt) {
				int u = E[i].u, v = E[i].v, w = E[i].w;
				if (findfa(u) != findfa(v)) {
					fa[findfa(u)] = findfa(v);
					addEdge(u, v, w);
				}
			}
			que[f=z=0] = k;
			dep[k] = 1;
			b[k][0] = 0;
			while (f <= z) {
				int u = que[f++];
				for (int i = h[u]; i != -1; i = nxt[i]) {
					if (t[i] != b[u][0]) {
						b[t[i]][0] = u;
						d[t[i]][0] = wv[i];
						dep[t[i]] = dep[u]+1;
						que[++z] = t[i];
					}
				}
			}

			rep(j, 1, 20)
				rep(i, 1, n) {
					b[i][j] = b[b[i][j-1]][j-1];
					d[i][j] = max(d[i][j-1], d[b[i][j-1]][j-1]);
				}
			q = fr();
			while (q--) {
				fr(x, y);
				printf("%lld\n", w_lca(x, y));
			}
			break;
		}



	return 0;
}
