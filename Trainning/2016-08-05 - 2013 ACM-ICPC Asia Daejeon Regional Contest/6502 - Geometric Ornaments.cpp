#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;
#define mp make_pair
#define pb push_back
#define x first
#define y second

const int mod = 10007;

LL a[50005];
LL b[50005];
LL c[50005];

int main() {
#ifdef lol
	freopen("hd.in", "r", stdin);
	freopen("hd.out", "w", stdout);
#endif

	a[0] = 0;
	a[1] = 1;
	for (int i = 2; i <= 50000; ++i)
		a[i] = (4 * a[i-1] % mod - a[i-2] + mod) % mod;
	c[1] = 2;
	c[2] = 12;
	c[3] = 50;
	for (int i = 4; i <= 50000; ++i) {
		c[i] = 5 * c[i-1] - 5 * c[i-2] + c[i-3];
		c[i] %= mod;
		c[i] += mod;
		c[i] %= mod;
	}
	//for (int i = 1; i <= 15; ++i)
	//	cout << c[i] << endl;;
	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		cout << a[n] << ' '<< ((c[n]*n % mod)*((mod+1)/2)) % mod<<endl;;
	}

	return 0;
}
