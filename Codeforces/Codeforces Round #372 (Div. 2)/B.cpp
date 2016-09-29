#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define _pir pair<int, int>
#define _vec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define pfile(x) freopen(#x".in", "r", stdin), freopen("_"#x".out", "w", stdout)
#define hfile freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define gfile(x) freopen(#x".in", "w", stdout);
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
};
using namespace my_useful_tools;


char str[50011];

int cnt[27];
int id(char s) {
	if (s == '?')
		return 0;
	else return s - 'A' + 1;
}


vector<char> dis;

bool ok() {
	dis.clear();
	for (int i = 1; i <= 26; ++i)
		if (cnt[i] > 1)
			return false;
		else if (cnt[i] == 0)
			dis.push_back('A' + i - 1);
	return true;
}

int main() {

#ifdef love_yxl
	file(B);
#endif

	scanf("%s", str);
	int n = strlen(str);
	if (n < 26) {
		puts("-1");
		return 0;
	}
	for (int i = 0, j = 0; i < n; ++i) {
		while (j - i < 26 && j < n) {
			++cnt[id(str[j])];
			++j;
		}
		if (j - i == 26) {
			if (ok()) {
				int t = 0;
				for (int w = 0; w < i; ++w)
					putchar(str[w] == '?' ?'A' : str[w]);
				for (int k = i; k < j; ++k) {
					if (str[k] != '?')
						putchar(str[k]);
					else {
						putchar(dis[t++]);
					}
				}
				for (int w = j; w < n; ++w)
					putchar(str[w] == '?' ?'A' : str[w]);
				puts("");
				return 0;
			}
		}
		--cnt[id(str[i])];
	}
	puts("-1");

	return 0;
}

