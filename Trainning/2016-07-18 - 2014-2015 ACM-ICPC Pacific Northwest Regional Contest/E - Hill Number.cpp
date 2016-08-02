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
	inline int fr() {
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


const int maxN = 70 + 5;

LL f[maxN][2][2][10];
int dig[maxN], n;

bool chk() {
	bool mrk = false;
	for (int i = 1; i < n; ++i) {
		if (dig[i+1] > dig[i]) {
			if (mrk) return false;
		}
		if (dig[i+1] < dig[i]) {
			mrk = true;
		}
	}
	return true;
}

int main() {
#ifdef lol
	freopen("e.in", "r", stdin);
	freopen("e.out", "w", stdout);
#endif

	int tCase = fr();
	string str;
	while (tCase--) {
		cin >> str;
		n = str.length();
		rep(i, 0, n)
			dig[i+1] = str[i] - '0';
		if (!chk()) {
			puts("-1");
			continue;
		}
		clr(f);
		dig[0] = 0;
		f[0][0][0][0] = 1;
		//pos
		   //free 1 lock 0
			  //inc 0 dec 1
		         //digit of this position
		rgo(i, 1, n) {
			rep(l, 0, 10) {
				rep(t, 0, l)
					f[i][1][0][l] += f[i-1][1][0][t];
				rgo(t, l+1, 9) {
					f[i][1][1][l] += f[i-1][1][1][t];
					f[i][1][1][l] += f[i-1][1][0][t];
				}
				f[i][1][0][l] += f[i-1][1][0][l];
				f[i][1][1][l] += f[i-1][1][1][l];
				if (l < dig[i]) {
					if (l > dig[i-1])
						f[i][1][0][l] += f[i-1][0][0][dig[i-1]];
					if (l < dig[i-1]) {
						f[i][1][1][l] += f[i-1][0][0][dig[i-1]];
						f[i][1][1][l] += f[i-1][0][1][dig[i-1]];
					}
					if (l == dig[i-1]) {
						f[i][1][0][l] += f[i-1][0][0][dig[i-1]];
						f[i][1][1][l] += f[i-1][0][1][dig[i-1]];
					}
				//	rgo(t, 0, l)
				//		f[i][1][0][l] += f[i-1][0][0][t];
				//	rgo(t, l, 9) {
				//		f[i][1][1][l] += f[i-1][0][1][t];
				//		f[i][1][1][l] += f[i-1][0][0][t];
				//	}
				}
				if (l == dig[i]) {
					if (l > dig[i-1])
						f[i][0][0][l] += f[i-1][0][0][dig[i-1]];
					if (l < dig[i-1]) {
						f[i][0][1][l] += f[i-1][0][0][dig[i-1]];
						f[i][0][1][l] += f[i-1][0][1][dig[i-1]];
					}
					if (l == dig[i-1]) {
						f[i][0][0][l] += f[i-1][0][0][dig[i-1]];
						f[i][0][1][l] += f[i-1][0][1][dig[i-1]];
					}
				}
			}
		}
		LL ans = 0;
		rep(i, 0, 2)
			rep(j, 0, 2)
				rep(k, 0, 10)
					ans += f[n][i][j][k];
		cout << ans-1 << endl;
	}


	return 0;
}
