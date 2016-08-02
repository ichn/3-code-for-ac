#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 1000 + 2;
int a[maxn], b[maxn], n, m;
int sg[maxn];
 
int dfs(int x) {
	if(sg[x] != -1) {
		return sg[x];
	}
	bool vis[maxn];
	memset(vis, false, sizeof vis);
	for(int i = 1; i <= m; ++i) {
		if(b[i] <= x) {
			dfs(x - b[i]);
			vis[sg[x - b[i]]] = true;
		}
	}
	for(int i = 0; ; ++i) {
		if(!vis[i]) {
			return sg[x] = i;
		}
	}
}
 
int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &b[i]);
	}
	sort(b + 1, b + m + 1);
	memset(sg, -1, sizeof sg);
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		ans ^= dfs(a[i]);
	}
	if(ans == 0) {
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			if(b[j] <= a[i] && (ans ^ sg[a[i]] ^ sg[a[i] - b[j]]) == 0) {
				printf("%d %d\n", i, b[j]);
				return 0;
			}
		}
	}
	return 0;
}
