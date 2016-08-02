#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e2 + 100;
int fa[maxn];
int getfa(int x) {
	return x == fa[x] ? x : fa[x] = getfa(fa[x]);
}
int vis[maxn];

int get[maxn], tot = 0;
int main() {
	freopen("2286.in", "w", stdout);
	int n = maxn-20;
	for (int i=1; i<=n; ++i) {
		fa[i] = i;
	}

	srand((int)time(NULL));
	printf("%d\n", n);
	for (int i=1; i<n; ++i) {
		int x = rand() %n+1, y = rand() %n+1;
		while (getfa(x) == getfa(y))
			x = rand() %n+1, y = rand() %n+1;
		printf("%d %d %d\n", x, y, rand() % 1000000+1);
		fa[getfa(x)] = getfa(y);
	}
	int m = maxn;
	printf("%d\n", m);
	vis[1] = 1;
	while (m--) {
		int k = rand() % 30;
		printf("%d", k);
		for (int i=1; i<=k; ++i) {
			int x = rand() %n+1;
			while (vis[x])
				x = rand() %n +1;
			get[i] = x, vis[x] = 1;
			printf(" %d", x);
		}
		puts("");
		for (int i=1; i<=k; ++i)
			vis[get[i]] = 0;
	}

	return 0;
}
