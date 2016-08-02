#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <bitset>
#include <vector>
#include <set>
using namespace std;

typedef long long LL;
int t, p;
pair<LL, LL> opt[111];
set<pair<LL, LL> > all;

int main() {
	scanf("%d %d", &p, &t);
	int i, j;
	while (scanf("%d %d", &i, &j) != EOF) {
		if (j > 50)
			opt[i].first |= 1<<(j-50);
		else opt[i].second |= 1<<j;
	}
	for (int i = 1; i <= p; ++i)
		if (all.find(opt[i]) == all.end())
			all.insert(opt[i]);
	printf("%d\n", (int)all.size());
	return 0;
}
