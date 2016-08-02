#include <bits/stdc++.h>
#define pt cerr << (double)clock() / CLOCKS_PER_SEC << endl
using namespace std;

typedef long long LL;

const int mod = 479 * (1 << 21) + 1;
const int G = 3;

const int maxn = 10000;


LL fpm(LL a, LL i, LL m) {
	LL r = 1;
	for (; i; i>>=1, a=a*a%m)
		if (i&1) r=r*a%m;
	return r;
}

int n, m, x, nS;
int s[maxn], ind[maxn];


int gPrimaryRoot(int a) {
	static vector<int> fac;
	fac.clear();
	int p = a - 1, b = sqrt(p + .5);
	for (int i = 2; i <= b; ++i)
		if (p % i == 0) {
			fac.push_back(i);
			while (p % i == 0)
				p /= i;
		}
	// Vergissmeinnicht 
	if (p != 1) fac.push_back(p);
	for (int i = 2; i <= a; ++i) {
		bool isPR = true;
		for (int j = 0; j < (int)fac.size(); ++j)
			if (fpm(i, (a - 1) / fac[j], a) == 1) {
				isPR = false;
				break;
			}
		if (isPR) return i;
	}
	return 0;
}

const int maxEle = 1<<15;

LL coef[maxEle], res[maxEle];
int N, rG[2][maxEle<<1], rev[maxEle];

void dft(LL *a, int N, int d) {
	for (int i = 0; i < N; ++i)
		if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int i = 2; i <= N; i <<= 1) {
		LL c = 1, s = rG[d][i], u, v;
		for (int j = 0; j < N; c = 1, j += i)
			for (int k = j; k < j + (i>>1); c = c * s % mod, ++k) {
				u = a[k], v = a[k + (i>>1)] * c % mod;
				a[k] = (u+v) % mod;
				a[k+(i>>1)] = (u-v+mod) % mod;
			}
	}
	if (d == 1) {
		int rN = fpm(N, mod - 2, mod);
		for (int i = 0; i < N; ++i)
			a[i] = a[i] * rN % mod;
	}
}

int main() {

#ifdef love_lhy
	freopen("3992.in", "r", stdin);
	freopen("3992.out", "w", stdout);
#endif

	scanf("%d %d %d %d", &n, &m, &x, &nS);
	x %= m;
	for (int i = 1; i <= nS; ++i) {
		scanf("%d", &s[i]);
		s[i] %= m;
		if (s[i] == 0) {
			--i, --nS;
		}
	}

	int g = gPrimaryRoot(m);

	int bs = 1;
	for (int i = 0; i < m - 1; ++i)
		ind[bs] = i, bs = bs * g % m;


	for (int i = 1; i <= nS; ++i) {
		coef[ind[s[i]]] = 1;
	}

	N = 1<<14;

	for (int i = 1; i <= N; i <<= 1)
		rG[0][i] = fpm(G, (mod - 1) / i, mod);
	for (int i = 1; i <= N; i <<= 1)
		rG[1][i] = fpm(rG[0][i], (mod - 2), mod);
	for (int i = 0; i < N; ++i)
		rev[i] = (rev[i>>1]>>1)|((i&1)<<13);

	res[0] = 1;

	//for (int i = 0; i < N; ++i) {
	//	printf("%d ", coef[i]);
	//} puts("");
	//
	//dft(coef, N, 0);
	//for (int i = 0; i < N; ++i)
	//	coef[i] = coef[i] * coef[i] % mod;
	//dft(coef, N, 1);
	//for (int i = m - 1; i < N; ++i)
	//	(coef[i - (m - 1)] += coef[i]) %= mod, coef[i] = 0;
	//
	//dft(coef, N, 0);
	//for (int i = 0; i < N; ++i)
	//	coef[i] = coef[i] * coef[i] % mod;
	//dft(coef, N, 1);
	//
	//for (int i = m - 1; i < N; ++i)
	//	(coef[i - (m - 1)] += coef[i]) %= mod, coef[i] = 0;
	//
	//printf("%d\n", coef[ind[x]]);
	//
	//for (int i = 0; i < N; ++i)
	//	printf("%d ", coef[i]);
	//puts("");
	//
	//return 0;

	// wenn die Jahreszeit des Tauens kommt

	for (; n; n >>= 1) {

		dft(coef, N, 0);
		if (n & 1) {
			dft(res, N, 0);
			for (int i = 0; i < N; ++i)
				res[i] = res[i] * coef[i] % mod;
			dft(res, N, 1);
			for (int i = m - 1; i < N; ++i)
				(res[i % (m - 1)] += res[i]) %= mod, res[i] = 0;
		}
	//	for (int i = 0; i < m; ++i)
	//		printf("%lld ", coef[i]);
	//	puts("");

		for (int i = 0; i < N; ++i)
			coef[i] = coef[i] * coef[i] % mod;
		dft(coef, N, 1);
		for (int i = m - 1; i < N; ++i)
			(coef[i % (m - 1)] += coef[i]) %= mod, coef[i] = 0;
	//	for (int i = 0; i < m - 1; ++i)
	//		printf("%lld ", coef[i]);
	//	puts("");
	}

	printf("%lld\n", res[ind[x]] % mod);

	return 0;
}
