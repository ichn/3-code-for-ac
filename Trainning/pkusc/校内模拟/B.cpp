#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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

vector<string> res[8], wh[8];

void init() {
	res[0].pb(string("X"));
	wh[0].pb(string(" "));
	for (int i = 1; i < 7; ++i) {
		int t = (int)res[i - 1].size();
		int s = t * 3;
		wh[i].resize(s);
		reu(j, 0, s) {
			wh[i][j].append(wh[i - 1][j % t]);
			wh[i][j].append(wh[i - 1][j % t]);
			wh[i][j].append(wh[i - 1][j % t]);
		}
		res[i].resize(s);
		reu(j, 0, s) {
			if ((j / t) % 2 == 0) {
				res[i][j].append(res[i - 1][j % t]);
				res[i][j].append(wh[i - 1][j % t]);
				res[i][j].append(res[i - 1][j % t]);
			} else {
				res[i][j].append(wh[i -1][j % t]);
				res[i][j].append(res[i-1][j%t]);
				res[i][j].append(wh[i - 1][j%t]);
			}
		}
	}
	//for (int i = 1; i < 7; ++i) {
	//	int s = (int)res[i].size();
	//	reu(j, 0, s) {
	//		while (res[i][j].
	//	}
	//}
}

void print(vector<string> ans) {
	int t = (int)ans.size();
	for (int i = 0; i < t; ++i)
		cout << ans[i] << "\n";
}

int main() {
#ifdef love_lhy
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif

	init();
	int x = fr();
	while (x != -1) {
		if (x == 1) {
			puts("X");
		} else {
			print(res[x - 1]);
		}
		puts("-");
		x = fr();
	}
 
	return 0;
}


