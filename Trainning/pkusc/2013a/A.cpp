#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;

int k, num[15];
int chs[15];

void dfs(int c, int p) {
	if (c == 6) {
		for (int i = 0; i < c; ++i) {
			printf("%d ", chs[i]);
		}
		puts("");
		return ;
	}
	if (p > k) return ;
	chs[c] = num[p];
	dfs(c + 1, p + 1);
	dfs(c, p + 1);
}

int main() {
#ifdef love_lhy
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif

	scanf("%d", &k);
	while (k != 0) {
		for (int i = 1; i <= k; ++i)
			scanf("%d", &num[i]);
		sort(num + 1, num + k + 1);
		dfs(0, 1);
		scanf("%d", &k);
		if (k != 0)
			puts("");
	}

	return 0;
}
