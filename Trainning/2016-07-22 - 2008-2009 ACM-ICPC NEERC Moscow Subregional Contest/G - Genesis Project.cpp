#include <bits/stdc++.h>
using namespace std;

pair<int, int> p[1001], q[1001*1001];
int n;



int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &p[i].first, &p[i].second);
	}
	int tot = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = i + 1; j <= n; ++j)
			q[++tot] = make_pair(p[i].first + p[j].first, p[i].second + p[j].second);
	}
	sort(q + 1, q + tot + 1);
	bool flg = false;
	for (int i = 1; i < tot; ++i)
		if (q[i] == q[i+1])
			flg = true;
	if (flg) {
		puts("1");
	} else {
		if (n <= 3) {
			puts("0");
		} else {
			puts("2");
		}
	}
	return 0;
}
