#include <bits/stdc++.h>
using namespace std;
namespace my_zone {
#define rep(_i, _k, _j) for(int _i = _k; _i < _j; ++_i)
#define rgo(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define clr(t) memset(t, 0, sizeof t);
#define clo(t, v) memcpy(t, v, sizeof t);
#define cls(t, v) memset(t,v,sizeof t);
#define pc(c) putchar(c)
#define gc() getchar()
	typedef pair<int, int> ipir;
	typedef vector<int> ivec;
	typedef set<int> iset;
	typedef long long LL;
	typedef double DB;
	inline char gchar(char r=gc()) {
		for(;r==' '||r=='\n'||r=='\r';
				r=gc());return r;}
	template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
		if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
		ret = ret * flag;
	}
	inline int fr() { int x; fr(x); return x; }
	template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }

};
using namespace my_zone;

const int INF = 0x7f7f7f7f;

const int maxN = 1e5 + 100;
int a[maxN], n, c[21][21];

int main() {
#ifdef lol
	freopen("5798.in", "r", stdin);
	freopen("5798.out", "w", stdout);
#endif

	int T = fr();
	while (T--) {
		scanf("%d", &n);
		scanf("%d", &a[1]);
		memset(c, 0, sizeof c);
		for (int i = 2; i <= n; ++i) {
			scanf("%d", &a[i]);
			int j = 19;
			for (; j >= 0; --j)
				if ((a[i]>>j)^(a[i-1]>>j)) break;
			int t = (a[i]>>j) > (a[i-1]>>j) ? 1 : -1;
			for (int k = j; k >= 0; --k) {
				int u = (a[i]>>k)&1;
				int v = (a[i-1]>>k)&1;
				if (u ^ v)
					c[j][k] += t * (u > v ? 1 : -1);
			}
		}
	//	for (int i = 0; i < 20; ++i) {
	//		for (int j = 0; j < 20; ++j)
	//			printf("%2d ", c[i][j]);
	//		puts("");
	//	}
		LL ans = LLONG_MAX;
		int X;
		for (int i = 0; i < 1<<20; ++i) {
			int sum = 0;
			for (int j = 19; 0 <= j; --j)
				for (int k = j; 0 <= k; --k)
					sum += c[j][k] * (1<<k) * ((((i>>j)&1)^((i>>k)&1)) > 0 ? -1 : 1);
			if (sum < ans) {
				ans = sum;
				X = i;
			}
		}
		cout << X << ' ' << ans << endl;
	}

	return 0;
}
