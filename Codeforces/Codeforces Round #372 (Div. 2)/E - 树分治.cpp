#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
typedef long long LL;

namespace t_dac {

	const int maxV = 100000 + 100;
	const int maxE = maxV * 2;

	int d, t;
	bool vis[maxV];

	LL ans;

	int h[maxV], to[maxE], nxt[maxE], wei[maxE], e;
	void addEdge(int u, int v, int c) {
		nxt[e] = h[u], to[e] = v, wei[e] = c, h[u] = e++;
		nxt[e] = h[v], to[e] = u, wei[e] = c, h[v] = e++;
	}

	void init() {
		memset(h, -1, sizeof h);
		e = 0;
		memset(vis, false, sizeof vis);

		ans = 0;

	}
	int get_s(int u, int f) {
		int r = 1;
		for (int i = h[u]; i != -1; i = nxt[i]) {
			int v = to[i];
			if (!vis[v] && v != f)
				r += get_s(v, u);
		}
		return r;
	}
	int get_d(int u, int f, int s) {
		int r = 1, mx = 0, w;
		for (int i = h[u]; i != -1; i = nxt[i]) {
			int v = to[i];
			if (!vis[v] && v != f) {
				r += (w = get_d(v, u, s));
				mx = max(mx, w);
			}
		}
		mx = max(mx, s - r);
		if (mx < t) {
			t = mx;
			d = u;
		}
		return r;
	}

	void calc(int u);

	void dfs(int u) {


		int s = get_s(u, -1);
		t = INF, d = u;
		get_d(u, -1, s);
		//fprintf(stderr, "%d %d\n", u, d);
		calc(d);

		vis[d] = 1;
		for (int i = h[d]; i != -1; i = nxt[i]) {
			int v = to[i];
			if (!vis[v])
				dfs(v);
		}
	}

	void solve() {
		dfs(1);
	}

};

typedef long long LL;
vector<int> fac;

int n, m, phi_m, rev[t_dac::maxV], pw10[t_dac::maxV];

vector<pair<int, int> > ot;
map<int, int> cnt;
vector<int> vals;


void doit(int u, int c1, int c2, int d, int f) {
	//printf("%d %d %d %d %d\n", u, c1, c2, d, f);
	for (int i = t_dac::h[u]; i != -1; i = t_dac::nxt[i]) {
		int v = t_dac::to[i];
		if (v == f) continue;

		int d1 = (c1 + (1LL * t_dac::wei[i] * pw10[d]) % m) % m;
		int d2 = (c2 * 10LL % m + t_dac::wei[i]) % m;
		vals.push_back(d1);

		int tVal = 1LL * (m - d2) * rev[d+1] % m;
		//printf("%d %d\n", d2, tVal);

		t_dac::ans += cnt[tVal];
		if (!t_dac::vis[v])
			doit(v, (c1 + (1LL * t_dac::wei[i] * pw10[d]) % m) % m, (c2 * 10LL % m + t_dac::wei[i]) % m, d+1, u);
	}
	//printf("%lld\n", t_dac::ans);
}

void t_dac::calc(int u) {
	cnt.clear();
	ot.clear();

	for (int i = t_dac::h[u]; i != -1; i = t_dac::nxt[i]) {
		int v = t_dac::to[i];
		ot.push_back({v, wei[i] % m});
		vals.clear();
		vals.push_back(wei[i] % m);
		t_dac::ans += cnt[1LL * (m - (wei[i] % m)) * rev[1] % m];
		if (!t_dac::vis[v]) {
			doit(v, t_dac::wei[i] % m, t_dac::wei[i] % m, 1, u);
		}
		for (auto j : vals) {
			++cnt[j];
			//printf("%d ", j);
		}
		//puts("");
	}
	//for (auto j : vals) {
	//	printf("%d\n", j);
	//}
	//puts("");
    //
	//printf("%d %lld\n", u, t_dac::ans);
	//exit(0);

	reverse(ot.begin(), ot.end());
	cnt.clear();
	for (auto i : ot) {
		int v = i.first, c = i.second;
		if (c % m == 0) {
			t_dac::ans++;
		}
		vals.clear();
		vals.push_back(c % m);
		t_dac::ans += cnt[1LL * (m - (c % m)) * rev[1] % m];
		if (!t_dac::vis[v]) {
			doit(v, c % m, c % m, 1, u);
		}
		for (auto j : vals) {
			++cnt[j];
			//printf("%d ", j);
		}
		//puts("");	
	}
	//printf("%d %lld\n", u, t_dac::ans);
	//exit(0);
}

LL fpw(LL a, LL b, LL m) {
	LL r = 1;
	for (; b; b>>=1, a=a*a%m)
		if (b&1) r = r*a%m;
	return r;
}

int main() {
#ifdef love_yxl
	freopen("E.in", "r", stdin);
	freopen("E.out", "w", stdout);
#endif

	scanf("%d %d", &n, &m);

	int t =  m;
	for (int i = 2, j = (int)sqrt(0.1 + m) + 1; i <= j; ++i)
		while (t % i == 0) {
			fac.push_back(i);
			t /= i;
		}
	if (t != 1) fac.push_back(t);
	phi_m = m;
	fac.erase(unique(fac.begin(), fac.end()), fac.end());

	for (auto i : fac) {
		phi_m /= i;
		phi_m *= (i - 1);
	}

	pw10[0] = 1;
	for (int i = 1; i <= n; ++i)
		pw10[i] = pw10[i-1] * 10LL % m;
	for (int i = 1; i <= n; ++i)
		rev[i] = fpw(pw10[i], phi_m-1, m);

	t_dac::init();

	for (int i = 1; i < n; ++i) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		++u, ++v;
		t_dac::addEdge(u, v, w);
	}

	t_dac::solve();

	cout << t_dac::ans << endl;

	return 0;
}

