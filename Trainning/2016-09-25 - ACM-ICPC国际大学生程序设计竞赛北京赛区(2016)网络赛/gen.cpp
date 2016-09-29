#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("E.in", "w", stdout);
	srand((int)time(NULL));
	int n = 10000, q = 10000;
	printf("%d %d\n", n, q);
	for (int i = 1; i <= n; ++i)
		puts("sdfsdf");
	srand((int)time(NULL));
	for (int i = 2; i <= n; ++i)
		printf("%d %d\n", i, rand() % (i-1) + 1);
	for (int i = 1; i <= q; ++i)
		printf("%d %d\n", rand() % n + 1, rand() % n + 1);
	
	return 0;
}

