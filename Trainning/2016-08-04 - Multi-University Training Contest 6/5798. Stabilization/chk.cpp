#include <bits/stdc++.h>
using namespace std;

int n, a[100001];
int main() {
	freopen("5798.in", "r", stdin);
	scanf("%d", &n);
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	freopen("5798.out", "r", stdin);
	int X;
	long long sum, ss = 0;
	cin >> X >> sum;
	for (int i = 2; i <= n; ++i)
		ss += abs((a[i-1]^X) - (a[i] ^ X));
	cout << ss << ' ' << sum << endl;

	assert(ss == sum);
	return 0;
}
