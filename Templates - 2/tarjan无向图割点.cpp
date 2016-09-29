#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 100;
const int maxe = 1000000 + 100;

int head[maxn], to[maxe], next[maxe], edge;

int n, m;

void init() {
	edge = 0;
	memset(head, -1, sizeof head);
}

void addEdge(int u, int v) {
	next[edge] = head[u], to[edge] = v, head[u] = edge++;
	next[edge] = head[v], to[edge] = u, head[v] = edge++;
}

bool is_cut[maxn];
int dfs_clock, dfn[maxn], low[maxn];
void dfs(int u, int fa) {
	dfn[u] = low[u] = ++dfs_clock;
	int child = 0;
	for (int i = head[u]; i != -1; i = next[i]) {
		int v = to[i];
		if (!dfn[v]) {
			dfs(v, u);
			++child;
			if (low[v] >= dfn[u]) {
				is_cut[u] = 1;
			} else {
				low[u] = min(low[u], low[v]);
			}
		} else low[u] = min(low[u], dfn[v]);
	}
	if (fa == -1 && child < 2)
		is_cut[u] = 0;
}


int main() {

	freopen("tt.in", "r", stdin), freopen("tt.out", "w", stdout);
	scanf("%d %d", &n, &m);
	init();
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d %d", &u, &v);
		addEdge(u, v);
	}

	dfs_clock = 0;
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) 
			dfs(i, -1);
	}
	for (int i = 1; i <= n; ++i) {
		if (is_cut[i]) {
			printf("%d ", i);
		}
	}
	puts("");
	return 0;
}
