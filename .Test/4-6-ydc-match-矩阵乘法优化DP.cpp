#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <climits>
#include <cstdlib>
#include <ctime>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<int, int>
#define ivec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define file_hza freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define file_gen(x) freopen(#x".in", "w", stdout);
	const int INF = 0x3f3f3f3f;
	typedef long long LL;
	typedef double DB;
	inline void pc(char c) { putchar(c); }
	template<class T> inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
	template<class T> inline void W(T p) { if(p < 0) pc('-'), p = -p; if(p / 10 != 0) W(p / 10); pc('0' + p % 10); }
	template<class T> inline void Wn(T p) { W(p), brl; } template<class T> inline void W(T a, T b) { W(a), pc(' '), W(b); }
	template<class T> inline void Wn(T a, T b) { W(a), pc(' '), Wn(b); }
	template<class T> inline void W(T a, T b, T c) { W(a), pc(' '), W(b), pc(' '), W(c); } 
	inline char gchar() { char ret = getchar(); for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar()); return ret; }
	template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
		if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
		ret = ret * flag;
	}
	inline int fr() { int x; fr(x); return x; }
	template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }
	template<class T> inline T fast_pow(T base, T index, T mod = 2147483647, T ret = 1) {
		for(; index; index >>= 1, base = base * base % mod) if(index & 1) ret = ret * base % mod;
		return ret;
	}
};
using namespace my_useful_tools;

const int mod = 998244353;
const int maxSize = 401;
struct Matrix {
	int d[maxSize][maxSize];
	int sz;
	void init(int _sz) {
		sz = _sz;
		reu(i, 0, sz) d[i][i] = 1;
	}
	void clear() {
		reu(i, 0, sz)
			reu(j, 0, sz)
				d[i][j] = 0;
	}
	void print() {
		reu(i, 0, sz) {
			reu(j, 0, sz)
				printf("%d ", d[i][j]);
			puts("");
		}
	}
	Matrix operator * (const Matrix&rhs) {
		Matrix ret;
		ret.sz = sz;
		ret.clear();
		reu(i, 0, sz)
			reu(j, 0, sz)
				reu(k, 0, sz) {
					LL t = 1LL * d[i][k] * rhs.d[k][j];
					t %= mod;
					(ret.d[i][j] += t) %= mod;
				}
	//	reu(i, 0, sz)
	//		reu(j, 0, sz)
	//			reu(k, 0, sz)
	//				(ret.d[i][k] += (LL)d[i][j]*rhs.d[j][k] % mod) %= mod;
		return ret;
	}
};
Matrix fpm(Matrix b, LL i) {
	Matrix r;
	r.init(b.sz);
	for (; i; i>>=1, b=b*b)
		if (i&1) r=r*b;
	return r;
}

LL n;
int m, s;

int main() {
	freopen("match.in", "r", stdin);
	freopen("match.out", "w", stdout);

	fr(n);
	fr(m);
	s = 1 << m;

	static Matrix a;
	a.sz = s;
	a.clear();

	//a.d[0][1] = 1;
	reu(i, 0, s) {
		int p = i;
		reu(j, 0, m) {
			if (p & (1 << j)) {
				a.d[i][p] = 1;
				p -= (1 << j);
				if (p == 0) break;
			} else break;
		}
		a.d[i][i + 1] = 1;
	}
	a.d[s - 1][0] = 1;
	static Matrix b = fpm(a, n - 1);

	printf("%d\n", b.d[0][s - 1]);
 
	return 0;
}
