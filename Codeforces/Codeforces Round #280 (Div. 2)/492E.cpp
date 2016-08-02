#include <cstdio>
int a[1000000], b[1000000], r, s, x, y, n, m, dx, dy;
int main() {
	scanf("%d%d%d%d", &n, &m, &dx, &dy);
	for (int i=1; i<=n; (x+=dx)%=n, (y+=dy)%=n, ++i)
		a[x]=y;
	while (m--) {
		scanf("%d%d", &x, &y);
		y = (y-a[x]+n)%n;
		if (++b[y]>r) r=b[y], s=y;
	}
	printf("0 %d\n", s);
	return 0;
}
