#include <bits/stdc++.h>
using namespace std;

const int maxn = 500000 + 100;
const int maxe = maxn;
int e, h[maxn], to[maxe], nxt[maxe];
void addEdge(int u, int v) {
	nxt[e] = h[u], to[e] = v, h[u] = e++;
}
int val[maxn], s, p, bar[maxn];

int pre[maxn], low[maxn], dfs_clock, stk[maxn], top, bl[maxn], sc;

void dfs(int u) {
	pre[u] = low[u] = dfs_clock++;
	stk[++top] = u;
	for (int i = h[u]; i != -1; i = nxt[i]) {
		int v = to[i];
		if (!pre[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		} else if (!bl[v]) {
			low[u] = min(low[u], pre[v]);
		}
	}
	if (low[u] == pre[u]) {
		++sc;
		while (stk[top] != u)
			bl[stk[top--]] = sc;
		bl[stk[top--]] = sc;
	}
}

struct DAG {
	int e, h[maxn], to[maxe], nxt[maxe];
	void addEdge(int u, int v) {
		nxt[e] = h[u], to[e] = v, h[u] = e++;
	}
	int val[maxn], s, p;
	bool ep[maxn];
	DAG() {
		e = 0;
		memset(h, -1, sizeof h);
		memset(val, 0, sizeof val);
		memset(ep, false, sizeof ep);
	}

	int f[maxn];

	int dp(int u) {
		if (f[u] == -1) {
			int mx = 0;
			for (int i = h[u]; i != -1; i = nxt[i])
				mx = max(mx, dp(to[i]));
			if (mx == 0)
				f[u] = ep[u] ? val[u] : INT_MIN;
			else f[u] = mx + val[u];
		}
		return f[u];
	}

	int solve() {
		memset(f, -1, sizeof f);
		return dp(s);
	}

} sv;

int n, m;

int main() {
	freopen("1179.in", "r", stdin);
	freopen("1179.out", "w", stdout);

	scanf("%d%d", &n, &m);
	e = 0, memset(h, -1, sizeof h);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}
	for (int i = 1; i <= n; ++i)
		scanf("%d", &val[i]);
	scanf("%d%d", &s, &p);
	for (int i = 1; i <= p; ++i)
		scanf("%d", &bar[i]);
	for (int i = 1; i <= n; ++i)
		if (!pre[i]) {
			dfs(i);
		}
	for (int i = 1; i <= n; ++i) {
		for (int j = h[i]; j != -1; j = nxt[j]) {
			if (bl[i] != bl[to[j]])
				sv.addEdge(bl[i], bl[to[j]]);
		}
		sv.val[bl[i]] += val[i];
	}
	for (int i = 1; i <= p; ++i)
		sv.ep[bl[bar[i]]] = true;
	sv.s = bl[s];
	printf("%d\n", sv.solve());

	return 0;	
}
