#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;
#define mp make_pair
#define pb push_back
#define x first
#define y second

const int maxN = 1e5 + 1000;
int a[maxN][2], n;

LL f[maxN][3];


int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i][0]);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i][1]);
		for (int i = 1; i <= n; ++i) {
			f[i][0] = max(max(f[i-1][1], f[i-1][0]), f[i-1][2]);
			f[i][1] = max(f[i-1][0], f[i-1][2]) + a[i][0];
			f[i][2] = max(f[i-1][0], f[i-1][1]) + a[i][1];
		}
		LL ans = max(max(f[n][1], f[n][2]), f[n][0]);
		cout << ans << endl;
	}

	return 0;
}
