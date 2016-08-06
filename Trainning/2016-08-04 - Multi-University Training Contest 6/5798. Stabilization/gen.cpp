#include <bits/stdc++.h>
using namespace std;;

int get() {
	int ret = rand() << 15;
	ret += rand();
	ret &= ((1<<20)-1);
	return ret;
}

int main() {
	freopen("5798.in", "w", stdout);
	int T = 10;
	srand((int)time(NULL));
	printf("%d\n", T);
	while (T--) {
		int n = rand() % 100000 + 1;
		printf("%d\n", n);
		for (int i = 1; i <= n; ++i)
			printf("%d ", get());
		puts("");
	}
	return 0;
}
