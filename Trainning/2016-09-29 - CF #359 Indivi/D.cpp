#include <bits/stdc++.h>
#define lst_pos vals
using namespace std;

const int maxN = 1e5 + 1;
const int maxK = 300 + 1;

int n, k;

struct point {
	int x, y;
	point() {
	}
	point(int x, int y):x(x), y(y) {
	}
	void read() {
		scanf("%d %d", &x, &y);
	}
	bool operator < (const point&rhs) const {
		return y < rhs.y || (y == rhs.y && x < rhs.x);
	}
} p[maxN];

struct event {
	int p, l, r, d;
	event() {}
	event(int p, int l, int r, int d):p(p), l(l), r(r), d(d) {}
	bool operator < (const event&rhs) const {
		return p < rhs.p || (p == rhs.p && (d < rhs.d || (d == rhs.d && l < rhs.l)));
	}
} e[maxN*2];

vector<int> vals;
int inj(int a) {
	return lower_bound(vals.begin(), vals.end(), a) - vals.begin();
}

vector<int> val;
long long ans[maxN];

int main() {
#ifdef love_lwd
	freopen("D.in", "r", stdin);
	freopen("D.out", "w", stdout);
#endif

	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		p[i].read();
	}
	sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; ++i) {
		int st;
		if (vals.empty()) {
			st = p[i].y - k + 1;
		} else {
			st = max(vals.back() + 1, p[i].y - k + 1);
		}
		for (int j = st; j <= p[i].y; ++j)
			vals.push_back(j);
	}

	

	int N = n << 1;
	for (int i = 1; i <= n; ++i) {
		e[(i<<1)-1] = event(p[i].x - k + 1, inj(p[i].y - k + 1), inj(p[i].y), 1);
		e[i<<1] = event(p[i].x + 1, inj(p[i].y - k + 1), inj(p[i].y), -1);
	}
	sort(e + 1, e + N + 1);


	int sz = vals.size() + 3;
	val.resize(sz);
	for (auto & i : lst_pos)
		i = INT_MIN;

	for (int i = 1, j; i <= N; i = j) {
		j = i;
		while (j <= N && e[j].p == e[i].p) {
			for (int c = e[j].l; c <= e[j].r; ++c) {
				if (lst_pos[c] != INT_MIN) {
					ans[val[c]] += e[j].p - lst_pos[c];
				}
				lst_pos[c] = e[j].p;
				val[c] += e[j].d;
			}
			++j;
		}
	}

	cout << ans[1];
	for (int i = 2; i <= n; ++i)
		cout << ' ' << ans[i];
	puts("");

	return 0;
}


