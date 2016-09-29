static const int maxE = 200000, maxV = 2000 + 100;
struct MaxFlow {
	int e, h[maxV], to[maxE], nxt[maxE], cap[maxE];
	void init() {
		cls(h, -1);
		e = 0;
	}
	void addEdge(int u,int v, int c) {
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

	int dfs(int u, int a = 0) {
		if (u == t || a == 0)
			return a;
		int flow = 0, f;
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
		dist[u] = -1;
		// 原来我写了两年的网络流算法都是错的 = = 膜拜wmj大爷
		return flow;
	}

	int maxFlow() {
		int flow = 0;
		while (bfs())
			flow += dfs(s, INF);
		return flow;
	}
};

MaxFlow mf;

