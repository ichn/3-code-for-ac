#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	return a == 0 ? b : gcd(b, a%b);
}

set<pair<int ,int> > ss;

int A, B;
void calc(int a, int b) {
	if (ss.find(make_pair(a, b)) != ss.end())
		return ;
	ss.insert(make_pair(a, b));
	//printf("%d %d\n", a, b);
	calc((a+b)%A, 0);
	calc(0, (a+b)%B);
	calc(0, 0);
	calc(a, 0);
	calc(0, b);
	calc(0, B-(A-a)%B);
	calc(A-(B-b)%A, 0);
	calc((a+b)%A, B);
	calc(A, (a+b)%B);
	calc(A, B);
	calc(a, B);
	calc(A, b);
	calc(A, B-(A-a)%B);
	calc(A-(B-b)%A, B);
}

int main() {
#ifdef lol
	freopen("B.in", "r", stdin);
	freopen("B2.out", "w", stdout);
#endif

	ss.clear();

	A = 25, B = 250;
	calc(11, 0);
	for (set<pair<int, int> >::iterator pp = ss.begin(); pp != ss.end(); ++pp) {
		printf("%d %d\n", pp->first, pp->second);
	}

	return 0;
}
