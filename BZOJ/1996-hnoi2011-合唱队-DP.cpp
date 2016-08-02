#include <stdio.h>
const int mod = 19650827;
int f[1001][1001][2];
int n, a[1001];
int main() {
	scanf("%d", &n);
	for (register int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		f[i][i][0] = 1;
	}
	for (register int i = 1; i < n; ++i)
		for (register int j = 1; j+i <= n; ++j) {
			f[j][j+i][0] = (a[j] < a[j+i]) * f[j+1][j+i][1] + (a[j] < a[j+1]) * f[j+1][j+i][0];
			f[j][j+i][1] = (a[j+i] > a[j]) * f[j][j+i-1][0] + (a[j+i] > a[j+i-1]) * f[j][j+i-1][1];
			if (f[j][j+i][0] > mod)
				f[j][j+i][0] -= mod;
			if (f[j][j+i][1] > mod)
				f[j][j+i][1] -= mod;
		}
	printf("%d\n", (f[1][n][0] + f[1][n][1])%mod);
 
	return 0;
}

