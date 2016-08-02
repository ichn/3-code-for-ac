#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int maxN = 2e5 + 100;
int h[maxN], to[maxN<<1], nxt[maxN<<1], ec;
int n, k, isK[maxN];
int sz[maxN], fa[maxN];
LL dis[maxN], ans;

void dfs(int u) {
	sz[u] = isK[u];
	for (int i = h[u]; i != -1; i = nxt[i]) {
		int v = to[i];
		if (fa[u] != v) {
			fa[v] = u;
			dfs(v);
			sz[u] += sz[v];
			dis[u] += dis[v] + sz[v];
		}
	}
}

priority_queue<int> Sz;
bool chk() {
	while (!Sz.empty()) {
		if (Sz.size() == 1)
			return Sz.top() == 0;
		int u = Sz.top(); Sz.pop();
		int v = Sz.top(); Sz.pop();
		if (u != v)
			Sz.push(abs(u - v));
	}
	return true;
}
void dfs2(int u, LL disFa) {
	int szFa = k*2 - sz[u];
	LL tmp = disFa + szFa;
	while (!Sz.empty()) Sz.pop();
	if (szFa + isK[u] != 0)
		Sz.push(szFa + isK[u]);
	for (int i = h[u]; i != -1; i = nxt[i])
		if (to[i] != fa[u]) {
			tmp += dis[to[i]] + sz[to[i]];
			if (sz[to[i]] != 0)
				Sz.push(sz[to[i]]);
		}
	if (chk()) ans = max(ans, tmp);
	for (int i = h[u]; i != -1; i = nxt[i]) {
		int v = to[i];
		if (v != fa[u]) {
			dfs2(v, tmp - dis[v] - sz[v]);
		}
	}
}

int main() {
#ifdef lol
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif

	scanf("%d %d", &n, &k);
	for (int i = 1; i <= k*2; ++i) {
		int u;
		scanf("%d", &u);
		isK[u] = 1;
	}
	ec = 0;
	memset(h, -1, sizeof h);
	for (int i = 1; i < n; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		to[ec] = v, nxt[ec] = h[u], h[u] = ec++;
		to[ec] = u, nxt[ec] = h[v], h[v] = ec++;
	}
	dfs(1);

	dfs2(1, 0);

	cout << ans << endl;

	return 0;
}

