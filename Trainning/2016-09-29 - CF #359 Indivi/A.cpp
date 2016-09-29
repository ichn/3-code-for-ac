#include <bits/stdc++.h>
using namespace std;

int dig1[10], dig2[10];
bool u1[7];
int d1, d2;
int ans = 0;

int chs[20];

void dfs2(int p, int o) {
	if (p == d2) {
		//for (int i = 0; i < d1; ++i)
		//	printf("%d", chs[i]);
		//putchar(' ');
		//for (int i = d1+1; i <= d1 + d2; ++i)
		//	printf("%d", chs[i]);
		//puts("");
		++ans;
		return ;
	}
	if (o) {
		for (int i = 0; i < 7; ++i)
			if (!u1[i]) {
				u1[i] = 1;
				chs[d1+1+p] = i;
				dfs2(p+1, o);
				u1[i] = 0;
			}
	} else {
		if (!u1[dig2[p]]) {
			u1[dig2[p]] = 1;
			chs[d1+1+p] = dig2[p];
			dfs2(p+1, 0);
			u1[dig2[p]] = 0;
		}
		for (int i = 0; i < dig2[p]; ++i)
			if (!u1[i]) {
				u1[i] = 1;
				chs[d1+1+p] = i;
				dfs2(p+1, 1);
				u1[i] = 0;
			}
	}
}

void dfs(int p, int o) {
	if (p == d1) {
		dfs2(0, 0);
		return ;
	}
	if (o) {
		for (int i = 0; i < 7; ++i)
			if (!u1[i]) {
				u1[i] = 1;
				chs[p] = i;
				dfs(p+1, o);
				u1[i] = 0;
			}
	} else {
		if (!u1[dig1[p]]) {
			u1[dig1[p]] = 1;
			chs[p] = dig1[p];
			dfs(p+1, 0);
			u1[dig1[p]] = 0;
		}
		for (int i = 0; i < dig1[p]; ++i)
			if (!u1[i]) {
				u1[i] = 1;
				chs[p] = i;
				dfs(p+1, 1);
				u1[i] = 0;
			}
	}
}

int main() {
#ifdef love_yxl
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif

	int n, m;
	scanf("%d %d", &n, &m);
	--n, --m;
	int tmp = n;
	do {
		dig1[d1++] = tmp % 7;
		tmp /= 7;
	} while (tmp);
	tmp = m;
	do {
		dig2[d2++] = tmp % 7;
		tmp /= 7;
	} while (tmp);
	reverse(dig1, dig1 + d1);
	reverse(dig2, dig2 + d2);
	dfs(0, 0);
	printf("%d\n", ans);

	return 0;
}

