#include <bits/stdc++.h>
using namespace std;

int a[1000111], n;
long long s;

int main() {
	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		reverse(a + 1, a + n + 1);
		s = 0;
		int ans = 0;
		for (int i = 1; i <= n; ++i) {
			s += a[i];
			if (s >= 0) {
				++ans;
				s = 0;
			}
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
