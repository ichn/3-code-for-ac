#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("1030.in", "w", stdout);
	srand((int)time(NULL));
	int n = 3;
	int len = 10;
	printf("%d %d\n", n, len);
	for (int i = 1; i <= n; ++i) {
		int l = rand() % len + 1;
		for (int j = 1; j <= l; ++j) {
			putchar('A'+rand() % 26);
		}
		puts("");
	}

	return 0;
}
