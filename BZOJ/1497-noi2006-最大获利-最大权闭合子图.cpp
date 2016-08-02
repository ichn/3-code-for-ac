#include <bits/stdc++.h>
using namespace std;

const int maxv = 60000 + 100;
const int maxe = 500000 + 100;

int n, m, p[maxv];
int e, h[maxv], to[maxe*2], nxt[maxe*2], cap[maxe*2];
void addEdge(int u, int v, int c) {
	nxt[e] = h[u], to[e] = v, cap[e] = c, h[u] = e++;
	nxt[e] = h[v], to[e] = u, cap[e] = 0, h[v] = e++;
}

int dis[maxv];
int que[maxv*30], f, b, c[maxv];
int s, t;
bool bfs() {
	que[f = b = 0] = s;
	memset(dis, 0x3f, sizeof (int)*(t+2));
	dis[s] = 0;
	while (f <= b) {
		int u = que[f++];
		for (int i = h[u]; i != -1; i = nxt[i])
			if (dis[to[i]] > dis[u]+1 && cap[i] > 0) {
				dis[to[i]] = dis[u]+1;
				que[++b] = to[i];
			}
	}
	return dis[t] != dis[t+1];
}
int dfs(int u, int a) {
	if (u == t || a == 0)
		return a;
	int f, fl = 0;
	for (int &i=c[u]; i!=-1; i = nxt[i]) {
		int v = to[i], p = cap[i];
		if (dis[v]==dis[u]+1 && (f=dfs(v, min(a, p)))>0) {
			a -= f;
			cap[i] -= f;
			cap[i^1] += f;
			fl += f;
			if (a==0) break;
		}
	}
	return fl;
}
int MaxFlow() {
	int fl = 0;
	while (bfs()) {
		memcpy(c, h, sizeof (int)*(t+1));
		fl += dfs(s, 0x3f3f3f3f);
	}
	return fl;
}

int main() {
#ifdef love_lhy
	freopen("1497.in", "r", stdin);
	freopen("1497.out", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	int sum = 0, a, b, c;
	e = 0;
	memset(h, -1, sizeof h);
	s = 0, t = n+m+1;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &p[i]);
		addEdge(m+i, t, p[i]);
	}
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &a, &b, &c);
		sum += c;
		addEdge(s, i, c);
		addEdge(i, m+a, 0x3f3f3f3f);
		addEdge(i, m+b, 0x3f3f3f3f);
	}
	printf("%d\n", sum-MaxFlow());
	return 0;
}
