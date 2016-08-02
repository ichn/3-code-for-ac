#include <cstdio>
int main() {
int n, ans, i;
	scanf("%d", &n); i = n+1;
	while(--i)
		ans+=n/i;
	printf("%d\n", ans);
	return 0;
}
