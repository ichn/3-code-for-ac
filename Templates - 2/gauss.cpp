#include <bits/stdc++.h>
using namespace std;

typedef vector<double> equ;

vector<equ> equs;
equ ans;

bool gauss(int n, int m) {

	for (int i = 1; i <= m; ++i) {
		double mx = 0.0;
		int k = 0;
		for (int j = i; j <= m; ++j)
			if (fabs(equs[j][i]) > fabs(mx)) {
				k = j;
				mx = equs[j][i];
			}
		if (k == 0) {
			continue;
		}
		swap(equs[i], equs[k]);
		for (int j = i + 1; j <= m; ++j) {
			double l = equs[j][i] / mx;
			for (int t = i; t <= n; ++t)
				equs[j][t] -= equs[j][t] * l;
			equs[j][0] -= equs[j][0] * l;
		}
	}
	ans.resize(n+1);
	for (int i = m; 0 < i; --i) {
		ans[i] = equs[i][0];
		for (int j = 1; j < i; ++j) {
			equs[j][0] -= equs[i][0] * equs[j][i];
			equs[j][i] = 0;
		}
	}
	return true;
}

int main() {

	freopen("gauss.in", "r", stdin);
	freopen("gauss.out", "w", stdout);

	int n, m;
	scanf("%d %d", &n, &m);
	equs.resize(m + 1);
	for (int i = 1; i <= m; ++i) {
		equ w;
		w.resize(n+2);
		for (int i = 0; i <= n; ++i)
			cin >> w[i];
		equs[i] = w;
	}
	assert(gauss(n, m));
	for (int i = 1; i <= n; ++i)
		cout << ans[i] << endl;

	return 0;
}

