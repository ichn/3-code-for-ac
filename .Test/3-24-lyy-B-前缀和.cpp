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
//#define generator_sbit

// 写代码是很快的，重要的是思考，不要急着写，先想清楚
//
// 把人们引向艺术和科学的最强烈的动机之一，
// 是要逃避日常生活中令人厌恶的粗俗和使人绝望的沉闷，
// 是要摆脱人们自己反复无常的欲望的桎梏。
// 一个修养有素的人总是渴望逃避个人生活而进入客观知觉和思维的世界。
//
// 铭记你的信仰，铭记你的使命，铭记你的罪恶，铭记你所深爱着的
// 永远不要相信自己的意志力

const int maxn = 1e4 + 100;
const int maxa = 1e6 + 100;
int n, k, a, b, c, tot, h, t;
pair<DB, int> act[maxn];
DB gl[maxa], pre_mul[maxa], pre_ans[maxa], suf_mul[maxa], suf_ans[maxa];


int main() {
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#ifdef generator_sbit
	srand((int)time(NULL));
#endif
	for (int TT=1, T=fr(); TT <= T; ++TT) {
		fr(n, k);
		rep(i, 1, n) {
			fr(a, b, c);
			act[i] = mp((DB)a/b, c);
		}
		sort(act+1, act+n+1);
		tot = 0;
		rep(i, 1, n) {
			rep(j, 1, act[i].second)
				gl[++tot] = act[i].first;
		}
		reverse(gl+1, gl+tot+1);
		pre_mul[0] = pre_ans[0] = 1;
		rep(i, 1, tot) {
			pre_ans[i] = pre_ans[i-1]*(1-gl[i]) + pre_mul[i-1]*gl[i];
			pre_mul[i] = pre_mul[i-1]*gl[i];
		}
		reverse(gl+1, gl+tot+1);
		suf_mul[0] = suf_ans[0] = 1;
		rep(i, 1, tot) {
			suf_ans[i] = suf_ans[i-1]*gl[i] + suf_mul[i-1]*(1-gl[i]);
			suf_mul[i] = suf_mul[i-1]*(1-gl[i]);
		}
		DB ans = 1e30;
		rep(i, 0, k) {
			DB tmp = pre_ans[i]*suf_mul[k-i] + pre_mul[i]*suf_ans[k-i] - pre_mul[i]*suf_mul[k-i];
			ans = min(ans, 1-tmp);
		}
		printf("Case #%d: %.10lf\n", TT, ans);
	}

	return 0;
}
