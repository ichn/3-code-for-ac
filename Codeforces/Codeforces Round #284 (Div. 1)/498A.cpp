#include <cstdio>



double x1, y1, x2, y2;
int n;
double a, b, c;

bool chk() {
	if ((a*x1+b*y1+c)*(a*x2+b*y2+c)>0)
		return false;
	return true;
}

int main() {
#ifdef love_sbit
	freopen("498A.in", "r", stdin);
#endif
	scanf("%lf %lf", &x1, &y1);
	scanf("%lf %lf", &x2, &y2);
	scanf("%d", &n);
	int ans = 0;
	for (int i=1; i<=n; ++i) {
		scanf("%lf %lf %lf", &a, &b, &c);
		ans += chk();
	}
	printf("%d\n", ans);

	return 0;
}
