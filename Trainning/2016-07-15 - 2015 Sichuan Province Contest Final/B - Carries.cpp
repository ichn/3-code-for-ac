#include <bits/stdc++.h>
using namespace std;


const int maxn = 1e5 + 100;
int n;
long long val[maxn], val2[maxn];
long long ans;

vector<int> seq;



int main() {
#ifdef lol
	freopen("b.in", "r", stdin);
	freopen("b.out", "w", stdout);
#endif

	while (scanf("%d", &n) != EOF) {
		for (int i = 1; i <= n; ++i)
			cin >> val[i];
		ans = 0;
		memset(val2, 0, sizeof val2);
		long long mult = 1;
		for (int i = 1; i <= 11; ++i) {
			seq.clear();
			for (int j = 1; j <= n; ++j) {
				val2[j] += (val[j] % 10) * mult;
				val[j] /= 10;
				seq.push_back(val2[j]);
			}
			mult *= 10;
			sort(seq.begin(), seq.end());
			for (int j = 1; j <= n; ++j) {
				vector<int>::iterator it = lower_bound(seq.begin(), seq.end(), mult - val2[j]);
				ans += n - (it - seq.begin());
				if (val2[j] >= mult - val2[j]) --ans;
			}
		}
		cout << ans / 2 << endl;
	}

	return 0;
}
