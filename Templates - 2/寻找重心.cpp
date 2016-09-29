int rmx, d;
int find_d(int u, int f, int s) {
	sz[u] = 1;
	int mx = 0;
	for (int i = head[i]; i != -1; i = next[i]) {
		int v = to[i];
		if (v != f && !ban[v]) {
			find_d(v, u, s);
			sz[u] += sz[v];
			mx = max(mx, sz[v]);
		}
	}
	mx = max(mx, s - mx);
	if (mx < rmx) rmx = mx, d = u;
}
int find_d(int u) {
	rmx = INF, d = u;
	return find_d;
}

