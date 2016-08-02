#include <bits/stdc++.h>
using namespace std;
int main() {
	freopen("osu.in", "w", stdout);
	int n = 500;
	printf("%d\n", n);
	for(int i = 1; i <= n; ++i) {
		printf("%lf ", (rand() % 100 + 99900) / 100000.0);
	}
	return 0;
}
