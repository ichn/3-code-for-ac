#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
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

struct fac {
	LL x, y;
	fac() {
		x = 0, y = 1;
	}
	fac(int p) {
		x = p, y = 1;
	}
	fac(LL a, LL b) {
		x = a, y = b;
	}
	void norm() {
		LL d = gcd(x, y);
		x /= d;
		y /= d;
	}
	void mult(int a) {
		x *= a;
		norm();
	}
	void div(int a) {
		y *= a;
		norm();
	}
	void minus(int a) {
		x -= a * y;
		norm();
	}
	void add(int a) {
		x += a * y;
		norm();
	}
	fac operator + (const fac&rhs) const {
		fac ret;
		ret.y = y * rhs.y;
		ret.x = x * rhs.y + y * rhs.x;
		ret.norm();
		return ret;
	}
	fac operator - (const fac&rhs) const {
		fac ret;
		ret.y = y * rhs.y;
		ret.x = x * rhs.y - y * rhs.x;
		ret.norm();
		return ret;
	}
	fac operator * (const fac&rhs) const {
		fac ret;
		ret.x = x * rhs.x;
		ret.y = y * rhs.y;
		ret.norm();
		return ret;
	}
	fac reverse() {
		fac ret;
		ret.x = y;
		ret.y = x;
		return ret;
	}
	fac operator / (fac rhs) {
		return (*this) * fac(rhs.y, rhs.x);
	}
	bool eq(int a) {
		return y == 1 && x == a;
	}
	void print(int mod) {
		fac ret;
		mod ^= 1;
		if (mod == 0)
			ret = *this;
		if (mod == 1)
			ret = fac(0) - (*this);
		if (mod == 2)
			ret = *this;
		if (mod == 3)
			ret = fac(1) / (*this);
		ret.norm();
		if (ret.y == 0) {
			puts("MULTIPLE");
			return ;
		}
		if (ret.x * ret.y < 0) {
			printf("-");
		}
		printf("%lld/%lld\n", abs(ret.x), abs(ret.y));
	}

} ans;

string eval;

stack<int> ope;
stack<fac> num;

char ss[50];
int main() {
#ifdef love_lhy
	freopen("C.in", "r", stdin);
	freopen("C.out", "w", stdout);
#endif

	gets(ss);
	eval = ss;
	reverse(eval.begin(), eval.end());

	// 0 +
	// 1 -
	// 2 *
	// 3 /
	bool flg = false;
	int rev = 0;
	int ans_mod = -1;
	for (int i = 0; i < eval.length(); ++i) {
		if (eval[i] == ' ')
			continue;
		if (flg) {
			continue;
		}
		if (eval[i] == '+')
			ope.push(1);
		else if (eval[i] == '-')
			ope.push(0);
		else if (eval[i] == '*')
			ope.push(3);
		else if (eval[i] == '/')
			ope.push(2);
		else if (eval[i] != 'X') {
			int p = eval[i] - '0';
			if (ope.size() == 0) {
				if (ans.eq(p)) {
					puts("MULTIPLE");
				} else {
					puts("NONE");
				}
				return 0;
			}
			int x = ope.top();
			if (x == 0) {
				ans.add(p);
			}
			if (x == 1) {
				ans.minus(p);
			}
			if (x == 2) {
				ans.mult(p);
			}
			if (x == 3) {
				if (p == 0) {
					puts("MULTIPLE");
					return 0;
				}
				ans.div(p);
			}
			ope.pop();
		} else {
			if (ope.size() == 0) {
				puts("NONE");
				return 0;
			}
			int x = ope.top();
			ope.top() ^= 1;
			ans_mod = x;
			eval = eval.substr(i + 1, eval.length());
			reverse(eval.begin(), eval.end());
			num.push(ans);
			for (int j = 0; j < eval.length(); ++j) {
				if (eval[j] == ' ') continue;
				if ('0' <= eval[j] && eval[j] <= '9') {
					num.push(fac(eval[j] - '0'));
				} else {
					fac a = num.top();
					num.pop();
					fac b = num.top();
					num.pop();

					if (eval[j] == '+') {
						a = a + b;
					}
					if (eval[j] == '-') {
						a = b - a;
					}
					if (eval[j] == '*') {
						a = a * b;
					}
					if (eval[j] == '/') {
						a = b / a;
					}
					num.push(a);
				}
			}
			while (!ope.empty()) {
				int y = ope.top() ^ 1;
				ope.pop();
				fac a = num.top();
				num.pop();
				fac b = num.top();
				num.pop();

				if (y == 0) {
					a = a + b;
				}
				if (y == 1) {
					a = b - a;
				}
				if (y == 2) {
					a = a * b;
				}
				if (y == 3) {
					a = b / a;
				}
				num.push(a);			
			}
			num.top().print(ans_mod);
			return 0;
		}
	}
 
	return 0;
}


