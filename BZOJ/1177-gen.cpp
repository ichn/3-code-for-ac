#include <bits/stdc++.h>
using namespace std;

int main() {

	freopen("1177.in", "w", stdout);
	srand((int)time(NULL));

	int n = 15, m = 15, k = 4;

	printf("%d %d %d\n", n, m, k);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j)
			printf("%d ", rand() % 500 + 1);
		puts("");
	}
	
	return 0;	
}
