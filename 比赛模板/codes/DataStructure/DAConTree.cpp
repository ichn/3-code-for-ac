#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
typedef long long LL;

namespace t_dac {

	const int maxV = 100000 + 100;
	const int maxE = maxV * 2;

	int d, t;
	bool vis[maxV];

	LL ans;

	int h[maxV], to[maxE], nxt[maxE], wei[maxE], e;
	void addEdge(int u, int v, int c) {
		nxt[e] = h[u], to[e] = v, wei[e] = c, h[u] = e++;
		nxt[e] = h[v], to[e] = u, wei[e] = c, h[v] = e++;
	}

	void init() {
		memset(h, -1, sizeof h);
		e = 0;
		memset(vis, false, sizeof vis);
		ans = 0;
	}
	int get_s(int u, int f) {
		int r = 1;
		for (int i = h[u]; i != -1; i = nxt[i]) {
			int v = to[i];
			if (!vis[v] && v != f)
				r += get_s(v, u);
		}
		return r;
	}
	int get_d(int u, int f, int s) {
		int r = 1, mx = 0, w;
		for (int i = h[u]; i != -1; i = nxt[i]) {
			int v = to[i];
			if (!vis[v] && v != f) {
				r += (w = get_d(v, u, s));
				mx = max(mx, w);
			}
		}
		mx = max(mx, s - r);
		if (mx < t) {
			t = mx;
			d = u;
		}
		return r;
	}

	void calc(int u);

	void dfs(int u) {


		int s = get_s(u, -1);
		t = INF, d = u;
		get_d(u, -1, s);
		//fprintf(stderr, "%d %d\n", u, d);
		calc(d);

		vis[d] = 1;
		for (int i = h[d]; i != -1; i = nxt[i]) {
			int v = to[i];
			if (!vis[v])
				dfs(v);
		}
	}

	void solve() {
		dfs(1);
	}

};

