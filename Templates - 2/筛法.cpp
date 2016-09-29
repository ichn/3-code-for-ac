#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e7 + 100;
typedef long long LL;

int prime[maxn], p_tot;
bool chk[maxn];

void linear_primes(int N) {
	memset(chk, false, sizeof chk);
	p_tot = 0;
	for (int i = 2; i <= N; ++i) {
		if (!chk[i]) prime[++p_tot] = i;
		for (int j = 1; j <= p_tot; ++j) {
			if (prime[j]*i > N) break;
			chk[i*prime[j]] = true;
			if (i % prime[j] == 0) break;
		}
	}
}

int inv[maxn];

int exgcd(int a, int b, int &x, int &y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	int d = exgcd(b, a%b, y, x);
	y -= (a/b)*x;
	return d;
}

int g_inv(int a, int n) {
	int x, y;
	exgcd(a, n, x, y);
	return (x%n+n)%n;
}

void get_inv(int N, int p) {
	memset(chk, 0, sizeof chk);
	p_tot = 0;
	inv[1] = 1;
	for (int i = 2; i <= N; ++i) {
		if (!chk[i]) {
			prime[++p_tot] = i;
			inv[i] = g_inv(i, p);
		}
		for (int j = 1; j <= p_tot; ++j) {
			if (prime[j]*i > N) break;
			inv[i*prime[j]] = (LL)inv[i]*inv[prime[j]]%p;
			if (i % prime[j] == 0) break;
		}
	}
}



int main() {
	freopen("筛法.in", "r", stdin);
	freopen("筛法.out", "w", stdout);

	int p = 1e9+7;
	get_inv(1e7, p);

	return 0;
}

