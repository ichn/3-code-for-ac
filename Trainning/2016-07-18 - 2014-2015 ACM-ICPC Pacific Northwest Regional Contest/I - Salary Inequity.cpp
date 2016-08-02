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
	char gchar() {
		char r = gc();
		for(;r==' '||r=='\n'||r=='\r';
				r=gc());return r;}
	template<class T>  void fr(T&r) {
		char c=gc();
		for(;c<'0'||'9'<c;c=gc());
		for(r=0;'0'<=c&&c<='9';c=getchar())
			r=r*10+c-'0';
	}
	template<class T>  void fr(T&a,T&b) {
		fr(a), fr(b);
	}
	template<class T>  void fr(T&a,T&b,T&c) {
		fr(a), fr(b), fr(c);
	}
	int fr() {
		int r=0;char c=gc();
		for(;c<'0'||'9'<c;c=gc());
		for(r=0;'0'<=c&&c<='9';c=getchar())
			r=r*10+c-'0';
		return r;
	}

};
using namespace my_zone;



const int maxN = 1000000 + 100;

const int maxE = maxN<<1, maxV = maxN;
int e, h[maxV], to[maxE], nxt[maxE];
void init() {
	cls(h,-1);
	e=0;
}
void addEdge(int u,int v) {
	to[e] = v, nxt[e] = h[u], h[u] = e++;
	to[e] = u, nxt[e] = h[v], h[v] = e++;
}

int pre[maxN], post[maxN], clk;
int salary[maxN];

bool vis[maxN];
int pos[maxN];
void dfs(int u) {
	pre[u] = ++clk;
	vis[u] = true;
	pos[clk] = u;
	for (int i = h[u]; i != -1; i = nxt[i]) {
		if (!vis[to[i]])
			dfs(to[i]);
	}
	post[u] = clk;
}

int n, m;

int tag[maxN<<2], minVal[maxN<<2], maxVal[maxN<<2];


void buildTree(int l, int r, int rt) {
	tag[rt] = 0;
	if (l == r) {
		minVal[rt] = maxVal[rt] = salary[pos[l]];
	//	minVal[rt] = maxVal[rt] = salary[pre[l]];
		return ;
	}
	int mid = (l+r)>>1;
	buildTree(l, mid, rt<<1);
	buildTree(mid+1, r, rt<<1|1);

	minVal[rt] = min(minVal[rt<<1], minVal[rt<<1|1]);
	maxVal[rt] = max(maxVal[rt<<1], maxVal[rt<<1|1]);
}

void add(int ql, int qr, int val, int l, int r, int rt) {
	if (ql <= l && r <= qr) {
		minVal[rt] += val;
		maxVal[rt] += val;
		tag[rt] += val;
		return ;
	}

	minVal[rt<<1] += tag[rt];
	minVal[rt<<1|1] += tag[rt];
	maxVal[rt<<1] += tag[rt];
	maxVal[rt<<1|1] += tag[rt];
	tag[rt<<1] += tag[rt];
	tag[rt<<1|1] += tag[rt];

	tag[rt] = 0;

	int mid = (l+r)>>1;
	if (ql <= mid) add(ql, qr, val, l, mid, rt<<1);
	if (mid < qr) add(ql, qr, val, mid+1, r, rt<<1|1);

	minVal[rt] = min(minVal[rt<<1], minVal[rt<<1|1]);
	maxVal[rt] = max(maxVal[rt<<1], maxVal[rt<<1|1]);

}

int getMin(int ql, int qr, int l, int r, int rt) {
	if (ql <= l && r <= qr) {
		return minVal[rt];
	}

	minVal[rt<<1] += tag[rt];
	minVal[rt<<1|1] += tag[rt];
	maxVal[rt<<1] += tag[rt];
	maxVal[rt<<1|1] += tag[rt];
	tag[rt<<1] += tag[rt];
	tag[rt<<1|1] += tag[rt];

	tag[rt] = 0;

	int mid = (l+r)>>1;
	int ret = INT_MAX;
	if (ql <= mid) ret = min(ret, getMin(ql, qr, l, mid, rt<<1));
	if (mid < qr) ret = min(ret, getMin(ql, qr, mid+1, r, rt<<1|1));

	minVal[rt] = min(minVal[rt<<1], minVal[rt<<1|1]);
	maxVal[rt] = max(maxVal[rt<<1], maxVal[rt<<1|1]);

	return ret;
}

int getMax(int ql, int qr, int l, int r, int rt) {
	if (ql <= l && r <= qr) {
		return maxVal[rt];
	}

	minVal[rt<<1] += tag[rt];
	minVal[rt<<1|1] += tag[rt];
	maxVal[rt<<1] += tag[rt];
	maxVal[rt<<1|1] += tag[rt];
	tag[rt<<1] += tag[rt];
	tag[rt<<1|1] += tag[rt];

	tag[rt] = 0;

	int mid = (l+r)>>1;
	int ret = -INF;
	if (ql <= mid) ret = max(ret, getMax(ql, qr, l, mid, rt<<1));
	if (mid < qr) ret = max(ret, getMax(ql, qr, mid+1, r, rt<<1|1));

	minVal[rt] = min(minVal[rt<<1], minVal[rt<<1|1]);
	maxVal[rt] = max(maxVal[rt<<1], maxVal[rt<<1|1]);

	return ret;
}

int main() {
#ifdef lol
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif

	int tCase = fr();
	while (tCase--) {
		init();
		clr(tag);
		clr(minVal);
		clr(maxVal);
		clr(vis);
		fr(n);
		rgo(i, 2, n)
			addEdge(fr(), i);
		clk = 0;
		dfs(1);

		rgo(i, 1, n) fr(salary[i]);
		buildTree(1, n, 1);

		fr(m);
		int u, v;
		while (m--) {
			if (gchar() == 'Q') {
				fr(u);
				int a = getMax(pre[u], post[u], 1, n, 1);
				int b = getMin(pre[u], post[u], 1, n, 1);
				printf("%d\n", a - b);
			} else {
				fr(u, v);
				add(pre[u], post[u], v, 1, n, 1);
			}
		}
	}
	return 0;
}
