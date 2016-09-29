#include <bits/stdc++.h>
using namespace std;

const int maxN = 100000 + 100;
const int maxE = maxN * 2;

int h[maxN], to[maxE], nxt[maxE], e, wei[maxE];
void addEdge(int u, int v, int c = 0) {
	nxt[e] = h[u], to[e] = v, wei[e] = c, h[u] = e++;
	nxt[e] = h[v], to[e] = u, wei[e] = c, h[v] = e++;
}

void init() {
	memset(h, -1, sizeof h);
	e = 0;
}


int fa[maxN], anc[maxN][20];
int dfn[maxN], dfs_clk, dep[maxN];

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
	if (dep[u] < dep[v])
		swap(u, v);
	for (int i = 19; 0 <= i; --i)
		if (dep[anc[u][i]] >= dep[v])
			u = anc[u][i];
	if (u == v) return u;
	for (int i = 19; 0 <= i; --i)
		if (anc[u][i] != anc[v][i])
			u = anc[u][i], v = anc[v][i];
	return anc[u][0];
}

int dis(int u, int v) {
	return dep[u] + dep[v] - dep[fa[lca(u, v)]];
}

bool cmp(int a, int b) {
	return dfn[a] < dfn[b];
}

void get(vector<int>&a) {
	sort(a.begin(), a.end(), cmp);
	

}

map<string, vector<int> > Id;
map<string, pair<int, int> > Token;
int n, q;

int main() {
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);

	ios_base::sync_with_stdio(false);

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
		fa[1] = 0;
		dep[1] = 1;
		dfs(1);

		for (int i = 1; i <= n; ++i)
			anc[i][0] = fa[i];
		for (int i = 1; i < 20; ++i)
			for (int j = 1; j <= n; ++j)
				anc[j][i] = anc[anc[j][i-1]][i-1];

		init();

		for (auto i : Id) {
			Token[i.first] = get(i.second);
		}
		for (int i = 1; i <= q; ++i) {
			string s, t;
			cin >> s >> t;
			ans = 0;
			pair<int, int> u = Token[s],
						   v = Token[t];
			ans = max(ans, dis(u.first, v.second));
			ans = max(ans, dis(v.first, u.second));
			ans = max(ans, dis(u.second, v.second));
			ans = max(ans, dis(u.fisrt, v.first));

			printf("%d\n", ans == 0 ? -1 : ans);
		}
	}

	return 0;
}
