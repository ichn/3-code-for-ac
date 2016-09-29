#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("E.in", "w", stdout);
	int n, m;
	n = 100000;
	m = 100000;
	printf("%d %d\n", n, m);
	for (int i = 1; i <= n; ++i)
		printf("%d ", ((rand() << 16 ) | rand()) % 1000000000 + 1);
	puts("");
	for (int i = 1; i <= m; ++i) {
		int a, b, c;
		if (rand() & 1) {
			a = rand() % n, b = rand() % n;
			++a, ++b;
			if (b < a) swap(a, b);
			printf("%d %d %d %d\n", 1, a, b, ((rand() << 16 ) | rand()) % 1000000000 + 1);
		} else {
			a = rand() % n, b = rand() % n;
			++a, ++b;
			if (b < a) swap(a, b);
			printf("%d %d %d\n", 2, a, b);
		}
	}
	return 0;
}
