#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 3000 + 10;
typedef double DB;
int n;
DB a0, at, c[maxn], a[maxn];

DB calc(DB a1) {
	a[0] = a0;
	a[1] = a1;

	for (int i = 2; i <= n+1; ++i)
		a[i] = (a[i - 1] + c[i - 1]) * 2 - a[i - 2];
	return a[n+1];
}

int main() {

	scanf("%d", &n);
	scanf("%lf %lf", &a0, &at);
	for (int i = 1; i <= n; ++i) 
		scanf("%lf", &c[i]);

	double l = -1000.0, r = 1000.0;

	while (r - l > 1e-4) {
		double m = (l + r) / 2;
		double aq = calc(m);
		if (aq < at)
			l = m;
		else r = m;
	}
	printf("%.2lf\n", l);

	return 0;
}
