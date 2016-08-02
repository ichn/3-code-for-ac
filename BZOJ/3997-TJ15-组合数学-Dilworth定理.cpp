#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 100;

int g[maxn][maxn], n, m;
int f[maxn][maxn];

int main() {
	freopen("3997.in", "r", stdin);
	freopen("3997.out", "w", stdout);

	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= m; ++j)
				scanf("%d", &g[i][j]);
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; ++i)
			for (int j = m; 1 <= j; --j)
				f[i][j] = max(f[i - 1][j + 1] + g[i][j], max(f[i - 1][j], f[i][j + 1]));
		printf("%d\n", f[n][1]);
	}

	return 0;
}
