#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int maxn = (1<<12) + 100;
int n, a[maxn], f[20][maxn];
LL fac[20], ans;


void dfs(int t, int s) {
	int len = 1 << (n - t);

	if (t == n) {
		ans += fac[s];
		return ;
	}

	int bp[7], tp = 0;

	for (int i = 0; i < len; i += 2) {
		if (tp > 4) return ;
		if (f[t][i] + 1 != f[t][i + 1])
			bp[tp++] = i, bp[tp++] = i + 1;
	}

	if (tp == 0) {
		for (int i = 0; i < len; i += 2)
			f[t + 1][i>>1] = f[t][i]>>1;
		dfs(t + 1, s);
	}

	for (int i = 0; i < tp; ++i)
		for (int j = i + 1; j < tp; ++j) {
			swap(f[t][bp[i]], f[t][bp[j]]);
			bool do_next = true;
			for (int k = 0; k < len; k += 2) {
				if (f[t][k] % 2 != 0 || f[t][k] + 1 != f[t][k + 1]) {
					do_next = false;
					break;
				}
				f[t + 1][k>>1] = f[t][k]>>1;
			}
			swap(f[t][bp[i]], f[t][bp[j]]);
			if (do_next)
				dfs(t + 1, s + 1);
		}
}

int main() {
#ifdef love_lhy
	freopen("3990.in", "r", stdin);
	freopen("3990.out", "w", stdout);
#endif

	scanf("%d", &n);
	for (int i = 0; i < (1<<n); ++i)
		scanf("%d", &a[i]);
	for (int i = 0; i < (1<<n); ++i)
		f[0][i] = a[i] - 1;

	ans = 0;
	fac[0] = 1;
	for (int i = 1; i <= n; ++i)
		fac[i] = fac[i - 1] * i;

	dfs(0, 0);

	printf("%lld\n", ans);
	
	return 0;
}
