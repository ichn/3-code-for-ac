#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;

#define rep(i, j, k) for (int i = j; i <= k; ++i)

const int maxn = 1200+100;
const int maxv = 2400+30, maxe = 3000000+10;
struct MaxFlow {
	int edge, head[maxv], to[maxe], next[maxe];
	int cap[maxe];
	MaxFlow() { edge = 0; memset(head, -1, sizeof head); }
	void addedge(int u, int v, int c) {
		to[edge] = v, next[edge] = head[u];
		cap[edge] = c;
		head[u] = edge++;
	}
	void addEdge(int u, int v, int c) {
	//	printf("%d %d %d\n", u, v, c);
		addedge(u, v, c);
		addedge(v, u, 0);
	}

	int s, t;
	int cur[maxv], dis[maxv], que[maxv*maxv/10], front, back;

	bool bfs() {
		que[front=back=0] = s;
		memset(dis, INF, sizeof (int)*(t+10));
		dis[s] = 0;
		while (front <= back) {
			int u = que[front++];
			for (int i=head[u]; i!=-1; i=next[i]) {
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
		for (int &i=cur[u], v; i!=-1; i=next[i])
			if (cap[i]>0 && dis[v=to[i]]==dis[u]+1 && (f=dfs(v, min(a, cap[i])))>0) {
				cap[i]-=f, cap[i^1]+=f;
				flow+=f, a-=f;
				if (a==0) break;
			}
		return flow;
	}

	int MF() {
		int ret = 0;
		while (bfs()) {
			memcpy(cur, head, sizeof (int) * (t+10));
			ret += dfs(s, INF);
		}
		return ret;
	}
} mf;

int n, m;

int main() {
	scanf("%d%d", &n, &m);
	int s = 0, t = n+m+1;
	int c, x, sum = 0;
	int p, v;
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &c);
		sum += c;
		mf.addEdge(s, i, c);
		scanf("%d", &x);
		for (int j = 1; j <= x; ++j) {
			scanf("%d %d", &p, &v);
			mf.addEdge(i, n+p, v);
		}
	}
	rep(i, 1, m) {
		scanf("%d", &c);
		mf.addEdge(n+i, t, c);
	}
	mf.s = s, mf.t = t;
	printf("%d\n", sum-mf.MF());

	return 0;
}

