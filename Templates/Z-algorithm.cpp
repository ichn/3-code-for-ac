#include <bits/stdc++.h>
using namespace std;
const int maxn = 10000;
char s[maxn];
int z[maxn], n;



int main() {
	freopen("z-a.in", "r", stdin);
	freopen("z-a.out", "w", stdout);
	scanf("%s", s);
	n = strlen(s);
	int L = 0, R = 0;
	for (int i = 1; i < n; i++) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R-L] == s[R]) R++;
			z[i] = R-L; R--;
		} else {
			int k = i-L;
			if (z[k] < R-i+1) z[i] = z[k];
			else {
				L = i;
				while (R < n && s[R-L] == s[R]) R++;
				z[i] = R-L; R--;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		printf("%d\n", z[i]);
	}
	return 0;
}

