#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include <map>


using namespace std;
namespace my_useful_tools {
#define rep(_i, _k, _j) for(int _i = _k; _i <= _j; ++_i)
#define reu(_i, _k, _j) for(int _i = _k; _i <  _j; ++_i)
#define red(_i, _k, _j) for(int _i = _k; _j <= _i; --_i)
#define pb push_back
#define mp make_pair
#define ipir pair<int, int>
#define ivec vector<int>
#define clr(t) memset(t, 0, sizeof t)
#define pse(t, v) memset(t, v, sizeof t)
#define brl puts("")
#define file(x) freopen(#x".in", "r", stdin), freopen(#x".out", "w", stdout)
#define file_hza freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#define file_gen(x) freopen(#x".in", "w", stdout);
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
};
using namespace my_useful_tools;

struct TreeNode {
	string name;
	TreeNode* fa;
	int ans;
	void init() {
		fa = NULL;
		name = "";
		ans = 0;
	}
	bool operator < (const TreeNode&rhs) const {
		return ans > rhs.ans || (ans == rhs.ans && name < rhs.name);
	}
} pool[1111], *loc = pool, *root;

TreeNode*newNode() {
	loc->init();
	return loc++;
}

int n, d;

map<string, TreeNode*> posInTree;
vector<string> son[1111];
vector<string> names;
set<string> sn;

void upd(TreeNode*x, int p) {
	if (!x) return ;
	if (p == 0) {
		++x->ans;
		return ;
	}
	upd(x->fa, p-1);
}

int main() {
#ifdef love_lhy
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif

	int T = fr();
	rep(t, 1, T) {
		fr(n, d);
		posInTree.clear();
		loc = pool;
		names.clear();
		sn.clear();
		rep(i, 1, n)
			son[i].clear();
		rep(i, 1, n) {
			loc->init();
			cin >> loc->name;
			sn.insert(loc->name);
			posInTree[loc->name] = loc;
			names.pb(loc->name);
			loc++;
			int m = fr();
			string tmp;
			rep(j, 1, m) {
				cin >> tmp;
				son[i].pb(tmp);
				names.pb(tmp);
			}
		}
		sort(names.begin(), names.end());
		names.erase(unique(names.begin(), names.end()), names.end());
		for (vector<string>::iterator i = names.begin(); i != names.end(); ++i) {
			if (posInTree.find(*i) == posInTree.end()) {
				loc->init();
				loc->name = *i;
				posInTree[*i] = loc;
				loc++;
			}
		}
		
		rep(i, 1, n) {
			for (vector<string>::iterator j = son[i].begin(); j != son[i].end(); ++j) {
				posInTree[*j]->fa = (pool + i - 1);
			}
		}

		for (map<string, TreeNode*>::iterator j = posInTree.begin(); j != posInTree.end(); ++j) {
			upd(j->second, d);
		}
		sort(pool, loc);
		cout << "Tree " << t << ":\n";
		int cnt = 0, xx = 0;
		for (TreeNode*x = pool; x != loc; ++x) {
			if (x->ans != 0 && (cnt < 3 || (cnt >= 3 && x->ans == xx))) {
				cout << x->name << " " << x->ans << '\n';
				xx = x->ans;
				++cnt;
			}
		}
		cout << endl;
	}
 
	return 0;
}


