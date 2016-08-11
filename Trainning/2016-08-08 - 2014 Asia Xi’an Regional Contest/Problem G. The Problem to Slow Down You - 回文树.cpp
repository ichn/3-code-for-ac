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

struct eertree {
	static const int Alpha = 26;
	static const int Size = 200000 + 1000;
	struct node {
		int go[26];
		int suf;
		int len;
		int sw;
		int dep;
		void init(int s, int l) {
			suf = s, len = l;
			sw = 0;
			dep = 0;
			memset(go, 0, sizeof go);
		}
	} nd[Size];
	int r1, r2, lc, lst, suf, n, pos;
	char s[Size];

	void init() {
		lc = 2;
		suf = 2;
		r1 = 1;
		r2 = 2;
		nd[r1].init(r1, -1);
		nd[r2].init(r1, 0);
		nd[r1].dep = 0;
		nd[r2].dep = 1;
		lst = r2;
		pos = 0;
	}
	
	void append(int c) {
		while (pos - nd[lst].len - 1 < 0 || s[pos - nd[lst].len - 1] != s[pos])
			lst = nd[lst].suf;
		if (nd[lst].go[c]) {
			lst = nd[lst].go[c];
			++nd[lst].sw;
		} else {
			++lc;
			nd[lc].init(nd[lst].suf, nd[lst].len + 2);
			++nd[lc].sw;
			nd[lst].go[c] = lc;
			lst = lc;
			if (nd[lc].len == 1) {
				nd[lc].suf = 2;
				nd[lc].dep = nd[r2].dep + 1;
			} else {
				while (pos - nd[nd[lst].suf].len - 1 < 0 || s[pos - nd[nd[lst].suf].len - 1] != s[pos])
					nd[lst].suf = nd[nd[lst].suf].suf;
				nd[lst].suf = nd[nd[lst].suf].go[c];
				nd[lst].dep = nd[nd[lst].suf].dep + 1;
			}
		}
		++pos;
	}

	int cid[Size], res[Size];
	void build() {
		n = strlen(s);
		init();
		for (int i = 0; i < n; ++i) {
			append(s[i] - 'a');
		}
		memset(cid, 0, sizeof cid);
		for (int i = 0; i <= lc; ++i)
			++cid[nd[i].dep];
		for (int i = 1; i <= lc; ++i)
			cid[i] += cid[i-1];
		for (int i = 0; i <= lc; ++i)
			res[cid[nd[i].dep]--] = i;
		reverse(res + 1, res + lc + 2);
		for (int i = 1; i <= lc+1; ++i) {
			nd[nd[res[i]].suf].sw += nd[res[i]].sw;
		}
	}

	void print(int r, vector<char> ss) {
		if (ss.size() != 0) {
			printf("%d ", nd[r].sw);
			for (int i = 0; i < (int)ss.size(); ++i)
				putchar(ss[i]);
			puts("");
		}
		for (int i = 0; i < 26; ++i) {
			if (nd[r].go[i]) {
				vector<char> tmp = ss;
				if (r == 1)
					tmp.pb('a' + i);
				else {
					tmp.clear();
					tmp.pb('a' + i);
					for (int j = 0; j < (int)ss.size(); ++j)
						tmp.pb(ss[j]);
					tmp.pb('a' + i);
				}
				print(nd[r].go[i], tmp);
			}
		}
	}

	void print() {
		vector<char> t;
		t.clear();
		puts("len of 1,3,5...");
		print(1, t);
		puts("");
		puts("len of 2,4,6...");
		t.clear();
		print(2, t);
	}

} *e1, *e2;

LL ans;
void solve(int a, int b) {
	if (a > 2 && b > 2) {
		ans += 1LL * e1->nd[a].sw * e2->nd[b].sw;
	}
	for (int i = 0; i < 26; ++i)
		if (e1->nd[a].go[i] && e2->nd[b].go[i])
			solve(e1->nd[a].go[i], e2->nd[b].go[i]);
}

int main() {
#ifdef lol
	freopen("G.in", "r", stdin);
	freopen("G.out", "w", stdout);
#endif

	int T = fr();
	e1 = new eertree();
	e2 = new eertree();
	for (int tt = 1; tt <= T; ++tt) {
		scanf("%s\n%s\n", e1->s, e2->s);
		e1->build(), e2->build();
		ans = 0;
		//puts("e1");
		//e1->print();
		//puts("");
		//puts("e2");
		//e2->print();
		//puts("");
		solve(1, 1);
		solve(2, 2);
		printf("Case #%d: %lld\n", tt, ans);
		
	}
	return 0;
}

