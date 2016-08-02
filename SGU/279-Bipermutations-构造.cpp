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
};
using namespace my_useful_tools;

// 写代码是很快的，重要的是思考，不要急着写，先想清楚
//
// 把人们引向艺术和科学的最强烈的动机之一，
// 是要逃避日常生活中令人厌恶的粗俗和使人绝望的沉闷，
// 是要摆脱人们自己反复无常的欲望的桎梏。
// 一个修养有素的人总是渴望逃避个人生活而进入客观知觉和思维的世界。
//
// 铭记你的信仰，铭记你的使命，铭记你的罪恶，铭记你深爱着的

const int maxn = 2000 + 100;

bool del[maxn];
int c[maxn], ans[maxn], cnt, *tmp, base[maxn], n, top;
 
int main() {
	file(279);

	fr(n);
	rep(i, 1, n) fr(c[i]);
	tmp = base;
	rep(i, 1, n) {
		int mn = INF, pos;
		rep(j, 1, n) {
			if (!del[j] && c[j] < mn) {
				mn = c[j];
				pos = j;
			}
		}
		if (c[pos] < 0) {
			puts("NO");
			return 0;
		}
		while (c[pos] != 0) {
			if (top == 0) {
				puts("NO");
				return 0;
			}
			ans[++cnt] = tmp[1];
			--top, tmp = tmp + 1;
			rep(j, 1-ans[cnt], n) if (!del[j])  {
				--c[j];
			}
			mn = INF;
			rep(j, 1, n) {
				if (!del[j] && c[j] < mn) {
					mn = c[j];
					pos = j;
				}
			}
			if (c[pos] < 0) {
				puts("NO");
				return 0;
			}

		}
		ans[++cnt] = pos;
		tmp[++top] = -pos;
		del[pos] = true;
		rep(j, 1, pos-1) if (!del[j]) {
			--c[j];
		}
	}
	puts("YES");
	//reverse(tmp+1, tmp+top+1);
	rep(j, 1, top) {
		ans[++cnt] = tmp[j];
	}
	reverse(ans+1, ans+cnt+1);
	rep(i, 1, n<<1) {
		printf("%d ", ans[i]);
	}
	puts("");

	return 0;
}

