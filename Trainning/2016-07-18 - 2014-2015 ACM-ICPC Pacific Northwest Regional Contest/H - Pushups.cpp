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
	inline char gchar(char r=gc()) {
		for(;r==' '||r=='\n'||r=='\r';
				r=gc());return r;}
	template<class T> inline void fr(T&r) {
		char c=gc();
		for(;c<'0'||'9'<c;c=gc());
		for(r=0;'0'<=c&&c<='9';c=getchar())
			r=r*10+c-'0';
	}
	template<class T> inline void fr(T&a,T&b) {
		fr(a), fr(b);
	}
	template<class T> inline void fr(T&a,T&b,T&c) {
		fr(a), fr(b), fr(c);
	}
	int fr() {
		int r=0;char c=gc();
		for(;c<'0'||'9'<c;c=gc());
		for(r=0;'0'<=c&&c<='9';c=getchar())
			r=r*10+c-'0';
		return r;
	}
	const int maxE = 10000, maxV = 10000;
	struct Edge {
		int e, h[maxV], to[maxE], nxt[maxE];
		void init() {
			cls(h,-1);
			e=0;
		}
		void addEdge(int u,int v) {
			to[e] = v, nxt[e] = h[u], h[u] = e++;
		}
	};
};
using namespace my_zone;



const int maxF = 2000;

int n, m, s[14];
int f[5001][maxF];

void solve() {
	memset(f, 0, sizeof f);
	f[0][0] = 1;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j < maxF; ++j)
			if (f[i][j])
				for (int k = 0; k < m; ++k)
					if (i+j+s[k] <= n)
						f[i+j+s[k]][j+s[k]] = 1;
	}
	int ans = -1;
	for (int i = maxF-1; 0 <= i; --i)
		if (f[n][i]) {
			ans = i;
			break;
		}
	printf("%d\n", ans);
}

int main() {
#ifdef lol
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif

	int tCase = fr();
	while (tCase--) {
		scanf("%d %d", &n, &m);
		rep(i, 0, m) {
			scanf("%d", &s[i]);
		}
		solve();
	}
	return 0;
}
