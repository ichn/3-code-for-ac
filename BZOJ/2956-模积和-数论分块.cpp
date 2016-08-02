#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const LL mod = 19940417;
const LL inv2 = 9970209;
const LL inv6 = 23263820;

LL get(LL n, LL k) {
	LL ret = 0, last, t;
	for(LL i = 1; i <= n; i = last + 1) {
		t = k / i; last = min(n, k / t);
		ret += ((last - i + 1) * (i + last) % mod * inv2) % mod * t % mod;
		ret %= mod;
	}
	return ret;
}

LL sum(LL p) {
	return p * (p + 1) % mod * (2 * p + 1) % mod * inv6 % mod;
}

int main() {
	LL n, m;
	scanf("%lld %lld", &n, &m);
	if(m < n) swap(n, m);
	LL ans = (m * m - get(m, m)) % mod * ((n * n - get(n, n)) % mod);

	(ans += -(n * n % mod * m % mod - n * get(n, m) % mod - m * get(n, n) % mod) % mod + mod) %= mod;
	for(LL i = 1, last; i <= n; i = last + 1) {
		last = min(n, min(n / (n / i), m / (m / i)));
		(ans += -(n / i) * (m / i) % mod * ((sum(last) - sum(i - 1)) % mod) % mod) %= mod;
		ans += mod, ans %= mod;
	}
	printf("%lld\n", (ans % mod + mod) % mod);

	return 0;
}

