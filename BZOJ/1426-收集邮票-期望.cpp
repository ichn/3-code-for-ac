#include <bits/stdc++.h>
using namespace std;

double f[10001], g[10001];

int main() {
	int n;
	scanf("%d", &n);
	f[n] = 0;
	for (int i = n-1; 0 <= i; --i) {
		f[i] = f[i+1]+n/(n-i+.0);
	}
	for (int i = n-1; 0 <= i; --i) {
		g[i] = g[i+1]+f[i+1]+i*f[i]/(n-i)+n/(n-i+.0);
	}
	printf("%.2lf\n", g[0]);
	return 0;
}
