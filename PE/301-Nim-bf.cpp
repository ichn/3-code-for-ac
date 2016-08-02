#include <cstdio>
int cnt = 0;

int main() {
	freopen("out.txt", "w", stdout);
	for (register long long i = 1; i <= (1<<30); ++i)
		cnt += (i^(i<<1)^(i*3)) == 0;
	printf("%d\n", cnt);
}

