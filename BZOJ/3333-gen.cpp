#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 100;
int ta[maxn];

int main() {

	freopen("3333.in", "w", stdout);
	srand(clock());
	int n = 5e5, m = 5e5;
	int r = 10000;
	printf("%d %d\n", n, m);
	for(int i = 0; i < r; ++i)
		ta[i] = rand() % (int)(1e9) + 1;
	
	for(int i = 1; i <= n; ++i) {
		printf("%d ", ta[rand() % r]);
	} puts("");

	while(m --) {
		printf("%d\n", rand() % n + 1);
	}
		

	return 0;
}
