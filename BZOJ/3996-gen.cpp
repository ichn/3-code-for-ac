#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("3996.in", "w", stdout);
	srand((int)time(NULL));
	int n = 500;
	printf("%d\n", n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j)
			printf("%d ", rand() % 1001);
		puts("");
	}
	for (int i = 1; i <= n; ++i) {
		printf("%d ", rand() % 1001);
	}
	puts("");
	return 0;
}

