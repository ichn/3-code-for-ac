
struct MaxFlow {
	static const int maxv = 1000;
	static const int maxe = maxv * 2;
	static const int maxq = maxe * 10;
	int e, h[maxv], to[maxe], nxt[maxe];
	int cap[maxe];
	MaxFlow() { e = 0; memset(h, -1, sizeof h); }
	void adde(int u, int v, int c) {
		to[e] = v, nxt[e] = h[u];
		cap[e] = c;
		h[u] = e++;
	}
	void addEdge(int u, int v, int c) {
	//	printf("%d %d %d\n", u, v, c);
		addedge(u, v, c);
		addedge(v, u, 0);
	}

	int s, t;
	int cur[maxv], dis[maxv], que[maxq], front, back;

	bool bfs() {
		que[front=back=0] = s;
		memset(dis, INF, sizeof dis);
		dis[s] = 0;
		while (front <= back) {
			int u = que[front++];
			for (int i=h[u]; i!=-1; i=nxt[i]) {
				if (cap[i]>0 && dis[to[i]]>dis[u]+1) {
					dis[to[i]] = dis[u]+1;
					que[++back] = to[i];
				}
			}
		}
		return dis[t]!=INF;
	}

	int dfs(int u, int a) {
		if (u==t || a==0)
			return a;
		int flow=0, f;
		for (int &i=cur[u], v; i!=-1; i=nxt[i])
			if (cap[i]>0 && dis[v=to[i]]==dis[u]+1 && (f=dfs(v, min(a, cap[i])))>0) {
				cap[i]-=f, cap[i^1]+=f;
				flow+=f, a-=f;
				if (a==0) break;
			}
		return flow;
	}

	int maxFlow() {
		int ret = 0;
		while (bfs()) {
			memcpy(cur, h, sizeof h);
			ret += dfs(s, INF);
		}
		return ret;
	}
};

