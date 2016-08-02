#include <bits/stdc++.h>
using namespace std;

bool isPrime(int x) {
	if (x < 2) return false;
	int p = sqrt(x + .5);
	for (int i = 2; i <= p; ++i)
		if (x % i == 0)
			return false;
	return true;
}

int main() {
	srand((int)time(NULL));
	freopen("3992.in", "w", stdout);

	int n = rand() % (1000000000) + 1;
	int p = rand() % 8000 + 1;
	while (!isPrime(p))
		p = rand() % 8000 + 1;


	int nS = p - (rand() % (p / 5));


	if (nS == p) nS = p - 2;

	printf("%d %d %d %d\n", n, p, rand() % p + 1, nS);

	static set<int> s;
	s.clear();
	for (int i = 1; i <= nS; ++i) {
		int a = rand() % p + 1;
		while (s.find(a) != s.end())
			a = rand() % p + 1;
		printf("%d\n", a);
		s.insert(a);
	}

	return 0;
}
