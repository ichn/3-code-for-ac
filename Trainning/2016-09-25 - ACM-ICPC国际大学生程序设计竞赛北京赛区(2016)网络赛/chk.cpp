#include <bits/stdc++.h>
using namespace std;

const int maxN = 100000 + 100;
const int maxE = maxN * 2;

int h[maxN], to[maxE], nxt[maxE], e;
void addEdge(int u, int v) {
	nxt[e] = h[u], to[e] = v, h[u] = e++;
	nxt[e] = h[v], to[e] = u, h[v] = e++;
}

void init() {
	memset(h, -1, sizeof h);
	e = 0;
}


int fa[maxN], anc[maxN][20];
int dfn[maxN], dfs_clk;
int dep[maxN]; 
void dfs(int u) {
	dfn[u] = ++dfs_clk;
	for (int i = h[u]; i != -1; i = nxt[i]) {
		int v = to[i];
		if (v != fa[u]) {
			dep[v] = dep[u] + 1;
			fa[v] = u;
			dfs(v);
		}
	}
}

int lca(int u, int v) {
	if (u == v) return u;
	if (dep[u] == dep[v])
		return lca(fa[u], fa[v]);
	if (dep[u] < dep[v])
		swap(u, v);
	return lca(fa[u], v);
}

map<string, vector<int> > Id;
map<string, pair<int, int> > Token;

int main() {
	freopen("E.in", "r", stdin);
	freopen("chk.out", "w", stdout);

	int n, q;
	while (cin >> n >> q) {
		init();
		Id.clear();
		for (int i = 1; i <= n; ++i) {
			string t;
			cin >> t;
			Id[t].push_back(i);
		}
		for (int i = 1; i < n; ++i) {
			int u, v;
			cin >> u >> v;
			addEdge(u, v);
		}

		dfs_clk = 0;
		fa[1] = 1;
		dep[0] = 1;
		dep[1] = 1;
		dfs(1);

		for (int i = 1; i <= n; ++i)
			anc[i][0] = fa[i];
		for (int i = 1; i < 20; ++i)
			for (int j = 1; j <= n; ++j)
				anc[j][i] = anc[anc[j][i-1]][i-1];
		for (int i = 1; i <= q; ++i) {
			int u, v;
			scanf("%d %d", &u, &v);
			printf("%d\n", lca(u, v));
		}
	}

	return 0;
}


