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


int n;

char p[10][10];

vector<vector<int> > per[6];
map<vector<int>, int> see;
vector<int> t;

int calc(vector<int> s) {
	int r = 0, m = 0;
	foreach(i, s) {
		if ((*i) > m) {
			++r;
			m = (*i);
		}
	}
	return r;
}

vector<int> pl[10];

bool shw[6][6];

bool ok(int x) {
	//printf("%d\n", x);
	//foreach(i, t) {
	//	printf("%d ", *i);
	//}
	//puts("");
	foreach(i, per[x]) {
		bool ok = true;
		for (int j = 0; j < t.size(); ++j)
			if ((*i)[j] != t[j]) {
				ok = false;
				break;
			}
		if (ok) return true;
	}
	return false;
}

bool chk(int d) {
	if (p[d][n+1] != '-') {
		t = pl[d];
		reverse(t.begin(), t.end());
		if (see[t] != p[d][n+1]-'0')
			return false;
	}
	for (int i = 1; i <= n; ++i)
		if (p[d][i] != '-')
			if (pl[d][i-1] != p[d][i]-'0')
				return false;
	for (int i = 1; i <= n; ++i)
		if (shw[i][pl[d][i-1]])
			return false;
	for (int i = 1; i <= n; ++i)
		if (p[0][i] != '-') {
			t.clear();
			for (int j = 1; j <= d; ++j)
				t.pb(pl[j][i-1]);
			if (!ok(p[0][i]-'0')) return false;
		}
	if (d == n) {
		for (int i = 1; i <= n; ++i)
			if (p[n+1][i] != '-') {
				t.clear();
				for (int j = n; 0 < j; --j)
					t.pb(pl[j][i-1]);
				if (!ok(p[n+1][i]-'0')) return false;
			}
	}
	for (int i = 1; i <= n; ++i)
		shw[i][pl[d][i-1]] = true;
	return true;
}

bool dfs(int d) {
	if (d == n+1) {
		return true;
	}
	if (p[d][0] != '-') {
		int x = p[d][0] - '0';
		foreach(i, per[x]) {
			pl[d] = *i;
			if (chk(d)) {
				if (dfs(d+1))
					return true;
				for (int i = 1; i <= n; ++i)
					shw[i][pl[d][i-1]] = false;
			}
		}
	} else {
		for (int x = 1; x <= n; ++x) {
			foreach(i, per[x]) {
				pl[d] = *i;
				if (chk(d)) {
					if (dfs(d+1))
						return true;
					for (int i = 1; i <= n; ++i)
						shw[i][pl[d][i-1]] = false;
				}
			}
		}
	}
	return false;
}

int main() {
#ifdef lol
	freopen("k.in", "r", stdin);
	freopen("k.out", "w", stdout);
#endif

	int tCase = fr();
	while (tCase--) {
		n = fr();
		rgo(i, 0, n+1)
			rgo(j, 0, n+1)
			p[i][j] = gchar();
		t.clear();
		see.clear();
		for (int i = 1; i <= n; ++i)
			per[i].clear();
		rgo(i, 1, n) t.pb(i);
	//	int cnt = 0;
		do {
			per[see[t] = calc(t)].pb(t);
	//		for (int i = 0; i < n; ++i)
	//			printf("%d ", t[i]);
	//		puts("");
	//		printf("%d\n", calc(t));
	//		++cnt;
		} while (next_permutation(t.begin(), t.end()));
	//	for (int i = 1; i <= n; ++i) {
	//		printf("%d\n", i);
	//		foreach(j, per[i]) {
	//			for (int k = 0; k < n; ++k) {
	//				printf("%d ", (*j)[k]);
	//			}
	//			puts("");
	//		}
	//	}
	//	cout << cnt << endl;;
	//	for (int i = 1; i <= n; ++i)
	//		printf("%d ", per[i].size());
	//	puts("");
		memset(shw, 0, sizeof shw);
		if (!dfs(1)) {
			puts("no");
		} else {
			for (int i = 1; i <= n; ++i) {
				for (int j = 0; j < n; ++j)
					printf("%d", pl[i][j]);
				puts("");
			}
		}
		if (tCase != 0)
			puts("");
	}


	return 0;
}
