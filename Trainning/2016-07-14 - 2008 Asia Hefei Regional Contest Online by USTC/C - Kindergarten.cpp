#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;

#define rep(i, j, k) for (int i = j; i < k; ++i)
#define rgo(i, j, k) for (int i = j; i <= k; ++i)


int G, B, M;
const int maxn = 200 + 10;

int g[maxn][maxn];

int link[maxn];
bool vis[maxn];

bool dfs(int u) {
	rgo(v, 1, G)
		if (g[u][v] != 0 && !vis[v]) {
			vis[v] = true;
			if (link[v] == -1 || dfs(link[v])) {
				link[v] = u;
				return true;
			}
		}
	return false;
}

int main() {
#ifdef lol
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif


	int tCase = 0;
	while (scanf("%d %d %d", &G, &B, &M) != EOF) {
		if (G + B + M == 0)
			break;
		++tCase;
		memset(g, -1, sizeof g);
		memset(link, -1, sizeof link);
		rep(i, 0, M) {
			int u, v;
			scanf("%d %d", &u, &v);
			g[v][u] = 0;
		}
		int ans = 0;
		rgo(i, 1, B) {
			memset(vis, false, sizeof vis);
			ans += dfs(i);
		}
		printf("Case %d: %d\n", tCase, G + B - ans);
	}

	return 0;
}
