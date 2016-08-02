#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

template<class T> T gcd(T a, T b) {
	return b == 0 ? a : gcd(b, a%b);
}
template<class T> T ex_gcd(T a, T b, T&x, T&y) {
	if (b == 0) {
		x = 1, y = 0;
		return a;
	}
	T d = ex_gcd(b, a%b, y, x);
	y -= a/b*x;
	return d;
}
template<class T> void fm(T&a, T m) {
	if (a >= m) a-= m;
}
LL fmm(LL a, LL b, LL m) {
	LL r = 0;
	for (; b; b>>=1, a+=a, fm(a, m))
		if (b&1) r+=a, fm(r, m);
	return r;
}
template<class T> T fpm(T b, T i, T m) {
	T r = 1;
	for (; i; i>>=1, b=fmm(b, b, m))
		if (i&1) r=fmm(r, b, m);
	return r;
}
bool MillerRabin(LL x, LL b) {
	LL s = x-1;
	int t = 0;
	for (; !(s&1); s>>=1, ++t);
	LL u = fpm(b, s, x);
	if (u == 1) return true;
	for (int i=0; i < t; ++i) {
		if (u == x-1) return true;
		u = fmm(u, u, x);
	}
	return false;
}
bool isPrime(LL x) {
	const int pNum = 10;
	const int P[pNum] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
	for (int i = 0; i < pNum; ++i) {
		if (x == P[i]) return true;
		if (!(x % P[i])) return false;
	}
	for (int i = 0; i < pNum; ++i) {
		if (!MillerRabin(x, P[i]))
			return false;
	}
	return true;
}
void PollardRho(LL x, vector<LL>&res) {
	if (x == 1) return ;
	if (isPrime(x)) {
		res.push_back(x);
		return ;
	}
	LL p = -1;
	LL cnt = 0;
	while (p == -1) {
		LL u = 1, v = 1;
		int stp = 1, cir = 2;
		++cnt;
		while (true) {
			u = (fmm(u, u, x)+cnt)%x;
			if (u == v) break;
			LL d = gcd(abs(u-v), x);
			if (d > 1) {
				p = d;
				break;
			}
			++stp;
			if (stp == cir) {
				v = u;
				cir <<= 1;
			}
		}
	}
	PollardRho(p, res);
	PollardRho(x/p, res);
}

LL Rand() {
	LL x = rand();
	return (x << 30) | rand();
}

LL gPrime() {
	LL ret = Rand();
	while (!isPrime(ret))
		ret = Rand();
	return ret;
}

LL succPrime(LL x) {
	++x;
	while (!isPrime(x))
		++x;
	return x;
}

int main() {

	int T;
	scanf("%d", &T);

	LL t;
	vector<LL> fac;
	while (T--) {
		cin >> t;
		if (isPrime(t)) {
			puts("Prime");
		} else {
			fac.clear();
			PollardRho(t, fac);
			sort(fac.begin(), fac.end());
			cout << fac.back() << endl;
		}
	}
	return 0;
}
