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

const int maxV = 105;
int n, m, m1, m2;
int a[maxV], b[maxV], c[maxV];

int g[maxV][maxV];
int lk[maxV], vis[maxV];
int mk;
bool del[maxV];

bool dfs(int u) {
	rgo(v, 1, n) if (!del[v] && g[u][v] && vis[v] != mk) {
		vis[v] = mk;
		if (lk[v] == -1 || dfs(lk[v])) {
			lk[v] = u;
			return true;
		}
	}
	return false;
}

int minVal[maxV], maxVal[maxV];

bool ok(int pos) {
	clr(vis);
	cls(lk, -1);
	rgo(i, pos+1, n) {
		mk = i;
		if (!dfs(i))
			return false;
	}
	return true;
}

void solve() {
	clr(g);
	m = m1 + m2;

	cls(minVal, 0);
	cls(maxVal, INF);
	rgo(i, 1, m1) {
		fr(a[i], b[i], c[i]);
		rgo(j, a[i], b[i])
			minVal[j] = max(minVal[j], c[i]);
	}
	rgo(i, m1+1, m) {
		fr(a[i], b[i], c[i]);
		rgo(j, a[i], b[i])
			maxVal[j] = min(maxVal[j], c[i]);
	}
	rgo(i, 1, n) {
		if (minVal[i] == 0) minVal[i] = 1;
		if (maxVal[i] == INF) maxVal[i] = n;
		rgo(j, minVal[i], maxVal[i])
			g[i][j] = 1;
	}
	rgo(i, 1, m) {
		rgo(j, 1, a[i]-1) g[j][c[i]] = 0;
		rgo(j, b[i]+1, n) g[j][c[i]] = 0;
	}
	/*
	rgo(i, 1, n) {
		rgo(j, 1, n) {
			printf("%d ", g[i][j]);
		} puts("");
	}
	*/

	clr(vis);
	cls(lk, -1);
	clr(del);

	rgo(i, 1, n) {
		mk = i;
		if (!dfs(i)) {
			puts("-1");
			return ;
		}
	}

	clr(del);
	rgo(i, 1, n) {
		rgo(j, 1, n) if (!del[j] && g[i][j]) {
			del[j] = true;
			if (ok(i)) {
				printf("%d%c", j, " \n"[i==n]);
				break;
			}
			del[j] = false;
		}
	}

}

int main() {
#ifdef lol
	freopen("h.in", "r", stdin);
	freopen("h.out", "w", stdout);
#endif

	while (scanf("%d %d %d", &n, &m1, &m2) != EOF) {

		solve();
	}
}
