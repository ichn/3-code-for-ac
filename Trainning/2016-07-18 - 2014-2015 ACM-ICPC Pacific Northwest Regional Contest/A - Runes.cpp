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

string equ, a, b, c, ope;
int n;

bool ok;
LL to_LL(string s) {
	LL t = s.length();
	LL ret = 0;
	if (s[0] == '0') {
		if (t == 1) {
			return 0;
		} else {
			ok = false;
			return 0;
		}
	}
	if (s[0] == '-') {
		if (s[1] == '0') {
			ok = false;
			return 0;
		} else {
			for (int i = 1; i < t; ++i)
				ret = ret * 10 + s[i] - '0';
			return -ret;
		}
	}
	for (int i = 0; i < t; ++i)
		ret = ret * 10 + s[i] - '0';
	return ret;
}

int show[10];

bool chk(int t) {
	if (show[t]) return false;
	string x = a, y = b, z = c;
	for (int i = 0; i < (int)a.length(); ++i)
		if (a[i] == '?') a[i] = '0'+t;
	for (int i = 0; i < (int)b.length(); ++i)
		if (b[i] == '?') b[i] = '0'+t;
	for (int i = 0; i < (int)c.length(); ++i)
		if (c[i] == '?') c[i] = '0'+t;
	ok = true;
	LL i = to_LL(a), j = to_LL(b), k = to_LL(c);
	a = x, b = y, c = z;
	if (!ok) {
		return false;
	}
	if (ope[0] == '*')
		return i * j == k;
	else if (ope[0] == '-')
		return i - j == k;
	else return i + j == k;
}

int main() {
#ifdef lol
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif

	int tCase = fr();
	while (tCase--) {
		cin >> equ;
		n = equ.length();
		clr(show);
		for (int i = 0; i < n; ++i)
			if ('0' <= equ[i] && equ[i] <= '9')
				show[equ[i] - '0'] = true;
		int j = 0;
		while (j < n) {
			if (equ[j] == '*' || equ[j] == '+' ||  equ[j] == '=' || (equ[j] == '-' && j != 0))
				break;
			++j;
		}
		a = equ.substr(0, j);
		ope = equ[j];
		int k = j+1;
		++j;
		while (j < n) {
			if (equ[j] == '*' || equ[j] == '+' || equ[j] == '=' || (equ[j] == '-' && j != k))
				break;
			++j;
		}
		b = equ.substr(k, j-k);
		c = equ.substr(j+1, n-j-1);
		//cout << a << ' ' << ope << ' '<< b <<' ' << c<<endl;
		bool mrk = false;
		rep(i, 0, 10)
			if (chk(i)) {
				printf("%d\n", i);
				mrk = true;
				break;
			}
		if (!mrk) {
			puts("-1");
		}
	}
		

	return 0;
}
