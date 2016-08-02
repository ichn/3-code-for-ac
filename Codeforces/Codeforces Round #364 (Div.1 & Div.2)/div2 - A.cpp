#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;


int n;
pair<int, int> a[201];
int main() {

#ifdef lol
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i].first);
		a[i].second = i;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n/2; ++i) {
		printf("%d %d\n", a[i].second, a[n - i + 1].second);
	}

	return 0;
}
