#include <bits/stdc++.h>
using namespace std;

int n;

bool val[1001];

bool val2[1001];

bool ans[1001];

int res;
void rnd() {
	for (int i = 1; i <= n; ++i)
		val[i] = rand() & 1;
}

int main() {

	scanf("%d", &n);

	srand(121);
	do {
		rnd();
		for (int i = 1; i <= n; ++i)
			printf("%d", val[i]);
		puts("");
		fflush(stdout);
		scanf("%d", &res);
	} while (res == 0);

	for (int i = 1; i < n; ++i) {
		val[i]^=1;
		val[i+1]^=1;
		for (int j = 1; j <= n; ++j)
			printf("%d", val[j]);
		puts("");
		fflush(stdout);
		scanf("%d", &res);
		val2[i] = (res != 0);
		val[i] ^= 1;
		val[i+1] ^= 1;
	}

	ans[1] = 1;
	for (int i = 1; i < n; ++i)
		if (val2[i]) {
			ans[i+1] = ans[i] ^ 1;
		} else {
			ans[i+1] = ans[i];
		}

	for (int i = 1; i <= n; ++i)
		if (ans[i]) {
			printf("%d", val[i]);
		} else printf("%d", val[i] ^ 1);
	puts("");
	fflush(stdout);
		
	scanf("%d", &res);
	if (res == n) {
		goto end;
	}


	for (int i = 1; i <= n; ++i)
		if (ans[i]) {
			printf("%d", val[i]^1);
		} else printf("%d", val[i]);

	puts("");
	fflush(stdout);
	

	//ans[1] = 0;
	//for (int i = 1; i < n; ++i)
	//	if (val2[i]) {
	//		ans[i+1] = ans[i] ^ 1;
	//	} else {
	//		ans[i+1] = ans[i];
	//	}
    //
	//for (int i = 1; i <= n; ++i)
	//	if (ans[i]) {
	//		printf("%d", val[i]);
	//	} else printf("%d", val[i] ^ 1);
	//goto end;


end:


	fflush(stdout);
	return 0;
}
