#include <bits/stdc++.h>
using namespace std;

int s[1<<13];
int n;

int main() {
	freopen("3990.in", "w", stdout);
	n = 8;
	printf("%d\n", n);
	for (int i = 0; i < (1<<n); ++i)
		s[i] = i + 1;

	srand((int)time(NULL));
	for (int i = 0; i < n; ++i) {
		if (rand() % 4 == 0) {
			int ds = (1<<n) / (1<<i);
			int a = rand() % ds, b = rand() % ds;
			while (a == b)
				a = rand() % ds, b = rand() % ds;
			a = a * (1<<i), b = b * (1 << i);
			for (int j = 0; j < (1<<i); ++j)
				swap(s[a + j], s[b + j]);
		}
	}
	for (int i = 0; i < (1<<n); ++i)
		printf("%d ", s[i]);
	puts("");


	return 0;
}
