#include <bits/stdc++.h>
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
	const int maxv = 100, maxe = 100;
	struct Edge {
		int edge, head[maxv], to[maxe], next[maxe];
		Edge() { edge = 0; memset(head, -1, sizeof head); }
		void addedge(int u, int v) {
			to[edge] = v, next[edge] = head[u];
			head[u] = edge++;
		}
	};
};
using namespace my_useful_tools;

const int mod = 1073741823;
const int maxn = 2000 * 2000 + 100;
int mu[maxn], pri[maxn], cnt_p, chk[maxn];
int a, b, c, n;
int f[maxn];
 
int main() {

	fr(a, b, c);
	n = a * b;
	mu[1] = 1;
	rep(i, 2, n) {
		if (!chk[i]) {
			pri[++cnt_p] = i;
			mu[i] = -1;
		}
		for (int j = 1; j <= cnt_p; ++j) {
			if (pri[j] * i > n) break;
			chk[i * pri[j]] = 1;
			mu[i * pri[j]] = mu[i] * -1;
			if (i % pri[j] == 0) {
				mu[i * pri[j]] = 0;
				break;
			}
		}
	}
	rep(i, 1, n) {
		rep(j, 1, n) {
			if (i % j == 0) {
				rep(k, 1, c)
					if (k % j == 0) {
						f[i] += mu[j] * (c / k);
					}
			}
		}
	}
	/*
	rep(i, 1, n) {
		if (mu[i] == 0) continue;
		int p = 0;
		rep(j, 1, n) {
			if (j % i == 0) {
				int x = j / i;
				p = 0;
				rep(k, 1, x)
					p += c / (k * i);
				f[j] += mu[i] * p;
			}
			continue;
			if (i * j > n) break;
			p = 0;
			rep(k, 1, j)
				p += c / (k * i);
			//int m = i * j;
			//p += c / m;
	//		p &= mod;
			f[i * j] += mu[i] * p;
	//		f[m] &= mod;
		}
	}
	rep(i, 1, n) {
		Wn(f[i]);
	}
	*/
	int ans = 0;
	rep(i, 1, a) {
		rep(j, 1, b)
			if (__gcd(i, j) == 1) {
				ans += (a / i) * (b / j) * f[i * j];
		//		ans = (ans + (((LL)(((a / i) * (b / j)) & mod) * f[i * j]) & mod)) & mod;
			}
	}
	printf("%d\n", ans);
 
	return 0;
}
