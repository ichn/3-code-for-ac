#include <bits/stdc++.h>
using namespace std;

pair<int, int> dom[1111];
int n, sumU, sumD, sum;

int main() {

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d %d", &dom[i].first, &dom[i].second);
		sumU += dom[i].first, sumD += dom[i].second;
	}
	if ((sumU + sumD) & 1) {
		puts("-1");
		return 0;
	}
	sum = (sumU + sumD) / 2;


	return 0;
}
