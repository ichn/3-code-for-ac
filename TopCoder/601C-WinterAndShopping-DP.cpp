#include <bits/stdc++.h>
using namespace std;

class WinterAndShopping {

	static const int maxN = 111;
	static const int maxT = 551;
	static const int mod = 1e9 + 7;

	int n, ans, ed;

	int r[maxT], g[maxT], b[maxT], s[maxT], e[maxT], a[maxT];
	long long C[maxT][maxT];

	vector<int> tl[maxT];

	long long dp[maxT][maxN][maxN];

	int calc(int t, int R, int G) {
		long long &ret = dp[t][R][G];
		if (ret != -1)
			return ret;
		ret = 0;

		if (t == ed + 1) {
			ret = 1;
			return ret;
		}

		int w = (int)tl[t].size();

		if (w == 0)
			ret = calc(t + 1, 0, 0);
		else if (w == 1) {
			int i = tl[t][0];
			if (a[i] - (t - s[i]) == 1)
				ret = calc(t + 1, 0, 0);
			else {
				if (r[i] > R)
					ret += calc(t + 1, R + 1, G);
				if (g[i] > G)
					ret += calc(t + 1, R, G + 1);
				if (b[i] > t - s[i] - R - G)
					ret += calc(t + 1, R, G);
			}
		} else {
			int i = tl[t][0], j = tl[t][1];
			if (e[i] == e[j]) {
				if (r[i] - R == r[j] && g[i] - G == g[j] && b[i] - (t - s[i] - R - G) == b[j]) {
					ret = C[a[j]][r[j] + g[j]];
					ret = (ret * C[r[j] + g[j]][r[j]]) % mod;
					ret = (ret * calc(e[j] + 1, 0, 0)) % mod;
				}
			} else if (e[i] < e[j]) {
				if (r[i] - R <= r[j] && g[i] - G <= g[j] && b[i] - (t - s[i] - R - G) <= b[j]) {
					ret = C[a[i] - (t - s[i])][r[i] - R + g[i] - G];
					ret = (ret * C[r[i] - R + g[i] - G][r[i] - R]) % mod;
					ret = (ret * calc(e[i] + 1, r[i] - R, g[i] - G)) % mod;
				}
			} else {
				if (r[i] - R >= r[j] && g[i] - G >= g[j] && b[i] - (t - s[i] - R - G) >= b[j]) {
					ret = C[a[j]][r[j] + g[j]];
					ret = (ret * C[r[j] + g[j]][r[j]]) % mod;
					ret = (ret * calc(e[j] + 1, R + r[j], G + g[j])) % mod;
				}
			}
		}

		ret %= mod;
		return ret;
	}
public:

	int getNumber(vector<int> _f, vector<int> _r, vector<int> _g, vector<int> _b) {
		ed = 0;
		n = (int)_f.size();
		for (int i = 0; i < n; ++i) {
			r[i] = _r[i];
			g[i] = _g[i];
			b[i] = _b[i];
			a[i] = r[i] + g[i] + b[i];
			s[i] = _f[i];
			e[i] = s[i] + a[i] - 1;
			ed = max(ed, e[i]);
			for (int j = s[i]; j <= e[i]; ++j)
				tl[j].push_back(i);
		}
		for (int j = 0; j < maxT; ++j)
			if ((int)tl[j].size() == 2 && s[tl[j][0]] > s[tl[j][1]])
				swap(tl[j][0], tl[j][1]);

		memset(C, 0, sizeof C);
		C[0][0] = 1;
		C[1][1] = 1, C[1][0] = 1;
		for (int i = 2; i < maxT; ++i) {
			C[i][0] = 1;
			for (int j = 1; j <= i; ++j)
				(C[i][j] = C[i - 1][j] + C[i - 1][j - 1]) %= mod;
		}

		memset(dp, -1, sizeof dp);
		ans = calc(0, 0, 0);
		return ans;
	}


};

#ifdef love_lhy

/*
 * 题目大意：
 * 给出n个四元组$(f_i,r_i,g_i,b_i)$，表示从$f_i$天开始，编号为$i$的商店开始在连续的$r_i+g_i+b_i$天内每天出售一个球，每种颜色的球数分别刚好为$r_i,g_i,b_i$。
 * 数据保证每天至多只有两家店在出售球。
 * 求满足如果在有两家店出售球时出售球颜色相同的方案数对$10^9+7$取模的结果。
 * */


vector<int> f, r, g, b;
int main() {
	freopen("data.in", "r", stdin);
	freopen("data.out", "w", stdout);

	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		int t;
		scanf("%d", &t);
		f.push_back(t);
	}
	for (int i = 1; i <= n; ++i) {
		int t;
		scanf("%d", &t);
		r.push_back(t);
	}
	for (int i = 1; i <= n; ++i) {
		int t;
		scanf("%d", &t);
		g.push_back(t);
	}
	for (int i = 1; i <= n; ++i) {
		int t;
		scanf("%d", &t);
		b.push_back(t);
	}

	cout << (new WinterAndShopping)->getNumber(f, r, g, b) << endl;


}
#endif
