#include <bits/stdc++.h>
using namespace std;

bitset<10000001> s;
int a[5000], id[5000];

int n, k;

inline int get(int v) {
	int r = v;
	while (v) {
		r += v % 10;
		v /= 10;
	}
	return r;
}

bool cmp(int x, int y) {
	return x[a] < y[a];
}

int main() {
#ifdef love_yxl
	freopen("108.in", "r", stdin);
	freopen("108.out", "w", stdout);
#endif

	scanf("%d %d", &n, &k);
	for (int i = 0; i < k; ++i) {
		scanf("%d", &a[i]);
		id[i] = i;
	}
	sort(id, id + k, cmp);

	for (int i = 1; i <= n; ++i) {
		int w = get(i);
		if (w > n) continue;
		s.set(w);
	}

	int p = 0, cnt = 0;

	for (int w = 1; w <= n; ++w)
		if (s[w] == 0) {
			++cnt;
			while (p < k && a[id[p]] == cnt) {
				a[id[p]] = w;
				++p;
			}
		}

	printf("%d\n", cnt);
	for (int i = 0; i < k; ++i)
		printf("%d ", a[i]);

	return 0;
}


