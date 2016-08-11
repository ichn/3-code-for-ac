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

const int maxN = 1001;
int a[maxN], id[maxN];
bool cmp(int x, int y) {
	return a[x] < a[y];
}

#define x first
#define y second
vector<int> g[maxN];
int n;
int inq[maxN], cnt, ind[maxN], ind2[maxN];
queue<int> que;

bool solve() {
	for (int i = 1; i <= n; ++i)
		g[i].clear();
	memset(ind, 0, sizeof ind);
	for (int i = 1; i <= n; ++i) {
		int p = id[i];
		memset(inq, 0, sizeof inq);
		while (!que.empty()) que.pop();
		for (int j = 1; j < i; ++j) {
			if (ind[id[j]] == 0) que.push(id[j]);
			inq[id[j]] = 1;
		}
		memcpy(ind2, ind, sizeof ind);
		int c = i - 1;
		if (c < a[p]) return false;
		while (c > a[p]) {
			if (que.empty())
				return false;
			int u = que.front();
			que.pop();
			inq[u] = false;
			--c;
			for (int j = 0; j < (int)g[u].size(); ++j) {
				int q = g[u][j];
				--ind2[q];
				if (ind2[q] == 0) {
					que.push(q);
				}
			}
		}
		for (int j = 1; j <= n; ++j)
			if (inq[j]) g[p].push_back(j), ++ind[j];
	}
	return true;
}

int main() {
#ifdef lol
	freopen("1005.in", "r", stdin);
	freopen("1005.out", "w", stdout);
#endif

	int T = fr();
	for (int tt = 1; tt <= T; ++tt) {
		fr(n);
		for (int i = 1; i <= n; ++i)
			fr(a[i]), id[i] = i;
		sort(id + 1, id + n + 1, cmp);
		printf("Case #%d: ", tt);
		if (!solve()) {
			puts("No");
		} else {
			puts("Yes");
			int m = 0;
			for (int i = 1; i <= n; ++i)
				m += g[i].size();
			printf("%d\n", m);
			for (int i = 1; i <= n; ++i)
				for (int j = 0; j < (int)g[i].size(); ++j)
					printf("%d %d\n", i, g[i][j]);
		}
	}
	return 0;
}

