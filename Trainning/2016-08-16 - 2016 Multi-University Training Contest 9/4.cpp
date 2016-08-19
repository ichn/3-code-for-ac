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

int n, m;
vector<int> N;
vector<int> ans, has;
set<int> got;

bool chk(int t) {
	if (got.find(t) != got.end()) return false;
	has.clear();
	has.pb(t);
	for (int i = ans.size()-1; 0 <= i; --i) {
		t += ans[i];
		if (got.find(t) != got.end()) return false;
		has.pb(t);
	}
	for (int i = 0 ; i < (int)has.size(); ++i)
		got.insert(has[i]);
	return true;
}


bool get(int _n) {
	n = _n;
	ans.clear();
	N.clear();
	got.clear();
	m = 3 * (n + 6) - 1;
	for (int i = 1; i <= m; ++i)
		N.pb(i);
	random_shuffle(N.begin(), N.end());
	ans.pb(1);
	got.insert(1);
	for (int i = 2; i <= n; ++i) {
		for (int j = 0; j < m; ++j)
			if (chk(N[j])) {
				ans.pb(N[j]);
				break;
			}
		if ((int)ans.size() != i) return false;
	}
	return true;
}

int main() {
#ifdef lol
	freopen("4.in", "r", stdin);
	freopen("4.out", "w", stdout);
#endif

	srand((int)time(NULL));
	int j = 2000;
		while (!get(j));
		for (int i = 0; i < j; ++i)
			printf("%d ", ans[i]);
		puts("");
	return 0;
	int T = fr();
	while (T--) {
		int _n = fr();
		get(_n);
		for (int i = 0; i < _n; ++i)
			printf("%d ", ans[i]);
		puts("");
	}
 
	return 0;
}

