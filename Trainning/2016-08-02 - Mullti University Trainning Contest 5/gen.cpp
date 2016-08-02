#include <bits/stdc++.h>
using namespace std;

set<pair<int ,int> > s;

int main() {
	freopen("1004.in", "w", stdout);

	srand((int)time(NULL));
	int T = 10;
	while (T--) {
		int n = rand() % 100 + 3;
		printf("%d\n", n);
		s.clear();
		for (int i = 1; i <= n; ++i) {
			int u = rand(), v = rand();
			while (s.find(make_pair(u, v)) != s.end()) {
				u = rand(), v = rand();
			}
			printf("%d %d\n", u, v);
			s.insert(make_pair(u, v));
		}
	}


	return 0;
}
