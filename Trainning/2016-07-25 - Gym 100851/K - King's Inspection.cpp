#include <bits/stdc++.h>
using namespace std;

const int maxN = 1e5 + 100000;
const int maxE = maxN<<1;
int h[maxN], to[maxE], nxt[maxE], ec;
int in[maxN], out[maxN], then[maxN];

int n, m;

void addEdge() {
	int u, v;
	scanf("%d %d", &u, &v);
	++in[v], ++out[u];
	then[u] = v;
	to[ec] = v, nxt[ec] = h[u], h[u] = ec++;
}

int tot;
vector<int> ch[5555];
int top[maxN];

vector<pair<int, int> > ugly;

int vis[maxN];

void dfs(int u) {
	ch[tot].push_back(u);
	top[u] = tot;
	vis[u] = 1;
	if (out[u] != 1) {
		for (int i = h[u]; i != -1; i = nxt[i]) {
			int v = to[i];
			if (vis[v]) {
				ugly.push_back(make_pair(ch[top[u]][0], v));
			} else {
				++tot;
				ugly.push_back(make_pair(ch[top[u]][0], v));
				dfs(v);
			}
		}
	} else {
		int v = then[u];
		if (vis[v]) {
			ugly.push_back(make_pair(ch[top[u]][0], v));
		} else if (in[v] != 1) {     
			++tot;                   
			ugly.push_back(make_pair(ch[top[u]][0], v));
			dfs(v);
		} else {
			dfs(v);
		}
	}
}


vector<int> ans;

bool dfs2(int u, int d) {
	if (vis[u]) {
		return d == tot+1 && u == 1;
	}
	vis[u] = 1;
	ans.push_back(u);
	for (int i = h[u]; i != -1; i = nxt[i]) {
		int v = to[i];
		if (dfs2(v, d+1)) {
			return true;
		}
	}
	vis[u] = 0;
	ans.pop_back();
	return false;
}

void addEdge(int u, int v) {
	//printf("%d %d\n", u, v);
	to[ec] = v, nxt[ec] = h[u], h[u] = ec++;
}

vector<int> ans2;

int main() {
	freopen("king.in", "r", stdin);
	freopen("king.out", "w", stdout);

	scanf("%d %d", &n, &m);
	memset(h, -1, sizeof h);
	ec = 0;
	for (int i = 1; i <= m; ++i)
		addEdge();
	for (int i = 1; i <= n; ++i) {
		if (in[i] > m - n + 1 || out[i] > m - n + 1) {
			puts("There is no route, Karl!");
			return 0;
		}
	}

	dfs(1);
	ec = 0;
	memset(h, -1, sizeof h);
	for (int i = 0; i < (int)ugly.size(); ++i)
		addEdge(ugly[i].first, ugly[i].second);

	memset(vis, 0, sizeof vis);


	if (dfs2(1, 0)) {
		for (int i = 0; i <= tot; ++i) {
			for (int j = 0; j < (int)ch[top[ans[i]]].size(); ++j)
				ans2.push_back(ch[top[ans[i]]][j]);
		}
		ans2.push_back(1);
		if ((int)ans2.size() != n + 1) {
			puts("There is no route, Karl!");
		} else {
			printf("%d", ans2[0]);
			for (int i = 1; i < (int)ans2.size(); ++i)
				printf(" %d", ans2[i]);
			puts("");
		}
	} else {
		puts("There is no route, Karl!");
	}

	return 0;
}
