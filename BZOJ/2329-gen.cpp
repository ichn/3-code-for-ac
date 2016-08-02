#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5;

int main() {
	srand((int)time(NULL));
	freopen("2329.in", "w", stdout);
	int n = 1e5;
	printf("%d %d\n", n, n);
	for (int i = 1; i <= n; ++i) {
		printf("%c", rand() & 1 ? '(' : ')');
	}
	puts("");
	for (int i = 1; i <= n; ++i) {
		int t = rand() % 4;
		int l = rand() % n + 1, r = rand() % n + 1;
		if (r < l) swap(l, r);
		if (t < 1) {
			while ((r - l + 1) & 1)
				l = rand() % n + 1, r = rand() % n + 1;
			if (r < l) swap(l, r);
			printf("Query %d %d\n", l, r);
		} else if (t < 2) {
			printf("Invert %d %d\n", l, r);
		} else if (t < 3) {

			//printf("Replace %d %d %c\n", l, r, rand() & 1 ? '(' : ')');
printf("Swap %d %d\n", l, r);
		} else 
			printf("Replace %d %d %c\n", l, r, rand() & 1 ? '(' : ')');
	}
	//for (int i = 1; i <= n; ++i) {
	//	int t = rand() % 3;
	//	int l = rand() % n + 1, r = rand() % n + 1;
	//	if (r < l) swap(l, r);
	//	if (t < 1) {
	//		while ((r - l + 1) & 1)
	//			l = rand() % n + 1, r = rand() % n + 1;
	//		if (r < l) swap(l, r);
	//		printf("Query %d %d\n", l, r);
	//	} else if (t < 2) {
	//		printf("Invert %d %d\n", l, r);
	//	} else if (t < -4) {
	//		printf("Replace %d %d %c\n", l, r, rand() & 1 ? '(' : ')');
	//	} else printf("Swap %d %d\n", l, r);
	//}
	return 0;
}
