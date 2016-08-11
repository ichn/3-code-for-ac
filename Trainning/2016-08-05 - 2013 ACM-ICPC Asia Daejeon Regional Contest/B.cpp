#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second

int gcd(int a, int b) {
	return a == 0 ? b : gcd(b, a%b);
}


int A, B, x, y, n, d;
vector<pair<int, int > > O;
void calc(int a, int b) {

}

int f[2][7];

int main() {
#ifdef lol
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	int T = fr();
	while (T--) {
		fr(n, A, B), fr(x, y);
		O.resize(n+1);
		O[0].x = x;
		O[0].y = y;
		d = gcd(A, B);
		for (int i = 1; i < n; ++i) {
			fr(O[i].x, O[i].y);
		}
		int c = 0, l = 1;
		for (int i = 0; i < n; ++i) {
			memset(f[c], 0, sizeof f[c]);
			f[c][0] = f[l][0] + chk(i, 0)
		}
	}
	return 0;
}
