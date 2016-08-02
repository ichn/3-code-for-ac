#include <bits/stdc++.h>
using namespace std;

const int mod = 1000000007;
const int B = 11;

class WinterAndSnowmen {
	int N, M, p;
	int add(int a, int b) {
		return (a + b) % mod;
	}
	int f[2001][2048][2];
	int dp(int t, int s, int b) {
		int &ret = f[t][s][b];
		if (ret != -1) return ret;
		ret = 0;
		if (t == 0) {
			if (s == 1 && !b)
				ret = 1;
		} else {
			ret = add(ret, dp(t-1, s, b));
			if (t <= M)
				ret = add(ret, dp(t-1, s^(t>>p), b));
			if (t <= N)
				ret = add(ret, dp(t-1, s^(t>>p), b^((t>>p)&1)));
		}
		return ret;
	}
	public:
	int getNumber(int _N, int _M) {
		N = _N, M = _M;
		int ans = 0;
		for (p = 0; p < B; ++p) {
			memset(f, -1, sizeof f);
			ans = add(ans, dp(max(N, M), 0, 0));
		}
		return ans;
	}
};

#ifdef love_lhy
int main() {
	cout << (new WinterAndSnowmen)->getNumber(3, 5) << endl;
	cout << (double)clock() / CLOCKS_PER_SEC << endl;
	return 0;
}

/*
 * 不错的题
 * 先想到一个n^3的dp，之后可以发现只要考虑一个数及另外一个数异或最高位为零，最终发现，把一个数无论放到哪个集合，都会对X^Y产生影响，因此只需把X^Y放入状态中。
 * */

#endif
