#include <bits/stdc++.h>
using namespace std;

int id(int a, int b) {
	return n * (a - 1) + b;
}

int main() { 
#ifdef love_yxl
	freopen("109.in", "r", stdin);
	freopen("109.out", "w", stdout);
#endif

	int n;

	scanf("%d", &n);
	printf("%d", n);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (n & 1) {
				if ((i + j) % 2 == 0) {
					printf(" %d", id(i, j));
				}
			} else {
				if ((i + j) & 1) {
					printf(" %d", id(i, j));
				}
			}
		}
	}



	return 0;
}
