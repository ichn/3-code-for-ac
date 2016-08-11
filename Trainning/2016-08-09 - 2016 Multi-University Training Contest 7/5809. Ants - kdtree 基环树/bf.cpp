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
	const int INF = 0x3f3f3f3f;
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
const int maxn = 200000+100;

int n, q;
struct Point {
	int x, y;
} p[maxn];


#define sqr(x) ((LL)(x)*(x))
int cls[maxn];
LL dis[maxn];
int main() {
#ifdef lol
	freopen("1001.in", "r", stdin);
	freopen("bf.out", "w", stdout);
#endif
	int T = fr();
	for (int tt = 1; tt <= T; ++tt) {
		int n, q;
		scanf("%d %d", &n, &q);
		for (int i = 1; i <= n; ++i) {
			fr(p[i].x, p[i].y);
			dis[i] = LLONG_MAX;
		}
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j)
				if (i != j) {
					LL dd = sqr((p[i].x-p[j].x))+sqr((p[i].y-p[j].y));
					if (dd < dis[i]) {
						dis[i] = dd;
						cls[i] = j;
					} else if (dd == dis[i]) {
						if (p[cls[i]].x > p[j].x || (p[cls[i]].x == p[j].x && p[cls[i]].y > p[j].y))
							cls[i] = j;
					}
				}
		}
		for (int i = 1, j, k; i <= q; ++i)
			scanf("%d %d", &j, &k);
		for (int i = 1; i <= n; ++i)
			printf("%d\n", cls[i]);
	}

	return 0;
}

