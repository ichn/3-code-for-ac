#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 500 + 10;

int b, c, n;

const int maxv = maxn + 200;
const int maxe = maxv * maxv * 2 + maxv * 2;
const int maxq = maxe * 10;

int e, h[maxv], to[maxe], nxt[maxe], cap[maxe];

void init() {
	e = 0;
	memset(h, -1, sizeof h);
}

void addEdge(int u, int v, int c) {
	nxt[e] = h[u], to[e] = v, cap[e] = c, h[u] = e++;
	nxt[e] = h[v], to[e] = u, cap[e] = 0, h[v] = e++;
}

int dis[maxv], s, t, sz, cur[maxv];
int que[maxq], qh, qt;

bool bfs() {
	memset(dis, INF, sizeof (int) * sz);
	que[qh = qt = 0] = s;
	dis[s] = 0;
	while (qh <= qt) {
		int u = que[qh++];
		for (int i = h[u]; i != -1; i = nxt[i]) {
			int v = to[i], c = cap[i];
			if (c > 0 && dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				que[++qt] = v;
			}
		}
	}
	return dis[t] != INF;
}

int dfs(int u, int a) {
	if (u == t || a == 0)
		return a;
	int flow = 0, f;
	for (int &i = cur[u]; i != - 1; i = nxt[i]) {
		int v = to[i], c = cap[i];
		if (dis[v] == dis[u] + 1 && (f = dfs(v, min(a, c))) > 0) {
			a -= f;
			cap[i] -= f;
			cap[i ^ 1] += f;
			flow += f;
		}
		if (a == 0) break;
	}
	return flow;
}

int maxFlow() {
	int flow = 0;
	while (bfs()) {
		memcpy(cur, h, sizeof (int) * sz);
		flow += dfs(s, 0x3f3f3f3f);
	}
	return flow;
}

int main() {
	freopen("3996.in", "r", stdin);
	freopen("3996.out", "w", stdout);

	int ans = 0;
	scanf("%d", &n);
	s = n, t = s + 1;
	sz = t + 1;
	init();

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			scanf("%d", &b);
			ans += b;
			addEdge(i, j, b);
			addEdge(s, i, b);
		}
	for (int i = 0; i < n; ++i) {
		scanf("%d", &c);
		addEdge(i, t, c);
	}
	
	printf("%d\n", ans - maxFlow());

	return 0;
}
