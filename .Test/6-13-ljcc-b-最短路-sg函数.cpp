#include <bits/stdc++.h>
using namespace std;

const int maxVer = 2e4 + 100;
const int maxArc = 2e5 + 100;

int h[maxVer], e, to[maxArc], nxt[maxArc], dis[maxArc];
void iniEdge() {
	memset(h, -1, sizeof h);
	e = 0;
}
void addArc(int u, int v, int d) {
	nxt[e] = h[u], to[e] = v, dis[e] = d, h[u] = e++;
}
void addEdge(int u, int v, int d) {
	addArc(u, v, d);
	addArc(v, u, d);
}

int n, m, k;

int dist[maxVer];

struct DijNode {
	int u, d;
	DijNode() {};
	DijNode(int u, int d):u(u), d(d) {}
	bool operator < (const DijNode&rhs) const {
		return d > rhs.d;
	}
};

priority_queue<DijNode> que;
int vis[maxVer];

void spfa(int s) {
	for (int i = 0; i <= n; ++i) {
		dist[i] = INT_MAX;
		vis[i] = 0;
	}

	dist[s] = 0;

	que.push(DijNode(s, 0));

	while (!que.empty()) {
		int u = que.top().u;
		que.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (int i = h[u]; i != -1; i = nxt[i]) {
			int v = to[i], d = dis[i];
			if (dist[u] + d < dist[v]) {
				dist[v] = dist[u] + d;
				que.push(DijNode(v, dist[v]));
			}
		}
	}
}

vector<int> adj[maxVer];

int sg[maxVer];
int calc(int u) {
	int &ret = sg[u];
	if (ret != -1)
		return ret;
	if ((int)adj[u].size() == 0) {
		ret = 1;
		return ret;
	}
	int *mex = (new int[(int)adj[u].size()+1]);
	for (int i = 0; i < (int)adj[u].size() + 1; ++i)
		mex[i] = 0;
	for (int i = 0; i < (int)adj[u].size(); ++i) {
		int val = calc(adj[u][i]);
		if (val > (int)adj[u].size())
			continue;
		mex[val] = 1;
	}
	for (ret = 0; mex[ret]; ++ret);
	delete mex;
	return ret;
}

int main() {
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);

	while (scanf("%d %d %d", &n, &m, &k) != EOF) {
		iniEdge();
		for (int i = 1; i <= m; ++i) {
			int x, y, c;
			scanf("%d %d %d", &x, &y, &c);
			addEdge(x, y, c);
		}
		spfa(1);
	//	for (int i = 1; i <= n; ++i) {
	//		printf("%d ", dist[i]);
	//	}
	//	puts("");

		for (int i = 1; i <= n; ++i) {
			adj[i].clear();
			for (int j = h[i]; j != -1; j = nxt[j]) {
				if (dist[to[j]] > dist[i])
					adj[i].push_back(to[j]);
			}
	//		printf("%d\n", (int)adj[i].size());
		}
		memset(sg, -1, sizeof sg);
		int ans = 0;
		for (int i = 1; i <= k; ++i) {
			int p;
			scanf("%d", &p);
			ans ^= calc(p);
		}

	//	puts("");
	//	for (int i = 1; i <= n; ++i) {
	//		calc(i);
	//		printf("%d\n", sg[i]);
	//	}
		printf("%s\n", ans == 0 ? "Bob" : "Alice");
	}
}


