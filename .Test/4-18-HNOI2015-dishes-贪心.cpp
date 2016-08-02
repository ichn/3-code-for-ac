#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5 + 100;
const int maxe = maxn * 2;

int n, m;

int ans[maxn], in[maxn], cnt;
priority_queue<int> que;
vector<int> pre[maxn];


void solve() {
	scanf("%d %d", &n, &m);
	memset(in, 0, sizeof in);
	cnt = 0;
	for (int i = 1; i <= n; ++i)
		pre[i].clear();
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		pre[y].push_back(x);
		++in[x];
	}
	while (!que.empty()) que.pop();
	for (int i = n; 0 < i; --i) {
		if (!in[i]) {
			que.push(i);
		}
	}
	while (!que.empty()) {
		int u = que.top();
		que.pop();
		ans[++cnt] = u;
		for (int i = 0; i < (int)pre[u].size(); ++i) {
			int v = pre[u][i];
			--in[v];
			if (!in[v]) {
				que.push(v);
			}
		}
	}
	if (cnt != n) {
		puts("Impossible!");
	} else {
		reverse(ans + 1, ans + cnt + 1);
		for (int i = 1; i <= cnt; ++i) {
			printf("%d ", ans[i]);
		}
		puts("");
	}
}


int main() {

	freopen("dishes.in", "r", stdin);
	freopen("dishes.out", "w", stdout);
	int D;
	scanf("%d", &D);
	while (D--) {
		solve();
	}

	return 0;	
}
