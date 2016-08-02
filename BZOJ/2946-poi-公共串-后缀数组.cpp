#include <bits/stdc++.h>
using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define Edges(_i, _u, _e) for(int _i = _e.head[_u]; _i != -1; _i = _e.next[_i])
#define foreach(_i, _s) for(typeof(_s.begin()) _i = _s.begin(); _i != _s.end(); ++_i)
#define pb push_back
#define mp make_pair
#define ipir pair<int, int>
#define ivec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
	const int INF = 0x3f3f3f3f;
	typedef long long LL;
	typedef double DB;
	inline void pc(char c) { putchar(c); }
	template<class T> inline T gcd(T a, T b) { return b == 0 ? a : gcd(b, a % b); }
	template<class T> inline void W(T p) { if(p < 0) pc('-'), p = -p; if(p / 10 != 0) W(p / 10); pc('0' + p % 10); }
	template<class T> inline void Wn(T p) { W(p), brl; } template<class T> inline void W(T a, T b) { W(a), pc(' '), W(b); }
	template<class T> inline void Wn(T a, T b) { W(a), pc(' '), Wn(b); }
	template<class T> inline void W(T a, T b, T c) { W(a), pc(' '), W(b), pc(' '), W(c); } 
	inline char gchar() { char ret = getchar(); for(; ret == '\n' || ret == '\r' || ret == ' '; ret = getchar()); return ret; }
	template<class T> inline void fr(T&ret) { char c = ' '; int flag = 1; for(c = getchar(); c != '-' && !('0' <= c && c <= '9'); c = getchar()); 
		if(c == '-') flag = -1, ret = 0; else ret = c - '0'; for(c = getchar(); '0' <= c && c <= '9'; c = getchar()) ret = ret * 10 + c - '0';
		ret = ret * flag;
	}
	inline int fr() { int x; fr(x); return x; }
	template<class T> inline void fr(T&a, T&b) { fr(a), fr(b); } template<class T> inline void fr(T&a, T&b, T&c) { fr(a), fr(b), fr(c); }
	template<class T> inline T fast_pow(T base, T index, T mod = 2147483647, T ret = 1) {
		for(; index; index >>= 1, base = base * base % mod) if(index & 1) ret = ret * base % mod;
		return ret;
	}
	const int maxv = 100, maxe = 100;
	struct Edge {
		int edge, head[maxv], to[maxe], next[maxe];
		Edge() { edge = 0; memset(head, -1, sizeof head); }
		void addedge(int u, int v) {
			to[edge] = v, next[edge] = head[u];
			head[u] = edge++;
		}
	};
};
using namespace my_useful_tools;

struct SuffixArray {
	static const int maxl = 5*2000 + 100;
	static const int maxm = 256;
	typedef int _arr[maxl];
	int n, m;
	_arr str, rank, sa, height, tmp1, tmp2, sum;
	int *x, *y;

	void construct() {
		x=tmp1, y=tmp2;
		for (int i=0; i<m; ++i)
			sum[i] = 0;
		for (int i=0; i<n; ++i)
			++sum[x[i]=str[i]];
		for (int i=1; i<m; ++i)
			sum[i] += sum[i-1];
		for (int i=n-1; 0<=i; --i)
			sa[--sum[x[i]]] = i;
		for (int k=1; k<=n; k<<=1) {
			int p = 0;
			for (int i=n-k; i<n; ++i)
				y[p++] = i;
			for (int i=0; i<n; ++i)
				if (sa[i]>=k)
					y[p++] = sa[i]-k;
			for (int i=0; i<m; ++i)
				sum[i] = 0;
			for (int i=0; i<n; ++i)
				++sum[x[y[i]]];
			for (int i=1; i<m; ++i)
				sum[i] += sum[i-1];
			for (int i=n-1; 0<=i; --i)
				sa[--sum[x[y[i]]]] = y[i];
			swap(x, y);
			p=1, x[sa[0]]=0;
			for (int i=1; i<n; ++i)
				x[sa[i]] = y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+k]==y[sa[i]+k]?p-1:p++;
			if (p >= n) break;
			m = p;
		}

		for (int i=0; i<n; ++i)
			rank[sa[i]] = i;
		for (int i=0, k=0, j; i<n; ++i) {
			if (0 < k) --k;
			if (0 <= rank[i]-1) {
				j = sa[rank[i]-1];
				while (str[i+k] == str[j+k])
					++k;
			}
			height[rank[i]] = k;
		}
	}
	
};


class Solution {

	static const int maxl = 2000 + 100;
	char str[maxl];
	int blg[SuffixArray::maxl];
	int n, vis[7];

	SuffixArray sa;
	
	bool check(int l) {
		for (int i=1, j, k; i<sa.n; ++i)
			if (sa.height[i] >= l) {
				for (j=i; j<sa.n && sa.height[j]>=l; ++j);
				memset(vis, 0, sizeof vis);
				for (k=i-1; k<j; ++k)
					++vis[blg[sa.sa[k]]];
				for (k=0; k<n && 0<vis[k]; ++k);
				if (k==n) return true;
				i = j-1;
			}
		return false;
	}

	public:
	void solve() {
		fr(n);
		sa.n = 0;
		int mnl = INF;
		reu(i, 0, n) {
			scanf("%s", str);
			int l = strlen(str);
			mnl = min(mnl, l);
			for (int j=0; j<l; ++j) {
				blg[sa.n] = i;
				sa.str[sa.n++] = str[j]-'a'+1;
			}
			if (i < n-1) {
				blg[sa.n] = n;
				sa.str[sa.n++] = 27+i;
			}
		}
		sa.m = 27+n;
		sa.construct();
		int l=0, r=mnl;
		while (l+1 < r) {
			int mid = (l+r)>>1;
			if (check(mid))
				l = mid;
			else r = mid-1;
		}
		if (check(r)) l = r;
		printf("%d\n", l);
	}
} sol;

int main() {
#ifdef love_lhy
	file(2946);
#endif

	sol.solve();

	return 0;
}
