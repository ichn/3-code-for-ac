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


typedef double DB;
map<string, int> Id;
int n, m, q;
int pos[70][3];

set<pair<int, int> > holes;

DB dis(int i, int j) {
	DB ret = 0;
	rep(k, 0, 3)
		ret += (DB)(pos[i][k] - pos[j][k]) * (pos[i][k] - pos[j][k]);
	return sqrt(ret);
}

DB d[70][70];

int rnd(DB a) {
	int b = ceil(a);
	int c = floor(a);
	if (b - a < a - c)
		return b;
	return c;
}
void solve(string a, string b) {
	DB ans = d[Id[a]][Id[b]];
	printf("The distance from %s to %s is %d parsecs.\n", a.c_str(), b.c_str(), rnd(ans));
}

int main() {
#ifdef lol
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif

	int tCase = fr();
	rgo(kase, 1, tCase) {
		n = fr();
		Id.clear();
		holes.clear();
		string name, name1;
		rgo(i, 1, n) {
			cin >> name;
			rep(j, 0, 3)
				pos[i][j] = fr();
			Id[name] = i;
		}
		m = fr();
		rgo(i, 1, m) {
			cin >> name >> name1;
			holes.insert(mp(Id[name], Id[name1]));
		}
		rgo(i, 1, n)
			rgo(j, 1, n)
				if (holes.find(mp(i, j)) != holes.end())
					d[i][j] = 0;
				else d[i][j] = dis(i, j);
	//	for (int i = 1; i <= n; ++i) {
	//		for (int j = 1; j <= n; ++j)
	//			printf("%f ", d[i][j]);
	//		puts("");
	//	}
	//	puts("");
		rgo(k, 1, n)
			rgo(i, 1, n)
				rgo(j, 1, n)
					d[i][j] = min(d[i][k] + d[k][j], d[i][j]);
		fr(q);
		printf("Case %d:\n", kase);
		rgo(i, 1, q) {
			cin >> name >> name1;
			solve(name, name1);
		}
	}

	return 0;
}
