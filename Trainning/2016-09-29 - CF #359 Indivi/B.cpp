#include <bits/stdc++.h>
using namespace std;

const int maxN = 3e5 + 100;
const int maxE = maxN<<1;

int h[maxN], to[maxE], nxt[maxE], e;

void init() {
	e = 0;
	memset(h, -1, sizeof h);
}
void addEdge(int u, int v) {
	to[e] = v, nxt[e] = h[u], h[u] = e++;
	to[e] = u, nxt[e] = h[v], h[v] = e++;
}

int n, q;
int que[maxN], qh, qt;
int que2[maxN], qh2, qt2;
int sz[maxN], ans[maxN];
int fa[maxN], mx[maxN];

bool work(int x, int y) {
	int M = mx[y];
	M = max(M, sz[x] - sz[y]);
	if (M * 2 <= sz[x]) {
		ans[x] = y;
		return true;
	}
	return false;
}

void got(int u) {
	que2[qh2 = qt2 = 0] = u;
	while (qh2 <= qt2) {
		int x = que2[qh2++];
		if (work(u, x)) return ;
		for (int i = h[x]; i != -1; i = nxt[i]) {
			int v = to[i];
			if (v == fa[x]) continue;
			if ((sz[u] - sz[v]) * 2 > sz[u]) continue;
			que2[++qt2] = v;
		}
	}
}

int upper[maxN], dep[maxN];

int main() {
#ifdef love_yxl
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif

	scanf("%d %d", &n, &q);
	init();
	for (int i = 2; i <= n; ++i) {
		int u;
		scanf("%d", &u);
		addEdge(u, i);
	}
	que[qh = qt = 0] = 1;
	dep[1] = 1;
	while (qh <= qt) {
		int u = que[qh++];
		sz[u] = 1;
		for (int i = h[u]; i != -1; i = nxt[i]) {
			int v = to[i];
			if (v != fa[u]) {
				fa[v] = u;
				dep[v] = dep[u] + 1;
				que[++qt] = v;
			}
		}
	}
	for (int i = qt; 0 <= i; --i) {
		sz[fa[que[i]]] += sz[que[i]];
	}

	for (int i = 1; i <= n; ++i) {
		ans[i] = i;
		upper[i] = i;
	}
	for (int i = qt; 0 <= i; --i) {
		int u = que[i];
		int w = 0;
		for (int j = h[u]; j != -1; j = nxt[j])
			if (to[j] != fa[u]) {
				if (sz[to[j]] > mx[u]) {
					w = to[j];
					mx[u] = max(mx[u], sz[to[j]]);
				}
			}
		if (w != 0) {
			w = ans[w];
			while (!work(u, w)) {
				w = fa[w];
			}
		}
	}
	while (q--) {
		int u;
		scanf("%d", &u);
		printf("%d\n", ans[u]);
	}
	return 0;


	for (int i = qt; 0 <= i; --i) {
		int u = que[i];
		for (int j = h[u]; j != -1; j = nxt[j]) {
			int v = to[j];
			if (v == fa[u]) continue;
			if (dep[upper[v]] < dep[upper[u]])
				upper[u] = upper[v];
		}
		while (upper[u] != 1 && (sz[fa[upper[u]]] - sz[u]) * 2 <= sz[fa[upper[u]]])
			upper[u] = fa[upper[u]];
		work(upper[u], u);
	}
	for (int i = qt; 0 <= i; --i) {
		int u = que[i];
		bool fid = false;
		for (int j = h[u]; j != -1; j = nxt[j]) {
			int v = to[j];
			if (v == fa[u]) continue;
			if (work(u, v)) {
				fid = true;
			}
			if (work(u, ans[v])) {
				fid = true;
			}
		}
		if (!fid) {
			if (work(u, u))
				fid = true;
			if (!fid) {
				got(u);
			}
		}
	}
	for (int i = 1; i <= q; ++i) {
		int u;
		scanf("%d", &u);
		printf("%d\n", ans[u]);
	}
	return 0;
}
