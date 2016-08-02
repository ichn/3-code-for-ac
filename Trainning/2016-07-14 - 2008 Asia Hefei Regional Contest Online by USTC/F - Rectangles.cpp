#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef double DB;

#define rep(i, j, k) for (int i = j; i < k; ++i)
#define rgo(i, j, k) for (int i = j; i <= k; ++i)

int n, m;

struct area {
	int x[2], y[2];
	int val;
	area() {val = 0;}
	area(int x0, int x1, int y0, int y1)
		{
		x[0] = (x0), x[1] = (x1), y[0] = (y0), y[1] = (y1) ;
			val = 0;
	}
	void read() {
		cin >> x[0] >> y[0] >> x[1] >> y[1];
	}
	bool in(area b) {
		return (x[0] <= b.x[0] && b.x[1] <= x[1]
		  &&y[0] <= b.y[0] && b.y[1] <= y[1]);
	}
	int size() {
		return (x[1]-x[0])*(y[1]-y[0]);
	}
} blk[21];

vector<int> x, y;
vector<area> ss;

int main() {
#ifdef lol
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);

	int tCase = 0;
	while (cin >> n >> m) {
		if (n == 0 && m == 0)
			break;
		++tCase;
		x.clear();
		y.clear();
		ss.clear();
		rep(i, 0, n) {
			blk[i].read();
			x.push_back(blk[i].x[0]);
			x.push_back(blk[i].x[1]);
			y.push_back(blk[i].y[0]);
			y.push_back(blk[i].y[1]);
		}
		sort(x.begin(), x.end());
		sort(y.begin(), y.end());
		x.erase(unique(x.begin(), x.end()), x.end());
		y.erase(unique(y.begin(), y.end()), y.end());
		for (int i = 1; i < x.size(); ++i)
			for (int j = 1; j < y.size(); ++j) {
				ss.push_back(area(x[i-1], x[i], y[j-1], y[j]));
			}
		for (int i = 0; i < ss.size(); ++i) {
			rep(j, 0, n)
				if (blk[j].in(ss[i]))
					ss[i].val|=(1<<j);
		}
		cout << "Case " << tCase << ":" << "\n";
		rep(i, 0, m) {
			int N;
			cin >> N;
			int t, s = 0;
			rep(j, 0, N) {
				cin >> t;
				--t;
				s |= 1<<t;
			}
			int ans = 0;
			for (int j = 0; j < ss.size(); ++j) {
				if ((ss[j].val & s) != 0) {
					ans += ss[j].size();
				}
			}
			cout << "Query " << i + 1 << ": " << ans << endl;
		}
		cout << endl;
	}

	return 0;
}
