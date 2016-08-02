#include <bits/stdc++.h>
using namespace std;

int n, m, k;

int main() {

#ifdef lol
	freopen("e.in", "r", stdin);
	freopen("e.out", "w", stdout);
#endif

	while (scanf("%d %d %d", &n, &m, &k) != EOF) {
		k /= 2;
		long long ans = 0;
		for (int i = 1; i <= min(k-1, n); ++i) {
			int t = min(k - i, m);
			long long x1 = n - i + 1;
			long long x2 = (2ll * m - t + 1) * (long long)t / 2;
			ans += x1 * x2;
		}
		cout << ans << endl;
	}

	return 0;
}
