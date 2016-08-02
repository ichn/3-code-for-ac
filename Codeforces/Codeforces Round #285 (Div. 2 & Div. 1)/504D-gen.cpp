#include <bits/stdc++.h>
using namespace std;

int main() {
	freopen("504D.in", "w", stdout);
	int n = 2000;
	printf("%d\n", n);
	for (int i=1; i<=n; ++i) {
		printf("%d", rand()%9+1);
		for (int j=1; j<600; ++j) {
			printf("%d", rand()%10);
		} puts("");
	}
	
	return 0;
}

