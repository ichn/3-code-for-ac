#include <bits/stdc++.h>
using namespace std;

int main() {

	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; ++i)
		putchar('9');
	putchar('8');
	for (int i = 1; i <= n; ++i)
		putchar('9');
	puts("");
	for (int i = 1; i <= n*2 - 1; ++i) {
		putchar('9');
	}
	puts("8");

	return 0;
}
